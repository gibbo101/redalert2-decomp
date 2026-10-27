# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged full active parent and House lookup; anchor/transfer effects supplied."""
from original_team_script import TeamScriptOracle,BASE,SIZE,TEAM,SCRIPT,STYPE,FEET,VT
from verify_team_command20 import verify
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EDI
AUX=0x6200000;AUXSIZE=0x10000;HOUSES=(AUX+0x1000,AUX+0x2000);TYPES=(AUX+0x3000,AUX+0x4000);SLOTS=AUX+0x5000;ALT=AUX+0x6000
TRANSFERS=(AUX+0x8000,AUX+0x8010)
class TeamCommand20Oracle(TeamScriptOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(AUX,AUXSIZE)
 def change(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw)
  if AUX<=p<p+n<=AUX+AUXSIZE:self.expectedAux[p-AUX:p-AUX+n]=raw
  if BASE<=p<p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=raw
 def ident(self,p):return FEET.index(p)+1 if p else 0
 def mutate(self,kind,member):
  self.event(13,kind,self.ident(member))
  if kind==1:self.change(member+0x4c8,0)
  if kind==2:
   nxt=self.word(member+0x4c8)
   if nxt:self.change(nxt+0x4c8,0)
  if kind==3:self.change(TYPES[0]+0xb8,-17)
  if kind==4:self.change(member,ALT)
  if kind in (6,7):self.change(TEAM+0x54,0)
 def checked_call(self,*args,**kw):
  if self.seed:
   self.seed=False;self.u.mem_write(AUX,bytes(AUXSIZE))
   for i in range(2):
    self.put(HOUSES[i]+0x34,TYPES[i]);self.put(TYPES[i]+0xb8,self.extra[0]);self.put(SLOTS+4*i,HOUSES[i])
   self.put(0xa322a8,2);self.put(0xa3229c,SLOTS)
   self.put(VT+0x378,TRANSFERS[0]);self.put(ALT+0x1c0,0x6d6e00);self.put(ALT+0x378,TRANSFERS[1])
   self.expected=bytearray(self.u.mem_read(BASE,SIZE))
   for i in range(2):self.change(STYPE+0xa4+8*i,20)
   self.lookupCount=0;self.transfers=0;self.expectedAux=bytearray(self.u.mem_read(AUX,AUXSIZE))
   # New actual lookup/table and virtual mappings stay immutable unless an
   # explicitly labeled supplied child diagnostic mutates them.
   inputs=kw['inputs'];kw['inputs']=[(a,n) for a,n in inputs if a!=VT]+[(0x4ed760,0x30)]
  return super().checked_call(*args,**kw)
 def code(self,u,a,n,ctx):
  if not self.active:return
  if 0x4ed760<=a and a+n<=0x4ed790:
   if a==0x4ed760:
    self.counts[hex(a)]+=1;self.lookupCount+=1;assert self.word(u.reg_read(UC_X86_REG_ESP)+4)==1
    country=u.reg_read(UC_X86_REG_ECX);assert country==self.wanted&0xffffffff;self.event(9,country)
    if self.extra[1]==4:self.mutate(4,self.current)
   return
  if a==0x6b7fec and self.extra[1]==7:self.mutate(7,0)
  if a==0x6b7ff9:
   self.current=u.reg_read(UC_X86_REG_EDI)
   self.event(10,self.ident(self.current),self.ident(self.word(self.current+0x4c8)))
  if a==0x6b7fff:self.event(12,self.ident(self.current),int(self.word(self.current)==ALT))
  if a in TRANSFERS:
   sp=u.reg_read(UC_X86_REG_ESP);member=u.reg_read(UC_X86_REG_ECX);house=self.word(sp+4);flag=self.word(sp+8)
   assert member==self.current and flag==1 and house in (0,*HOUSES)
   self.event(11,self.ident(member),HOUSES.index(house)+1 if house else 0,flag,TRANSFERS.index(a));self.transfers+=1
   if self.extra[1] in (1,2,3,6):self.mutate(self.extra[1],member)
   u.reg_write(UC_X86_REG_EAX,self.extra[2]&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+12);return
  # Base fixture's active supported-domain guard remains, but these new branch
  # instructions are already inside its complete6B7AD0 span.
  return super().code(u,a,n,ctx)
 def run(self,f):
  self.seed=True;self.extra=f[9:];self.wanted=f[3];row=super().run(f[:9])
  expected=-17 if self.extra[1]==3 and self.transfers else self.extra[0]
  assert self.word(TYPES[0]+0xb8)==expected&0xffffffff
  assert self.word(TYPES[1]+0xb8)==self.extra[0]&0xffffffff
  assert bytes(self.u.mem_read(AUX,AUXSIZE))==self.expectedAux,'Unrelated command20 auxiliary arena changed'
  assert self.word(0xa322a8)==2 and self.word(0xa3229c)==SLOTS
  return row+['X',str(self.ident(self.word(TEAM+0x54))),str(self.transfers),str(self.word(TYPES[0]+0xb8)),*[str(self.ident(self.word(p+0x4c8))) for p in FEET],*[str(int(self.word(p)==ALT)) for p in FEET]]
