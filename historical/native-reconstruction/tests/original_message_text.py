# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original scratch/scroll/segment consumer through actual text pixels."""
import struct
from original_font_alignment import FontAlignmentOracle,FONT2,SURFACE2,BOX
from original_font_text import FontTextOracle,SURFACEOBJ,VT,TEXT
from original_font_glyph import ARENA,SIZE,FONT,PRIMARY,INDICES,GLYPHS,FALLBACK,SURFACE,STUB,digest,signed
from original_presentation import STOP
from verify_message_text import verify,RANGES,TABLES,GLOBALS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EDI
SCROLL=ARENA+0x7100
class MessageTextOracle(FontAlignmentOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x737e30 and self.f['imeContext']:
   self.counts['supplied.IME']+=1;self.event('i',self.word(0xb263ec),self.word(0xb263f0));self.ret(0,0);return
  if a==STUB+96:
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   b=struct.unpack('<4I',u.mem_read(self.word(sp+4),16));self.event('b',b[0],b[1]);self.event('b',b[2],b[3]);self.event('b',self.word(sp+8),0);self.counts['supplied.fill']+=1;self.ret(8,1);return
  if a==0x5fd290:
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   from unicorn.x86_const import UC_X86_REG_EDX
   x,y=struct.unpack('<2I',u.mem_read(u.reg_read(UC_X86_REG_EDX),8));x2,y2=struct.unpack('<2I',u.mem_read(self.word(sp+4),8));assert x==x2
   self.event('c',x,y);self.event('c',y2,self.word(sp+8));self.event('c',self.word(sp+12),0);self.counts['supplied.line']+=1;self.ret(12,1);return
  if a==0x600938:
   for i,unit in enumerate(struct.unpack('<2048H',u.mem_read(sp+0x40,4096))):self.event('s',i,unit)
  if a==0x6009a0:self.event('f',u.reg_read(UC_X86_REG_EDI),u.reg_read(UC_X86_REG_EAX))
  if a==0x600a31:self.event('w',u.reg_read(UC_X86_REG_EAX),0)
  if a in (STUB+16,STUB+32,STUB+48,STUB+64,STUB+80):FontTextOracle.code(self,u,a,n,ctx);return
  if a==STUB or 0x431000<=a<0x433000 or 0x5fe1b0<=a<0x5fe375 or 0x63cf20<=a<0x63cfa6:super().code(u,a,n,ctx);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected message consumer instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(INDICES,f['indices']);u.mem_write(GLYPHS,f['glyph']);u.mem_write(FALLBACK,f['fb']);self.glyphSize=len(f['glyph']);self.fallbackSize=len(f['fb'])
  for p,v in ((FONT+4,PRIMARY if f['present'] else 0),(FONT+8,FALLBACK if f['fallback'] else 0),(FONT+12,SURFACE if f['bound'] else 0),(FONT+16,32),(FONT+24,f['stride']),(FONT+28,f['line']),(FONT+32,f['origin']),(FONT+36,f['color']),(FONT+40,f['tab']),(FONT+44,f['spacing']),(PRIMARY+8,f['rows']),(PRIMARY+20,f['glyphStride']),(PRIMARY+24,INDICES),(PRIMARY+28,GLYPHS)):self.put(p,v)
  u.mem_write(FONT+0x30,struct.pack('<4i',*f['clip']));u.mem_write(FONT+0x41,bytes([f['clipping']]));u.mem_write(FONT2,bytes(u.mem_read(FONT,0x44)))
  for off,value in ((44,f['spacing']+2),(28,f['line']+1),(40,f['tab']+3),(32,f['origin']+17)):self.put(FONT2+off,value)
  self.put(0x79a4a8,STUB);self.put(SURFACEOBJ,VT);self.put(SURFACE2,VT)
  for off,target in ((0x5c,16),(0x74,32),(0x7c,48),(0x80,64),(0x60,80)):self.put(VT+off,STUB+target)
  for a,v in zip(GLOBALS,f['shifts']):self.put(a,v)
  for a,v in ((0x839958,SURFACEOBJ),(0x84e9e8,FONT if f['fontPresent'] else 0),(0x84e9d0,0)):self.put(a,v)
  u.mem_write(0xa40d28,bytes([f['enabled']]));u.mem_write(0xab6849,bytes(f['target']));u.mem_write(TEXT+f['offset'],f['text']+b'\0\0');u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));u.mem_write(BOX,struct.pack('<4i',*f['box']));self.put(VT+0x14,STUB+96);self.put(0x839d4c,0)
  self.put(SCROLL,f['scroll']);self.put(0xb263e4,f['imeContext']);self.put(0xb263ec,len(f['composition'])//2);self.put(0xb263f0,f['compositionCursor']);self.put(0xb263f4,f['extra']);u.mem_write(0xb261a8,f['composition']+b'\0\0');self.put(0xa76150,f['highlight']);self.put(0xa7338c,f['cursorRgb']);self.put(0xa763ec,f['suppression'])
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  font=FONT2 if f['fontChoice'] else FONT
  writes=[(FONT+12,8),(FONT+32,6),(FONT+48,16),(FONT+65,1),(SURFACE,1536),(BOX,16),(SCROLL,4),(0xa763ec,4)]
  if f['ime']:writes.extend([(0xb261a8,2),(0xb263ec,4),(0xb263f0,4)])
  inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),*[(a,4) for a in GLOBALS],(0xab6849,3),(0xa40d28,1),(0x839958,4),(0x84e9e8,4),(0x84e9d0,4),(0x839d4c,2),(0xb263e4,4),(0xb263f4,4),(0xa76150,4),(0xa7338c,4)]
  try:self.checked_call(0x600830,[0 if f['nullText'] else TEXT+f['offset'],f['caret'],FONT,f['rgb'],SCROLL,f['ime'],f['mask'],f['background'],f['reveal']],SURFACEOBJ,BOX,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in writes:
   if ARENA<=p<p+n<=ARENA+SIZE:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
  assert after==before,'Aligned drawing changed unselected owner/input/padding/arena'
  def state(p):return [struct.unpack('<H',u.mem_read(p+36,2))[0],signed(self.word(p+16)),signed(self.word(p+32)),int(bool(self.word(p+12))),*struct.unpack('<4i',u.mem_read(p+48,16))]
  return ['R','0','B',digest(bytes(u.mem_read(SURFACE,1536))),'T',digest(self.trace),'S',*map(str,state(FONT)),'Q',*map(str,struct.unpack('<4i',u.mem_read(BOX,16))),'Z',str(signed(self.word(SCROLL))),str(signed(self.word(0xa763ec))),str(signed(self.word(0xb263ec))),str(signed(self.word(0xb263f0))),str(signed(self.word(0xb263f4))),str(int(bool(u.mem_read(FONT+65,1)[0])))]
