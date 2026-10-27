#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Owned profile preparation/decoder/guard checks; no original execution.

The originals and generated blobs remain read-only. Temporary malformed files and
all optional evidence stay in ignored build/private directories.
"""
import argparse,hashlib,json,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from prepared_data_profiles import DISC,PATCHED,default_output
import prepare_direction_data,prepare_render_data,prepare_raster_data

def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--disc',type=Path,required=True);p.add_argument('--patched',type=Path,required=True)
 p.add_argument('--native',type=Path,default=Path('build/native/prepared-data-check'))
 p.add_argument('--report',type=Path);a=p.parse_args()
 identities={};blobs={};outputs={};checks=0
 for engine,exe in ((DISC,a.disc),(PATCHED,a.patched)):
  source=exe.read_bytes();assert hashlib.sha256(source).hexdigest()==engine
  identities[str(exe)]=engine;blobs[engine]=[]
  for kind in ('direction','render','raster'):
   prepared=default_output(engine,kind+'-data.bin');data=prepared.read_bytes()
   assert data==globals()['prepare_'+kind+'_data'].extract(source)
   assert data[8:40].hex()==engine
   blobs[engine].append(data);identities[str(prepared)]=hashlib.sha256(data).hexdigest();checks+=2
  command=[str(a.native),str(exe),*[str(default_output(engine,k+'-data.bin')) for k in ('direction','render','raster')]]
  result=subprocess.run(command,capture_output=True,text=True,check=True)
  values=result.stdout.split();assert values[0]==engine;outputs[engine]=values[1:];checks+=1
  other=PATCHED if engine==DISC else DISC
  for index,kind in enumerate(('direction','render','raster'),2):
   mixed=command.copy();mixed[index]=str(default_output(other,kind+'-data.bin'))
   result=subprocess.run(mixed,capture_output=True,text=True)
   assert result.returncode and 'does not match GAME.EXE' in result.stderr,(kind,result.stderr);checks+=1
  with tempfile.TemporaryDirectory(prefix='prepared-guards-',dir=ROOT/'build') as temp:
   for index,data in enumerate(blobs[engine],2):
    for label,invalid in (('truncated',data[:-1]),('corrupt',data[:-1]+bytes([data[-1]^1]))):
     target=Path(temp)/label;target.write_bytes(invalid);command2=command.copy();command2[index]=str(target)
     result=subprocess.run(command2,capture_output=True,text=True)
     assert result.returncode and 'prepared data' in result.stderr,(label,result.stderr);checks+=1
   target=Path(temp)/'unknown.exe';target.write_bytes(b'MZ synthetic');command2=command.copy();command2[1]=str(target)
   result=subprocess.run(command2,capture_output=True,text=True)
   assert result.returncode and 'Unsupported GAME.EXE hash' in result.stderr;checks+=1
 for old,new in zip(blobs[DISC],blobs[PATCHED]):assert old[40:]==new[40:];checks+=1
 assert outputs[DISC]==outputs[PATCHED];checks+=1
 for path,digest in identities.items():assert hashlib.sha256(Path(path).read_bytes()).hexdigest()==digest
 report={'scope':'Native preparation/decoded input equivalence and source guards; no original execution or new fidelity claim',
         'checks':checks,'inputs':identities,'native_sha256':hashlib.sha256(a.native.read_bytes()).hexdigest(),
         'decoded_byte_count':int(outputs[DISC][0]),'decoded_sha256':outputs[DISC][1],
         'sources':{str(path.relative_to(ROOT)):hashlib.sha256(path.read_bytes()).hexdigest() for path in
                    [Path(__file__).resolve(),ROOT/'tests/prepared_data_check.cpp',*[ROOT/'tools'/('prepare_'+k+'_data.py') for k in ('direction','render','raster')],ROOT/'tools/prepared_data_profiles.py']}}
 if a.report:
  path=a.report.absolute()
  if any(v.is_symlink() for v in (path,*path.parents)):raise ValueError('Symlink report refused')
  path=path.resolve()
  if not any(path.is_relative_to(ROOT/d) for d in ('private','build')):raise ValueError('Report must remain private')
  if path.exists():raise ValueError('Choose a fresh report')
  path.parent.mkdir(parents=True,exist_ok=True);path.write_text(json.dumps(report,indent=2)+'\n')
 print(f'{checks} owned preparation/decoder/profile checks: PASS; {outputs[DISC][0]} decoded bytes match')
if __name__=='__main__':main()
