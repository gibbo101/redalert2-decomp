# SPDX-License-Identifier: GPL-3.0-or-later
"""Later two-pass map parent with actual shared resources/Cell/wall children."""
import hashlib
from original_map_preparation import (MAP,FALLBACK,CELLS,TYPES,REGISTRY,SLOTS,BUFF4,BUFF10,RULES,SCENARIO,FIELDS,STATE,pack)
from original_resident_map_preparation import ResidentMapPreparationOracle
from original_map_preparation import RANGES as OLD_RANGES
from original_foot_lit import words,ret
from verify_map_cell_children import LAT_GLOBALS
from verify_resident_map_finalization import verify,RANGES
from original_presentation import STOP
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
OVERLAYS=0x3600000;OVERLAY_REG=0x3640000;RESOURCES=0x3650000;RESOURCE_IMAGES=0x3651000;RESOURCE_REG=0x3654000
BUILD=0x3700000;BUILD_TYPES=0x3800000;HOUSES=0x3900000;COUNTRIES=0x3a00000;BUILD_REG=0x3b00000
SELECTED={**FIELDS,0x44:(19,4),0x11e:(20,1),0x50:(21,4)}
def digest(b):return hashlib.sha256(b).hexdigest()
class ResidentMapFinalizationOracle(ResidentMapPreparationOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(OVERLAYS,0x600000)
  self.entries.update({hex(a):0 for a in RANGES if a not in OLD_RANGES});self.logs=self.owner_calls=self.distances=self.buffer_stores=0;self.resource_returns=[]
  self.frames=list(self.u.mem_read(0x7d2c10,36))[::4]
  for a in {*set(RANGES).difference(OLD_RANGES),0x54b505,0x5d4c8b,0x4068f0,0x4706c0}:self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
 def block(self,u,a,n,ctx):
  if a in (STOP,0x4068f0,0x4706c0):return
  if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected finalization block {a:#x}/{n}')
 def cell_id(self,p):
  assert CELLS<=p<CELLS+self.count*512 and (p-CELLS)%512==0
  return (p-CELLS)//512
 def building_id(self,p):
  assert BUILD<=p<BUILD+len(self.buildings)*4096 and (p-BUILD)%4096==0
  return (p-BUILD)//4096
 def code(self,u,a,n,ctx):
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
  if a in RANGES and a not in OLD_RANGES:self.entries[hex(a)]+=1
  if a==0x476ba0:self.resource_cell=self.cell_id(ecx)
  elif a==0x472540:self.current_recalc=ecx
  elif a==0x54b505:
   value=u.reg_read(UC_X86_REG_EAX);self.events.extend([310,self.resource_cell,value]);self.resource_returns.append(value)
  elif a==0x5dc0b0:self.current_overlay=ecx;self.events.extend([312,ecx])
  elif a==0x4068f0:
   assert words(u,sp+4,1)==[0x7e8b60] and bytes(u.mem_read(sp+8,49))==bytes(49)
   self.events.extend([313,self.current_overlay]);self.logs+=1;ret(u,0,0)
  elif a==0x4724a0:
   self.owner_cell=self.cell_id(ecx);self.events.extend([311,self.owner_cell]);self.owner_calls+=1
  elif a==0x5d4c00:
   assert words(u,sp+4,1)==[CELLS+self.owner_cell*512];self.events.extend([314,self.building_id(ecx)]);self.distances+=1
  elif a==0x5d4c8b:self.events.extend([315,u.reg_read(UC_X86_REG_EAX)])
  elif a==0x6c7420:self.events.extend([316,self.building_id(ecx)])
  elif a==0x4706c0:
   ptr=words(u,sp+4,1)[0];self.events.extend([317,self.owner_cell,*words(u,ptr,2)]);ret(u,4,self.cell_heights[self.owner_cell]&0xffffffff)
  if a in OLD_RANGES or a==0x55a679:super().code(u,a,n,ctx)
 def run(self,common,shape,types,cells,overlays,resources,frames,buildings):
  width,height,seed,hole,cliff=common[:5];light=common[5:11];mapping=common[11:27];lat=common[27:42];directions=common[42:50];speeds=common[50:61]
  self.count=len(cells);self.cell_heights=[r[16] for r in cells];self.buildings=buildings;self.events=[];self.visits=[];capacity=(width+height+1)**2
  self.u.mem_write(CELLS,b'\xa5'*(len(cells)*512));self.u.mem_write(SLOTS,bytes(0x100000));self.u.mem_write(TYPES,bytes(len(types)*1024));image_region=self.install_types(types)
  for i,row in enumerate(cells):
   x,y,tile,sub,level,flags,tube,land,slope,extra,data,ice,passability,field30,overlay,owner,z=row;p=CELLS+i*512
   self.put(p,0x79db04);self.put(p+0x24,(x&65535)|((y&65535)<<16));self.put(p+0x3c,0);self.put(p+0x44,overlay);self.put(p+0x50,owner);self.put(p+0xe4,0);self.put(p+0x34,0);self.put(p+0x30,field30)
   for (off,n),v in zip(STATE,[tile,land,tube,sub,level,slope,flags,extra,data,ice,passability]):self.u.mem_write(p+off,(v&((1<<(8*n))-1)).to_bytes(n,'little'))
   if i!=hole:self.put(SLOTS+(y*512+x)*4,p)
  self.u.mem_write(FALLBACK,bytes(0x148));self.put(FALLBACK+0x24,0xffffffff);self.put(FALLBACK+0x38,65535);self.put(FALLBACK+0x44,-1);self.u.mem_write(FALLBACK+0x116,b'\xff\xff')
  self.put(MAP+0xf0,width);self.put(MAP+0xf4,height)
  for off,v in zip((0xf8,0xfc,0x100,0x104),shape[1:]):self.put(MAP+off,v)
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x64,BUFF4);self.put(MAP+0x68,capacity);self.put(MAP+0x6c,BUFF10)
  self.u.mem_write(BUFF4,b'\xa5'*(capacity*4)+b'\xa7'*64);self.u.mem_write(BUFF10,b'\xa5'*(capacity*10)+b'\xa7'*64)
  self.put(0xa40970,0);self.put(0xa40cd4,REGISTRY);self.put(0xa40ce0,len(types));self.put(0x8661d8,0);self.put(0x839848,RULES);self.u.mem_write(RULES,bytes(0x600));self.u.mem_write(RULES+0x584,bytes([cliff]))
  for a,v in zip(LAT_GLOBALS,lat):self.put(a,v)
  self.u.mem_write(0x851a70,pack(directions));self.u.mem_write(0x7de4ec,pack(mapping))
  for i,v in enumerate(speeds):self.put(0x850ea8+i*36,v)
  self.put(0xa3d290,SCENARIO);self.u.mem_write(SCENARIO,bytes(0x22c8))
  for off,v in zip((0x22ac,0x22b4,0x22b8,0x22bc,0x22c0,0x22c4),light):self.put(SCENARIO+off,v)
  self.u.mem_write(0xa51934,b'\0');self.put(0xa5193c,0);self.put(0xa6e828,0);self.put(0x839950,0)
  assert frames==self.frames
  for i,row in enumerate(overlays):
   land,*flags=row;p=OVERLAYS+i*1024;self.u.mem_write(p,bytes(1024));self.put(p+0x268,land);self.put(OVERLAY_REG+i*4,p)
   for off,v in zip((0x1fd,0x278,0x279,0x27c,0x284,0x285),flags):self.u.mem_write(p+off,bytes([v]))
  self.put(0xa35dec,OVERLAY_REG);self.put(0xac0b34,RESOURCE_REG);self.put(0xac0b40,len(resources))
  for i,(index,image,images,slopes,frame_count,value) in enumerate(resources):
   r=RESOURCES+i*256;t=RESOURCE_IMAGES+i*1024;self.u.mem_write(r,bytes(256));self.u.mem_write(t,bytes(1024));self.put(RESOURCE_REG+i*4,r)
   for off,v in ((0x98,index),(0xb8,value),(0xe0,t),(0xe4,frame_count),(0xe8,images),(0xec,slopes)):self.put(r+off,v)
   self.put(t+0x264,image)
  self.put(0xa40afc,BUILD_REG);self.put(0xa40b08,len(buildings));immutable=[]
  for i,row in enumerate(buildings):
   active,onmap,eligible,owner,foundation,w,h,x,y,z=row;b=BUILD+i*4096;t=BUILD_TYPES+i*4096;house=HOUSES+i*4096;c=COUNTRIES+i*4096
   assert words(self.u,0x7cfc70+foundation*4,1)==[w] and words(self.u,0x7cfcc8+foundation*4,1)==[h]
   for p,size in ((b,0x420),(t,0xc80),(house,0x40),(c,0x1b0)):self.u.mem_write(p,b'\xa5'*size);immutable.append((p,size))
   self.put(BUILD_REG+i*4,b);self.put(b,0x79cbbc);self.u.mem_write(b+0x74,bytes([onmap]));self.u.mem_write(b+0x7d,bytes([active]));self.put(b+0x1b4,house);self.put(b+0x418,t);self.u.mem_write(b+0x88,pack([x,y,z]));self.put(t+0xc78,foundation);self.put(house+0x30,owner);self.put(house+0x34,c);self.u.mem_write(c+0x1a7,bytes([eligible]))
  for p,count in ((BUILD_REG,len(buildings)),(OVERLAY_REG,len(overlays)),(RESOURCE_REG,len(resources))):self.u.mem_write(p+count*4,b'\xa7'*64);immutable.append((p,count*4+64))
  before=bytes(self.u.mem_read(CELLS,len(cells)*512));old_fallback=bytes(self.u.mem_read(FALLBACK,0x148))
  def stores(u,access,p,n,v,ctx):
   self.stores+=1
   if CELLS<=p<CELLS+len(cells)*512:
    index,off=divmod(p-CELLS,512);assert off in SELECTED and SELECTED[off][1]==n,(hex(p),n);self.events.extend([index,SELECTED[off][0],v&((1<<(8*n))-1)])
   elif p==FALLBACK+0x24:assert n==4;self.events.extend([0xffffffff,0,v&0xffffffff])
   else:
    for base,stride,tag in ((BUFF4,4,0xfffffffe),(BUFF10,10,0xfffffffd)):
     if base<=p<base+capacity*stride:
      assert n==1;index,off=divmod(p-base,stride);pos=words(u,self.current_recalc+0x24,1)[0];x=pos&65535;y=pos>>16;expected=(width+height+1)*y+x
      assert index==min(capacity-1,max(0,expected)) and off in ((0,1) if stride==4 else (8,));self.buffer_stores+=1;self.events.extend([tag,p-base,v&255])
  immutable.extend([(TYPES,len(types)*1024),(REGISTRY,len(types)*4+64),image_region,(SLOTS,0x100000),(MAP+0xf0,24),(MAP+0x64,16),(MAP+0x138,4),(RULES,0x600),(SCENARIO,0x22c8),(0xa3d290,4),(0x839848,4),(0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0xa40970,4),(0x851a70,32),(0x7de4ec,64),(0x850ea8,396),(0xa51934,1),(0xa5193c,4),(0xa6e828,4),(0x839950,4),*[(a,4) for a in LAT_GLOBALS],(0xa35dec,4),(0xac0b34,16),(0xa40afc,4),(0xa40b08,4),(OVERLAYS,len(overlays)*1024),(RESOURCES,len(resources)*256),(RESOURCE_IMAGES,len(resources)*1024),(0x7d2c10,36),(0x7cfc70,176),(0x817dfc,65536)])
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:self.checked_call(0x54b2e0,ecx=MAP,writes=[(CELLS,len(cells)*512),(MAP+0x108,16),(FALLBACK+0x24,4),(BUFF4,capacity*4),(BUFF10,capacity*10)],inputs=immutable)
  finally:self.u.hook_del(hook)
  total=self.u.reg_read(UC_X86_REG_EAX)
  after=bytearray(self.u.mem_read(CELLS,len(cells)*512));state=[]
  for i in range(len(cells)):
   p=CELLS+i*512;state.extend([words(self.u,p+0x24,1)[0],*[int.from_bytes(self.u.mem_read(p+off,n),'little') for off,n in ((0x38,4),(0xec,4),(0x116,2),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4),(0x11d,1),(0x11e,1),(0x119,1),(0x4c,4),(0x30,4),(0x34,4),(0x104,4),*[(0x108+j*2,2) for j in range(7)],(0x44,4),(0x50,4))]])
   for off,(_,n) in SELECTED.items():after[i*512+off:i*512+off+n]=before[i*512+off:i*512+off+n]
  assert bytes(after)==before
  final_fallback=bytearray(self.u.mem_read(FALLBACK,0x148));final_fallback[0x24:0x28]=old_fallback[0x24:0x28];assert bytes(final_fallback)==old_fallback
  for p,n in ((BUFF4,capacity*4),(BUFF10,capacity*10)):assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64
  cursor=words(self.u,MAP+0x108,4);cursor[-1]=(cursor[-1]-SLOTS)//4
  return [digest(pack(state)),digest(pack(self.events)),digest(pack(self.visits)),digest(bytes(self.u.mem_read(BUFF4,capacity*4))),digest(bytes(self.u.mem_read(BUFF10,capacity*10))),digest(pack([*cursor,words(self.u,FALLBACK+0x24,1)[0]])),str(total)]
