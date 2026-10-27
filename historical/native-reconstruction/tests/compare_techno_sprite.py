# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Techno sprite parent with actual Building numeric children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_techno_sprite import verify
ORIGINAL=('tests/compare_techno_sprite.py','tests/original_techno_sprite.py','tools/verify_techno_sprite.py')
NATIVE=('src/render/TechnoSpriteDraw.hpp','src/render/TechnoSpriteDraw.cpp','src/render/BuildingTypeBounds.hpp','src/render/BuildingTypeBounds.cpp','src/render/Redraw.hpp','src/render/Redraw.cpp','src/sim/RevealArea.cpp','src/sim/RevealArea.hpp','src/sim/OriginalMath.hpp','tests/techno_sprite_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_techno_sprite=True,both_mode_tables=True,actual_height_projection=True,actual_ftol=True,actual_building_brightness=True,actual_byte_predicates=True,actual_type_getter=True,other_children_and_startup_supplied=True,pixels=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Techno sprite evidence/domain differs')
from techno_sprite_fields import FIELDS,DEFAULT
def command(**kwargs):
 require(set(kwargs)<=set(FIELDS));return ' '.join(str(kwargs.get(k,DEFAULT[k])) for k in FIELDS)
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(FIELDS) and all(-2**31<=n<2**31 for n in v));f=dict(zip(FIELDS,v))
 for k in ('p1bc','p1c0','building1386','flag5bb','typeB48','shadow','footBB0','footBB1','ownerPredicate','ownedHousePredicate','pC0','p32c','flag37c'):require(0<=f[k]<=255)
 for k in ('cellTerrain','count','width','heightCanvas','rectX','rectY','rectW','rectH'):require(-32768<=f[k]<=32767)
 for k in ('converter','cellConverter','initConverter','houseConverter','currentConverter'):require(0<=f[k]<=4)
 require(f['image'] in (0,1) and f['target'] in (0,1) and 0<=f['mutation']<=8 and f['frame'] in (-2147483648,-1,0,1,2,7,31))
 return v
def scenarios():
 for mode in (-1,0,1,2,3,4,5,6):
  for gradient in (-1,0,2):
   for shadow in (0,128):
    for mask in (0,0x4804,-1):yield 'both_mode_tables_shadow_mask',command(mode=mode,gradient=gradient,shadow=shadow,mask=mask)
 for kind in (1,2,6,15,99):
  for mode in (0,1,2,5,6):
   for flag in (0,128):
    for b48 in (0,255):yield 'type_adjustment_and_shadow_priority',command(kind=kind,mode=mode,flag5bb=flag,typeB48=b48,target=kind%2,footBB1=128 if mode==2 else 0)
 for building in (0,255):
  for cell in (0,2):
   for init in (0,3):
    for owner in (0,255):
     for first,second in ((0,0),(21,0),(0,37)):
      for house in (0,4):yield 'converter_initialization_owner_and_fallback',command(building1386=building,cellConverter=cell,initConverter=init,ownerPredicate=owner,objectKind1=first,objectKind2=second,houseConverter=house)
 for p in (0,128):
  for q in (0,255):
   for owned in (0,255):
    for pc in (0,128):
     for status in (0,255):yield 'low_byte_short_circuit_and_effects',command(p1bc=p,p1c0=q,ownedHousePredicate=owned,pC0=pc,p32c=status,flagsD8=2147483647,statusAdd=-2147483648,flagsXor=-1,raw8=256)
 for flags in (0,1,2,3,-1,-2147483648):
  for light in (-2147483648,-1,0,1000,1500,1501,2000,2147483647):
   yield 'actual_building_brightness_threshold_and_width',command(flagsD8=flags,light=light)
 for bounds in ((0,0,0,0),(0,0,1,1),(50,60,3,4),(2147483647,-2147483648,10,20)):
  for rect in ((3,4,21,31),(3,4,0,-1),(-32768,32767,32767,32767)):
   for count in (0,6,-3):
    for frame in (-1,0,-2147483648):yield 'infantry_metadata_inclusive_union_and_unsigned_index',command(kind=1,flag5bb=128,boundX=bounds[0],boundY=bounds[1],boundW=bounds[2],boundH=bounds[3],rectX=rect[0],rectY=rect[1],rectW=rect[2],rectH=rect[3],count=count,frame=frame,width=-61,heightCanvas=-71,pointX=2147483647,pointY=-2147483648,emptyX=-3,emptyY=7,emptyW=9,emptyH=11)
 for mutation in range(1,9):
  for kind in (1,2,6,15):
   for mode in (0,1,2):yield 'child_mutations_saved_vs_live',command(mutation=mutation,kind=kind,mode=mode,building1386=0 if mutation==2 else 255,cellConverter=0 if mutation==8 else 2,ownerPredicate=0 if mutation==5 else 1,objectKind1=21,flag5bb=128 if kind==1 else 0,pC0=255,p32c=255)
 rng=random.Random(0x6d1510)
 for _ in range(200):
  word=lambda:rng.randint(-2**31,2**31-1)
  yield 'seeded_branch_width_wrapping',command(kind=rng.choice((1,2,6,15,99)),mode=rng.choice((-1,0,1,2,3,4,5,6)),building1386=rng.choice((0,128)),field1bc=word(),p1bc=rng.choice((0,128)),p1c0=rng.choice((0,255)),flag5bb=rng.choice((0,128)),typeB48=rng.choice((0,0,128)),shadow=rng.choice((0,255)),ownerPredicate=rng.choice((0,128)),objectKind1=rng.choice((0,21)),objectKind2=rng.choice((0,37)),cellConverter=rng.randrange(5),initConverter=rng.randrange(5),ownedHousePredicate=rng.choice((0,255)),pC0=rng.choice((0,128)),p32c=rng.choice((0,255)),flagsXor=word(),flagsD8=word(),statusAdd=word(),raw8=rng.choice((0,1,128,256,-1)),gradient=rng.choice((-1,0,2)),adjust=word(),light=word(),extra=word(),tail0=word(),tailX=word(),tailY=word(),mask=rng.choice((0,0,-1,word())),pointX=word(),pointY=word(),height=word(),depth=word(),flag37c=rng.choice((0,255)),count=rng.choice((-32768,-3,0,1,2,6,32767)),mutation=rng.randrange(9))
 for mode in range(8):yield 'null_image_before_all_children',command(image=0,mode=mode)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_sprite.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+25)
 for j in range(0,i,4):
  require(1<=int(row[j])<=8)
  for v in row[j+1:j+4]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_sprite import TechnoSpriteOracle
  oracle=TechnoSpriteOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x6d1510','0x6a2970','0x77f110','0x49eea0')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno sprite parent sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
