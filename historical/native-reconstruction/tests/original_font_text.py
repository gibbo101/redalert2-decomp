# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original text-to-pixels and binding; named surface methods supplied."""
import struct
from original_font_glyph import FontGlyphOracle,ARENA,SIZE,FONT,PRIMARY,INDICES,GLYPHS,FALLBACK,SURFACE,STUB,digest,signed
from original_presentation import STOP
from verify_font_text import verify,RANGES,TABLES,GLOBALS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
SURFACEOBJ=ARENA+0x3000;VT=ARENA+0x4000;TEXT=ARENA+0x280000
class FontTextOracle(FontGlyphOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def read(self,u,access,p,n,value,context):
  # Compare ordered raster reads; actual measurement has its existing separate
  # trace proof and is entered here without replacement in shortened-reveal tails.
  if 0x4318e0<=u.reg_read(UC_X86_REG_EIP)<0x431cbd:super().read(u,access,p,n,value,context)
 def ret(self,n,value):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a==STUB:super().code(u,a,n,ctx);return
  if a in (STUB+16,STUB+32,STUB+48,STUB+64,STUB+80):
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   kind={STUB+16:'L',STUB+32:'P',STUB+48:'V',STUB+64:'H',STUB+80:'U'}[a];self.event(kind,bool(self.word(FONT+12)),self.word(FONT+16));self.counts['supplied.'+kind]+=1
   if kind=='L':
    sp=u.reg_read(UC_X86_REG_ESP);assert self.word(sp+4)==self.word(sp+8)==0;self.ret(8,SURFACE)
   elif kind=='P':self.ret(0,self.f['pitch'])
   elif kind=='V':self.ret(0,self.f['width'])
   elif kind=='H':
    if self.f['mutation']==1:u.mem_write(FONT+0x30,struct.pack('<4i',2,2,19,15))
    self.ret(0,self.f['height'])
   else:
    if self.f['mutation']==2:self.put(FONT+16,777);self.put(FONT+12,SURFACE)
    self.ret(0,0x12345678)
   return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected text instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(INDICES,f['indices']);u.mem_write(GLYPHS,f['glyph']);u.mem_write(FALLBACK,f['fb']);self.glyphSize=len(f['glyph']);self.fallbackSize=len(f['fb'])
  for p,v in ((FONT+4,PRIMARY if f['present'] else 0),(FONT+8,FALLBACK if f['fallback'] else 0),(FONT+12,SURFACE if f['bound'] else 0),(FONT+16,32),(FONT+24,f['stride']),(FONT+28,f['line']),(FONT+32,f['origin']),(FONT+36,f['color']),(FONT+40,f['tab']),(FONT+44,f['spacing']),(PRIMARY+8,f['rows']),(PRIMARY+20,f['glyphStride']),(PRIMARY+24,INDICES),(PRIMARY+28,GLYPHS)):self.put(p,v)
  u.mem_write(FONT+0x30,struct.pack('<4i',*f['clip']));u.mem_write(FONT+0x41,bytes([f['clipping']]));self.put(0x79a4a8,STUB);self.put(SURFACEOBJ,VT)
  for off,target in ((0x5c,16),(0x74,32),(0x7c,48),(0x80,64),(0x60,80)):self.put(VT+off,STUB+target)
  for a,v in zip(GLOBALS,f['shifts']):self.put(a,v)
  u.mem_write(0xab6849,bytes(f['target']));u.mem_write(TEXT+f['offset'],f['text']+b'\0\0');u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  writes=[(FONT+12,8),(FONT+32,6),(FONT+48,16),(SURFACE,1536)];inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),*[(a,4) for a in GLOBALS],(0xab6849,3)]
  try:
   if f['op']=='J':self.checked_call(0x432350,[FONT if f['fontPresent'] else 0,SURFACEOBJ,TEXT+f['offset'],f['x'],f['y'],f['count'],f['reveal']],writes=writes,inputs=inputs)
   elif f['op']=='D':self.checked_call(0x431cc0,[TEXT+f['offset'],f['x'],f['y'],f['count'],f['reveal']],FONT,writes=writes,inputs=inputs)
   else:
    self.checked_call(0x4320b0,[SURFACEOBJ],FONT,writes=writes,inputs=inputs);self.checked_call(0x432150,[SURFACEOBJ],FONT,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in writes:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
  assert after==before,'Text changed unowned font/input/padding/arena storage'
  color=struct.unpack('<H',u.mem_read(FONT+36,2))[0];state=[color,signed(self.word(FONT+16)),signed(self.word(FONT+32)),int(bool(self.word(FONT+12))),*struct.unpack('<4i',u.mem_read(FONT+48,16))]
  return ['R',str(signed(u.reg_read(UC_X86_REG_EAX))),'B',digest(bytes(u.mem_read(SURFACE,1536))),'T',digest(self.trace),'S',*map(str,state)]
