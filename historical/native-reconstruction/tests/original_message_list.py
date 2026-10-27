# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original insertion/recursion, actual metrics/CRT/gadget/list children."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_message_list import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3f00000;SIZE=0x100000;LIST=ARENA+0x1000;FONT=ARENA+0x10000;PRIMARY=FONT+0x100;GLYPH=FONT+0x200;NODES=ARENA+0x20000;INDICES=ARENA+0x40000;PREFIX=ARENA+0x70000;BODY=ARENA+0x72000;RULES=ARENA+0x74000;CLOCK=ARENA+0x78000
class MessageListOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def ident(self,p):
  if not p:return 0
  assert NODES<=p<NODES+256*0x100 and (p-NODES)%0x100==0,('Unknown message node',hex(p));return (p-NODES)//0x100+1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x782017:
   assert self.word(sp+4)==0x4c and self.allocated<256;p=NODES+self.allocated*0x100;self.allocated+=1;self.events.extend(('A',str(self.ident(p))));self.counts['supplied.allocate']+=1
   if self.f['mutation']&1:
    for off,value in ((4,777),(8,-888),(0x2c4,333),(0xc,17),(0x14,23)):self.put(LIST+off,value)
    u.mem_write(LIST+0x19,b'\1\1');self.put(0xa3d298,4);u.mem_write(0xa3f209,b'\0');self.put(RULES+0x5cc,12);self.put(0x839980,999);self.put(0x839988,0xfffffff0)
   if self.f['mutation']&8:self.put(0x84e9e8,0)
   self.ret(0,p);return
  if a==0x781d3b:
   p=self.word(sp+4);self.events.extend(('F',str(self.ident(p))));self.counts['supplied.free']+=1;self.ret(0);return
  if a==CLOCK:
   self.events.append('T');self.counts['supplied.timeGetTime']+=1
   if self.f['mutation']&2:
    self.put(LIST+0x2c4,444);self.put(0x839980,7);self.put(0x839988,777);self.put(0xa3d298,3);u.mem_write(0xa3f208,b'\0');self.put(RULES+0x5cc,19);self.put(LIST+8,234);self.put(LIST+0x14,7);u.mem_write(LIST+0x19,b'\1\1')
   self.ret(0,self.f['milliseconds']);return
  if a==0x713db0:
   assert u.reg_read(UC_X86_REG_ECX)==self.word(RULES+0x5cc) and u.reg_read(UC_X86_REG_EDX)==8192 and [self.word(sp+i) for i in (4,8)]==[0x3f800000,0];self.events.append('S');self.counts['supplied.sound']+=1
   if self.f['mutation']&4:u.mem_write(LIST+0x19,b'\3\4');self.put(LIST+8,-999);self.put(LIST+0x14,45)
   self.ret(8);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected message path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.allocated=f['initial'];self.events=[]
  self.put(LIST,NODES if f['initial'] else 0)
  for off,value in ((4,-11),(8,23),(0xc,f['capacity']),(0x14,-13),(0x2c4,f['width'])):self.put(LIST+off,value)
  u.mem_write(LIST+0x19,bytes((f['res19'],f['res1a'])))
  for i in range(14):u.mem_write(LIST+0x1480+i*2,struct.pack('<H',0x101 if f['available']&(1<<i) else 0))
  self.put(0x84e9e8,FONT if f['present'] else 0);self.put(FONT+4,PRIMARY);self.put(FONT+8,GLYPH);self.put(FONT+0x1c,12);self.put(FONT+0x28,64);self.put(FONT+0x2c,1);self.put(PRIMARY+0x14,1);self.put(PRIMARY+0x18,INDICES);self.put(PRIMARY+0x1c,GLYPH);u.mem_write(INDICES,b'\1\0'*65536);u.mem_write(GLYPH,bytes([f['glyphWidth']]))
  for p,v in ((0xa3d298,f['mode']),(0x839980,f['start']),(0x839988,f['accum']),(0x839848,RULES),(RULES+0x5cc,-7),(0x79a524,CLOCK)):self.put(p,v)
  u.mem_write(0xa3f208,bytes((f['mode3'],f['mode4'])))
  for i in range(3):self.put(0x865ff0+i*4,NODES if f['initial'] and f['focus']&(1<<i) else 0)
  u.mem_write(PREFIX,f['prefix']+b'\0\0');u.mem_write(BODY,f['body']+b'\0\0');self.active=True
  inputs=[*RANGES.items(),*TABLES.items(),(0x84e9e8,4),(FONT,0x300),(INDICES,131072),(0xa3d298,4),(0xa3f208,2),(0x839980,12),(0x839848,4),(RULES,0x600),(0x79a524,4),(PREFIX,len(f['prefix'])+2),(BODY,len(f['body'])+2)]
  writes=[(LIST,4),(LIST+0x2c8,14*324),(LIST+0x1480,28),(NODES,256*0x100),(0x865ff0,12)]
  if f['mutation']:
   mutable={0x84e9e8,0xa3d298,0xa3f208,0x839980,RULES}
   inputs=[(p,n) for p,n in inputs if p not in mutable]
   inputs.extend(((RULES,0x5cc),(RULES+0x5d0,0x30)))
   writes.extend(((LIST+4,12),(LIST+0x14,4),(LIST+0x19,2),(LIST+0x2c4,4),(RULES+0x5cc,4),(0x84e9e8,4),(0xa3d298,4),(0xa3f208,2),(0x839980,12)))
  try:
   for i in range(f['initial']):
    p=NODES+i*0x100;self.checked_call(0x6f15c0,[LIST+0x2c8+i*324,-11,23,3,4],p,writes=writes,inputs=inputs);self.put(p+4,p+0x100 if i+1<f['initial'] else 0);self.put(p+8,p-0x100 if i else 0);self.put(p+0x20,0x12345778);u.mem_write(p+0x1c,b'\2');u.mem_write(p+0x41,b'\3');self.put(p+0x10,100+i)
   before=bytes(u.mem_read(ARENA,SIZE));returns=[]
   for i in range(f['repeats']):
    self.checked_call(0x5b4da0,[PREFIX if f['hasPrefix'] else 0,0x81234567,BODY if f['bodyPresent'] else 0,-2,0x12345678,f['lifetime'],f['silent']],LIST,writes=writes,inputs=inputs);returns.append(str(self.ident(u.reg_read(UC_X86_REG_EAX))))
   after=bytearray(u.mem_read(ARENA,SIZE))
   for p,n in writes:
    if ARENA<=p<ARENA+SIZE:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
   assert after==before,'Message insertion changed unowned arena'
   result=['R',str(len(returns)),*returns,'H',str(self.ident(self.word(LIST))),'U',*[str(struct.unpack('<H',u.mem_read(LIST+0x1480+i*2,2))[0]) for i in range(14)],'B',hashlib.sha256(u.mem_read(LIST+0x2c8,14*324)).hexdigest(),'G',*[str(self.ident(self.word(0x865ff0+i*4))) for i in range(3)],'N',str(self.allocated)]
   signed=lambda v:v if v<2**31 else v-2**32
   for i in range(self.allocated):
    p=NODES+i*0x100;b=bytes(u.mem_read(p,76));w=lambda off:struct.unpack_from('<I',b,off)[0];text=w(0x30);slot=(text-LIST-0x2c8)//324 if LIST+0x2c8<=text<LIST+0x1480 and (text-LIST-0x2c8)%324==0 else -1
    result.extend(map(str,['O',i+1,self.ident(w(4)),self.ident(w(8)),*[signed(w(o)) for o in (12,16,20,24)],*b[28:32],*[w(o) for o in (32,36,40,44)],slot,signed(w(52)),signed(w(56)),w(60),b[64],b[65],struct.unpack_from('<H',b,66)[0],w(68),w(72),int(w(0)==0x7a18b4)]))
   result.extend(map(str,['L',*[signed(self.word(LIST+o)) for o in (4,8,0x2c4,0x14,0xc)],*u.mem_read(LIST+0x19,2),signed(self.word(0xa3d298)),*u.mem_read(0xa3f208,2),self.word(0x839980),self.word(0x839988),signed(self.word(RULES+0x5cc)),int(bool(self.word(0x84e9e8)))]))
   result.extend(('E',*self.events));return result
  finally:self.active=False
