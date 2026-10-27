# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pinned raw/RLE auxiliary sprite depth clipping and signed spans."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from collections import Counter
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
ORIGINAL=('tests/compare_sprite_depth_pixels.py','tests/original_props.py','tests/original_scenery.py','tests/original_sprite_depth_pixels.py')
NATIVE=('src/render/Scenery.cpp','src/render/Scenery.hpp','src/render/Composition.cpp','src/render/Composition.hpp','src/render/SurfaceFill.hpp','src/assets/Shp.cpp','src/assets/Shp.hpp','tests/scenery_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(auxiliary_depth_nonnull=True,signed_depth_bytes=True,rle_row_phase_bypass=True,raw_intersection_only=True,nonnegative_adjusted_origin=True,actual_complete_wrapper=True,actual_raw_rle_spans=True,building_flags_2000=True,body_gradients_zero_two=True,synthetic_surfaces_and_palettes=True,converter_lifetime=False,actor_parent=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Sprite auxiliary-depth pixel evidence/domain differs')
def verify(data):
 require(len(data)==4485392 and hashlib.sha256(data).hexdigest()==PATCHED_EXPECTED)
 p=pefile.PE(data=data);ranges={0x49eea0:1275,0x4350c0:1137,0x485d60:676,0x48be80:415,0x48a6c0:221,0x489220:225,0x487ae0:109}
 result={}
 for a,n in ranges.items():
  raw=p.get_data(a-0x400000,n);instructions=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(raw,a))
  require(sum(i.size for i in instructions)==n)
  result[hex(a)]=dict(bytes=n,instructions=len(instructions),sha256=hashlib.sha256(raw).hexdigest())
 require(p.get_data(0x49f398-0x400000,3)==b'\xc2\x34\x00')
 return dict(ranges=result,gradient_table_sha256=hashlib.sha256(p.get_data(0x7ce168-0x400000,72)).hexdigest())
def scenarios():
 for fmt in (1,3):
  for flags,gradient in ((0x6e00,0),(0x6e00,2),(0x6e01,0)):
   for loc in range(8):
    for variant in range(10):yield f'aux_raw_rle_clip_{fmt}',[fmt,flags,gradient,loc,variant%4,fmt*1000+loc*41+variant*73,variant]
ASSET=None
def auxiliary(variant):
 if variant==8:return ASSET
 w,h=19,17
 values=(0,1,127,128,255)
 pixels=bytes(values[variant] if variant<5 else values[(x*3+y)%5] for y in range(h) for x in range(w))
 return struct.pack('<4H4H4I',0,25,23,1,2,3,w,h,1,0,0,32)+pixels
def offsets(variant):return ((10,4),(15,12),(28,19),(10,4),(15,12),(28,19),(50,50),(10,4),(198,446),(10,4))[variant]
def fixture(fmt):
 w,h=17,13;pixels=bytes((0 if (x+y)%9<4 else (x*13+y*17)%255+1) for y in range(h) for x in range(w))
 if fmt==1:payload=pixels
 else:
  payload=bytearray()
  for row in range(h):
   encoded=bytearray()
   line=pixels[row*w:(row+1)*w];x=0
   while x<w:
    if line[x]:encoded.append(line[x]);x+=1
    else:
     end=x+1
     while end<w and not line[end]:end+=1
     encoded.extend(bytes((0,end-x)));x=end
   payload+=struct.pack('<H',len(encoded)+2)+encoded
 return struct.pack('<4H',0,31,25,2)+struct.pack('<4H4I',3,5,w,h,fmt,0,0,56)*2+payload
def inputs(cmd):
 require(len(cmd)==7);fmt,flags,gradient,loc,lighting,seed,variant=cmd
 require(0<=variant<10)
 require(fmt in (1,3) and (flags,gradient) in ((0x4e00,2),(0x4e01,0),(0x6e00,2),(0x6e00,0),(0x6e01,0),(0x4e00,0)) and 0<=loc<8 and 0<=lighting<4 and 0<=seed<10000)
 rng=random.Random(seed);w,h=40,36
 location=((20,18),(0,0),(-4,13),(39,35),(60,60),(20,-3),(9,27),(25,19))[loc]
 clip=(0,0,w,h) if loc%2==0 else (3,4,31,25)
 z=(-3,-12,-72,0)[lighting];brightness=(0,500,1000,3000)[lighting]
 colors=[rng.randrange(65536) for _ in range(w*h)];depth=[rng.choice((0,65535,32700+rng.randrange(100))) for _ in colors];alpha=[rng.randrange(256) for _ in colors];palette=[rng.randrange(65536) for _ in range(53*256)]
 return fmt,flags,gradient,flags&1,w,h,location,clip,z,brightness,colors,depth,alpha,palette
