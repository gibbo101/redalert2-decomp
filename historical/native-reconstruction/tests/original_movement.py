# SPDX-License-Identifier: GPL-3.0-or-later
"""Isolated original drive routines with explicit flat-world service boundaries.
No original instructions are patched. Hooked services are listed in the report.
"""
import hashlib
import struct
from pathlib import Path
import pefile
from compare_original import EXPECTED
from movement_profiles import movement_profile, address
from unicorn import *
from unicorn.x86_const import *
from collections import Counter,deque
UNIT,TYPE,HOUSE,COUNTRY,LOCO,VT,TYPVT,RULES,CELL,ARG,STACK,STOP,STUB = (0x1100000,0x1102000,0x1104000,0x1105000,0x1106000,0x1107000,0x1108000,0x1109000,0x1110000,0x1120000,0x11ff000,0x1000000,0x1200000)
class Oracle:
 def __init__(self, executable, terrain=1.0, precision=0x27f, *, allow_patched=False, audit_calls=False):
  data=Path(executable).read_bytes()
  self.digest,self.profile=movement_profile(data,allow_patched=allow_patched)
  self.audit_calls=audit_calls;self.root_calls=0
  PE=pefile.PE(data=data);BASE=PE.OPTIONAL_HEADER.ImageBase
  if BASE!=0x400000 or PE.FILE_HEADER.Machine!=0x14c:raise ValueError("Unexpected image base")
  self.u=Uc(UC_ARCH_X86,UC_MODE_32);u=self.u
  u.mem_map(BASE,(PE.OPTIONAL_HEADER.SizeOfImage+4095)&~4095)
  for s in PE.sections:u.mem_write(BASE+s.VirtualAddress,s.get_data())
  self.read_only_ranges=[(BASE+s.VirtualAddress,BASE+s.VirtualAddress+len(s.get_data())) for s in PE.sections if not s.Characteristics&0x80000000]
  u.mem_map(0x1000000,0x300000)
  self.canaries=[(UNIT-32,32),(UNIT+0x1000,32),(TYPE-32,32),(TYPE+0x1000,32),
                 (HOUSE-32,32),(HOUSE+0x800,32),(COUNTRY-32,32),(COUNTRY+0x800,32),
                 (LOCO-32,32),(LOCO+0x100,32),(RULES+0x2000,32),(ARG+0x200,32)]
  if audit_calls:
   for a,n in self.canaries:u.mem_write(a,bytes([0xa5])*n)
   u.hook_add(UC_HOOK_MEM_WRITE,self.audit_write)
  self.terrain=terrain;self.cells={};u.mem_map(0x1300000,0x100000);u.reg_write(UC_X86_REG_FPCW,precision)
  self.hooks={};self.calls=Counter();self.trace=deque(maxlen=35)
  u.hook_add(UC_HOOK_CODE,self.hook)
  self.put(UNIT,VT);self.put(TYPE,TYPVT);self.put(UNIT+0x5ac,TYPE)
  self.put(UNIT+0x1b4,HOUSE);self.put(HOUSE+0x34,COUNTRY);self.put(COUNTRY+0x12c,1.,'f')
  self.put(self.va(0x821b68),RULES);self.put(UNIT+0x5b4,-1);self.put(UNIT+0x7d,1,'B')
  self.put(UNIT+0x470,1.,'d');self.put(UNIT+0x468,1.,'d');self.put(TYPE+0x5a0,15)
  self.put(CELL+0x44,-1);self.put(CELL+0x116,-1,'h');self.put(CELL+0xec,0)
  self.put(LOCO,self.va(0x78b59c));self.put(LOCO+4,self.va(0x78b4d4));self.put(LOCO+8,UNIT);self.put(LOCO+12,UNIT)
  self.put(LOCO+0x10,1,'B');self.put(LOCO+0x65,1,'B');self.put(LOCO+0x50,1.,'d')
  self.put(LOCO+0x58,0);self.put(LOCO+0x63,1,'B');self.put(UNIT+0x4d0,-1)
  self.put(UNIT+0x564,LOCO+4)
  self.put(UNIT+0x2e0+20,1280,'H');self.put(UNIT+0x2f8+20,1280,'H')
  for offset,address in [(0x4bc,0x4c95c0),(0x4c8,0x4c2910),(0x338,0x6ce2b0)]:self.put(VT+offset,self.va(address))
  self.virtual(0x80,0,lambda:TYPE,'unit type')
  self.virtual(0x2c,0,lambda:1,'unit class ID')
  self.virtual(0x1a4,0,lambda:self.cell_for_coord(UNIT+0x88),'unit cell')
  self.virtual(0x1b8,0,lambda:0,'unit height')
  self.virtual(0xbc,0,lambda:0,'jumpjet predicate')
  self.virtual(0x19c,4,self.set_position,'set location')
  self.virtual(0x1a0,4,self.cellcoords,'get cellcoords')
  self.virtual(0x11c,4,lambda:1,'mark redraw/occupation')
  self.virtual(0x1b4,4,lambda:0,'set height')
  self.virtual(0x174,4,lambda:0,'per-cell notification')
  self.virtual(0x490,0,lambda:0,'post-cell callback')
  self.virtual(0x16c,0,lambda:2,'mission move')
  self.virtual(0x2c,0,lambda:40,'type class ID',TYPVT)
  self.bind(0x6ccd30,4,lambda:0,'non-veteran ability predicate')
  self.bind(0x545340,4,lambda:self.cell_for_coord(self.arg(0)),'map cell from coord')
  self.bind(0x5453b0,4,lambda:self.cell(*struct.unpack('<hh',self.u.mem_read(self.arg(0),4))),'map cell from cellcoords')
  self.setup_world()
 def va(self,disc_va):return address(self.profile,disc_va)
 def audit_write(self,u,access,a,n,value,context):
  if any(start<a+n and a<end for start,end in self.read_only_ranges):raise AssertionError(f'Original read-only image write {a:#x}')
 def audit_arenas(self):
  for a,n in self.canaries:
   if bytes(self.u.mem_read(a,n))!=bytes([0xa5])*n:raise AssertionError(f'Original fixture canary changed {a:#x}')
 def put(self,a,v,fmt='I'):self.u.mem_write(a,struct.pack('<'+fmt,v&0xffffffff if fmt=='I' else v))
 def get(self,a,fmt='I'):return struct.unpack('<'+fmt,self.u.mem_read(a,struct.calcsize(fmt)))[0]
 def arg(self,n):return self.get(self.u.reg_read(UC_X86_REG_ESP)+4+4*n)
 def bind(self,a,n,f,label):self.hooks[self.va(a) if a<0xc00000 else a]=(n,f,label)
 def virtual(self,offset,n,f,label,vt=VT):
  a=STUB+len(self.hooks)*16;self.put(vt+offset,a);self.bind(a,n,f,label)
 def hook(self,u,a,n,_):
  self.trace.append(a)
  if a in self.hooks:
   argc,fn,label=self.hooks[a];self.calls[label]+=1
   result=fn();sp=u.reg_read(UC_X86_REG_ESP);ret=self.get(sp)
   u.reg_write(UC_X86_REG_EAX,result&0xffffffff if result is not None else 0)
   u.reg_write(UC_X86_REG_ESP,sp+4+argc);u.reg_write(UC_X86_REG_EIP,ret)
 def set_position(self):
  self.u.mem_write(UNIT+0x88,bytes(self.u.mem_read(self.arg(0),12)));return 1
 def cellcoords(self):
  p=self.arg(0);x,y,z=struct.unpack('<iii',self.u.mem_read(UNIT+0x88,12));self.u.mem_write(p,struct.pack('<hh',int(x/256),int(y/256)));return p
 def call(self,a,args=(),this=LOCO,budget=100000):
  caller=struct.pack('<'+'I'*(len(args)+1),STOP,*[v&0xffffffff for v in args])
  if self.audit_calls:caller+=bytes([0x5a])*32
  self.u.mem_write(STACK,caller)
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  if self.audit_calls:
   for register,value in preserved.items():self.u.reg_write(register,value)
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_ECX,this)
  try:self.u.emu_start(self.va(a),STOP,count=budget)
  except Exception:
   print('ERROR at',hex(self.u.reg_read(UC_X86_REG_EIP)),'last',list(map(hex,self.trace)));print('callbacks',self.calls);raise
  assert self.u.reg_read(UC_X86_REG_EIP)==STOP,hex(self.u.reg_read(UC_X86_REG_EIP))
  if self.audit_calls:
   self.root_calls+=1
   if self.u.reg_read(UC_X86_REG_ESP)!=STACK+4+4*len(args):raise AssertionError(f'Caller ESP changed {a:#x}')
   # Drive reuses its consumed argument slot as scratch. Preserve the return
   # address and caller-owned bytes beyond the callee's argument extent.
   if bytes(self.u.mem_read(STACK,4))!=caller[:4] or bytes(self.u.mem_read(STACK+4+4*len(args),32))!=bytes([0x5a])*32:raise AssertionError(f'Caller stack changed {a:#x}')
   for register,value in preserved.items():
    if self.u.reg_read(register)!=value:raise AssertionError(f'Callee-saved register changed {a:#x}')
   self.audit_arenas()
  return self.u.reg_read(UC_X86_REG_EAX)
 def state(self):return [*[self.get(UNIT+0x88+i,'i') for i in (0,4,8)],self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B')]

 def cell_for_coord(self,p):
  x,y=struct.unpack('<ii',self.u.mem_read(p,8));return self.cell(int(x/256),int(y/256))
 def cell(self,x,y):
  key=(x,y)
  if key not in self.cells:
   a=0x1300000+len(self.cells)*0x200
   if len(self.cells)>=2048:raise RuntimeError('Cell fixture bound exceeded')
   self.cells[key]=a;self.put(a+0x44,-1);self.put(a+0x116,-1,'h');self.put(a+0xec,0)
   self.u.mem_write(a+0x24,struct.pack('<hh',x,y))
  return self.cells[key]
 def setup_world(self):
  for off,n,value,label in [(0x1bc,0,0,'immobilized A'),(0x1c0,0,0,'immobilized B'),(0x324,0,0,'disabled A'),(0x328,0,0,'disabled B'),(0x27c,0,1,'eligible mover'),(0x194,20,0,'can enter empty cell'),(0x4b8,8,0,'mark next cell'),(0x398,0,TYPE+0xc00,'weapon slot'),(0xe8,4,0,'occupation mark'),(0xec,4,0,'occupation unmark'),(0x410,8,0,'mission transition'),(0x2ac,4,0,'destination accessible predicate'),(0x84,0,TYPE,'object type')]:
   self.virtual(off,n,lambda value=value:value,label)
  self.virtual(0x48,4,self.coords,'get coords')
  self.bind(0x557970,8,lambda:1,'cell occupancy reserve')
  self.bind(0x556f20,4,lambda:0,'flat terrain height')
  self.bind(0x4768c0,4,lambda:1,'empty-cell occupation')
  self.bind(0x6cda60,4,lambda:0,'weapon disabled predicate')
  self.bind(0x4c2b20,12,lambda:0,'pathfinder returns no route')
  self.put(TYPE+0xa0,400);self.put(UNIT+0x6c,400);self.put(RULES+0x1368,0.5,'d')
  self.put(TYPE+0x5a4,1)
  for land in range(12):self.put(self.va(0x8391b0)+4*(land*9+1),self.terrain,'f')
  self.put(TYPE+0xaab,1,'B')
  # Execute the original CRT initializers, not a guessed direction table.
  self.call(0x491400);self.call(0x4914b0)
 def coords(self):
  p=self.arg(0);self.u.mem_write(p,bytes(self.u.mem_read(UNIT+0x88,12)));return p
 def facing(self,field,tick):
  self.put(self.va(0xa2894c),tick);self.call(0x4b8700,[ARG],this=UNIT+field);return self.get(ARG,'H')
 def begin(self,x,y,heading,rot,speed):
  self.u.mem_write(UNIT+0x88,struct.pack('<iii',x,y,0))
  for j in range(24):self.put(UNIT+0x4d0+4*j,-1)
  self.put(LOCO+0x58,-1);self.put(LOCO+0x63,0,'B');self.put(LOCO+0x62,0,'B')
  self.put(LOCO+0x4c,0);self.put(LOCO+0x5c,0)
  self.u.mem_write(LOCO+0x34,bytes(24))
  self.set_ini_speed(speed)
  for field in [0x2e0,0x2f8]:
   self.call(0x4b89b0,[rot],this=UNIT+field);self.put(ARG,heading);self.call(0x4b8630,[ARG],this=UNIT+field)
 def set_ini_speed(self,value,previous=0):
  self.put(TYPE+0x5a0,previous)
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EBP,TYPE)
  self.u.emu_start(self.va(0x6d2021),self.va(0x6d2061),count=100)
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x6d2061):raise RuntimeError('Speed block did not terminate')
  return self.get(TYPE+0x5a0)
 def order(self,d,count):
  base=LOCO+0x40 if self.get(LOCO+0x63,'B') else UNIT+0x88
  x,y,z=struct.unpack('<iii',self.u.mem_read(base,12));dx,dy=struct.unpack('<ii',self.u.mem_read(self.va(0x839dd0)+8*d,8))
  target=(x+dx*count,y+dy*count,z)
  self.call(0x49fa00,[LOCO+4,*target],this=0)
  for j in range(24):self.put(UNIT+0x4d0+4*j,d if j<count else -1)
 def stop(self):
  self.call(0x49fac0,[LOCO+4],this=0)
  for j in range(24):self.put(UNIT+0x4d0+4*j,-1)
 def step(self,tick):
  self.put(self.va(0xa2894c),tick);self.call(0x4a01c0,[LOCO+4],this=0)
  self.call(0x6f03d0,[],this=UNIT)
  return self.state()+[self.facing(0x2e0,tick),self.facing(0x2f8,tick),self.get(LOCO+0x62,'B'),self.get(UNIT+0x3f0)]
