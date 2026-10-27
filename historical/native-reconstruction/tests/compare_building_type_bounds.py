# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building Type bounds predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_type_bounds import verify
ORIGINAL=('tests/compare_building_type_bounds.py','tests/original_building_type_bounds.py','tools/verify_building_type_bounds.py')
NATIVE=('src/render/BuildingTypeBounds.hpp','src/render/BuildingTypeBounds.cpp','src/render/Redraw.hpp','src/render/Redraw.cpp','src/render/Composition.hpp','src/assets/Shp.hpp','tests/building_type_bounds_vectors.cpp','tests/building_type_assets.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_type_bounds=True,actual_frame_accessor=True,actual_rectangle_constructor=True,actual_release_parent=True,image_getters_supplied=True,heap_supplied=True,demand_loading_recovered=False)
def require(v):
 if not v:raise ValueError('Building Type bounds evidence/domain differs')
def image(size=(101,99),count=3,frames=((10,12,20,30),(5,6,40,20),(1,2,15,50))):return (*size,count,*(v for f in frames for v in f))
def command(op=0,mode=0,cache=(0,0,0,0),empty=(0,0,0,0),initial=-1,aux=-1,release=0,flag=128,primary=0,secondary=-1,index=0,images=None):
 if images is None:images=[image(),image(size=(9,7),frames=((-5,-9,6,7),(50,60,7,9),(4,5,1,1))),image(size=(55,77),frames=((100,200,10,20),(-100,-200,30,40),(0,0,5,5)))]
 return ' '.join(map(str,(op,mode,*cache,*empty,initial,aux,release,flag,primary,secondary,index,*(v for im in images for v in im))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)>=62 and (len(v)-26)%12==0);capacity=(len(v)-26)//12;stride=3+capacity*4
 require(3<=capacity<=32 and v[0] in (0,1,2) and 0<=v[1]<=6 and all(-2**31<=n<2**31 for n in v) and all(-1<=v[i]<=2 for i in (10,11,14,15)) and 0<=v[12]<=255 and 0<=v[13]<=255 and all(-32768<=n<=32767 for n in v[17:]))
 require(v[0]!=1 or v[14]>=0)
 for id in range(3):require(v[17+id*stride+2]<=capacity)
 # Successful huge-index aliases are resolved by wrapped byte displacement.
 if v[0]==1 and (v[16]&0xffffffff)<(v[19]&0xffffffff):
  offset=((v[16]&0xffffffff)*24)&0xffffffff;require(offset%24==0 and offset//24<capacity)
 return v
def scenarios():
 for field in range(4):
  for value in (-2147483648,-1,1,2147483647):
   cache=[0]*4;cache[field]=value
   yield 'cache_returns_without_image_children',command(cache=cache)
 yield 'null_primary_returns_empty_without_cache_write',command(primary=-1,empty=(1,2,3,4),cache=(1,2,3,4))
 for count in (-32768,-1,0,1,2,3):
  for width,height in ((0,0),(101,99),(-101,-99),(-32768,32767)):
   for frames in (((10,12,20,30),(5,6,40,20),(1,2,15,50)),((0,0,0,0),(1,2,-3,4),(5,6,7,-8)),((-32768,32767,32767,1),(32767,-32768,1,32767),(0,0,-32768,-1))):
    yield 'signed_frames_dimensions_empty_union_centering',command(images=[image((width,height),count,frames)]*3)
 for initial in (-1,0,1):
  for secondary in (-1,1):
   for release in (0,1,128,255):
    for aux in (-1,2):
     yield 'secondary_initial_identity_release_and_auxiliary',command(initial=initial,secondary=secondary,release=release,aux=aux)
 for mode in range(7):
  for count in (-1,0,1,3):
   yield 'late_secondary_free_auxiliary_and_saved_primary_dimensions',command(mode=mode,secondary=1,aux=2,release=128,images=[image(),image(count=count),image(count=-1)])
 for count in (-32768,-1,0,1,2,3):
  for index in (-2147483648,-1,0,1,2):
   yield 'unsigned_index_against_sign_extended_count',command(op=1,index=index,images=[image(count=count)]*3)
 for release in (0,1,128,255):
  for initial in (-1,0,1,2):
   for mode in (0,2):yield 'complete_release_raw_flags_identity_clear_order',command(op=2,initial=initial,release=release,mode=mode)
 rng=random.Random(0x45e290)
 for _ in range(128):
  yield 'seeded_signed_header_metadata_and_optional_images',command(initial=rng.choice((-1,0,1)),aux=rng.choice((-1,2)),release=rng.choice((0,1,128,255)),secondary=rng.choice((-1,1)),mode=rng.randrange(7),images=[image(size=(rng.randint(-32768,32767),rng.randint(-32768,32767)),count=rng.randint(-1,3),frames=tuple(tuple(rng.randint(-32768,32767) for _ in range(4)) for _ in range(3))) for _ in range(3)])
def produced(a):
 if not getattr(a,'asset_producer',None):return [],None
 require(a.data_dir is not None)
 runner=hash_file(a.asset_producer);p=subprocess.run([str(a.asset_producer),str(a.data_dir)],capture_output=True,text=True,check=True);rows=[];assets={}
 for line in p.stdout.splitlines():
  label,digest,cmd=line.split('\t');require(len(digest)==64);parse(cmd);rows.append([label,cmd]);assets[label.split(':')[0]]=digest
 require(len(rows)==14 and runner==hash_file(a.asset_producer))
 return rows,dict(producer_sha256=runner,stdout_sha256=hashlib.sha256(p.stdout.encode()).hexdigest(),assets=assets)
def identities(a):
 rows,producer=produced(a);paths=python_closure(ROOT/'tests/compare_building_type_bounds.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},asset_rows=rows,environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE},native_input_producer=producer)
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios())+[tuple(row) for row in current['original']['asset_rows']];require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+9)
 for j in range(0,i,4):
  require(1<=int(row[j])<=10)
  for v in row[j+1:j+4]:int(v)
 for v in row[i+1:]:int(v)
 require(all(-1<=int(row[i+j])<=2 for j in (5,6)) and all(0<=int(row[i+j])<=255 for j in (7,8)))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report','asset-producer','data-dir'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_type_bounds import BuildingTypeBoundsOracle
  oracle=BuildingTypeBoundsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios())+current['original']['asset_rows']:commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.parents>0 and oracle.frames>0 and oracle.releases>0 and oracle.frees>0)
  meta=dict(FLAGS,actual_parent_entries=oracle.parents,actual_frame_accessor_entries=oracle.frames,actual_release_entries=oracle.releases,supplied_getter_calls=oracle.gets,supplied_heap_calls=oracle.frees,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building Type bounds redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
