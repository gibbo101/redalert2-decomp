#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual overlay-bearing two-pass map preparation on shared Cells."""
import argparse,configparser,json,random,struct,subprocess,time
from pathlib import Path
import pefile
import compare_resident_map_preparation as terrain
import compare_map_wall_owner as wall
from compare_resident_cell import SOURCES as CELL_SOURCES
from compare_resource_type_inputs import SOURCES as RESOURCE_TYPE_SOURCES
from compare_resource_map_inputs import initialize
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_resident_map_finalization import verify
SOURCES=tuple(dict.fromkeys((*terrain.SOURCES,*wall.SOURCES,*CELL_SOURCES,*RESOURCE_TYPE_SOURCES,
 'tests/compare_resource_map_inputs.py',
 'src/assets/ResidentMapFinalization.hpp','src/assets/ResidentMapFinalization.cpp',
 'src/assets/MapOverlay.cpp','tests/resident_map_finalization_vectors.cpp',
 'tests/compare_resident_map_finalization.py','tests/original_resident_map_finalization.py',
 'tests/compare_map_overlay_loading.py','tools/prepare_overlay_loading_fixture.py',
 'tools/verify_resident_map_finalization.py',
 'src/assets/ResidentMapFloor.hpp','src/assets/ResidentMapFloor.cpp',
 'src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp',
 'src/render/UnitBaseDepth.hpp','src/render/UnitBaseDepth.cpp',
 'src/render/PreparedFootDepth.hpp','src/render/PreparedFootDepth.cpp',
 'src/render/FootDepth.hpp','src/render/FootDepth.cpp')))
def command(common,shape,types,cells,overlays,resources,frames,buildings):
 return 'G '+' '.join(map(str,[*common,*shape,len(types),*[n for r in types for n in r],len(cells),*[n for r in cells for n in r],len(overlays),*[n for r in overlays for n in r],len(resources),*[n for r in resources for n in r],*frames,len(buildings),*[n for r in buildings for n in r]]))
def parse(cmd):
 c=cmd.split();assert c[0]=='G';v=list(map(int,c[1:]));common=v[:61];shape=v[61:66];at=66;count=v[at];at+=1;assert 0<count<=1024;types=[]
 for _ in range(count):
  row=v[at:at+5];assert len(row)==5;end=at+5+row[1]*row[2]*6;types.append(v[at:end]);at=end
 count=v[at];at+=1;assert 0<=count<=16384;cells=[v[i:i+17] for i in range(at,at+count*17,17)];at+=count*17
 count=v[at];at+=1;assert 0<=count<=255;overlays=[v[i:i+7] for i in range(at,at+count*7,7)];at+=count*7
 for row in overlays:assert len(row)==7 and 0<=row[0]<=11 and all(0<=n<=255 for n in row[1:])
 for row in cells:assert len(row)==17 and -1<=row[14]<len(overlays) and all(-2147483648<=n<=2147483647 for n in row[15:])
 count=v[at];at+=1;assert 0<=count<=8;resources=[v[i:i+6] for i in range(at,at+count*6,6)];at+=count*6
 for row in resources:assert len(row)==6 and 0<=row[0]<count and 0<=row[1]<len(overlays) and 1<=row[4]<=2147483647 and all(-2147483648<=n<=2147483647 for n in row)
 frames=v[at:at+9];at+=9;assert len(frames)==9 and all(0<=n<=255 for n in frames)
 count=v[at];at+=1;assert 0<=count<=64 and len(v)==at+count*10;buildings=[v[i:i+10] for i in range(at,len(v),10)]
 wall.parse(wall.command('W',0,1,0,0,0,buildings))
 # Reuse strict general resident metadata/geometry/Cell checks with projected
 # ordinary fields. These inputs remain host fixtures, not original startup.
 land=[[0,0,common[50+i] if i<11 else 0,0,0,0,0,0,0] for i in range(12)]
 terrain.parse(terrain.command(common,land,shape,types,[r[:14] for r in cells]))
 return common,shape,types,cells,overlays,resources,frames,buildings

def identities(a):
 fixture=json.loads(a.overlay_fixture.read_text())
 if any(hash_file(Path(p))!=h for p,h in fixture['source_hashes'].items()):raise ValueError('Finalization owned overlay source changed')
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'render_data_sha256':hash_file(a.render_data),'terrain_input_snapshot_sha256':hash_file(a.terrain_fixture),
  'overlay_input_snapshot_sha256':hash_file(a.overlay_fixture),'owned_source_hashes':fixture['source_hashes']}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map finalization engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Map finalization source/inspection/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map finalization counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map finalization command') from None

