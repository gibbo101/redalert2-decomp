#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell color policy alone and in terrain/projection, with original reuse."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_radar_terrain as terrain
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_resource_color import verify
NATIVE=('src/assets/MapOverlay.cpp','src/assets/MapOverlay.hpp','src/render/PreparedRadarAssets.hpp','src/assets/OverlayImage.hpp','src/render/OverlayRadarColor.hpp','src/assets/OverlayTypeInputs.hpp','src/sim/CellResidentSearch.hpp','src/sim/CellResidentKind6.hpp',*terrain.NATIVE,'src/render/CellRadarColor.hpp','tests/radar_cell_color_fixture.hpp','tests/cell_radar_color_vectors.cpp','src/assets/TileVariants.cpp')
ORIGINAL=('tests/original_radar_resource_color.py','tools/verify_radar_resource_color.py','tests/compare_radar_resource_color.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_resource_color.py')
FLAGS=dict(complete_cell_color_parent=True,actual_initialized_variant_image_helpers_scale_ftol=True,joined_terrain_projection=True,actual_resident_search=True,virtual_kind_and_authored_lists_supplied=True,actual_overlay_color_and_full_demand_getter=True,crt_file_storage_lifetime_supplied=True,actual_resource_classifier_shared_overlay=True,resource_registry_and_missing_log_supplied=True,image_install_leaf_supplied=True,authored_tmp_and_animation_and_scale_inputs=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Cell radar color input/evidence differs')
def profile(**kw):
 defaults=dict(resident=0,flags=0,tile=0,overlay=-1,data=0,sub=0,variants=1,raw=0,mode=0,frames=0,nulls=0,force=0,resource=-1,lazy=0,scale=0x3f800000);require(not set(kw)-set(defaults));defaults.update(kw);return list(defaults.values())
def validate_profile(p):
 require(len(p)==15);r,flags,tile,overlay,data,sub,variants,raw,mode,frames,nulls,force,resource,lazy,scale=p
 require(r in (0,1) and 0<=flags<2**32 and tile in (0,1,65535) and -1<=overlay<=250 and 0<=data<=255 and 0<=sub<=3 and 1<=variants<=4 and 0<=raw<=9 and 0<=mode<=3 and -1<=frames<=4 and 0<=nulls<=15 and force in (0,1) and -1<=resource<=2 and lazy in (0,1) and 0<=scale<2**32 and (frames>=0 or data<=3));return p
def standalone(seed,alias,p,resources):return 'R '+' '.join(map(str,[seed,alias,*p,len(resources),*[v for row in resources for v in row]]))
def joined(seed,mode,p,resources,region=(0,0,8,8)):
 return 'E '+' '.join(map(str,[mode,3,0,0,8,8,*region,seed,-1,3,1537,1,3,1026,2,2,515,3,1,*p,len(resources),*[v for row in resources for v in row]]))
def parse(cmd):
 p=cmd.split();require(p and p[0] in ('R','E'))
 if p[0]=='R':
  end=18;v=list(map(int,p[1:end]));require(len(v)==17 and 0<=v[0]<=255 and v[1] in (0,1));f=dict(kind='K',seed=v[0],alias=v[1],profile=validate_profile(v[2:]))
 else:
  n=int(p[13]);base=14+n*3;end=base+15
  f=dict(kind='C',terrain=terrain.parse('T '+' '.join(p[1:base])),profile=validate_profile(list(map(int,p[base:end]))))
 require(len(p)>end);count=int(p[end]);require(0<=count<=8 and len(p)==end+1+count*6);v=list(map(int,p[end+1:]));require(all(-2147483648<=x<=2147483647 for x in v));f['resources']=[v[i:i+6] for i in range(0,len(v),6)];return f
def scenarios():
 # Preserve the earlier color domain with actual classifier execution replacing
 # the supplied resource answer. All fixture tables remain original inputs.
 import compare_radar_demand_color as old
 stock=[[0,127,12,0,9,25],[1,147,12,0,9,50]]
 for label,cmd in old.scenarios():
  yield 'joined_resource_'+label,('R' if cmd[0]=='M' else 'E')+cmd[1:]+' '+' '.join(map(str,[len(stock),*[v for row in stock for v in row]]))
 edges=[-2147483648,-1,0,1,126,127,128,138,139,2147483647]
 tables=[[],[[7,127,12,0,9,25]],[[-1,127,12,0,9,25]],[[2,127,0,12,9,25]],
  [[-1,127,12,0,9,25],[9,127,12,0,9,25]],[[9,127,12,0,9,25],[-1,127,12,0,9,25]]]
 for start in edges:
  for images,slopes in ((0,0),(1,1),(-1,12),(2147483647,2147483647),(-2147483648,-1)):
   tables.append([[7,start,images,slopes,0,-2147483648]])
 for i,rows in enumerate(tables):
  for overlay in (126,127,138,139):
   p=profile(overlay=overlay,mode=1,sub=2,lazy=1)
   for alias in (0,1):yield 'classifier_signed_ranges_first_match_and_missing',standalone((i*31+overlay)&255,alias,p,rows)
  for mode in (0,1):yield 'classifier_inside_complete_terrain_projection',joined((i*31+17)&255,mode,profile(overlay=127,mode=1,sub=2,lazy=1),rows)
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('R')==1);at=row.index('R');n=15 if f['kind']=='K' else 17;require(len(row)-at==n);v=list(map(int,row[at+1:]));require(row.count('D')>0)
 if f['kind']=='K':require(all(0<=x<=255 for x in v[:6]) and all(x in (0,1) for x in v[6:]) and row.count('F')==4 and row.count('D')==1)
 else:require(v[12]==0 and all(0<=x<2**64 for x in v[13:]) and row.count('Q')==row.count('D') and row.count('F')==4*row.count('D') and row.count('K')==f['terrain'][0])
 i=0
 while i<at:
  n=dict(G=2,X=4,U=1,V=6,Q=2,C=4,P=4,S=4,W=2,H=2,K=3,N=1,D=3,L=2,J=3,O=3,E=2,Y=2,Z=2,F=5).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
 require(i==at)
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_resource_color.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-radar-color-vectors');p.add_argument('--terrain-native',type=Path,default=ROOT/'build/native/radar-terrain-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runners={str(path):hash_file(path) for path in (a.native,a.terrain_native)}
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_resource_color import RadarResourceColorOracle
  oracle=RadarResourceColorOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.audit_calls==len(commands) and oracle.counts['color_root']>len(commands) and oracle.counts['variant']>0 and oracle.counts['0x63cdf0']>0 and oracle.counts['actual_resident']==oracle.counts['color_root'] and oracle.counts['supplied_kind']>0 and oracle.counts['actual_overlay']>0 and oracle.counts['overlay_getter']==oracle.counts['actual_overlay'] and oracle.counts['file_load']>0 and oracle.counts['file_cleanup']==2*oracle.counts['file_load'] and oracle.counts['image_stores']==2*oracle.counts['file_load'] and oracle.counts['actual_resource']>0 and oracle.counts['resource_return']==oracle.counts['actual_resource'] and oracle.counts['missing_resource_log']>0 and not oracle.counts['supplied_resource'] and not oracle.counts['supplied_overlay_color'] and not oracle.counts['supplied_resident'] and not oracle.counts['supplied_colors'] and current==identities(a) and runners=={str(path):hash_file(path) for path in (a.native,a.terrain_native)})
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();report.parent.mkdir(parents=True,exist_ok=True);actual=[None]*len(commands)
 for kind,path in (('R',a.native),('E',a.terrain_native)):
  indexes=[i for i,c in enumerate(commands) if c.startswith(kind+' ')];run=subprocess.run([str(path)],input='\n'.join(commands[i] for i in indexes)+'\n',capture_output=True,text=True);report.with_suffix('.'+kind+'.stdout').write_text(run.stdout);report.with_suffix('.'+kind+'.stderr').write_text(run.stderr);require(run.returncode==0);rows=[x.split() for x in run.stdout.splitlines()];require(len(rows)==len(indexes))
  for i,row in zip(indexes,rows):actual[i]=row
 require(actual==expected);comparison=time.monotonic()-now
 for path in (a.native,a.terrain_native):require('guards PASS' in subprocess.check_output([str(path),'--guards'],text=True))
 require(current==identities(a) and runners=={str(path):hash_file(path) for path in (a.native,a.terrain_native)});hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runners,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Joined radar resource color sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
