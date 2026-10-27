#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Patched-only stock caller metadata guards using isolated owned-data copies."""
import argparse,hashlib,subprocess,tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--data-dir',type=Path,required=True)
p.add_argument('--native',type=Path,default=Path('build/native/redalert2-native'));a=p.parse_args()
source=a.data_dir.resolve();build=Path('build').resolve()
if source==build or source in build.parents:raise ValueError('Fixtures must be outside source installation')
exe=next(path for path in source.iterdir() if path.name.lower()=='game.exe')
if hashlib.sha256(exe.read_bytes()).hexdigest()!='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f':
    print('Patched Unit caller metadata guards: retained disc profile skipped');raise SystemExit(0)
with tempfile.TemporaryDirectory(prefix='unit-caller-assets-',dir=build) as work:
    work=Path(work);export=work/'export';fixture=work/'game';fixture.mkdir()
    subprocess.run(['build/native/map-light-vectors','--export',str(source),str(export)],check=True)
    for path in source.iterdir():
        if path.is_file() and path.name.lower()!='rules.ini':(fixture/path.name).symlink_to(path)
    rules=(export/'rules.ini').read_text();target=work/'preview.ppm';checks=0
    for extra in ('','ZFudgeCliff=11','TooBigToFitUnderBridge=no','FireAngle=9'):
        (fixture/'rules.ini').write_text(rules+('\n[HTNK]\n'+extra+'\n' if extra else ''))
        if target.exists():target.unlink()
        r=subprocess.run([str(a.native),'--data-dir',str(fixture),'--render',str(target)],text=True,capture_output=True)
        if extra:assert r.returncode and 'stock HTNK drawing metadata/FireAngle' in r.stderr and not target.exists(),r.stderr
        else:assert r.returncode==0 and target.exists(),r.stderr
        checks+=1
    print(f'Patched Unit caller stock metadata/FireAngle guards: {checks} isolated native checks PASS')
