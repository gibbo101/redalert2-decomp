# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual complete expiry composed with original insertion and shared node owners."""
import struct,hashlib
from original_message_list import MessageListOracle,ARENA,SIZE,LIST,FONT,PRIMARY,GLYPH,NODES,INDICES,BODY,RULES,CLOCK
from original_presentation import STOP
from verify_message_expiry import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX
class MessageExpiryOracle(MessageListOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.updating=False
 def code(self,u,a,n,context):
  if not self.active or a==STOP:return
  if 0x5b5610<=a and a+n<=0x5b56ec:
   if a==0x5b5610:self.counts[hex(a)]+=1
   return
  if a==CLOCK:
   value=self.f['times'][self.clock%len(self.f['times'])];self.clock+=1;self.events.extend(('T',str(value)));self.counts['supplied.timeGetTime']+=1
   if self.updating and self.f['mutation']&1:
    self.put(0x839980,7);self.put(0x839988,777)
    if self.allocated:self.put(NODES+0x24,0)
    if self.allocated>1:self.put(NODES+0x100+0x24,101)
   self.ret(0,value);return
  if a==0x781d3b:
   from unicorn.x86_const import UC_X86_REG_ESP
   p=self.word(u.reg_read(UC_X86_REG_ESP)+4);self.events.extend(('F',str(self.ident(p))));self.counts['supplied.free']+=1
   if self.updating and self.f['mutation']&2:
    self.put(0x839980,0xffffffff);self.put(0x839988,101);self.put(LIST+8,-17);self.put(LIST+0x14,2147483647);u.mem_write(LIST+0x19,b'\2\3')
    if self.allocated>1:self.put(NODES+0x100+0x24,0)
   if self.updating and self.f['mutation']&4:
    living=[NODES+i*0x100 for i in range(self.allocated) if self.word(NODES+i*0x100)==0x7adccc];last=living[-1] if living else 0;self.put(LIST,last);self.put(p+4,last)
   self.ret(0);return
  super().code(u,a,n,context)
 def snapshot(self,result):
  u=self.u;signed=lambda v:v if v<2**31 else v-2**32
  out=['R',str(result),'H',str(self.ident(self.word(LIST))),'U',*[str(struct.unpack('<H',u.mem_read(LIST+0x1480+i*2,2))[0]) for i in range(14)],'B',hashlib.sha256(u.mem_read(LIST+0x2c8,14*324)).hexdigest(),'G',*[str(self.ident(self.word(0x865ff0+i*4))) for i in range(3)],'N',str(self.allocated)]
  for i in range(self.allocated):
   p=NODES+i*0x100;b=bytes(u.mem_read(p,76));w=lambda off:struct.unpack_from('<I',b,off)[0];text=w(48);slot=(text-LIST-0x2c8)//324 if LIST+0x2c8<=text<LIST+0x1480 and (text-LIST-0x2c8)%324==0 else -1
   out.extend(map(str,['O',i+1,self.ident(w(4)),self.ident(w(8)),*[signed(w(o)) for o in (12,16,20,24)],*b[28:32],*[w(o) for o in (32,36,40,44)],slot,signed(w(52)),signed(w(56)),w(60),b[64],b[65],struct.unpack_from('<H',b,66)[0],w(68),w(72),int(w(0)==0x7a18b4)]))
  out.extend(map(str,['L',signed(self.word(LIST+8)),signed(self.word(LIST+0x14)),*u.mem_read(LIST+0x19,2),self.word(0x839980),self.word(0x839988),self.clock,'E',*self.events,'END']));return out
 def run(self,f):
  u=self.u;self.f=dict(f,mutation=0);self.updating=False;self.clock=0;self.allocated=len(f['nodes']);self.events=[];u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(LIST,NODES if self.allocated else 0)
  for o,v in ((4,-11),(8,f['y']),(0xc,4),(0x14,f['step']),(0x2c4,120)):self.put(LIST+o,v)
  u.mem_write(LIST+0x19,bytes((f['res19'],f['res1a'])))
  occupied={slot for _,slot in f['nodes']}
  for i in range(14):u.mem_write(LIST+0x1480+i*2,struct.pack('<H',0 if i in occupied else 0x101))
  for p,v in ((0x84e9e8,FONT),(FONT+4,PRIMARY),(FONT+8,GLYPH),(FONT+0x1c,12),(FONT+0x28,64),(FONT+0x2c,1),(PRIMARY+0x14,1),(PRIMARY+0x18,INDICES),(PRIMARY+0x1c,GLYPH),(0xa3d298,0),(0x839980,f['start']),(0x839988,f['accum']),(0x839848,RULES),(RULES+0x5cc,-7),(0x79a524,CLOCK)):self.put(p,v)
  u.mem_write(INDICES,b'\1\0'*65536);u.mem_write(GLYPH,b'\5');u.mem_write(0xa3f208,b'\1\1')
  for i in range(3):self.put(0x865ff0+i*4,NODES if self.allocated and f['focus']&(1<<i) else 0)
  immutable=[*RANGES.items(),*TABLES.items(),(0x84e9e8,4),(FONT,0x300),(INDICES,131072),(0xa3d298,4),(0xa3f208,2),(0x839848,4),(RULES,0x600),(0x79a524,4)]
  writes=[(LIST,4),(LIST+0x2c8,14*324),(LIST+0x1480,28),(NODES,256*0x100),(0x865ff0,12)]
  if f['mutation']:writes.extend(((LIST+8,4),(LIST+0x14,4),(LIST+0x19,2),(0x839980,12)))
  else:immutable.append((0x839980,12))
  self.active=True
  try:
   for i,(expiry,slot) in enumerate(f['nodes']):
    p=NODES+i*0x100;self.checked_call(0x6f15c0,[LIST+0x2c8+slot*324 if slot>=0 else BODY,-11,f['y'],3,4],p,writes=writes,inputs=immutable);self.put(p+4,p+0x100 if i+1<self.allocated else 0);self.put(p+8,p-0x100 if i else 0);self.put(p+0x24,expiry);self.put(p+0x20,0x12345778);self.put(p+0x10,100+i);u.mem_write(p+0x1c,b'\2');u.mem_write(p+0x41,b'\3')
   self.f['mutation']=f['mutation'];out=[]
   for operation in f['operations']:
    if operation[0]=='I':u.mem_write(BODY,operation[2]+b'\0\0')
    before=bytes(u.mem_read(ARENA,SIZE));self.updating=operation[0]=='U'
    if self.updating:self.checked_call(0x5b5610,ecx=LIST,writes=writes,inputs=immutable)
    else:
     # Original insertion has its own diagnostics disabled in this suite; only
     # expiry leaves perform the declared late mutations.
     saved=self.f['mutation'];self.f['mutation']=0
     try:self.checked_call(0x5b4da0,[0,77,BODY,-2,0x12345678,operation[1],1],LIST,writes=writes,inputs=[*immutable,(BODY,len(operation[2])+2)])
     finally:self.f['mutation']=saved
    result=u.reg_read(UC_X86_REG_EAX);result=result if self.updating else self.ident(result)
    self.updating=False;after=bytearray(u.mem_read(ARENA,SIZE))
    for p,n in writes:
     if ARENA<=p<ARENA+SIZE:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
    assert after==before,'Message expiry changed unowned arena';out.extend(self.snapshot(result))
   return out
  finally:self.active=False;self.updating=False
