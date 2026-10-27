# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_building_frame_redraw import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX
BASE=0x3d00000;SIZE=0x8000;TACTICAL=BASE
ACTORS=[BASE+0x2000+i*0x1000 for i in range(3)]
BACKINGS=[BASE+0x6000,BASE+0x6100]
def signed(v):return (v+2**31)%2**32-2**31
class BuildingFrameOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.total_coordinates=0
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def write(self,u,access,p,n,v,_):
  if self.active and BASE<=p<BASE+SIZE:raise AssertionError('Frame predicate wrote owner arena')
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0xa40b08:self.trace+=['N',str(signed(self.word(p)))]
  if p==0xa40afc:self.trace+=['B',str(BACKINGS.index(self.word(p)))]
  for i,a in enumerate(ACTORS):
   if p-a in (0x7d,0x75,0x74):
    assert n==1;self.trace+=['G',str(i),str(p-a),str(u.mem_read(p,1)[0])]
 def mutate_write(self,p,b):
  self.u.mem_write(p,b)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+len(b)]=b
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Building frame instruction',hex(a))
  if a==0x453c70:self.trace+=['C',str(ACTORS.index(u.reg_read(UC_X86_REG_ECX)))];self.coordinate_calls+=1;self.total_coordinates+=1
  if a==0x6aa209 and not self.mutated and self.mode:
   self.mutated=True;self.trace+=['M',str(self.mode)]
   if self.mode in (1,6):self.final_count=0 if self.mode==1 else -1;self.put(0xa40b08,self.final_count)
   if self.mode==2:self.final_count=3;self.final_backing=1;self.put(0xa40b08,3);self.put(0xa40afc,BACKINGS[1])
   if self.mode==3:self.mutate_write(ACTORS[1]+0x7d,b'\0')
   if self.mode==4:self.mutate_write(TACTICAL+0xb0,struct.pack('<2i',2147483647,-2147483648))
   if self.mode==5:
    x,y,z=struct.unpack('<3i',u.mem_read(ACTORS[1]+0x88,12));self.mutate_write(ACTORS[1]+0x88,struct.pack('<3i',signed(x+257),signed(y-129),728))
 def run(self,f):
  ox,oy,x,y,w,h,scale,count,self.mode,*rest=f;order=rest[:3];rows=[rest[3+i*6:9+i*6] for i in range(3)]
  self.trace=[];self.mutated=False;self.coordinate_calls=0;self.final_count=count;self.final_backing=0
  self.u.mem_write(BASE,bytes([0x5a])*SIZE);self.put(TACTICAL+0xb0,ox);self.put(TACTICAL+0xb4,oy)
  for i,row in enumerate(rows):
   a=ACTORS[i];self.put(a,0x79cbbc)
   for off,v in zip((0x7d,0x75,0x74),row[:3]):self.u.mem_write(a+off,bytes([v]))
   self.u.mem_write(a+0x88,struct.pack('<3i',*row[3:]))
  self.u.mem_write(BACKINGS[0],struct.pack('<3I',*[ACTORS[i] for i in order]));self.u.mem_write(BACKINGS[1],struct.pack('<3I',*reversed(ACTORS)))
  self.put(0xa40b08,count);self.put(0xa40afc,BACKINGS[0]);self.u.mem_write(0xabe490,struct.pack('<Q',scale))
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6aa180,(x,y,w,h),TACTICAL,inputs=[*RANGES.items(),(0x79cbbc,0xac),(0x79a728,8),(0xabe490,8)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Frame predicate changed unrelated owner bytes'
  assert signed(self.word(0xa40b08))==self.final_count and self.word(0xa40afc)==BACKINGS[self.final_backing]
  self.trace+=['R',str(self.u.reg_read(UC_X86_REG_EAX)&255)]
  return self.trace
