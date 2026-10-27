#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original rectangle/Cell admission and direct permission comparisons."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_nearby_cell_admission import verify
NATIVE=('tests/nearby_cell_admission_vectors.cpp','src/assets/MapCellChildren.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/nearby_cell_admission/CMakeLists.txt','tests/original_nearby_cell_admission.py',
 'tests/compare_nearby_cell_admission.py','tests/test_nearby_cell_admission_evidence.py','tools/verify_nearby_cell_admission.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_rectangle_and_Cell_admission=True,actual_direct_Cell_permission=True,
 actual_inline_shared_map_lookup=True,supplied_zone_resolver=True,supplied_initial_records_and_associations=True,
 diagnostic_mutations_not_gameplay=True,nearby_parent_joined=False,Unit_Scatter_joined=False,
 Advance6_joined=False,Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
SCALARS='mode op x y width height speed zone movement level alternate disallow ignore_low ignore_middle elevation dimension0 origin_x origin_y shape_width shape_height zone_result mutation'.split()
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Cell admission evidence/input')
def defaults():
 cells=[[y*512+x,x,y,0,0,0,0,0,0,-1] for x in range(49,53) for y in range(49,53)]
 cells.append([-1,-7,5,0,0,0,0,0,0,-1])
 return dict(zip(SCALARS,(0,0,50,50,1,1,1,-1,0,-1,0,0,0,0,1,2,0,0,100,100,7,0)),cells=cells,speeds=[0x3f800000]*108,overlays=[[0,0,0],[1,0,1],[1,1,0],[1,128,255]])
def command(**kw):
 c=defaults();c.update(kw)
 return 'A '+' '.join(map(str,[*[c[k] for k in SCALARS],len(c['cells']),*itertools.chain.from_iterable(c['cells']),len(c['speeds']),*c['speeds'],len(c['overlays']),*itertools.chain.from_iterable(c['overlays'])]))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='A')
 try:v=list(map(int,t[1:]))
 except ValueError:raise ValueError('Malformed Cell admission integer') from None
 require(len(v)>=len(SCALARS)+1);c=dict(zip(SCALARS,v));at=len(SCALARS);count=v[at];at+=1
 require(1<=count<=128 and len(v)>at+10*count);c['cells']=[v[i:i+10] for i in range(at,at+10*count,10)];at+=10*count
 n=v[at];at+=1;require(1<=n<=4096 and len(v)>at+n);c['speeds']=v[at:at+n];at+=n
 n=v[at];at+=1;require(n==4 and len(v)==at+3*n);c['overlays']=[v[i:i+3] for i in range(at,len(v),3)]
 i32=lambda n:-2147483648<=n<=2147483647;word=lambda n:-32768<=n<=32767;u32=lambda n:0<=n<=0xffffffff
 require(all(i32(c[k]) for k in SCALARS if k!='alternate') and u32(c['alternate']) and 0<=c['mode']<4 and 0<=c['op']<=2 and c['mutation'] in (0,1))
 require(word(c['x']) and word(c['y']) and all(0<=c[k]<=255 for k in ('disallow','ignore_low','ignore_middle','elevation')))
 slots=set()
 for i,row in enumerate(c['cells']):
  slot,x,y,level,slope,flags,land,occupation,elevated,overlay=row
  require(-1<=slot<262144 and (slot==-1)==(i==count-1) and word(x) and word(y) and -128<=level<=127 and 0<=slope<=255)
  require(all(u32(n) for n in (flags,occupation,elevated)) and i32(land) and -1<=overlay<4)
  if slot!=-1:require(slot not in slots);slots.add(slot)
 require(all(u32(n) for n in c['speeds']) and all(r[0] in (0,1) and all(0<=n<=255 for n in r[1:]) for r in c['overlays']))
 # Bound research loops and actual original speed accesses; these are harness
 # domains, not replacement gameplay. Native guards are independently exercised.
 require(c['op']!=1 or c['width']<=8 and c['height']<=8)
 signed=lambda n:(n+0x80000000)%0x100000000-0x80000000
 require(c['speed']==4 or all(0<=signed(row[6]*9+c['speed'])<len(c['speeds']) for row in c['cells']))
 if c['speed']!=4 and (c['mutation'] or any(row[9] in (2,3) for row in c['cells'])):require(0<=c['speed']<len(c['speeds']))
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1)
def generate(a):
 from original_nearby_cell_admission import NearbyCellAdmissionOracle
 o=NearbyCellAdmissionOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x478760)
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed Cell admission case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 def cell(**changes):
  rows=defaults()['cells'];keys='slot x y level slope flags land occupation elevated overlay'.split()
  for k,v in changes.items():rows[0][keys.index(k)]=v
  return rows
 for mode,op in itertools.product(range(4),range(3)):add('roots',mode=mode,op=op)
 for flags,base,level,alt in itertools.product((0,0x100,0x1100),(-128,-2,0,127),(-1,-128,-124,-2,0,4,127,131),(0,1,256,0x800000ff)):
  add('level_bridge_and_elevated_selection',cells=cell(flags=flags,level=base,occupation=0x40,elevated=0),level=level,alternate=alt)
 for occupation,low,middle in itertools.product(range(256),(0,128),(0,255)):
  add('all_occupation_bits_and_masks',cells=cell(occupation=occupation),ignore_low=low,ignore_middle=middle)
 for occupation in (0x100,0x10000,0x80000000,0xffffff00,0xffffffff):
  add('only_low_occupation_byte',cells=cell(occupation=occupation))
  add('only_low_elevated_byte',cells=cell(flags=0x100,elevated=occupation))
 for zone,movement,overlay in itertools.product((-1,0,7,65535),(0,1,2,3,4,5,8,9),(-1,0,1,2,3)):
  add('zone_and_overlay_wall_policy',zone=zone,movement=movement,cells=cell(overlay=overlay),zone_result=7)
 for mode,bits,flags in itertools.product(range(4),(0,0x80000000,1,0x80000001,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7fc00001,0x7f800001),(0,0x100)):
  speeds=defaults()['speeds'];speeds[1]=bits;add('zero_unordered_not_positive',mode=mode,speeds=speeds,cells=cell(flags=flags))
 for speed in (0,4,8,9,17,107):add('raw_speed_index_and_bypass',speed=speed,zone=0,zone_result=7,cells=cell(occupation=255,overlay=2),level=999)
 for speed,land in ((-1,1),(-9,1),(9,0),(1,477218589)):
  rows=defaults()['cells']
  for row in rows:row[6]=land
  add('combined_signed_wrapped_speed_index',speed=speed,cells=rows)
 for zone in (-1,7,8):
  for level in (-2,-1,0,2):add('diagnostic_zone_late_Cell_reads',zone=zone,zone_result=7,mutation=1,level=level,ignore_low=1,ignore_middle=1)
 for width,height in ((-1,3),(0,3),(3,-1),(3,0),(1,1),(2,3),(3,2),(8,8)):
  for disallow in (0,1,255):add('rectangle_order_and_empty_dimensions',op=1,width=width,height=height,disallow=disallow)
 for index in range(16):
  rows=defaults()['cells'];rows[index][7]=1;add('rectangle_first_occupied_return',op=1,x=49,y=49,width=4,height=4,cells=rows)
  rows=defaults()['cells'];rows[index][9]=0;add('rectangle_disallowed_overlay_before_speed4',op=1,x=49,y=49,width=4,height=4,cells=rows,disallow=1,speed=4)
 for x,y in ((32767,0),(-32768,0),(0,32767),(0,-32768),(-1,1),(512,-1)):
  add('rectangle_word_wrap_alias_fallback',op=1,x=x,y=y,width=2,height=2)
 for zone in (-1,7,8):add('rectangle_actual_nested_zone_mutation',op=1,width=2,height=2,zone=zone,mutation=1,ignore_low=255)
 for elevation,slope,level in itertools.product((0,1,128,255),(0,1,21,255),(-128,-1,0,127)):
  for x,y in ((0,0),(1,1),(2,2),(4,4),(5,4),(50,50),(-32768,32767),(32767,-32768)):
   add('direct_permission_no_lookup_strict_bounds',op=2,elevation=elevation,cells=cell(x=x,y=y,level=level,slope=slope),shape_width=4,shape_height=4)
 for dimension,x,y,w,h in ((2147483647,0,0,1,1),(-2147483648,2147483647,-2147483648,2147483647,2147483647),(2,-2147483648,2147483647,-1,0)):
  add('permission_wrapped_geometry',op=2,dimension0=dimension,origin_x=x,origin_y=y,shape_width=w,shape_height=h)
 for i in range(100):
  rows=defaults()['cells']
  for row in rows:row[3]=rng.randint(-2,2);row[5]=rng.choice((0,0x100));row[7]=rng.choice((0,1,0x80,0x100));row[8]=rng.choice((0,0x20));row[9]=rng.randrange(-1,4)
  add('seeded_shared_rectangle',op=1,cells=rows,mode=i%4,width=rng.randrange(1,5),height=rng.randrange(1,5),movement=rng.choice((0,1,2,3,4,8)),disallow=rng.randrange(2),alternate=rng.choice((0,1,256)))
 for op in range(3):require(all(o.counts['top_return.'+str(op)+'.'+str(r)]>0 for r in (0,1)))
 require(all(o.counts[hex(a)]>0 for a in (0x4788ba,0x478820,0x47882d,0x47888e,0x478899,0x4788ad,0x550d5d,0x55a784,0x55a7dd,0x55a7e6)))
 require(o.counts['zone_service']>0 and o.counts['diagnostic_mutation']>0)
 require(all(o.counts['speed_compare.'+k]>0 for k in ('unordered','zero','negative','positive')))
 require(o.counts['elevated_occupation']>0 and o.counts['primary_occupation']>0)
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),full_arena_and_caller_guards=True,native_machine_store_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 require(p.returncode==0);rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Cell admission differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True);p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  require(a.output is not None and a.report is None);folder=private_path(a.output,a.exe);require(not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'Cell admission sequences PASS')
if __name__=='__main__':main()
