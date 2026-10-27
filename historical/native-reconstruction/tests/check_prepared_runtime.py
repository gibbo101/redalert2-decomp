#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Owned application profile-selection and explicit-override guards; no SDL window."""
import argparse,hashlib,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from prepared_data_profiles import DISC,PATCHED,default_output
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--data-dir',type=Path,required=True)
p.add_argument('--app',type=Path,default=Path('build/native/redalert2-native'));a=p.parse_args()
engine=hashlib.sha256((a.data_dir/'game.exe').read_bytes()).hexdigest()
if engine not in (DISC,PATCHED):raise ValueError('Unknown engine')
other=PATCHED if engine==DISC else DISC
with tempfile.TemporaryDirectory(prefix='prepared-runtime-',dir=ROOT/'build') as work:
 output=Path(work)/'frame.ppm';base=[str(a.app),'--data-dir',str(a.data_dir),'--render',str(output)]
 auto=subprocess.run(base,capture_output=True,text=True,check=True);pixels=output.read_bytes();output.unlink()
 if engine not in auto.stdout:raise AssertionError('Application did not identify selected engine')
 flags=[]
 for kind in ('direction','render','raster'):flags += ['--'+kind+'-data',str(default_output(engine,kind+'-data.bin'))]
 subprocess.run(base+flags,capture_output=True,text=True,check=True)
 assert output.read_bytes()==pixels;output.unlink()
 for kind in ('direction','render','raster'):
  result=subprocess.run(base+['--'+kind+'-data',str(default_output(other,kind+'-data.bin'))],capture_output=True,text=True)
  assert result.returncode and 'does not match GAME.EXE' in result.stderr,(kind,result.stderr)
  assert not output.exists()
print('5 owned runtime profile/override checks: PASS (native integration only)')
