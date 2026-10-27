#!/usr/bin/env python3
"""Fresh accepted-only compile, strict V4 comparison, fixed-address link/package.
All authored execution dependencies are tracked. Proprietary inputs stay private.
"""
import argparse
from collections import OrderedDict
from contextlib import contextmanager
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import time

import pefile
from canonical import CanonicalAudit, compiler_arguments, sha, source_path
from coff import Coff
from verify_manifest import require
import catalog_io

REPOSITORY = Path(__file__).resolve().parents[2]
# On Windows the VC6 tools run natively (config "wine_kind": "native");
# elsewhere they run under Wine with the filesystem mapped to drive Z:.
NATIVE = os.name == 'nt'


@contextmanager
def exclusive_lock(path):
    """Hold an exclusive lock on `path` (one compiler session per config)."""
    with Path(path).open('a+') as lock:
        if NATIVE:
            import msvcrt
            while True:
                try:
                    lock.seek(0); msvcrt.locking(lock.fileno(), msvcrt.LK_NBLCK, 1); break
                except OSError:
                    time.sleep(0.5)
            try:
                yield
            finally:
                lock.seek(0); msvcrt.locking(lock.fileno(), msvcrt.LK_UNLCK, 1)
        else:
            import fcntl
            fcntl.flock(lock, fcntl.LOCK_EX)
            yield


def write_json(path, data):
    path.write_text(json.dumps(data, indent=2)+'\n')


def win(path):
    value = str(Path(path).resolve())
    require(not any(c in value for c in '\r\n"%!'), 'Unsupported Windows command path')
    return value if NATIVE else 'Z:' + value.replace('/', '\\')


def run(command, directory, name, env=None, timeout=180):
    started = time.monotonic()
    # Output goes to a file, not a pipe: Wine may start a wineserver daemon
    # that inherits the child's handles, and a pipe would then never reach
    # end-of-file after the command itself has finished.
    log = directory/(name+'.log')
    with log.open('w') as output:
        result = subprocess.run(command, cwd=directory, env=env, stdin=subprocess.DEVNULL,
                                stdout=output, stderr=subprocess.STDOUT, timeout=timeout)
    receipt = dict(command=command, returncode=result.returncode, seconds=time.monotonic()-started)
    write_json(directory/(name+'-command.json'), receipt)
    require(result.returncode == 0, 'Command failed: '+str(directory/(name+'.log')))
    return receipt