def generate(a):
 from original_resident_map_finalization import ResidentMapFinalizationOracle
 from compare_map_overlay_loading import parse as overlay_parse
 from prepare_overlay_loading_fixture import parse_ini
 o=ResidentMapFinalizationOracle(a.exe);rng=random.Random(0x46494e41);p=pefile.PE(str(a.exe));frames=o.frames
 widths=struct.unpack('<22i',p.get_data(0x7cfc70-0x400000,88));heights=struct.unpack('<22i',p.get_data(0x7cfcc8-0x400000,88))
 commands=[];expected=[];labels=[];groups={};totals=[];owned=[]
 def building(i,owner=7):return [1,255,2,owner,i,widths[i],heights[i],512,768,0]
 def add(label,*args):
  cmd=command(*args);args=parse(cmd);result=o.run(*args);commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1;totals.append(int(result[-1]))
 for case in range(32):
  width=3+case%4;height=2+(case//4)%3;types=[]
  for i in range(64):
   columns,rows=(2,2) if i%3 else (1,1);row=[int((i+case)%7!=0),columns,rows,60,rng.choice([30,45,60])]
   for j in range(columns*rows):row.extend([int((i+j)%11!=0),rng.choice([0,2,6,8]),rng.randrange(7),rng.choice([-30,0,45]),rng.choice([-15,0,60]),rng.randrange(2)])
   types.append(row)
  overlays=[[4,0,1,0,1,0,0],[0,0,0,1,0,0,0],[4,0,255,1,1,0,0],[9,0,0,1,0,0,0],[5,1,0,0,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[6,0,0,0,0,1,1]]
  resources=[[0,1,3,0,9,2147483647 if case%2 else 25],[1,6,1,0,3,-2147483648]]
  cells=[]
  for y in range(width+height+1):
   for x in range(width+height+1):
    if x+y>width and abs(x-y)<width and x+y<=width+2*height:
     cells.append([x,y,rng.randrange(70),rng.randrange(6),rng.randrange(13),rng.getrandbits(32),-1,0,rng.randrange(7),rng.randrange(256),rng.randrange(256),rng.randrange(256),17,rng.getrandbits(32),rng.randrange(-1,8),41,rng.randrange(-1000,1000)])
  hole=-1 if case%8 else len(cells)//2
  common=[width,height,case,hole,case%3,100,100,100,86,0,28,*[n%10 for n in range(16)],*([-1]*15 if case<16 else [10,20,1,2,3,4,5,6,7,8,9,11,12,13,14]),*o.initial_directions,*[terrain.floatbits(rng.choice([0,0.005,0.01,1])) for _ in range(11)]]
  buildings=[building(0),building(3,-7),building(21,9)];buildings[2][:3]=[case%2,2,128]
  if case%5==0:buildings=[]
  add('shared_overlay_parent_resource_wrap_cell_clearing_and_wall_owner',common,[width,0,0,width,height],types,cells,overlays,resources,frames,buildings)
 # Initial terrain/TMP and decoded overlay data are pinned owned fixture inputs;
 # this does not execute their reader/actor loading/startup parents in this guest.
 e=json.loads(a.terrain_fixture.read_text());validate_receipt(e,json.loads((a.terrain_fixture.parent/'report.json').read_text()),hash_file(a.terrain_fixture))
 assert e['executable_sha256']==PATCHED_EXPECTED
 fixture=json.loads(a.overlay_fixture.read_text());_,v=overlay_parse('M '+' '.join(map(str,fixture['values'])))
 at=12+v[11]*4;count=v[at];at+=1+count;count=v[at];at+=1;overlay_by_slot=dict(zip(v[at:at+2*count:2],v[at+1:at+2*count:2]));at+=2*count;count=v[at];at+=1;data_by_slot=dict(zip(v[at:at+2*count:2],v[at+1:at+2*count:2]))
 rules=parse_ini(Path(next(p for p in fixture['source_hashes'] if p.endswith('rules.ini'))).read_bytes())
 def flag(name,key,default='no'):return int(rules.get(name,key,fallback=default).strip().lower().startswith(('1','t','y')))
 overlays=[]
 lands={'clear':0,'road':1,'water':2,'rock':3,'wall':4,'tiberium':5,'beach':6,'rough':7,'ice':8,'railroad':9,'tunnel':10,'weeds':11}
 for name in fixture['type_names']:
  tib=flag(name,'Tiberium');land=5 if tib else lands[rules.get(name,'Land',fallback='Clear').strip().lower()]
  overlays.append([land,flag(name,'Crushable'),flag(name,'Wall'),tib,flag(name,'NoUseTileLandType','yes'),flag(name,'IsRubble'),flag(name,'IsARock')])
 # Explicit selected-record transfer from a separately audited original type
 # guest; no startup parent or ordering claim. Native type projection already has
 # its independent differential suite; this parent's fixtures receive the fields.
 from original_resource_type_inputs import ResourceTypeInputOracle
 type_oracle=ResourceTypeInputOracle(a.exe)
 resource_rows=[[int(key),len(name.strip()),1,int(rules.get(name,'Image')),int(rules.get(name,'Value'))] for key,name in rules['Tiberiums'].items()]
 resources,resource_snapshot=initialize(type_oracle,resource_rows,0)
 for cmd in e['commands'][-3:]:
  common,land,shape,types,base_cells=terrain.parse(cmd);cells=[]
  for row in base_cells:
   slot=row[1]*512+row[0];r=row.copy();r[10]=data_by_slot.get(slot,0);cells.append([*r,overlay_by_slot.get(slot,-1),-1,0])
  add('owned_all_positions_primary_TMP_and_660_decoded_overlays_supplied_initial_actor_height_type_records_cliff_'+str(common[4]),common,shape,types,cells,overlays,resources,frames,[building(0)])
  owned.append({'records':len(cells),'overlays':sum(r[14]!=-1 for r in cells),'types':len(types),'resident_types':sum(r[0] for r in types),'cliff_mode':common[4],'resource_total':totals[-1]})
 return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_entries':o.entries,'selected_stores':o.stores,'buffer_stores':o.buffer_stores,'missing_resource_logs':o.logs,'wall_owner_calls':o.owner_calls,'actual_distances':o.distances,'resource_totals':totals,'owned':owned,'initial_type_actor_height_terrain_and_resource_fields_supplied':True,'palette_disabled':True,'earlier_reader_and_original_startup_not_executed':True,'resource_selected_phase_snapshot':resource_snapshot,'separate_resource_phase_audits':type_oracle.audit_calls,'separate_resource_phase_entries':type_oracle.roots}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/resident-map-finalization-vectors')
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--terrain-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v6/expected.json');p.add_argument('--overlay-fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resident-finalization-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh finalization destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native finalization: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Finalization result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Finalization run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} shared overlay-bearing map finalization results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
