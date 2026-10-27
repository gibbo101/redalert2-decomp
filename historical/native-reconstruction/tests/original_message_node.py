# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original node admission/color/typewriter through real text pixels."""
import struct
from original_message_text import MessageTextOracle
from original_font_alignment import FONT2,SURFACE2,BOX
from original_font_text import SURFACEOBJ,VT,TEXT
from original_font_glyph import ARENA,SIZE,FONT,PRIMARY,INDICES,GLYPHS,FALLBACK,SURFACE,STUB,digest,signed
from original_presentation import STOP
from verify_message_node import verify,RANGES,TABLES,GLOBALS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
NODE=ARENA+0x8000;COLORTABLE=ARENA+0x9000;COLORS=ARENA+0xa000;RULES=ARENA+0xb000;TEXT2=TEXT+0x10000
class MessageNodeOracle(MessageTextOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x497a50:self.currentFont=self.word(0x84e9e8)
  if a in (STUB+16,STUB+32,STUB+48,STUB+64,STUB+80):
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   font=self.currentFont;kind={STUB+16:'L',STUB+32:'P',STUB+48:'V',STUB+64:'H',STUB+80:'U'}[a];self.event(kind,bool(self.word(font+12)),self.word(font+16));self.counts['supplied.'+kind]+=1
   if kind=='L':assert self.word(sp+4)==self.word(sp+8)==0;self.ret(8,SURFACE)
   elif kind=='P':self.ret(0,self.f['pitch'])
   elif kind=='V':
    if not self.widthCalls and self.f['nodeMutation']&4:
     self.put(NODE+12,7);self.put(NODE+16,9);self.put(NODE+0x38,15);self.put(FONT+28,7);self.put(0x84e9e8,FONT2)
     for i in range(2):u.mem_write(COLORS+i*0x400+0x30a,bytes([173]))
    self.widthCalls+=1;self.ret(0,self.f['width'])
   elif kind=='H':
    if self.f['mutation']==1:u.mem_write(font+0x30,struct.pack('<4i',2,2,19,15))
    self.ret(0,self.f['height'])
   else:
    if self.f['mutation']==2:self.put(font+16,777);self.put(font+12,SURFACE)
    self.ret(0,0x12345678)
   return
  if a==STUB+112:
   now=(self.f['milliseconds']+self.f['timeStep']*self.clock)&0xffffffff;self.clock+=1;self.event('t',now,0);self.counts['supplied.timeGetTime']+=1
   if self.f['nodeMutation']&1:self.put(NODE+0x44,3);self.put(NODE+0x48,now-48);self.put(NODE+0x30,TEXT2);self.put(0x865ff8,0 if self.word(0x865ff8) else NODE)
   self.ret(0,now);return
  if a==0x713db0:
   sound=u.reg_read(UC_X86_REG_ECX);flags=u.reg_read(UC_X86_REG_EDX);assert flags==8192 and [self.word(sp+i) for i in (4,8)]==[0x3f800000,0];self.event('a',sound,flags);self.counts['supplied.sound']+=1
   if self.f['nodeMutation']&2:self.put(NODE+0x44,2);self.put(NODE+0x48,99);self.put(NODE+0x30,TEXT2);self.put(NODE+0x3c,1);self.put(0x865ff8,0 if self.word(0x865ff8) else NODE)
   self.ret(8,0);return
  if any(lo<=a and a+n<=lo+size for lo,size in ((0x6f1620,0x1b7),(0x4cf240,0x20),(0x4cf630,0xe),(0x497a50,6),(0x4ff050,0x115))):
   if a in RANGES:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.f=f;self.widthCalls=0;self.clock=0;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(INDICES,f['indices']);u.mem_write(GLYPHS,f['glyph']);u.mem_write(FALLBACK,f['fb']);self.glyphSize=len(f['glyph']);self.fallbackSize=len(f['fb'])
  for p,v in ((FONT+4,PRIMARY if f['present'] else 0),(FONT+8,FALLBACK if f['fallback'] else 0),(FONT+12,SURFACE if f['bound'] else 0),(FONT+16,32),(FONT+24,f['stride']),(FONT+28,f['line']),(FONT+32,f['origin']),(FONT+36,f['color']),(FONT+40,f['tab']),(FONT+44,f['spacing']),(PRIMARY+8,f['rows']),(PRIMARY+20,f['glyphStride']),(PRIMARY+24,INDICES),(PRIMARY+28,GLYPHS)):self.put(p,v)
  u.mem_write(FONT+0x30,struct.pack('<4i',*f['clip']));u.mem_write(FONT+0x41,bytes([f['clipping']]));u.mem_write(FONT2,bytes(u.mem_read(FONT,0x44)))
  for off,value in ((44,f['spacing']+2),(28,f['line']+1),(40,f['tab']+3),(32,f['origin']+17)):self.put(FONT2+off,value)
  self.put(0x79a4a8,STUB);self.put(SURFACEOBJ,VT);self.put(SURFACE2,VT)
  for off,target in ((0x5c,16),(0x74,32),(0x7c,48),(0x80,64),(0x60,80)):self.put(VT+off,STUB+target)
  for a,v in zip(GLOBALS,f['shifts']):self.put(a,v)
  for a,v in ((0x839958,SURFACEOBJ),(0x84e9e8,FONT if f['fontPresent'] else 0),(0x84e9d0,0)):self.put(a,v)
  u.mem_write(0xa40d28,bytes([f['enabled']]));u.mem_write(0xab6849,bytes(f['target']));u.mem_write(TEXT+f['offset'],f['text']+b'\0\0');u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));u.mem_write(BOX,struct.pack('<4i',*f['box']));self.put(VT+0x14,STUB+96);self.put(0x839d4c,0);self.put(0x83995c,SURFACEOBJ)
  self.put(NODE,0x7adccc)
  for off,value in ((12,f['nodeX']),(16,f['nodeY']),(0x30,TEXT+f['offset']),(0x34,f['selector']),(0x38,f['maximumWidth']),(0x3c,f['initialScroll']),(0x44,f['initialReveal']),(0x48,f['initialTime'])):self.put(NODE+off,value)
  u.mem_write(NODE+0x1c,bytes([f['dirty']]));u.mem_write(NODE+0x40,bytes((f['hidden'],f['typewriter'])));self.put(0x865ff8,NODE if f['focus'] else 0)
  self.put(0xab6f08,f['colorCount']);self.put(0xab6efc,COLORTABLE)
  for i in range(2):self.put(COLORTABLE+i*4,0 if f['missing']&(1<<i) else COLORS+i*0x400);u.mem_write(COLORS+i*0x400+0x308,bytes(f['hsv'][i]))
  u.mem_write(TEXT2,'baX'.encode('utf-16le')+b'\0\0');self.put(0x79a524,STUB+112);self.put(0x839848,RULES);self.put(RULES+0x5e4,-7)
  self.put(0xb263e4,0);self.put(0xb263ec,2);self.put(0xb263f0,1);self.put(0xb263f4,0);u.mem_write(0xb261a8,b'a\0b\0\0\0');self.put(0xa76150,0);self.put(0xa7338c,0x789abc);self.put(0xa763ec,0)
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  writes=[(FONT+12,8),(FONT+32,6),(FONT+48,16),(FONT+65,1),(SURFACE,1536),(NODE+0x1c,1),(NODE+0x3c,4),(NODE+0x44,8),(0xa763ec,4),(0xb261a8,2),(0xb263ec,4),(0xb263f0,4)]
  inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),*[(a,4) for a in GLOBALS],(0xab6849,3),(0xa40d28,1),(0x839958,4),(0x83995c,4),(0x84e9e8,4),(0x84e9d0,4),(0x839d4c,2),(0xb263e4,4),(0xb263f4,4),(0xa76150,4),(0xa7338c,4),(0x79a524,4),(0x839848,4),(0x865ff8,4),(0xab6efc,4),(0xab6f08,4)]
  writes.extend([(FONT2+12,8),(FONT2+32,6),(FONT2+48,16),(FONT2+65,1)])
  if f['nodeMutation']&3:writes.extend([(NODE+0x30,4),(0x865ff8,4)]);inputs.remove((0x865ff8,4))
  if f['nodeMutation']&4:
   writes.extend([(NODE+12,8),(NODE+0x38,4),(FONT+28,4),(0x84e9e8,4),(COLORS+0x30a,1),(COLORS+0x70a,1)]);inputs.remove((0x84e9e8,4))
  results=[]
  try:
   for _ in range(f['repeats']):self.checked_call(0x6f1620,[f['force']],NODE,writes=writes,inputs=inputs);results.append(str(u.reg_read(UC_X86_REG_EAX)))
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in writes:
   if ARENA<=p<p+n<=ARENA+SIZE:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
  assert after==before,'Aligned drawing changed unselected owner/input/padding/arena'
  def state(p):return [struct.unpack('<H',u.mem_read(p+36,2))[0],signed(self.word(p+16)),signed(self.word(p+32)),int(bool(self.word(p+12))),*struct.unpack('<4i',u.mem_read(p+48,16))]
  slot=0 if self.word(NODE+0x30)==TEXT+f['offset'] else 1
  return ['R',str(len(results)),*results,'B',digest(bytes(u.mem_read(SURFACE,1536))),'T',digest(self.trace),'S',*map(str,state(FONT)),'D',*map(str,state(FONT2)),'E',str(int(bool(u.mem_read(FONT+65,1)[0]))),str(int(bool(u.mem_read(FONT2+65,1)[0]))),'O',str(signed(self.word(NODE+12))),str(signed(self.word(NODE+16))),str(signed(self.word(NODE+0x38))),str(u.mem_read(NODE+0x1c,1)[0]),str(self.word(NODE+0x3c)),*map(str,u.mem_read(NODE+0x40,2)),str(self.word(NODE+0x44)),str(self.word(NODE+0x48)),str(slot),'F',str(int(self.word(0x865ff8)==NODE)),'G',str(int(self.word(0x84e9e8)==FONT2)),'H',str(signed(self.word(FONT+28))),str(signed(self.word(FONT2+28))),'C',*map(str,u.mem_read(COLORS+0x308,3)),*map(str,u.mem_read(COLORS+0x708,3))]
