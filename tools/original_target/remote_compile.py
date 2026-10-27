#!/usr/bin/env python3
"""Optional remote VC6 compile backend: a Windows host reached over ssh.

Opt in with RA2_REMOTE_COMPILE (or the config key "remote_compile"):

    ssh://USER@HOST[:PORT]/C:/ra2/remote?identity=~/.ssh/KEY&jobs=6&compiler=C:/ra2/remote/toolchain

The job stages the compile units' sources and every non-.cpp file under src/
into ROOT\\<job> with the same repository-relative layout as the local tree,
checks the remote compiler files against manifests/toolchain.json, runs the
identical compiler command lines in `jobs` concurrent below-normal-priority
cmd sessions, then streams back only each unit's object, log and exit code
into their local places and deletes the job folder. Units compile from their
own directory with a relative source name, so the only path VC6 records in an
object (the .file symbol) is identical on both hosts. Anything that prevents
a complete remote run (host unreachable, ssh or tar failure, toolchain drift,
missing outputs) raises Unavailable; the caller then compiles locally.
RA2_REMOTE_COMPILE=off disables a configured backend; RA2_REMOTE_KEEP=1
keeps the remote job folder for inspection.
"""
import io
import os
from pathlib import Path, PureWindowsPath
import subprocess
import tarfile
import threading
import time
from urllib.parse import parse_qs, unquote, urlsplit

MAX_JOBS = 12
COMPILER_FILES = ('CL.EXE', 'C1.DLL', 'C1XX.DLL', 'C2.DLL', 'MSPDB60.DLL')


class Unavailable(Exception):
    """The remote host could not complete the job; compile locally instead."""


def settings(config):
    value = os.environ.get('RA2_REMOTE_COMPILE', config.get('remote_compile'))
    if not value or str(value).strip().lower() in ('0', 'off', 'no', 'false', 'local'):
        return None
    if isinstance(value, dict):
        spec = dict(value)
    else:
        parts = urlsplit(str(value))
        if parts.scheme != 'ssh' or not parts.hostname:
            raise SystemExit('RA2_REMOTE_COMPILE must be ssh://user@host/C:/root?...')
        spec = {k: v[-1] for k, v in parse_qs(parts.query).items()}
        spec.update(host=parts.hostname, user=parts.username, port=parts.port,
                    root=unquote(parts.path).lstrip('/') or spec.get('root'))
    spec.setdefault('root', 'C:/ra2/remote')
    spec.setdefault('compiler', spec['root'].rstrip('/\\') + '/toolchain')
    spec['jobs'] = max(1, min(int(spec.get('jobs', 6)), MAX_JOBS))
    spec['lock'] = spec.get('lock') or str(Path(config['lock']).with_name('remote-compile.lock'))
    return spec


def ssh_command(spec, remote, connect_timeout=5):
    command = ['ssh', '-o', 'BatchMode=yes', '-o', 'ConnectTimeout=%d' % connect_timeout,
               '-o', 'ServerAliveInterval=15', '-o', 'ServerAliveCountMax=4']
    if spec.get('identity'):
        command += ['-i', os.path.expanduser(spec['identity'])]
    if spec.get('port'):
        command += ['-p', str(spec['port'])]
    return command + [('%s@%s' % (spec['user'], spec['host'])) if spec.get('user') else spec['host'], remote]


def ssh(spec, remote, data=None, timeout=120):
    try:
        result = subprocess.run(ssh_command(spec, remote), input=data, capture_output=True, timeout=timeout)
    except (OSError, subprocess.TimeoutExpired) as error:
        raise Unavailable('ssh: %s' % error)
    if result.returncode:
        raise Unavailable('ssh exit %d: %s' % (result.returncode, result.stderr.decode(errors='replace').strip()[-300:]))
    return result.stdout


def absolute(path):
    # Not resolved: a linked folder inside the tree (check_plans links
    # build/class-work) is staged at its in-tree path.
    return Path(os.path.abspath(path))


def windows(root, relative):
    return str(PureWindowsPath(root, *Path(relative).parts))


