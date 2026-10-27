# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged passability and actual Unit/Building/Terrain kind calls."""
import struct
from original_presentation import PresentationOracle,STOP
from original_map_floor_height import CELL,SLOTS,MAP,FALLBACK
from original_foot_lit import words
from verify_occupied_cell import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_CODE,UC_HOOK_BLOCK,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX
ACTORS=[CELL+0x2000+i*0x1000 for i in range(8)]
TYPES=[0x2600000+i*0x2000 for i in range(8)];HOUSES=[0x2620000+i*0x1000 for i in range(8)];SCENARIO=0x2630000;OVERLAY=0x2631000;OVERLAYS=0x2632000
VTABLE={1:0x7addf8,6:0x79cbbc,36:0x7ad3cc}
class OccupiedCellOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(CELL,0x10000);self.u.mem_map(SLOTS,0x100000);self.u.mem_map(0x2600000,0x40000)
  self.entries={hex(a):0 for a in RANGES};self.selected_stores=0
  self.u.hook_add(UC_HOOK_BLOCK,self.block);self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(p<=a and a+n<=p+s for p,s in RANGES.items()):raise AssertionError(f'Uninspected occupied Cell block {a:#x}/{n}')
 def code(self,u,a,n,ctx):
  if a in RANGES:self.entries[hex(a)]+=1
  if a in (0x70a2d0,0x453c40,0x6e4b00):self.events.extend(('k',str(ACTORS.index(u.reg_read(UC_X86_REG_ECX))),str({0x70a2d0:1,0x453c40:6,0x6e4b00:36}[a])))
 def run(self,h,actors):
  shape=h[:5];x,y,level,ramp,land,present,ol,crush,wall,rock,rubble=h[5:16];speeds=h[16:27];theater,initial,head=h[27:30];u=self.u;self.events=[]
  u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(0x2600000,b'\xa5'*0x40000);u.mem_write(SLOTS,bytes(0x100000))
  for off,v in zip((0xf0,0xf8,0xfc,0x100,0x104),shape):self.put(MAP+off,v)
  self.put(MAP+0x138,SLOTS);self.put(SLOTS+(y*512+x)*4,CELL);self.put(CELL+0x24,(x&65535)|((y&65535)<<16));u.mem_write(CELL+0x11b,bytes([level&255,ramp]));self.put(CELL+0xec,land);self.put(CELL+0x4c,initial);self.put(CELL+0x44,0 if present else -1);self.put(CELL+0xe4,0 if head==-1 else ACTORS[head])
  self.put(0xa3d290,SCENARIO);self.put(SCENARIO+0x838,theater);self.put(0xa35dec,OVERLAYS);self.put(OVERLAYS,OVERLAY);self.put(OVERLAY+0x268,ol)
  for off,v in zip((0x1fd,0x278,0x285,0x284),(crush,wall,rock,rubble)):u.mem_write(OVERLAY+off,bytes([v]))
  for i,bits in enumerate(speeds):self.put(0x850ea8+i*36,bits)
  for i,(kind,next,b1359,b135a,h142,mission,t278,t27c) in enumerate(actors):
   p=ACTORS[i];self.put(p,VTABLE[kind]);self.put(p+0x30,0 if next==-1 else ACTORS[next]);self.put(p+0x418,TYPES[i]);self.put(p+0xb0,TYPES[i]);self.put(p+0x1b4,HOUSES[i]);self.put(p+0x4ec,mission)
   u.mem_write(TYPES[i]+0x1359,bytes([b1359,b135a]));u.mem_write(HOUSES[i]+0x142,bytes([h142]));self.put(TYPES[i]+0x278,t278);self.put(TYPES[i]+0x27c,t27c)
  arena=bytes(u.mem_read(CELL,0x10000))
  def stores(u,access,p,n,v,ctx):
   if CELL+0x4c<=p<CELL+0x50:assert p==CELL+0x4c and n==4;self.events.extend(('W',str(v&0xffffffff)));self.selected_stores+=1
  hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:self.checked_call(0x478f40,ecx=CELL,writes=[(CELL+0x4c,4)],inputs=[*RANGES.items(),*[(p,4) for p in DISPATCH],(MAP,0x140),(SLOTS,0x100000),(0x2600000,0x40000),(0xa3d290,4),(0xa35dec,4),(0x850ea8,396)])
  finally:u.hook_del(hook)
  after=bytearray(u.mem_read(CELL,0x10000));after[0x4c:0x50]=arena[0x4c:0x50];assert bytes(after)==arena
  self.events.extend(('R',str(words(u,CELL+0x4c,1)[0])));return self.events
