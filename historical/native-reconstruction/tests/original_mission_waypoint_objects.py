# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base reveal-area parent with supplied startup tables/effects."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_mission_waypoint_objects import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI

ARENA=0x3400000;SIZE=0x290000;MAP=0x8324e0;ACTION=ARENA+0x100;SCENARIO=ARENA+0x10000;RULES=ARENA+0x1000;CURRENT=ARENA+0x3000;OTHER=ARENA+0x9000;COUNTRY=ARENA+0xf000
PRIMARY=ARENA+0x20000;SECONDARY=ARENA+0x120000;CELLS=ARENA+0x220000;POINT=ARENA+0x23f000
OBJECTS=ARENA+0x240000;VT=ARENA+0x270000;BUILD_VT=ARENA+0x271000;TYPE=ARENA+0x280000;TAG=ARENA+0x282000;STRIDE=0x800
FALLBACK=0xa6f9f8
def signed(v):return v if v<2**31 else v-2**32
def point(raw):return struct.unpack('<hh',raw)
class MissionWaypointObjectsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.stores)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def cid(self,p):
  if p==FALLBACK:return 16
  assert CELLS<=p<CELLS+16*0x200 and (p-CELLS)%0x200==0;return (p-CELLS)//0x200
 def hid(self,p):assert p in (CURRENT,OTHER);return 1 if p==CURRENT else 2
 def p(self,address):return point(self.u.mem_read(address,4))
 def actor(self,p):
  actor=(p-OBJECTS)//STRIDE;assert 0<=actor<34 and OBJECTS+actor*STRIDE==p;return actor
 def stores(self,u,access,p,n,value,_):
  if not self.active:return
  for id in range(34):
   obj=OBJECTS+id*STRIDE
   if p in (obj+0x373,obj+0x374,obj+0xa0,obj+0xa4):
    assert n==(4 if p==obj+0xa0 else 1);self.trace.extend(('DW','0',str(p-obj),str(value&0xffffffff)));return
  for house in (CURRENT,OTHER):
   if p in (house+0x13c,house+0x5668,house+0x5669,house+0x1b4,house+0x18d,house+0x144):
    assert n==(4 if p==house+0x1b4 else 1);self.trace.extend(('DW',str(self.hid(house)+1),str(p-house),str(value&0xffffffff)));return
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x6b0670,0x663180,0x548070):self.counts[hex(a)]+=1;return
  if any(lo<a and a+n<=lo+size for lo,size in ((0x6b0670,0x18f),(0x663180,0x14),(0x548070,0x38))):
   returnAddress=self.word(sp);kind='V' if returnAddress==0x499fce else 'M' if 0x6a8d40<=returnAddress<0x6a911d else 'P'
   if a==0x54809f:
    p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EDX)&0xffffffff));self.trace.extend(('L',kind,str(p[0]),str(p[1])))
   elif a==0x5480a5:
    p=self.p(self.word(sp+4));self.trace.extend((kind,str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_EAX)))))
   return
  if a==0x4e5540:
   assert ecx==OTHER and self.word(sp+4)==CURRENT;self.trace.extend(('A','2',str(self.f['predicate'])));self.counts['supplied.housePredicate']+=1;self.ret(4,self.f['predicate']);return
  if a==0x6a8d40:
   self.maskMode=self.word(sp+8);assert self.maskMode in (0,1)
  if a==0x49a0f0:raise AssertionError('Fog child outside waypoint profile')
  if a==0x6aadd0:
   self.trace.extend(('DRAW',str(self.cid(self.word(sp+4)))));self.counts['supplied.redraw']+=1;self.ret(4);return
  if a==0x6328f0:
   p=self.p(self.word(sp+4));self.trace.extend(('NOTIFY',str(p[0]),str(p[1])));self.counts['supplied.notify']+=1;self.ret(4);return
  if a==0x6b3df0:
   args=[self.word(sp+4+i*4) for i in range(5)];actor=self.actor(args[1]);assert ecx==TAG and args==[4,OBJECTS+actor*STRIDE,(self.f['flagsSeed']-17)&0xffffffff,0,0]
   self.trace.extend(('TAG',str(actor),str(self.f['flagsSeed']-17)));self.counts['supplied.Tag']+=1
   if self.f['flagsSeed']%5==0:
    obj=OBJECTS+actor*STRIDE;owner=3-self.hid(self.word(obj+0x1b4));self.put(obj+0x1b4,CURRENT if owner==1 else OTHER);self.trace.extend(('OWNER',str(actor),str(owner)))
   self.ret(20);return
  if a==0x4426d0:
   actor=self.actor(ecx);assert self.word(sp+4)==0;self.trace.extend(('ACT',str(actor),'0'));self.counts['supplied.activation']+=1;self.ret(4);return
  if a==0x47be00:
   self.trace.extend(('REF',str(self.cid(ecx))));self.counts['supplied.refresh']+=1;self.ret(0);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected reveal-area instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a in (0x448fe0,0x6c2440):
   actor=self.actor(ecx);assert self.word(sp+4)==CURRENT
   if a==0x448fe0 or not actor&1:self.trace.extend(('BY',str(actor),'1'))
   if a==0x6c2440:self.trace.extend(('D','d','1'))
  elif a==0x5d4230:self.trace.extend(('D','b',str(self.hid(self.word(sp+4)))))
  elif a==0x4f52f0:self.trace.extend(('D','h',str(self.hid(ecx))))
  elif a==0x594770:self.trace.extend(('D','g','0'))
  elif a==0x594cb0:
   assert self.word(sp+8)==0;self.trace.extend(('D','q',str(signed(self.word(sp+4)))))
  elif a==0x636f10:self.trace.extend(('RADIO',str(self.actor(ecx))))
  elif a==0x458940:
   assert ecx==TYPE;self.trace.extend(('BH',str(self.word(sp+4)&255)))
  elif a==0x458930:
   assert ecx==TYPE;self.trace.append('BW')
  elif a==0x444080:self.trace.extend(('COORD',str(self.actor(ecx))))
  elif a==0x56856d:
   p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EDX)&0xffffffff));self.trace.extend(('L','Q',str(p[0]),str(p[1])))
  elif a==0x568573:
   p=self.p(sp+0x1c);self.trace.extend(('Q',str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_ESI)))))
  elif a==0x5d4e40:
   actor=self.actor(ecx);self.trace.extend(('COORD',str(actor)))
  elif a in (0x6a9111,0x6a911a):self.trace.extend(('V',str(self.maskMode),str(u.reg_read(UC_X86_REG_EAX)&255)))
  elif a==0x49a004:self.trace.extend(('G',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a in (0x47c849,0x47c8ac):self.trace.extend(('C',str(self.cid(ecx)),'0'))
  elif a in (0x47c85a,0x47c8bd,0x47c8cf):self.trace.extend(('C',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c876:self.trace.extend(('F',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a in (0x47c893,0x47c8ec):self.trace.extend(('G',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x49a03b:self.trace.extend(('P',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(u.reg_read(UC_X86_REG_EAX)&255)))
  elif a==0x49a052:self.trace.extend(('F',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x49a074:self.trace.extend(('S',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(u.reg_read(UC_X86_REG_ECX)&255)))
  elif a==0x49a08d:self.trace.extend(('G',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(signed(self.word(u.reg_read(UC_X86_REG_ESI)+0x140)|1))))
  elif a==0x6a29ab:self.trace.extend(('H',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x54a413:self.trace.extend(('D',str(struct.unpack('<h',struct.pack('<H',u.reg_read(UC_X86_REG_EAX)&0xffff))[0])))
  elif a==0x54a44c:
   p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EAX)&0xffffffff));self.trace.extend(('L','C',str(p[0]),str(p[1])))
  elif a==0x54a456:
   p=self.p(sp+0x30);self.trace.extend(('C',str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_ESI)))))
  elif a==0x54a4bc:
   p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EAX)&0xffffffff));self.trace.extend(('L','G',str(p[0]),str(p[1])))
  elif a==0x54a4c6:
   p=self.p(sp+0x58);self.trace.extend(('G',str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x54a4e7:
   cell=u.reg_read(UC_X86_REG_ESI);old=self.word(cell+0x140);new=u.reg_read(UC_X86_REG_EDX);self.trace.extend(('W',str(self.cid(cell)),str(signed(old)),str(signed(new))))
 def fill_table(self,base,mode,rawx,rawy):
  u=self.u;u.mem_write(base,bytes(0x100000))
  if mode==2:return
  for y in range(rawy-24,rawy+25):
   for x in range(rawx-24,rawx+25):
    index=y*512+x
    if not 0<=index<262144 or (mode==1 and ((x+y)&1)):continue
    cid=(x&3)|((y&3)<<2);self.put(base+index*4,CELLS+cid*0x200)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(FALLBACK,b'\xa5'*0x148)
  self.put(MAP+0x138,SECONDARY);self.put(MAP+0xf0,f['origin']);self.put(MAP+0xf4,f['extent']);self.put(0x832618,SECONDARY);self.put(0x839848,RULES);self.put(0xa35db4,CURRENT)
  self.put(CURRENT+0x34,COUNTRY);self.put(COUNTRY+0xb8,2);self.put(OTHER+0x5414,(1<<2) if f['allied'] else 0)
  u.mem_write(RULES+0x1432,bytes([f['rule1432']]));u.mem_write(RULES+0x142b,bytes([f['rule142b']]));u.mem_write(0xa6fc30,struct.pack('<i',f['divisor']));u.mem_write(0xabe490,struct.pack('<Q',f['scaleBits']))
  u.mem_write(POINT,struct.pack('<iii',f['x'],f['y'],f['z']))
  u.mem_write(0xa6f248,b''.join(struct.pack('<hh',*p) for p in f['offsets']));u.mem_write(0xa6ed18,b''.join(struct.pack('<hh',*p) for p in f['heightOffsets']))
  rawx=int(f['x']/256);rawy=int(f['y']/256);self.fill_table(PRIMARY,f['primaryMode'],rawx,rawy);self.fill_table(SECONDARY,f['secondaryMode'],rawx,rawy)
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;u.mem_write(cell+0x11b,struct.pack('<b',((f['levelSeed']+i*3)%15)-7));self.put(cell+0x12c,8 if ((f['flagsSeed']+i)&1) else 0);self.put(cell+0x140,(f['flagsSeed']+i*17)&0xff)
  self.put(ACTION+0x74,f['waypoint']);self.put(0xa3d290,SCENARIO);self.put(0xabfe08,f['heightScale']);self.put(RULES+0x54c,f['range']);u.mem_write(CURRENT+0x188,bytes([f['disabled']]))
  offset=(0x632+f['waypoint']*4)&0xffffffff;assert offset+4<=0x1000
  u.mem_write(SCENARIO+offset,struct.pack('<hh',int(f['x']/256),int(f['y']/256)))
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;self.put(cell+0x140,self.word(cell+0x140)|f['bridge'])
  self.put(0x83996c,MAP);self.put(SCENARIO,0x1000 if f['flagsSeed']&1 else 0)
  u.mem_write(0x7ac3bc,bytes((i*37+f['flagsSeed']*13)&255 for i in range(256)))
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;seed=f['flagsSeed']
   u.mem_write(cell+0x120,bytes([(seed+i*5)&255,(seed+i*7+3)&255]));self.put(cell+0x12c,self.word(cell+0x12c)|0xa5000000|(0x10 if (seed+i)&2 else 0))
   self.put(cell+0x130,(-2147483648,-1,0,1,2,2147483647)[(seed+i)%6]);self.put(cell+0x134,(-2,0,1,3,2147483647)[(seed+i)%5])
  for vt,coord,discovery in ((VT,0x5d4e40,0x6c2440),(BUILD_VT,0x444080,0x448fe0)):
   self.put(vt+0x48,coord);self.put(vt+0x180,discovery);self.put(vt+0x16c,0x594770);self.put(vt+0x1d0,0x594cb0);self.put(vt+0x468,0x4426d0)
  seed=f['flagsSeed'];self.put(TYPE+0xb90,seed-2048);self.put(TYPE+0xc78,seed%22);u.mem_write(TYPE+0x1214,b'\xff')
  self.put(0xa3d298,seed%3-1);self.put(0xa40774,seed%2);self.put(0xac0148,seed-17)
  for id,house in ((1,CURRENT),(2,OTHER)):
   for off,value in ((0x134,255 if (seed+id)&1 else 0),(0x135,128 if (seed+id)&2 else 0),(0x13c,17),(0x5668,33),(0x5669,65),(0x18d,127),(0x144,255)):u.mem_write(house+off,bytes([value]))
   self.put(house+0x1b4,-1)

  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200
   if i<16:u.mem_write(cell+0x24,struct.pack('<hh',16+(i&3),16+(i>>2)))
   members=(f['flagsSeed']+i)%4;active=(f['flagsSeed']//4+i)%4;head=0
   for m in (1,0):
    actor=i*2+m;obj=OBJECTS+actor*STRIDE;self.put(obj,BUILD_VT if actor&1 else VT);u.mem_write(obj+0x14,bytes([0x80|((active>>m)&1)]));self.put(obj+0x30,head if members&(1<<m) else 0)
    seed=f['flagsSeed'];u.mem_write(obj+0x88,struct.pack('<iii',seed+i*17+(37 if m and seed%3 else 0),seed+i*23+(-19 if m and seed%3 else 0),0))
    self.put(obj+0x1b4,OTHER);self.put(obj+0x34,TAG if actor%3==0 else 0);self.put(obj+0x418,TYPE)
    u.mem_write(obj+0x372,bytes([0 if (seed+actor)%3 else 255,255 if seed%7==0 and actor%4==0 else 0,129]));self.put(obj+0x98,(14,18,-1,19)[actor%4]);self.put(obj+0xa0,(18,-1,5)[actor%3]);u.mem_write(obj+0xa4,b'\xc1')
    self.put(obj+0xcc,obj+0x500);self.put(obj+0xd0,2 if actor%3==0 else 0 if actor%3==1 else -1);self.put(obj+0x500,0 if actor%5 else 1);self.put(obj+0x504,1)
    if members&(1<<m):head=obj
   self.put(cell+0xe4,head)
  before=bytearray(u.mem_read(ARENA,SIZE));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.trace=[];self.active=True
  writes=[(0xa6fa1c,4)]+[(cell+off,n) for cell in [*[CELLS+i*0x200 for i in range(16)],FALLBACK] for off,n in ((0x120,2),(0x12c,8),(0x140,4))]
  writes += [(OBJECTS+i*STRIDE+off,n) for i in range(34) for off,n in ((0x373,2),(0xa0,5),(0x1b4,4))]
  writes += [(house+off,n) for house in (CURRENT,OTHER) for off,n in ((0x13c,1),(0x5668,2),(0x1b4,4),(0x18d,1),(0x144,1))]
  inputs=[*RANGES.items(),*TABLES.items(),(0x83996c,4),(0xa3d290,4),(0xabfe08,4),(ACTION,0x100),(SCENARIO,0x1000),(0x832618,4),(0x839848,4),(0xa35db4,4),(0xa6fc30,4),(0xabe490,8),(0xa6f248,len(f['offsets'])*4),(0xa6ed18,len(f['heightOffsets'])*4),(MAP,0x200),(RULES,0x2000),(COUNTRY,0x1000),(PRIMARY,0x100000),(SECONDARY,0x100000),(POINT,12),(VT,0x46c),(BUILD_VT,0x46c),(TYPE,0x2000),(0xa3d298,4),(0xa40774,4),(0xac0148,4)]
  for i in range(16):inputs.extend(((CELLS+i*0x200,0x120),(CELLS+i*0x200+0x122,10),(CELLS+i*0x200+0x134,12),(CELLS+i*0x200+0x144,0xbc)))
  inputs.extend(((FALLBACK,0x24),(FALLBACK+0x28,0xf8),(FALLBACK+0x122,10),(FALLBACK+0x134,12),(FALLBACK+0x144,4)))
  house=(0,CURRENT,OTHER)[f['house']]
  try:self.checked_call(0x6b0670,[0xffffffff,0xabcdef01,0x12345678,0x76543210],ACTION,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE));after_fallback=bytearray(u.mem_read(FALLBACK,0x148))
  for p,n in writes:
   if ARENA<=p<ARENA+SIZE:before[p-ARENA:p-ARENA+n]=after[p-ARENA:p-ARENA+n]
  for off,n in ((0x24,4),(0x120,2),(0x12c,8),(0x140,4)):before_fallback[off:off+n]=after_fallback[off:off+n]
  assert after==before and after_fallback==before_fallback
  self.trace.append('Z')
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200
   self.trace.extend((str(signed(self.word(cell+0x140))),str(signed(self.word(cell+0x12c))),str(signed(self.word(cell+0x130))),str(u.mem_read(cell+0x120,1)[0]),str(u.mem_read(cell+0x121,1)[0])))
  self.trace.extend(map(str,self.p(FALLBACK+0x24)));self.trace.append('U')
  for i in range(34):
   obj=OBJECTS+i*STRIDE;self.trace.extend(map(str,(self.hid(self.word(obj+0x1b4)),*u.mem_read(obj+0x373,2),signed(self.word(obj+0xa0)),u.mem_read(obj+0xa4,1)[0])))
  self.trace.append('HOUSES')
  for house in (CURRENT,OTHER):self.trace.extend(map(str,(u.mem_read(house+0x13c,1)[0],*u.mem_read(house+0x5668,2),signed(self.word(house+0x1b4)),u.mem_read(house+0x18d,1)[0],u.mem_read(house+0x144,1)[0])))
  self.trace.extend(('END',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
