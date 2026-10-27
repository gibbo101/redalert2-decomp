# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual shared message lifecycle and ordinary list/gadget/text drawing roots."""
import struct
from original_message_node import MessageNodeOracle
from original_font_alignment import FONT2,SURFACE2,BOX
from original_font_text import SURFACEOBJ,VT,TEXT
from original_font_glyph import ARENA,SIZE,FONT,PRIMARY,INDICES,GLYPHS,FALLBACK,SURFACE,STUB,digest,signed
from original_presentation import STOP
from original_message_list import ARENA as EXTRA,SIZE as EXTRA_SIZE,LIST,NODES,PREFIX,BODY
from verify_message_pipeline import verify,RANGES,RAW,TABLES,GLOBALS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESI,UC_X86_REG_ESP
RULES=EXTRA+0x74000;COLORTABLE=ARENA+0x9000;COLORS=ARENA+0xa000
class MessagePipelineOracle(MessageNodeOracle):
 def __init__(self,exe,list_address=LIST):
  super().__init__(exe);self.list_address=list_address;self.inspection=verify(exe.read_bytes());self.u.mem_map(EXTRA,EXTRA_SIZE)
 def ident(self,p):
  if not p:return 0
  assert NODES<=p<NODES+256*0x100 and (p-NODES)%0x100==0,('Unknown pipeline node',hex(p));return (p-NODES)//0x100+1
 def node(self,i):
  assert 0<=i<=self.allocated
  return NODES+(i-1)*0x100 if i else 0
 def mutate(self,bit):
  if not self.drawing or not self.current or not self.f['pipelineMutation']&bit or self.used&bit:return
  self.used|=bit
  if bit in (1,2):self.put(self.current+4,self.node(3) if self.allocated>=3 else 0)
  if bit==4 and self.allocated:self.put(self.list_address,self.node(self.allocated))
  if bit==8:self.put(0x839980,0xffffffff);self.put(0x839988,101);self.put(self.current+0x24,1)
  if bit==16 and self.allocated:self.put(0x865ff8,self.node(self.allocated));self.u.mem_write(self.node(self.allocated)+0x1c,b'\1');self.u.mem_write(self.node(self.allocated)+0x40,b'\0')
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4cf272:
   self.current=u.reg_read(UC_X86_REG_ESI);self.event('n',self.ident(self.current),0)
  if a==0x4cf281:self.event('l',self.ident(u.reg_read(UC_X86_REG_ESI)),self.ident(u.reg_read(UC_X86_REG_EAX)))
  if a==0x497a50:self.currentFont=self.word(0x84e9e8)
  if a==0x782017:
   assert self.word(sp+4)==76 and self.allocated<256;self.allocated+=1;p=self.node(self.allocated);self.event('A',self.allocated,0);self.counts['supplied.allocate']+=1;self.ret(0,p);return
  if a==0x781d3b:
   self.event('F',self.ident(self.word(sp+4)),0);self.counts['supplied.free']+=1;self.ret(0,0);return
  if a==STUB+112:
   now=(self.milliseconds+self.timeStep*self.clock)&0xffffffff;self.clock+=1;self.event('t',now,0);self.counts['supplied.timeGetTime']+=1;self.mutate(1);self.ret(0,now);return
  if a==0x713db0:
   sound=u.reg_read(UC_X86_REG_ECX);flags=u.reg_read(UC_X86_REG_EDX);assert flags==8192 and [self.word(sp+i) for i in (4,8)]==[0x3f800000,0];self.event('a',sound,flags);self.counts['supplied.sound']+=1;self.mutate(2);self.mutate(8);self.ret(8,0);return
  if a==STUB+96:
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   b=struct.unpack('<4I',u.mem_read(self.word(sp+4),16));self.event('b',b[0],b[1]);self.event('b',b[2],b[3]);self.event('b',self.word(sp+8),0);self.counts['supplied.fill']+=1;self.mutate(4);self.mutate(16);self.ret(8,1);return
  if any(lo<=a and a+n<=lo+size for lo,size in RAW.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def snapshot(self):
  u=self.u;out=['H',self.ident(self.word(self.list_address)),'U',*struct.unpack('<14H',u.mem_read(self.list_address+0x1480,28)),'B',digest(bytes(u.mem_read(self.list_address+0x2c8,14*324))),'G',*[self.ident(self.word(0x865ff0+i*4)) for i in range(3)],'N',self.allocated]
  for i in range(self.allocated):
   p=self.node(i+1);b=bytes(u.mem_read(p,76));w=lambda off:struct.unpack_from('<I',b,off)[0];text=w(0x30);slot=(text-self.list_address-0x2c8)//324 if self.list_address+0x2c8<=text<self.list_address+0x1480 and (text-self.list_address-0x2c8)%324==0 else -1
   out.extend(['O',i+1,self.ident(w(4)),self.ident(w(8)),*[signed(w(o)) for o in (12,16,20,24)],*b[28:32],*[w(o) for o in (32,36,40,44)],slot,signed(w(52)),signed(w(56)),w(60),b[64],b[65],struct.unpack_from('<H',b,66)[0],w(68),w(72),int(w(0)==0x7a18b4)])
  out.extend(['L',*[signed(self.word(self.list_address+o)) for o in (4,8,0x2c4,0x14,0xc)],*u.mem_read(self.list_address+0x19,2),signed(self.word(0xa3d298)),*u.mem_read(0xa3f208,2),self.word(0x839980),self.word(0x839988),signed(self.word(RULES+0x5cc)),int(bool(self.word(0x84e9e8)))])
  out.extend(['S',struct.unpack('<H',u.mem_read(FONT+36,2))[0],signed(self.word(FONT+16)),signed(self.word(FONT+32)),int(bool(self.word(FONT+12))),*struct.unpack('<4i',u.mem_read(FONT+48,16)),int(bool(u.mem_read(FONT+65,1)[0])),'P',digest(bytes(u.mem_read(SURFACE,1536))),'I',signed(self.word(0xb263ec)),signed(self.word(0xb263f0)),signed(self.word(0xb263f4)),signed(self.word(0xa763ec))])
  return digest(' '.join(map(str,out)).encode())
 def run(self,f):
  self.f=f;self.widthCalls=0;self.clock=0;self.allocated=0;self.drawing=False;self.current=0;self.used=0;self.milliseconds=f['milliseconds'];self.timeStep=f['timeStep'];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(EXTRA,b'\xa5'*EXTRA_SIZE);u.mem_write(INDICES,f['indices']);u.mem_write(GLYPHS,f['glyph']);u.mem_write(FALLBACK,f['fb']);self.glyphSize=len(f['glyph']);self.fallbackSize=len(f['fb'])
  for p,v in ((FONT+4,PRIMARY if f['present'] else 0),(FONT+8,FALLBACK if f['fallback'] else 0),(FONT+12,SURFACE if f['bound'] else 0),(FONT+16,32),(FONT+24,f['stride']),(FONT+28,f['line']),(FONT+32,f['origin']),(FONT+36,f['color']),(FONT+40,f['tab']),(FONT+44,f['spacing']),(PRIMARY+8,f['rows']),(PRIMARY+20,f['glyphStride']),(PRIMARY+24,INDICES),(PRIMARY+28,GLYPHS)):self.put(p,v)
  u.mem_write(FONT+0x30,struct.pack('<4i',*f['clip']));u.mem_write(FONT+0x41,bytes([f['clipping']]));u.mem_write(FONT2,bytes(u.mem_read(FONT,0x44)))
  for off,value in ((44,f['spacing']+2),(28,f['line']+1),(40,f['tab']+3),(32,f['origin']+17)):self.put(FONT2+off,value)
  self.put(0x79a4a8,STUB);self.put(SURFACEOBJ,VT);self.put(SURFACE2,VT)
  for off,target in ((0x5c,16),(0x74,32),(0x7c,48),(0x80,64),(0x60,80)):self.put(VT+off,STUB+target)
  for a,v in zip(GLOBALS,f['shifts']):self.put(a,v)
  for a,v in ((0x839958,SURFACEOBJ),(0x84e9e8,FONT if f['fontPresent'] else 0),(0x84e9d0,0)):self.put(a,v)
  u.mem_write(0xa40d28,bytes([f['enabled']]));u.mem_write(0xab6849,bytes(f['target']));u.mem_write(TEXT+f['offset'],f['text']+b'\0\0');u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));u.mem_write(BOX,struct.pack('<4i',*f['box']));self.put(VT+0x14,STUB+96);self.put(0x839d4c,0);self.put(0x83995c,SURFACEOBJ)
  self.put(self.list_address,0)
  for off,value in ((4,f['listX']),(8,f['listY']),(0xc,f['capacity']),(0x14,f['lineStep']),(0x2c4,f['listWidth'])):self.put(self.list_address+off,value)
  u.mem_write(self.list_address+0x19,b'\0\0');u.mem_write(self.list_address+0x1480,struct.pack('<14H',*[0x101]*14))
  for a,v in ((0x839980,f['start']),(0x839988,f['accum']),(0xa3d298,f['mode']),(0x79a524,STUB+112),(0x839848,RULES),(RULES+0x5cc,-7),(RULES+0x5e4,-9),(0xab6efc,COLORTABLE),(0xab6f08,f['colorCount']),(0xb263e4,0),(0xb263ec,2),(0xb263f0,1),(0xb263f4,0),(0xa76150,0),(0xa7338c,0x789abc),(0xa763ec,0)):self.put(a,v)
  u.mem_write(0xa3f208,bytes((f['mode3'],f['mode4'])));u.mem_write(0x865ff0,b'\0'*12);u.mem_write(0xb261a8,b'a\0b\0\0\0')
  for i,hsv in enumerate(((0,255,255),(137,211,239))):self.put(COLORTABLE+i*4,0 if f['missing']&(1<<i) else COLORS+i*0x400);u.mem_write(COLORS+i*0x400+0x308,bytes(hsv))
  self.initialize_extra(f)
  self.trace=bytearray();self.active=True;result=['R',str(len(f['actions']))]
  writes=[(FONT+12,8),(FONT+32,6),(FONT+48,16),(FONT+65,1),(SURFACE,1536),(self.list_address,4),(self.list_address+0x2c8,14*324),(self.list_address+0x1480,28),(0x865ff0,12),(0xb261a8,2),(0xb263ec,4),(0xb263f0,4),(0xa763ec,4),*[(NODES+i*256,76) for i in range(256)]]
  inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),*[(a,4) for a in GLOBALS],(0xab6849,3),(0xa40d28,1),(0x839958,4),(0x83995c,4),(0x84e9e8,4),(0x84e9d0,4),(0x839d4c,2),(0xb263e4,4),(0xb263f4,4),(0xa76150,4),(0xa7338c,4),(0x79a524,4),(0x839848,4),(0xab6efc,4),(0xab6f08,4),(RULES,0x600),(0xa3d298,4),(0xa3f208,2)]
  if f['pipelineMutation']&8:writes.extend([(0x839980,4),(0x839988,4)])
  else:inputs.extend([(0x839980,4),(0x839988,4)])
  inputs.extend(self.extra_inputs())
  try:
   for op,*values in f['actions']:
    returned=0
    if op=='I':
     prefix,body,lifetime,color,flags,silent=values;u.mem_write(PREFIX,(prefix or b'')+b'\0\0');u.mem_write(BODY,body+b'\0\0')
    self.prepare_action(op,values)
    before=[bytes(u.mem_read(p,n)) for p,n in self.guarded_regions()]
    if op=='I':self.checked_call(0x5b4da0,[0 if prefix is None else PREFIX,0x81234567,BODY,color,flags,lifetime,silent],self.list_address,writes=writes,inputs=inputs);returned=self.ident(u.reg_read(UC_X86_REG_EAX))
    elif op=='E':self.checked_call(0x5b5610,ecx=self.list_address,writes=writes,inputs=inputs);returned=u.reg_read(UC_X86_REG_EAX)
    elif op in ('D','G'):
     self.drawing=True;self.current=0
     if op=='D':assert not u.mem_read(self.list_address+0x19,1)[0];self.checked_call(0x5b5b30,ecx=self.list_address,writes=writes,inputs=inputs)
     else:self.checked_call(0x4cf260,values,self.word(self.list_address),writes=writes,inputs=inputs)
     self.drawing=False;self.current=0
    elif op=='F':self.put(0x865ff8,self.node(values[0]))
    elif op=='H':
     i,dirty,hidden,typewriter,reveal,lastTime,scroll=values;p=self.node(i);assert p and self.word(p)==0x7adccc;u.mem_write(p+0x1c,bytes([dirty]));u.mem_write(p+0x40,bytes((hidden,typewriter)));self.put(p+0x44,reveal);self.put(p+0x48,lastTime);self.put(p+0x3c,scroll)
    elif op=='T':self.milliseconds,self.timeStep=values;self.clock=0
    else:returned=self.additional_action(op,values,writes,inputs)
    for (base,size),old in zip(self.guarded_regions(),before):
     after=bytearray(u.mem_read(base,size))
     for p,n in writes:
      if base<=p<p+n<=base+size:after[p-base:p-base+n]=old[p-base:p-base+n]
     assert after==old,'Pipeline changed unowned arena/input/padding'
    result.extend((str(returned),self.snapshot()))
   return result+['T',digest(self.trace)]
  finally:self.active=False

 def initialize_extra(self,f):pass
 def extra_inputs(self):return []
 def guarded_regions(self):return ((ARENA,SIZE),(EXTRA,EXTRA_SIZE))
 def additional_action(self,op,values,writes,inputs):raise ValueError('Unknown pipeline action')

 def prepare_action(self,op,values):pass
