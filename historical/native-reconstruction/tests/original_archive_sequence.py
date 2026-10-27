# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged base startup/theater requests with explicit service fixtures."""
from original_archive import ArchiveOracle,STACK,STOP,HEAP,INDEX,VTABLE,S_HANDLE
from archive_sequence_profiles import address
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX
S_FORMAT=STOP+0x100;S_DESTROY=STOP+0x110

class ArchiveSequenceOracle(ArchiveOracle):
 def va(self,a):return address(self.profile,a)
 def configure(self):
  self.events=[];self.requests=[];self.allocated=HEAP;self.current=''
  def malloc():
   assert self.get(self.u.reg_read(UC_X86_REG_ESP)+4)==0x28
   p=self.allocated;self.allocated+=0x40;assert self.allocated<=HEAP+0x1000
   self.put(p,VTABLE);self.ret(0,p)
  def construct():
   sp=self.u.reg_read(UC_X86_REG_ESP);name=self.string(self.get(sp+4)).lower()
   assert self.get(sp+8)==self.va(0x821330)
   self.requests.append(name);self.events.append(['construct',name]);self.ret(8,self.u.reg_read(UC_X86_REG_ECX))
  def format_name():
   sp=self.u.reg_read(UC_X86_REG_ESP);p,fmt,v=[self.get(sp+off) for off in (4,8,12)]
   assert STACK-0x4000<=p<STACK
   fmt=self.string(fmt)
   value=self.string(v) if '%s' in fmt else v
   data=(fmt%value).encode()+b'\0';assert p+len(data)<=STACK
   self.u.mem_write(p,data);self.ret(0,len(data)-1)
  def event(kind,pop=0):self.events.append([kind]);self.ret(pop)
  self.services={self.va(0x76d5a7):malloc,self.va(0x591fa0):construct,self.va(0x4960f0):lambda:self.ret(),
    self.va(0x4068f0):lambda:self.ret(),self.va(0x76d684):format_name,S_FORMAT:format_name,
    self.va(0x438290):lambda:self.ret(),self.va(0x42f250):lambda:self.ret(),
    self.va(0x46e0c0):lambda:self.ret(0,self.media),self.va(0x6dcc60):lambda:event('theme-initialization'),
    self.va(0x62ff10):lambda:self.ret()}
  self.put(VTABLE,S_DESTROY);self.services[S_DESTROY]=lambda:event('destroy',4)
  return format_name
 def startup(self,enumerate,media,available,maps=(),movies=()):
  self.media=media;self.configure();self.available=set(available);enumeration=[[],0]
  self.u.mem_write(INDEX,bytes([0x69])*0x1000)
  self.put(self.va(0x81f78c),INDEX);self.put(self.va(0x81f790),64);self.put(self.va(0x81f798),0)
  self.put(self.va(0x81f7c4),INDEX+0x400);self.put(self.va(0x81f7c8),64);self.put(self.va(0x81f7d0),0)
  for va in [0x81f800,0x81f804,0x81f814,0x81f7b8,0x819768,0x81f7f4]:self.put(self.va(va),0)
  self.u.mem_write(self.va(0x838b50),bytes([enumerate]))
  def file():
   sp=self.u.reg_read(UC_X86_REG_ESP);obj=self.u.reg_read(UC_X86_REG_ECX)
   self.current=self.string(self.get(sp+4)).lower();self.put(obj,VTABLE);self.ret(4,obj)
  def exists():self.events.append(['exists',self.current]);self.ret(4,int(self.current in self.available))
  def first():
   p=self.u.reg_read(UC_X86_REG_ECX);pattern=self.string(p).lower()
   names=list(maps if pattern.startswith('maps') else movies)
   self.events.append(['enumerate',pattern,names]);enumeration[:]=[names,0]
   if names:self.u.mem_write(p,names[0].encode()+b'\0')
   self.ret(0,int(bool(names)))
  def next_name():
   names,i=enumeration;i+=1;enumeration[1]=i;p=self.u.reg_read(UC_X86_REG_ECX)
   if i<len(names):self.u.mem_write(p,names[i].encode()+b'\0')
   self.ret(0,int(i<len(names)))
  self.put(VTABLE+0x14,S_HANDLE)
  self.services.update({self.va(0x468b70):file,self.va(0x62ff90):file,S_HANDLE:exists,
   self.va(0x46feb0):first,self.va(0x470000):next_name,self.va(0x470070):lambda:self.ret()})
  globals=[(self.va(va),n) for va,n in [(0x81f800,8),(0x81f814,4),(0x81f7b8,4),(0x819768,4),
    (0x81f7f4,4),(0x81f798,4),(0x81f7d0,4),(0xa28838,1)]]
  value=self.call(0x5152c0,writes=[*globals,(INDEX,0x1000)],inputs=[(self.va(0x838b50),1)])&255
  if enumerate and 'multi.mix' in self.requests:
   assert self.get(self.va(0x81f798))==max(0,len(maps)-1)
  self.services={}
  return [value,len(self.requests),*self.requests],self.events
 def theater(self,new,previous,existing=False,palette=True):
  self.media=0;self.configure();scenario=HEAP+0x2000;self.put(self.va(0xa255a0),scenario)
  self.u.mem_write(scenario,bytes([0x5a])*0x900);self.put(self.va(0x7c396c),previous)
  self.put(self.va(0xa9e9f0),0)
  self.put(self.va(0x7854a0),S_FORMAT)
  for i,va in enumerate([0x81f7e8,0x81f7e0,0x81f7e4,0x81f7ec,0x81f7f0]):
   old=HEAP+0x1000+i*0x40 if existing else 0
   if old:self.put(old,VTABLE)
   self.put(self.va(va),old)
  def retrieve():
   name=self.string(self.u.reg_read(UC_X86_REG_ECX));self.events.append(['retrieve',name])
   self.ret(0,INDEX if palette else 0)
  def copy_palette():
   p=self.get(self.u.reg_read(UC_X86_REG_ESP)+4);assert p in (INDEX,self.va(0x820130))
   self.ret(4)
  self.u.mem_write(INDEX,bytes([17])*768)
  self.u.mem_write(self.va(0x820d30),bytes([19])*768)
  self.services.update({self.va(0x6682c0):lambda:self.ret(4),self.va(0x5924c0):lambda:self.ret(4,1),
    self.va(0x592370):retrieve,self.va(0x5fab10):copy_palette,self.va(0x4821e0):lambda:self.ret(),
    self.va(0x5fb1e0):lambda:self.ret(),self.va(0x6d4a60):lambda:self.ret()})
  writes=[(scenario+0x838,4),(self.va(0x81f7e0),20),(self.va(0x820130),768),(self.va(0x820d30),768)]
  self.call(0x519290,ecx=new,writes=writes,inputs=[(INDEX,768),(self.va(0x7c396c),4)])
  assert self.get(scenario+0x838)==new
  self.services={}
  return [len(self.requests),*self.requests],self.events