def native_command(cmd,folder):
 fmt,flags,gradient,frame,w,h,loc,clip,z,light,colors,depth,alpha,palette=inputs(cmd)
 return ' '.join(map(str,['H',folder/f'format-{fmt}.shp',w,h,frame,*loc,*clip,flags,z,gradient,light,folder/f'aux-{cmd[-1]}.shp',int(cmd[-1]==9),*offsets(cmd[-1]),*colors,*depth,*alpha,*palette]))
def wordhash(v):return hashlib.sha256(struct.pack('<'+'H'*len(v),*v)).hexdigest()
def identities(a):
 paths=python_closure(ROOT/'tests/compare_sprite_depth_pixels.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE},native_render_data=hash_file(a.render_data),auxiliary_asset_sha256=hash_file(a.asset))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'] and e['evidence']['identities']['auxiliary_asset_sha256']==current['auxiliary_asset_sha256'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  inputs(cmd);require(len(row)==2 and all(isinstance(v,str) and len(v)==64 and set(v)<=set('0123456789abcdef') for v in row))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','asset'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic()
 global ASSET
 raw=a.asset.read_bytes();require(hashlib.sha256(raw).hexdigest()=='f91653da1f2c4b8e823a7db6ffb5e4c0fc003a9e74eef920adcad2feec739490')
 normalized=bytearray(raw);offset=struct.unpack_from('<I',raw,28)[0];width,height=struct.unpack_from('<2h',raw,2)
 for at in range(offset,offset+width*height):
  if normalized[at]:normalized[at]=(normalized[at]-0x41)&255
 require(hashlib.sha256(normalized[offset:offset+width*height]).hexdigest()=='c83c79123de049c0fd63de84ba74c0f29965638754b1f46104747fc7376e4397')
 ASSET=bytes(normalized);current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json');folder=source.parent
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());folder.mkdir(parents=True)
  from original_sprite_depth_pixels import SpriteDepthPixelsOracle
  from unicorn import UC_HOOK_CODE
  oracle=SpriteDepthPixelsOracle(a.exe,[0]*768,allow_patched=True);counts=Counter()
  targets=(0x49eea0,0x4350c0,0x48be80,0x48a6c0,0x489220,0x487ae0)
  def entered(u,address,size,ctx):
   if address in targets:counts[hex(address)]+=1
  hook=oracle.u.hook_add(UC_HOOK_CODE,entered);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   fmt,flags,gradient,frame,w,h,loc,clip,z,light,colors,depth,alpha,palette=inputs(cmd)
   result=oracle.draw_depth(fixture(fmt),auxiliary(cmd[-1]),int(cmd[-1]==9),offsets(cmd[-1]),frame,w,h,loc,clip,flags,z,gradient,light,colors,depth,alpha,palette)
   commands.append(cmd);labels.append(label);expected.append([wordhash(v) for v in result])
  generation=time.monotonic()-now;oracle.u.hook_del(hook);require(all(counts[hex(k)] for k in targets));require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),actual_entries=dict(counts),audited_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 for fmt in (1,3):
  path=folder/f'format-{fmt}.shp';blob=fixture(fmt)
  if path.exists():require(path.read_bytes()==blob)
  else:
   require(not a.expectations);path.write_bytes(blob)
 for variant in range(10):
  path=folder/f'aux-{variant}.shp';blob=auxiliary(variant)
  if path.exists():require(path.read_bytes()==blob)
  else:
   require(not a.expectations);path.write_bytes(blob)
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(native_command(cmd,folder) for cmd in commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 require(current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Sprite auxiliary-depth pixel cases PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