def check(text):
    if any(c in text for c in '\r\n"%!&|<>^'):
        raise Unavailable('unsupported remote path: ' + text)
    return text


def shard_script(lines, temporary):
    return ('\r\n'.join(['@echo off', 'set CL=', 'set _CL_=', 'set LINK=', 'set INCLUDE=', 'set LIB=',
                         'if not exist "%s" mkdir "%s"' % (temporary, temporary),
                         'set "TMP=%s"' % temporary, 'set "TEMP=%s"' % temporary] + lines +
                        ['exit /b 0']) + '\r\n').encode()


def run(spec, repository, directory, units, name, expected_compiler, render, timeout=3600):
    """Compile `units` remotely; write their outputs locally or raise Unavailable.

    `render(unit, path, include, compiler)` returns the unit's cmd lines, with
    `path` spelling a local path on the remote host, `include` the remote src/
    and `compiler` the remote CL.EXE. Units are dealt round-robin to shards.
    """
    import fcntl
    repository = Path(repository).resolve()
    directory = absolute(directory)
    try:
        relative_directory = directory.relative_to(repository)
    except ValueError:
        raise Unavailable('output is outside the repository')
    job = '%s-%d-%d' % (name, os.getpid(), time.time_ns() % 10**12)
    root = check(windows(spec['root'], Path(job)))
    compiler = check(str(PureWindowsPath(spec['compiler'])))
    if ' ' in root + compiler + str(relative_directory):
        # These appear unquoted in the job's own commands.
        raise Unavailable('remote root, compiler or output path contains a space')

    def remote(path):
        path = absolute(path)
        try:
            return check(windows(root, path.relative_to(repository)))
        except ValueError:
            raise Unavailable('path outside the repository: %s' % path)

    started = time.monotonic()
    count = min(spec['jobs'], len(units))
    shards = [[] for _ in range(count)]
    members = {}
    for index, unit in enumerate(units):
        shards[index % count] += render(unit, remote, windows(root, 'src'), str(PureWindowsPath(compiler, 'CL.EXE')))
        members[absolute(unit['source'])] = None
        for key in ('cwd', 'obj', 'log', 'returncode'):
            members.setdefault((absolute(unit[key]) if key == 'cwd' else absolute(unit[key]).parent), 'dir')
    # Stage: every non-.cpp file under src/ (the include closure), each unit
    # source, every working/output directory and the shard scripts.
    buffer = io.BytesIO()
    with tarfile.open(fileobj=buffer, mode='w', format=tarfile.GNU_FORMAT) as archive:
        def add_bytes(arcname, data):
            info = tarfile.TarInfo(arcname); info.size = len(data); info.mtime = int(time.time())
            archive.addfile(info, io.BytesIO(data))
        def add_dir(arcname):
            info = tarfile.TarInfo(arcname); info.type = tarfile.DIRTYPE; info.mode = 0o755
            archive.addfile(info)
        for path in sorted((repository/'src').rglob('*')):
            if path.is_file() and path.suffix.lower() != '.cpp':
                add_bytes(path.relative_to(repository).as_posix(), path.read_bytes())
        for path, kind in members.items():
            try:
                arcname = path.relative_to(repository).as_posix()
            except ValueError:
                raise Unavailable('path outside the repository: %s' % path)
            if kind == 'dir':
                add_dir(arcname)
            else:
                add_bytes(arcname, path.read_bytes())
        for index, lines in enumerate(shards):
            add_bytes('shard-%d.cmd' % index, shard_script(lines, '%s\\tmp-%d' % (root, index)))
    staged = buffer.getvalue()
    expected = [expected_compiler[n] for n in COMPILER_FILES]
    hashes = ' & '.join('certutil -hashfile "%s" SHA256' % PureWindowsPath(compiler, n) for n in COMPILER_FILES)
    lock_path = Path(spec['lock'])
    with lock_path.open('a+') as lock:
        before = time.monotonic()
        fcntl.flock(lock, fcntl.LOCK_EX)
        waited = time.monotonic() - before
        stage_started = time.monotonic()
        output = ssh(spec, 'cmd /d /c "mkdir %s && tar -xf - -C %s && (%s)"' % (root, root, hashes), staged)
        actual = [line.strip().replace(' ', '').lower() for line in output.decode(errors='replace').splitlines()
                  if len(line.strip().replace(' ', '')) == 64]
        if actual != expected:
            cleanup(spec, root)
            raise Unavailable('remote compiler differs from manifests/toolchain.json: %s' % actual)
        stage_seconds = time.monotonic() - stage_started
        run_started = time.monotonic()
        sessions = [None] * count; errors = []
        def session(index):
            begun = time.monotonic()
            try:
                ssh(spec, 'cmd /d /c start "" /belownormal /b /wait cmd /d /c %s\\shard-%d.cmd' % (root, index),
                    timeout=timeout)
            except Unavailable as error:
                errors.append(str(error))
            sessions[index] = time.monotonic() - begun
        threads = [threading.Thread(target=session, args=(i,)) for i in range(count)]
        for thread in threads: thread.start()
        for thread in threads: thread.join()
        run_seconds = time.monotonic() - run_started
        if errors:
            stop(spec, job); cleanup(spec, root)
            raise Unavailable('remote session failed: %s' % errors[0])
        fetch_started = time.monotonic()
        keep = os.environ.get('RA2_REMOTE_KEEP') == '1'
        fetch = ('cmd /d /c "tar -cf - --exclude *.cpp --exclude *.hpp -C %s %s%s"' %
                 (root, check(str(PureWindowsPath(*relative_directory.parts))),
                  '' if keep else ' && cd /d %s && rmdir /s /q %s' % (check(str(PureWindowsPath(spec['root']))), job)))
        returned = ssh(spec, fetch, timeout=600)
        fetch_seconds = time.monotonic() - fetch_started
    wanted = {}
    for unit in units:
        for key in ('obj', 'log', 'returncode'):
            path = absolute(unit[key])
            wanted[path.relative_to(repository).as_posix()] = path
    found = {}
    try:
        with tarfile.open(fileobj=io.BytesIO(returned), mode='r:') as archive:
            for member in archive:
                name_ = member.name[2:] if member.name.startswith('./') else member.name
                if member.isfile() and name_ in wanted:
                    found[wanted[name_]] = archive.extractfile(member).read()
    except tarfile.TarError as error:
        raise Unavailable('returned archive: %s' % error)
    for unit in units:
        # A missing exit code means the unit never ran; a missing object with
        # exit code 0 cannot happen with VC6. Either is a backend failure.
        if absolute(unit['returncode']) not in found or absolute(unit['log']) not in found:
            raise Unavailable('remote outputs missing for %s' % unit['cwd'])
    for path, data in found.items():
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
    return dict(backend='remote', host=spec['host'], job=root, jobs=count, priority='belownormal',
                remote_compiler=dict(zip(COMPILER_FILES, actual)), lock_wait_seconds=waited,
                stage_bytes=len(staged), returned_bytes=len(returned), stage_seconds=stage_seconds,
                run_seconds=run_seconds, fetch_seconds=fetch_seconds, sessions=[dict(seconds=s) for s in sessions],
                seconds=time.monotonic() - started, kept=keep, killed_hung_compilers=[])


def stop(spec, job):
    """Best effort: end compilers still running for a failed job."""
    try:
        ssh(spec, 'powershell -NoProfile -Command "Get-CimInstance Win32_Process | Where-Object '
                  '{ $_.CommandLine -like \'*%s*\' } | ForEach-Object { Stop-Process -Id $_.ProcessId -Force }"' % job,
            timeout=60)
    except Unavailable:
        pass


def cleanup(spec, root):
    if os.environ.get('RA2_REMOTE_KEEP') == '1':
        return
    try:
        ssh(spec, 'cmd /d /c "if exist %s rmdir /s /q %s"' % (root, root), timeout=120)
    except Unavailable:
        pass
