# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original5FE1B0 over distinct font/surface identities and real children."""
import struct
from original_font_text import FontTextOracle,SURFACEOBJ,VT,TEXT
from original_font_glyph import ARENA,SIZE,FONT,PRIMARY,INDICES,GLYPHS,FALLBACK,SURFACE,STUB,digest,signed
from original_presentation import STOP
from verify_font_alignment import verify,RANGES,TABLES,GLOBALS
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
FONT2=ARENA+0x5000;SURFACE2=ARENA+0x6000;BOX=ARENA+0x7000
class FontAlignmentOracle(FontTextOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a==STUB:super().code(u,a,n,ctx);return
  if a==0x5fe26a:
   sp=u.reg_read(UC_X86_REG_ESP);self.event('M',self.word(sp+0x10),self.word(sp+0x14))
   if self.f['diagnostic']:
    x,y,w,h=struct.unpack('<4I',u.mem_read(BOX,16));u.mem_write(BOX,struct.pack('<4I',(x+5)&0xffffffff,(y-2)&0xffffffff,(w+3)&0xffffffff,(h+4)&0xffffffff))
  if a in (STUB+16,STUB+32,STUB+48,STUB+64,STUB+80):
   receiver=u.reg_read(UC_X86_REG_ECX);assert receiver in (SURFACEOBJ,SURFACE2);self.event('C',1 if receiver==SURFACEOBJ else 2,0)
   font=FONT2 if self.f['fontChoice'] else FONT;kind={STUB+16:'L',STUB+32:'P',STUB+48:'V',STUB+64:'H',STUB+80:'U'}[a];self.event(kind,bool(self.word(font+12)),self.word(font+16));self.counts['supplied.'+kind]+=1
   if kind=='L':
    sp=u.reg_read(UC_X86_REG_ESP);assert self.word(sp+4)==self.word(sp+8)==0;self.ret(8,SURFACE)
   elif kind=='P':self.ret(0,self.f['pitch'])
   elif kind=='V':self.ret(0,self.f['width'])
   elif kind=='H':
    if self.f['mutation']==1:u.mem_write(font+0x30,struct.pack('<4i',2,2,19,15))
    self.ret(0,self.f['height'])
   else:
    if self.f['mutation']==2:self.put(font+16,777);self.put(font+12,SURFACE)
    self.ret(0,0x12345678)
   return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected aligned text instruction',hex(a))
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
  u.mem_write(0xa40d28,bytes([f['enabled']]));u.mem_write(0xab6849,bytes(f['target']));u.mem_write(TEXT+f['offset'],f['text']+b'\0\0');u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));u.mem_write(BOX,struct.pack('<4i',*f['box']));before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  font=FONT2 if f['fontChoice'] else FONT
  writes=[(font+12,8),(font+32,6),(font+48,16),(font+65,1),(SURFACE,1536)] if f['enabled'] else []
  if f['enabled'] and f['diagnostic']:writes.append((BOX,16))
  inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),*[(a,4) for a in GLOBALS],(0xab6849,3),(0xa40d28,1),(0x839958,4),(0x84e9e8,4),(0x84e9d0,4)]
  try:self.checked_call(0x5fe1b0,[BOX,TEXT+f['offset'],f['count'],f['horizontal'],f['vertical'],SURFACE2 if f['surfaceChoice'] else 0,f['reveal']],f['rgb'],FONT2 if f['fontChoice'] else 0,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in writes:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
  assert after==before,'Aligned drawing changed unselected owner/input/padding/arena'
  def state(p):return [struct.unpack('<H',u.mem_read(p+36,2))[0],signed(self.word(p+16)),signed(self.word(p+32)),int(bool(self.word(p+12))),*struct.unpack('<4i',u.mem_read(p+48,16))]
  from unicorn.x86_const import UC_X86_REG_EAX
  return ['R',str(signed(u.reg_read(UC_X86_REG_EAX))),'B',digest(bytes(u.mem_read(SURFACE,1536))),'T',digest(self.trace),'S',*map(str,state(FONT)),'D',*map(str,state(FONT2)),'Q',*map(str,struct.unpack('<4i',u.mem_read(BOX,16))),'E',str(int(bool(u.mem_read(FONT+65,1)[0]))),str(int(bool(u.mem_read(FONT2+65,1)[0])))]
