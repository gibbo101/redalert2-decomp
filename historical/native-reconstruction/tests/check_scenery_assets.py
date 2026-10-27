#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Owned ordinary static scenery guards and protected exports; native integration."""
import argparse,re,struct,subprocess,tempfile
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--data-dir',type=Path,required=True)
p.add_argument('--native',type=Path,default=Path('build/native/redalert2-native'));a=p.parse_args()
source=a.data_dir.resolve();build=Path('build').resolve()
if build==source or source in build.parents:raise ValueError('Fixtures must be outside source installation')
with tempfile.TemporaryDirectory(prefix='scenery-assets-',dir=build) as work:
 work=Path(work);export=work/'export';fixture=work/'game';fixture.mkdir();checks=0
 exporter='build/native/scenery-vectors'
 subprocess.run([exporter,'--export',str(source),str(export)],check=True)
 files=('mp03t4.map','rules.ini','art.ini','tree01.tem','sign03.tem')
 for path in source.iterdir():
  if path.is_file() and path.name.lower() not in files:(fixture/path.name).symlink_to(path)
 originals={name:(export/name).read_bytes() for name in files}
 def run(name,changes={},error=None):
  global checks
  for file,data in originals.items():(fixture/file).write_bytes(changes.get(file,data))
  target=work/(name+'.ppm')
  r=subprocess.run([str(a.native),'--data-dir',str(fixture),'--render',str(target)],capture_output=True,text=True)
  if error:assert r.returncode and error in r.stderr and not target.exists(),(name,r.stderr)
  else:assert r.returncode==0,(name,r.stderr)
  checks+=1
 run('stock')
 run('unverified-theater',{'mp03t4.map':originals['mp03t4.map'].replace(b'Theater=TEMPERATE',b'Theater=SNOW')},'Only TEMPERATE maps are currently verified')
 run('strength-sentinel',{'rules.ini':originals['rules.ini']+b'\n[TREE01]\nStrength=-1\n'})
 for tree in ('TREE05','TREE13','TREE28'):
  run(tree+'-animated',{'rules.ini':originals['rules.ini']+f'\n[{tree}]\nIsAnimated=yes\n'.encode()},'Only stock healthy static terrain types')
 for key in ('IsAnimated','SpawnsTiberium','IsVeinhole','WaterBound'):
  run(key,{'rules.ini':originals['rules.ini']+f'\n[TREE01]\n{key}=yes\n'.encode()},'Only stock healthy static terrain types')
 run('strength',{'rules.ini':originals['rules.ini']+b'\n[TREE01]\nStrength=1\n'},'Only stock healthy static terrain types')
 run('image',{'rules.ini':originals['rules.ini']+b'\n[TREE01]\nImage=TREE02\n'},'Only stock healthy static terrain types')
 for key,value in [('Theater','no'),('Foundation','2x2'),('Image','TREE02')]:
  run(key,{'art.ini':originals['art.ini']+f'\n[TREE01]\n{key}={value}\n'.encode()},'Only stock healthy static terrain types')
 run('map-override',{'mp03t4.map':originals['mp03t4.map']+b'\n[TREE01]\nName=Override\n'},'Only stock healthy static terrain types')
 bad=bytearray(originals['tree01.tem']);bad[16]=2
 run('format',{'tree01.tem':bad},'Only SHP formats 1 and 3')
 run('truncated',{'tree01.tem':originals['tree01.tem'][:-16]},'Truncated or invalid')
 # Each supplied prop must reach the guarded loader in a temporary map, even
 # when absent from mp03t4. The paired animated refusal proves it was not skipped.
 props=['HDSTN01',*[f'LT_GEN{n:02}' for n in range(1,5)],*[f'LT_SGN{n:02}' for n in range(1,5)],
        'LT_EUR01','LT_EUR02','POLE01','POLE02',*[f'SIGN{n:02}' for n in range(1,7)],*[f'TRFF{n:02}' for n in range(1,5)]]
 def prop_map(id):
  data,count=re.subn(rb'(?m)^(\d+=)TREE01(?=\r?$)',lambda m:m[1]+id.encode(),originals['mp03t4.map'])
  assert count==27,count
  return data
 for id in props:
  mapdata=prop_map(id)
  run(id+'-stock',{'mp03t4.map':mapdata})
  run(id+'-animated',{'mp03t4.map':mapdata,'rules.ini':originals['rules.ini']+f'\n[{id}]\nIsAnimated=yes\n'.encode()},'Only stock healthy static terrain types')
 signmap=prop_map('SIGN03')
 for key,value in [('SpawnsTiberium','yes'),('IsVeinhole','yes'),('WaterBound','yes'),('Strength','1'),('Image','SIGN04')]:
  run('prop-'+key,{'mp03t4.map':signmap,'rules.ini':originals['rules.ini']+f'\n[SIGN03]\n{key}={value}\n'.encode()},'Only stock healthy static terrain types')
 for key,value in [('Theater','no'),('Foundation','2x2'),('Image','SIGN04')]:
  run('prop-art-'+key,{'mp03t4.map':signmap,'art.ini':originals['art.ini']+f'\n[SIGN03]\n{key}={value}\n'.encode()},'Only stock healthy static terrain types')
 run('prop-map-override',{'mp03t4.map':signmap+b'\n[SIGN03]\nName=Override\n'},'Only stock healthy static terrain types')
 for fmt in (0,2):
  bad=bytearray(originals['sign03.tem']);struct.pack_into('<I',bad,16,fmt)
  run(f'raw-sign-format-{fmt}',{'mp03t4.map':signmap,'sign03.tem':bad},'Only SHP formats 1 and 3')
 bad=bytearray(originals['sign03.tem']);struct.pack_into('<H',bad,6,1)
 run('raw-sign-frames',{'mp03t4.map':signmap,'sign03.tem':bad},'Animated/damaged terrain images')
 blob=originals['sign03.tem'];size=struct.unpack_from('<H',blob,12)[0]*struct.unpack_from('<H',blob,14)[0]
 end=struct.unpack_from('<I',blob,28)[0]+size-1
 run('raw-sign-truncated',{'mp03t4.map':signmap,'sign03.tem':blob[:end]},'Truncated or invalid')
 # Export failures must leave the fixture contents untouched. Never target the
 # actual source installation, even for tests of the rejection path.
 def rejected(src,out):
  global checks
  r=subprocess.run([exporter,'--export',str(src),str(out)],capture_output=True,text=True)
  assert r.returncode,(src,out);checks+=1
 rejected(fixture,fixture/'export')
 link=work/'linked-export';link.symlink_to(export,target_is_directory=True);rejected(source,link)
 child=work/'exports';child.mkdir();(child/'tree01.tem').symlink_to(export/'tree01.tem');rejected(source,child)
 (export/'tree01.tem').write_bytes(b'different');rejected(source,export)
 assert (export/'tree01.tem').read_bytes()==b'different'
print(f'{checks} owned-data scenery/profile/export checks: PASS (native integration only)')
