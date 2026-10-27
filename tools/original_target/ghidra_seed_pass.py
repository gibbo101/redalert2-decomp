#!/usr/bin/env python3
"""Run a seeded Ghidra discovery pass and export a new frozen inventory pass.

Copies an existing analysed Ghidra project (never modifying it), creates
functions at the seed addresses with ghidra/SeedPointers.java (which refuses
seeds inside known functions, instructions or defined data), reruns automatic
analysis, and exports functions.jsonl, decompiled/ and the unassigned gap list
with ghidra/ExportAll.java and ExportSupplement.java. The output directory is a
new inventory pass usable by sweep_seeds.py / promote_sweep.py; entries remain
analysis hypotheses until strict acceptance.

Seeds: JSON lines with a hex `target` and an `evidence` description.
"""
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import time

REPOSITORY = Path(__file__).resolve().parents[2]
SCRIPTS = Path(__file__).resolve().parent / 'ghidra'
GHIDRA = Path('/opt/homebrew/Cellar/ghidra/12.1.4/libexec')
JDK = Path('/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--base-project', type=Path, required=True, help='analysed Ghidra project directory to copy')
    parser.add_argument('--project', type=Path, required=True, help='new project directory (must not exist)')
    parser.add_argument('--seeds', type=Path, help='seed JSON lines for SeedPointers.java')
    parser.add_argument('--pre-script', nargs='+', help='alternative pre-script and its arguments '
                        '(e.g. FixNoReturn.java entries.json summary.json)')
    parser.add_argument('--output', type=Path, required=True, help='new inventory pass directory (must not exist)')
    parser.add_argument('--no-analysis', action='store_true', help='skip automatic analysis before export')
    parser.add_argument('--ghidra', type=Path, default=GHIDRA)
    parser.add_argument('--jdk', type=Path, default=JDK)
    args = parser.parse_args()
    project, output = args.project.resolve(), args.output.resolve()
    if project.exists() or output.exists():
        raise SystemExit('project/output must be new')
    shutil.copytree(args.base_project, project)
    output.mkdir(parents=True)
    work = project.parent / (project.name + '-work')
    for name in ('settings', 'cache', 'tmp', 'logs'):
        (work / name).mkdir(parents=True, exist_ok=True)
    jars = args.ghidra / 'Ghidra/Framework/Utility/lib/Utility.jar'
    command = [str(args.jdk / 'bin/java'), '-Djava.system.class.loader=ghidra.GhidraClassLoader',
               '-Dfile.encoding=UTF8', '-Xshare:off', '--enable-native-access=ALL-UNNAMED', '-Xmx4G',
               '-Djava.awt.headless=true', '-cp', str(jars), 'ghidra.Ghidra',
               'ghidra.app.util.headless.AnalyzeHeadless', str(project), 'WholeProgram',
               '-process', 'game.exe', *(['-noanalysis'] if args.no_analysis else []),
               '-analysisTimeoutPerFile', '1200', '-max-cpu', '4',
               '-scriptPath', str(SCRIPTS),
               '-preScript', *(args.pre_script or ['SeedPointers.java', str(args.seeds.resolve()),
                                                    str(output / 'seed-attempts.jsonl')]),
               '-postScript', 'ExportAll.java', str(output),
               '-postScript', 'ExportSupplement.java', str(output),
               '-log', str(work / 'logs/ghidra.log'), '-scriptlog', str(work / 'logs/script.log')]
    env = dict(os.environ, PATH=str(args.jdk / 'bin') + ':' + os.environ['PATH'], TMPDIR=str(work / 'tmp'),
               JAVA_TOOL_OPTIONS=' '.join('-D%s=%s' % (k, work / v) for k, v in [
                   ('application.settingsdir', 'settings'), ('application.cachedir', 'cache'),
                   ('application.tempdir', 'tmp'), ('java.io.tmpdir', 'tmp')]))
    meta = dict(command=command, started_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                base_project=str(args.base_project), seeds=str(args.seeds) if args.seeds else None,
                seeds_sha256=hashlib.sha256(args.seeds.read_bytes()).hexdigest() if args.seeds else None,
                pre_script=args.pre_script,
                scripts={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in SCRIPTS.glob('*.java')},
                classification='seeded Ghidra hypotheses; no strict byte acceptance')
    started = time.monotonic()
    with (work / 'logs/stdout.txt').open('w') as out, (work / 'logs/stderr.txt').open('w') as err:
        result = subprocess.run(command, env=env, stdout=out, stderr=err)
    meta.update(seconds=time.monotonic() - started, returncode=result.returncode,
                finished_utc=datetime.datetime.now(datetime.timezone.utc).isoformat())
    (output / 'pass-run.json').write_text(json.dumps(meta, indent=2))
    print(json.dumps({k: meta[k] for k in ('seconds', 'returncode')}))
    raise SystemExit(result.returncode)


if __name__ == '__main__':
    main()