def wine_invocation(config, directory, lines, name, temporary_name='tmp'):
    """Write a cmd script for lines; return the Wine command and environment."""
    script = directory/(name+'.cmd')
    temporary = directory/temporary_name; temporary.mkdir(exist_ok=True)
    text = ['@echo off', 'set CL=', 'set _CL_=', 'set LINK=', 'set INCLUDE=', 'set LIB=',
            'set "TMP='+win(temporary)+'"', 'set "TEMP='+win(temporary)+'"'] + lines + ['exit /b %errorlevel%']
    script.write_bytes(('\r\n'.join(text)+'\r\n').encode())
    env = dict(os.environ)
    for key in ['CL','_CL_','LINK','INCLUDE','LIB','WINEPREFIX','CX_BOTTLE','CX_INITIALIZED']:
        env.pop(key, None)
    if config.get('wine_kind', 'crossover') == 'native':
        require(NATIVE, 'wine_kind native needs Windows')
        env.update(TMP=str(temporary), TEMP=str(temporary))
        command = ['cmd.exe', '/d', '/c', str(script)]
    elif config.get('wine_kind', 'crossover') == 'wine':
        # Plain Wine with a project-local prefix. A persistent wineserver keeps
        # each session start near 0.5s; `wineserver -p` exits at once when one
        # is already running for this prefix.
        env.update(WINEPREFIX=config['wine_prefix'], TMPDIR=str(temporary), WINEDEBUG='-all',
                   WINEDLLOVERRIDES='winemenubuilder.exe=d;mscoree=d;mshtml=d')
        if config.get('wineserver'):
            subprocess.run([config['wineserver'], '-p'], env=env, stdin=subprocess.DEVNULL,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        command = [config['wine'], 'cmd.exe', '/d', '/c', win(script)]
    else:
        bottle = Path(config['bottle'])
        env.update(CX_BOTTLE_PATH=str(bottle.parent), CX_BOTTLE=str(bottle), CX_BOTTLE_MODE='ignore',
                   TMPDIR=str(temporary), WINEDEBUG='-all', WINEDLLOVERRIDES='winemenubuilder.exe=d')
        command = [config['wine'], '--bottle', str(bottle), '--scope', 'private', '--no-gui', '--cx-app',
                   'C:\\windows\\system32\\cmd.exe', '/d', '/c', win(script)]
    return command, env


def wine_command(config, directory, lines, name, timeout=180):
    command, env = wine_invocation(config, directory, lines, name)
    before = time.monotonic()
    with exclusive_lock(config['lock']):
        waited = time.monotonic()-before
        receipt = run(command, directory, name, env, timeout)
    receipt['lock_wait_seconds'] = waited
    write_json(directory/(name+'-command.json'), receipt)
    return receipt


def kill_hung_compilers(marker, limit, done, killed):
    """Kill CL.EXE processes working in `marker` for longer than `limit` s.

    Under heavy load Wine occasionally leaves a compiler hung on a file it
    compiles in well under a second otherwise; the session then continues
    with the next unit and the caller retries the failed ones.
    """
    while not done.wait(15):
        listing = subprocess.run(['ps', '-axo', 'pid=,etime=,command='], capture_output=True, text=True).stdout
        for line in listing.splitlines():
            parts = line.split(None, 2)
            if len(parts) < 3 or 'CL.EXE' not in parts[2] or marker not in parts[2]:
                continue
            fields = parts[1].replace('-', ':').split(':')
            seconds = 0
            for value, scale in zip(reversed(fields), (1, 60, 3600, 86400)):
                seconds += int(value) * scale
            if seconds > limit:
                subprocess.run(['kill', '-9', parts[0]], capture_output=True)
                killed.append(parts[2][:300])


def wine_parallel(config, directory, units, name, timeout=3600, hang_seconds=600):
    """Run independent command units in concurrent Wine sessions.

    Each unit is a list of script lines (one compile and its exit-code
    capture); units are dealt to `parallel_sessions` scripts (config, default
    4), each with its own temporary directory, all in one prefix under one
    lock acquisition. Every unit still writes its own log and exit code.
    """
    from concurrent.futures import ThreadPoolExecutor
    count = max(1, min(int(config.get('parallel_sessions', 4)), len(units)))
    shards = [[] for _ in range(count)]
    for index, unit in enumerate(units):
        shards[index % count].extend(unit)
    invocations = [wine_invocation(config, directory, shard + ['exit /b 0'], '%s-%d' % (name, i), 'tmp-%d' % i)
                   for i, shard in enumerate(shards)]
    import threading
    before = time.monotonic()
    with exclusive_lock(config['lock']):
        waited = time.monotonic()-before
        started = time.monotonic()
        done = threading.Event(); killed = []
        # Hung compilers are a Wine artefact; native runs need no watchdog.
        watchdog = threading.Thread(target=kill_hung_compilers, args=(win(directory), hang_seconds, done, killed))
        if not NATIVE:
            watchdog.start()
        try:
            with ThreadPoolExecutor(count) as pool:
                receipts = list(pool.map(lambda item: run(item[1][0], directory, '%s-%d' % (name, item[0]), item[1][1], timeout),
                                         enumerate(invocations)))
        finally:
            done.set()
            if not NATIVE:
                watchdog.join()
    receipt = dict(sessions=receipts, seconds=time.monotonic()-started, lock_wait_seconds=waited,
                   killed_hung_compilers=killed)
    write_json(directory/(name+'-command.json'), receipt)
    return receipt


def unit_lines(unit, path, include, compiler):
    """Cmd lines for one compile unit (dict: cwd, source, obj, log, returncode,
    args). The compiler runs from the unit's directory with a relative source
    name: VC6 records the source name as given in the object's .file symbol,
    so objects then do not depend on where the tree lives (Wine Z:\\ or a
    remote host). `path` spells a local path for the executing host."""
    source = os.path.relpath(os.path.abspath(unit['source']), os.path.abspath(unit['cwd'])).replace('/', '\\')
    require(not any(c in source for c in '\r\n"%!'), 'Unsupported source path')
    args = [*unit['args'], '/I'+include, '/Fo'+path(unit['obj']), source]
    return ['cd /d "%s"' % path(unit['cwd']),
            '"'+compiler+'" '+' '.join('"'+a+'"' for a in args)+' >"'+path(unit['log'])+'" 2>&1',
            '>"'+path(unit['returncode'])+'" echo %errorlevel%']


def compile_units(config, directory, units, name, parallel=True, timeout=3600, hang_seconds=600):
    """Compile units with the opt-in remote backend (remote_compile.py), or
    locally: `parallel_sessions` Wine sessions, or one session if not
    `parallel`. An unreachable or failing remote host falls back to local."""
    import remote_compile
    spec, fallback = remote_compile.settings(config), None
    if spec and units:
        try:
            pinned = json.loads((REPOSITORY/'manifests/toolchain.json').read_text())['compiler']
            receipt = remote_compile.run(spec, REPOSITORY, directory, units, name, pinned, unit_lines, timeout)
            write_json(directory/(name+'-command.json'), receipt)
            return receipt
        except remote_compile.Unavailable as error:
            fallback = str(error)
            print('remote compile unavailable (%s); compiling locally' % fallback, file=sys.stderr, flush=True)
    rendered = [unit_lines(u, win, win(REPOSITORY/'src'), win(Path(config['compiler_directory'])/'CL.EXE'))
                for u in units]
    if parallel:
        receipt = wine_parallel(config, directory, rendered, name, timeout, hang_seconds)
    else:
        receipt = wine_command(config, directory, [l for u in rendered for l in u] + ['exit /b 0'], name, timeout)
        receipt['killed_hung_compilers'] = []
    receipt['backend'] = 'local'
    if fallback:
        receipt['remote_fallback'] = fallback
    write_json(directory/(name+'-command.json'), receipt)
    return receipt


def check_toolchain(config, pinned):
    require(Path(config['compiler_directory']).is_absolute() and Path(config['linker']).is_absolute(),
            'Tool paths must be explicit absolute paths')
    actual = {}
    for kind, directory in [('compiler',Path(config['compiler_directory'])), ('linker',Path(config['linker']).parent)]:
        actual[kind] = {}
        for name, expected in pinned[kind].items():
            digest = sha((directory/name).read_bytes())
            require(digest == expected, 'Toolchain drift: '+name)
            actual[kind][name] = digest
    require(Path(config['linker']).name == 'LINK.EXE', 'Unexpected linker name')
    return actual


def compile_sources(config, catalog, destination):
    from canonical import compile_group_key, separate_unit_populations
    groups = OrderedDict()
    separate = separate_unit_populations(catalog)
    for row in sorted(catalog['regions'], key=lambda r:r['source_order']):
        groups.setdefault(compile_group_key(row, separate), []).append(row)
    # A few concurrent Wine sessions (or the opt-in remote host) run every
    # group. Each group keeps its own source, object, compiler log and exit
    # code; a failure in any group fails the build.
    units, planned = [], []
    for index, (key, rows) in enumerate(groups.items()):
        population, options = key[0], key[1]
        directory = destination/('compile-%03d'%index); directory.mkdir()
        source = directory/'accepted.cpp'
        source.write_bytes(b'\n'.join(source_path(REPOSITORY,r['source']).read_bytes() for r in rows))
        obj = directory/'accepted.obj'
        units.append(dict(cwd=directory, source=source, obj=obj, log=directory/'compile.log',
                          returncode=directory/'returncode.txt', args=compiler_arguments(options)))
        planned.append((population, options, rows, directory, source, obj))
    session = compile_units(config, destination, units, 'compile')
    failed = [i for i, p in enumerate(planned) if not (p[3]/'returncode.txt').exists() or
              (p[3]/'returncode.txt').read_text().strip() != '0']
    if failed and session['killed_hung_compilers']:
        # Only a killed (hung) compiler earns a retry; real errors still fail.
        session['retry'] = compile_units(config, destination, [units[i] for i in failed], 'compile-retry')
    outputs, receipts = [], []
    for index, (population, options, rows, directory, source, obj) in enumerate(planned):
        returncode = int((directory/'returncode.txt').read_text().strip())
        require(returncode == 0 and obj.exists(), 'Compile failed: '+str(directory/'compile.log'))
        receipts.append(dict(group=index, returncode=returncode, population=population, options=list(options),
                             source_sha256=sha(source.read_bytes()), sources=[r['source'] for r in rows],
                             object_sha256=sha(obj.read_bytes())))
        outputs.append((rows,obj))
    print('Compiled %d groups (%d tracked sources) in %d %s sessions, %.1fs'%(
        len(planned), sum(len(p[2]) for p in planned), len(session['sessions']), session['backend'],
        session['seconds'] + session.get('retry', {}).get('seconds', 0)), flush=True)
    write_json(destination/'compile-receipt.json', dict(session=session, groups=receipts))
    return outputs


def transferred_parts(audit, manifest):
    parts, rows = [], []
    for row in sorted(manifest['accepted'],key=lambda r:r['entry']):
        # Use the exact frozen object byte snapshot accepted by the verifier.
        coff = audit.coffs[audit.path(row['object'])]
        symbol, section, start, end = coff.function(row['symbol_prefix'])
        data = bytearray(section['data'][start:end])
        for relocation in row['relocations']:
            struct.pack_into('<I', data, relocation['offset'], relocation['resolved'])
        require(sha(data) == row['full_extent_sha256'] and bytes(data) == audit.original(row['entry'],len(data)),
                'Transfer differs from verified fresh compiler extent')
        parts.append(('.text$%08x'%row['entry'],bytes(data)))
        rows.append(dict(entry=row['entry'], source=row['source'], source_sha256=row['source_sha256'],
                         object_sha256=row['object_sha256'], object=str(audit.path(row['object'])),
                         section_index=symbol['section'], section_start=start, section_end=end,
                         transferred_sha256=sha(data), bytes=len(data)))
    return parts, rows


def verify_discard_transfer(audit, transfers, parts, container):
    """Prove exact placement-only container, with no discarded input interval."""
    parsed = Coff(container)
    require([(s['name'], s['data']) for s in parsed.sections] == parts and
            not parsed.symbols and not any(s['relocs'] for s in parsed.sections),
            'Transferred container differs from verified placement plan')
    discarded = getattr(audit, 'discarded_outputs', {})
    receipts = []
    for obj, components in discarded.items():
        for component in components:
            require(all(t['object'] != obj or t['section_index'] != component['section_index'] or
                        t['section_end'] <= component['first'] or t['section_start'] >= component['last']
                        for t in transfers), 'Discarded compiler output entered transfer plan')
            receipts.append(dict(component, object=obj, object_sha256=audit.sha(audit.read(obj))))
    return dict(status='verified-physical-prelink-omission', components=receipts,
                accepted_container_sha256=sha(container), transferred_regions=len(transfers),
                transferred_bytes=sum(t['bytes'] for t in transfers), original_image_credit=0,
                scope='Only verified placement sections enter accepted.obj; raw compiler objects are not link inputs. Original helper scaffold remains.')


def write_coff(parts):
    require(0 < len(parts) < 32768,'Unsupported classic COFF section count')
    payload = bytearray(); headers=[]; strings=bytearray(b'\0\0\0\0'); offset=20+40*len(parts)
    for name, data in parts:
        field=('/'+str(len(strings))).encode().ljust(8,b'\0'); strings.extend(name.encode()+b'\0')
        headers.append(struct.pack('<8sIIIIIIHHI',field,0,0,len(data),offset+len(payload),0,0,0,0,0x60100020))
        payload.extend(data)
    struct.pack_into('<I',strings,0,len(strings))
    return struct.pack('<HHIIIHH',0x14c,len(parts),0,offset+len(payload),0,0,0)+b''.join(headers)+payload+strings


def integrate(config, audit, manifest, destination):
    pe = audit.pe; base=pe.OPTIONAL_HEADER.ImageBase; text=pe.sections[0]
    require(text.Name.rstrip(b'\0') == b'.text' and text.VirtualAddress == 0x1000, 'Unexpected text layout')
    scaffold = destination/'scaffold'; scaffold.mkdir()
    for section in pe.sections:
        name=section.Name.rstrip(b'\0').decode()
        (scaffold/(name+'.bin')).write_bytes(section.get_data()[:min(section.Misc_VirtualSize,section.SizeOfRawData)])
    parts, receipts = transferred_parts(audit,manifest)
    container = write_coff(parts)
    discard_receipt = verify_discard_transfer(audit, receipts, parts, container)
    (destination/'accepted.obj').write_bytes(container)
    write_json(destination/'discarded-output-receipt.json', discard_receipt)
    cursor=base+text.VirtualAddress; limit=cursor+min(text.Misc_VirtualSize,text.SizeOfRawData)
    asm=['# Explicit unrecovered original-byte scaffold.','.section .text,"xr"']
    text_path=(scaffold/'.text.bin').as_posix()
    for row in sorted(manifest['accepted'],key=lambda r:r['entry']):
        require(cursor<=row['entry'] and row['entry']+row['full_extent_bytes']<=limit,'Extent outside text')
        if cursor<row['entry']:
            asm += ['.section .text$%08x,"xr"'%cursor,
                    '.incbin "%s", %d, %d'%(text_path,cursor-base-text.VirtualAddress,row['entry']-cursor)]
        cursor=row['entry']+row['full_extent_bytes']
    if cursor<limit:
        asm += ['.section .text$%08x,"xr"'%cursor,
                '.incbin "%s", %d, %d'%(text_path,cursor-base-text.VirtualAddress,limit-cursor)]
    for section in pe.sections[1:]:
        name=section.Name.rstrip(b'\0').decode(); emitted='.rawres' if name=='.rsrc' else name
        flags='dw' if name=='.data' else 'dr'
        asm += ['.section %s,"%s"'%(emitted,flags), '.incbin "%s"'%((scaffold/(name+'.bin')).as_posix())]
        if section.Misc_VirtualSize>section.SizeOfRawData:
            asm += ['.zero %d'%(section.Misc_VirtualSize-section.SizeOfRawData)]
    asm += ['.section .text,"xr"','.globl _original_entry',
            '.set _original_entry, .text + %d'%(pe.OPTIONAL_HEADER.AddressOfEntryPoint-text.VirtualAddress)]
    source=destination/'scaffold.s';source.write_text('\n'.join(asm)+'\n')
    assembler=config.get('assembler')
    if not assembler:
        assembler=subprocess.check_output(['xcrun','--find','clang'],text=True).strip()
    run([assembler,'--target=i686-pc-windows-msvc','-c',str(source),'-o',str(destination/'original.obj')],destination,'assemble')
    write_json(destination/'integration-receipt.json',dict(regions=receipts,
               remaining_text_scaffold_bytes=limit-base-text.VirtualAddress-sum(r['bytes'] for r in receipts),
               assembler=assembler,assembler_sha256=sha(Path(assembler).read_bytes())))
    args=['/nologo','/machine:ix86','/subsystem:windows,4.0','/base:0x400000','/entry:original_entry',
          '/fixed','/align:4096','/nodefaultlib','/incremental:no', '/out:'+win(destination/'linked.exe'),
          '/map:'+win(destination/'linked.map'),win(destination/'original.obj'),win(destination/'accepted.obj')]
    line='"'+win(config['linker'])+'" '+' '.join('"'+a+'"' for a in args)
    require((destination/'accepted.obj').read_bytes() == container, 'Placement container changed before link')
    discard_receipt['link_inputs'] = [dict(path=str(destination/name), sha256=sha((destination/name).read_bytes()))
                                      for name in ['original.obj', 'accepted.obj']]
    write_json(destination/'discarded-output-receipt.json', discard_receipt)
    wine_command(config,destination,[line],'link')


def check_tail(tail, expected_size):
    require(len(tail)==expected_size and not any(tail),'Incomplete/nonzero virtual tail')


def pe_structure(pe):
    fields = ['ImageBase', 'AddressOfEntryPoint', 'SectionAlignment', 'FileAlignment',
              'SizeOfHeaders', 'SizeOfImage', 'CheckSum', 'Subsystem', 'DllCharacteristics']
    return dict(machine=pe.FILE_HEADER.Machine, timestamp=pe.FILE_HEADER.TimeDateStamp,
                optional={name:getattr(pe.OPTIONAL_HEADER,name) for name in fields},
                directories=[dict(name=d.name,rva=d.VirtualAddress,size=d.Size) for d in pe.OPTIONAL_HEADER.DATA_DIRECTORY],
                sections=[dict(name=s.Name.rstrip(b'\0').decode(),rva=s.VirtualAddress,
                               virtual_size=s.Misc_VirtualSize,raw_offset=s.PointerToRawData,
                               raw_size=s.SizeOfRawData,flags=s.Characteristics) for s in pe.sections])


def package(original, linked, destination):
    old_pe=pefile.PE(data=original); new_pe=pefile.PE(data=linked)
    require(len(old_pe.sections)==len(new_pe.sections)==4,'Section count differs')
    output=bytearray(original[:old_pe.OPTIONAL_HEADER.SizeOfHeaders]); reports=[]
    for old,new in zip(old_pe.sections,new_pe.sections):
        require(old.VirtualAddress==new.VirtualAddress and old.Misc_VirtualSize==new.Misc_VirtualSize,'Section layout differs')
        live=min(old.Misc_VirtualSize,old.SizeOfRawData)
        data=new.get_data()[:live]
        require(len(data)==live and data==old.get_data()[:live],'Linked payload differs')
        require(old.PointerToRawData==len(output),'Original file layout discontinuity')
        output.extend(data);output.extend(old.get_data()[live:old.SizeOfRawData])
        tail_size=max(0,old.Misc_VirtualSize-live)
        check_tail(new.get_data()[live:old.Misc_VirtualSize],tail_size)
        reports.append(dict(name=old.Name.rstrip(b'\0').decode(),rva=old.VirtualAddress,
                            payload_bytes=live,payload_sha256=sha(data),verified_zero_tail_bytes=tail_size,
                            retained_padding_bytes=old.SizeOfRawData-live))
    overlay_start=old_pe.get_overlay_data_start_offset()
    require(overlay_start is not None and overlay_start==len(output),'Unexpected original overlay boundary')
    output.extend(original[overlay_start:])
    require(bytes(output)==original,'Complete packaged file differs')
    (destination/'reference.exe').write_bytes(output)
    report=dict(whole_file_exact=True,output_sha256=sha(output),output_bytes=len(output),
                raw_linked_sha256=sha(linked),raw_linked_bytes=len(linked),raw_linked_is_original_file=linked==original,
                raw_differing_common_bytes=sum(a!=b for a,b in zip(original,linked)),
                raw_length_difference=len(linked)-len(original),sections=reports,
                original_pe_structure=pe_structure(old_pe),raw_linked_pe_structure=pe_structure(new_pe),
                retained_header_bytes=old_pe.OPTIONAL_HEADER.SizeOfHeaders,retained_overlay_bytes=len(original)-overlay_start,
                scope='Fresh compiled source plus explicit original scaffold; retained original headers, file padding and overlay. Not full source recovery/playability.')
    write_json(destination/'reference-receipt.json',report)
    return report


def remove_intermediates(destination, groups):
    """Delete a verified build's bulky intermediates (several GB), keeping
    every receipt, log and the packaged output."""
    for index in range(groups):
        shutil.rmtree(destination/('compile-%03d'%index))
    (destination/'fresh-accepted.json').unlink()
    for temporary in destination.glob('tmp*'):
        shutil.rmtree(temporary,ignore_errors=True)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config',type=Path,default=REPOSITORY/'private/original-target.local.json')
    parser.add_argument('--manifest',type=Path,default=catalog_io.locate(REPOSITORY),
                        help='catalog directory (or a legacy .json file)')
    parser.add_argument('--output',type=Path,default=None)
    parser.add_argument('--verify-inputs',action='store_true')
    parser.add_argument('--keep-intermediates',action='store_true',
                        help='keep compile-NNN folders (sources, objects, logs) and fresh-accepted.json')
    parser.add_argument('--verify-jobs',type=int,default=None,
                        help='verification processes (default RA2_VERIFY_JOBS or min(4, CPUs))')
    args=parser.parse_args(); started=time.monotonic()
    marks=[started]
    def phase(name):
        # Elapsed time per build phase, on stderr (the receipt keeps the total).
        now=time.monotonic(); print('phase %s: %.1fs'%(name,now-marks[-1]),file=sys.stderr,flush=True); marks.append(now)
    config=json.loads(args.config.read_text());catalog_blobs={};catalog=catalog_io.load(args.manifest,blobs=catalog_blobs)
    audit=CanonicalAudit(REPOSITORY,catalog,config)
    tools=check_toolchain(config,json.loads((REPOSITORY/'manifests/toolchain.json').read_text()))
    phase('load and audit setup')
    if args.verify_inputs:
        print(json.dumps(dict(status='input-hashes-and-source-catalog-verified',sources=len(catalog['regions']))));return
    destination=(args.output or REPOSITORY/'build'/('original-target-'+str(time.time_ns()))).resolve()
    require(destination.is_relative_to(REPOSITORY/'build') or destination.is_relative_to(REPOSITORY/'private'),
            'Build output must stay beneath ignored root build/private')
    require('"' not in str(destination) and '\n' not in str(destination),'Unsupported assembler path')
    destination.mkdir(parents=True,exist_ok=False)
    # Pin authored tools and source catalog at build start. Verify again at end.
    inputs=[REPOSITORY/'manifests/toolchain.json',
            *[Path(__file__).with_name(name) for name in ['build.py','remote_compile.py','canonical.py','catalog_io.py','source_paths.py','verify_manifest.py','coff.py','compiler_output.py']]]
    for population in catalog['populations']:
        reference = population.get('compiler_output_policy')
        if reference:
            policy_path = REPOSITORY/reference['path']
            policy = audit.document(policy_path, reference['sha256'])
            inputs.extend([policy_path, REPOSITORY/policy['original_identity']['readiness_path']])
    fingerprints={str(p.relative_to(REPOSITORY)):sha(p.read_bytes()) for p in inputs}
    # The catalog is pinned by its digest (a sharded index pins every shard).
    catalog_key=str(args.manifest.resolve().relative_to(REPOSITORY))
    fingerprints[catalog_key]=catalog_io.digest(args.manifest,catalog_blobs)
    compiled=compile_sources(config,catalog,destination); phase('compile')
    manifest=audit.verify_fresh(destination,compiled,jobs=args.verify_jobs); phase('verify fresh objects')
    integrate(config,audit,manifest,destination); phase('integrate and link')
    original=audit.read(config['executable']);report=package(original,(destination/'linked.exe').read_bytes(),destination); phase('package')
    # Final input checks; each file is read once.
    # 1. Authored tools, toolchain manifest, catalog and policies: the code and
    #    plan that ran are the ones fingerprinted at build start.
    for p in inputs: require(sha(p.read_bytes())==fingerprints[str(p.relative_to(REPOSITORY))],'Build tool/catalog changed during run')
    require(catalog_io.digest(args.manifest)==fingerprints[catalog_key],'Build tool/catalog changed during run')
    # 2. The tree as it is now still matches the catalog (every source and
    #    header hash, no uncatalogued file, includes): source drift during the
    #    build cannot hide behind the snapshots the audit read.
    from canonical import validate_catalog
    current=validate_catalog(REPOSITORY,catalog)
    # 3. Every proof input the audit read (executable, inventories, policies,
    #    sources, headers, objects, group manifests) and the streamed fresh
    #    manifest still hold the bytes verified, compared by content or by
    #    SHA-256 for those read in verification workers; files step 2 just
    #    read are compared from those bytes instead of being read again.
    resolved={p: p.resolve() for p in [*audit.blobs, *getattr(audit,'blob_digests',{})]}
    audit.verify_inputs_unchanged({p: current[r] for p, r in resolved.items() if r in current})
    phase('final input checks')
    report.update(canonical_manifest_sha256=fingerprints[catalog_key],tracked_sources=len(catalog['regions']),
                  tracked_headers=catalog.get('headers', []),
                  discarded_output_receipt_sha256=sha((destination/'discarded-output-receipt.json').read_bytes()),
                  body_bytes=manifest['body_bytes'],padding_bytes=manifest['frozen_padding_bytes'],
                  toolchain=tools,authored_dependencies=fingerprints,seconds=time.monotonic()-started,
                  compile_policy='Fresh accepted-only sources; historical population/option groups, no candidate-search matrices')
    if not args.keep_intermediates:
        report.update(removed_after_verification=dict(
            paths=['compile-NNN/ (%d folders: accepted.cpp, accepted.obj, compile.log, returncode.txt)'%len(compiled),
                   'fresh-accepted.json'],
            reason='Intermediates of a verified build; hashes stay in compile-receipt.json, fresh-verification.json '
                   'and integration-receipt.json. Rebuild with --keep-intermediates to keep them.'))
    write_json(destination/'build-receipt.json',report)
    if not args.keep_intermediates:
        remove_intermediates(destination,len(compiled))
    print(json.dumps(dict(receipt=str(destination/'build-receipt.json'),**{k:report[k] for k in ['whole_file_exact','output_sha256','tracked_sources','seconds']})))


if __name__=='__main__':
    main()
