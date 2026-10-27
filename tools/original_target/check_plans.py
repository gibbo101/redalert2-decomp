#!/usr/bin/env python3
"""Dry-run acceptance (portable version of check_plans.sh; macOS, Linux, Windows).

    python tools/original_target/check_plans.py [--build] NAME HEADER_DIR PLAN...

Runs the real accept_sources.py for each plan, in order, inside a throwaway
git worktree of HEAD whose src/ and manifests/ are copies of the main tree's
(including uncommitted accepted work), with the proposed header copies from
HEADER_DIR (or HEADER_DIR/shared) installed over src/shared. The worktree gets
its own copies of private/original-target.*.json and its own inventory folder
(acceptance writes population mappings and composite passes there); the rest
of private/ is linked. Results go to build/check/NAME/results.txt with each
plan's JSON reports and compile logs; the worktree is removed afterwards.
RA2_CONFIG selects the compiler config (default original-target.interactive.json).
With --build, the full build (build.py) then runs in the worktree, so a header
change that breaks a unit outside the plans is caught before delivery (about
five minutes more). RA2_CHECK_ROOT, if set, holds the throwaway worktree instead (a short path such as
C:\ra2\c keeps Windows paths under 260 characters).
"""
import catalog_io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
NATIVE = os.name == 'nt'
KEEP = ('"candidates"', '"accepted"', '"missed"', '"error"', 'refus', 'plan replaces', 'rror')


def link(source, destination):
    """Link a file or folder (a junction for folders on Windows, which needs no
    privilege). Every link is recorded so removal never follows one."""
    with open(RECORD[0], 'a') as handle:
        handle.write(str(destination) + '\n')
    if NATIVE and source.is_dir():
        subprocess.run(['cmd', '/d', '/c', 'mklink', '/J', str(destination), str(source)],
                       check=True, stdout=subprocess.DEVNULL)
    elif NATIVE:
        shutil.copy2(source, destination)
    else:
        destination.symlink_to(source)


RECORD = [None]


def unlink_tree(path, record):
    """Remove a worktree: first every recorded link (rmdir of a junction or
    unlink of a symlink never touches its target), then the rest."""
    if record.exists():
        for line in reversed(record.read_text().splitlines()):
            link_path = Path(line)
            if link_path.is_symlink():
                link_path.unlink()
            elif NATIVE and link_path.is_dir():
                os.rmdir(link_path)          # a junction: removes the link only
            elif NATIVE and link_path.is_file():
                link_path.unlink()           # a copied file
        record.unlink()
    if path.exists():
        shutil.rmtree(path)


def copy_tree(source, destination):
    if destination.exists():
        shutil.rmtree(destination)
    shutil.copytree(source, destination)


def main():
    full_build = '--build' in sys.argv[1:]
    if full_build:
        sys.argv.remove('--build')
    if len(sys.argv) < 4:
        raise SystemExit(__doc__)
    name, headers, plans = sys.argv[1], Path(sys.argv[2]), sys.argv[3:]
    config = Path(os.environ.get('RA2_CONFIG', REPOSITORY / 'private/original-target.interactive.json'))
    base = REPOSITORY / 'build/check' / name
    worktree = Path(os.environ['RA2_CHECK_ROOT']) / name if os.environ.get('RA2_CHECK_ROOT') else base / 'wt'
    os.chdir(REPOSITORY)
    record = REPOSITORY / 'build/check' / (name + '.links')
    RECORD[0] = record
    unlink_tree(worktree, record)
    subprocess.run(['git', 'worktree', 'prune'])
    if base.exists():
        shutil.rmtree(base)
    base.mkdir(parents=True)
    subprocess.run(['git', 'worktree', 'add', '--detach', str(worktree), 'HEAD'], check=True,
                   stdout=subprocess.DEVNULL)
    try:
        copy_tree(REPOSITORY / 'src', worktree / 'src')
        # Acceptance rewrites the manifest in place; retry until a complete copy parses.
        for _ in range(10):
            copy_tree(REPOSITORY / 'manifests', worktree / 'manifests')
            try:
                catalog_io.load(catalog_io.locate(worktree), references=False)
                break
            except ValueError:
                time.sleep(3)
        private = worktree / 'private'
        private.mkdir()
        evidence = REPOSITORY / 'private/original-target-20261020'
        for entry in (REPOSITORY / 'private').iterdir():
            if entry.name.startswith('original-target.') and entry.suffix == '.json':
                shutil.copy2(entry, private / entry.name)
            elif entry != evidence:
                link(entry, private / entry.name)
        (private / evidence.name / 'inventory').mkdir(parents=True)
        for entry in evidence.iterdir():
            if entry.name != 'inventory':
                link(entry, private / evidence.name / entry.name)
        for entry in (evidence / 'inventory').iterdir():
            link(entry, private / evidence.name / 'inventory' / entry.name)
        (worktree / 'build').mkdir(exist_ok=True)
        link(REPOSITORY / 'build/class-work', worktree / 'build/class-work')
        if (headers / 'shared').is_dir():
            headers = headers / 'shared'
        for header in headers.glob('*.hpp'):
            shutil.copy2(header, worktree / 'src/shared' / header.name)
        lines = []
        for plan in plans:
            stem = Path(plan).stem
            lines.append('=== %s' % plan)
            result = subprocess.run([sys.executable, '-B', 'tools/original_target/accept_sources.py',
                                     '--config', str(private / config.name),
                                     '--output', str(worktree / 'build' / ('accept-' + stem)),
                                     str(REPOSITORY / plan)],
                                    cwd=worktree, capture_output=True, text=True)
            output = (result.stdout + result.stderr).splitlines()
            lines += [l for l in output if any(k in l for k in KEEP)][:12]
            if result.returncode:
                lines += output[-3:]
            with open(base / 'results.txt', 'w') as handle:
                handle.write('\n'.join(lines) + '\n')
        if full_build:
            result = subprocess.run([sys.executable, '-B', 'tools/original_target/build.py',
                                     '--config', str(private / config.name),
                                     '--output', str(worktree / 'build' / 'check-build')],
                                    cwd=worktree, capture_output=True, text=True)
            output = (result.stdout + result.stderr).splitlines()
            lines.append('=== full build')
            lines += [l for l in output if 'whole_file_exact' in l or 'rror' in l][:6] or output[-3:]
            for log in sorted((worktree / 'build' / 'check-build').glob('compile-*/compile.log')):
                lines += sorted({l.strip() for l in log.read_text(errors='replace').splitlines() if 'error C' in l})[:4]
        # Keep each plan's reports and compile logs, then drop the worktree.
        for report in (worktree / 'build').glob('accept-*'):
            for path in report.rglob('*'):
                if path.suffix in ('.json', '.log') and path.is_file():
                    target = base / report.name / path.relative_to(report)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(path, target)
    finally:
        unlink_tree(worktree, record)
        subprocess.run(['git', 'worktree', 'prune'], cwd=REPOSITORY)
    lines.append('DONE')
    (base / 'results.txt').write_text('\n'.join(lines) + '\n')
    print('\n'.join(lines))


if __name__ == '__main__':
    main()
