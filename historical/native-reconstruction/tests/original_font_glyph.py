# SPDX-License-Identifier: GPL-3.0-or-later
"""Original complete glyph raster; only USER32 SetRect is supplied."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_font_glyph import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x400000;FONT=ARENA+0x1000;PRIMARY=ARENA+0x2000;INDICES=ARENA+0x10000;GLYPHS=ARENA+0x40000;FALLBACK=ARENA+0x200000;SURFACE=ARENA+0x210000;STUB=ARENA+0x300000
def digest(b):return hashlib.sha256(b).hexdigest()
def signed(v):return v if v<2**31 else v-2**32
class FontGlyphOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def event(self,k,a,v):self.trace.extend(k.encode()+struct.pack('<II',a,v))
 def read(self,u,access,p,n,value,_):
  if not self.active:return
  if INDICES<=p<INDICES+131072:
   assert n==2;self.event('I',(p-INDICES)//2,int.from_bytes(u.mem_read(p,n),'little'))
  elif GLYPHS<=p<GLYPHS+self.glyphSize:
   assert n==1;self.event('G',p-GLYPHS+1,u.mem_read(p,1)[0])
  elif FALLBACK<=p<FALLBACK+self.fallbackSize:
   assert n==1;self.event('F',p-FALLBACK,u.mem_read(p,1)[0])
 def write(self,u,access,p,n,value,_):
  if self.active and SURFACE<=p<SURFACE+1536:
   assert n==2 and p%2==0;self.event('W',(p-SURFACE)//2,value&65535)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==STUB:
   sp=u.reg_read(UC_X86_REG_ESP);p=self.word(sp+4);u.mem_write(p,bytes(u.mem_read(sp+8,16)));self.counts['supplied.SetRect']+=1
   target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+24);u.reg_write(UC_X86_REG_EAX,1);u.reg_write(UC_X86_REG_EIP,target);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected glyph instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(INDICES,f['indices']);u.mem_write(GLYPHS,f['glyph']);u.mem_write(FALLBACK,f['fb']);self.glyphSize=len(f['glyph']);self.fallbackSize=len(f['fb'])
  for p,v in ((FONT+4,PRIMARY if f['present'] else 0),(FONT+8,FALLBACK if f['fallback'] else 0),(FONT+12,SURFACE if f['surface'] else 0),(FONT+16,32),(FONT+24,f['stride']),(FONT+32,f['origin']),(FONT+36,0xabcd),(FONT+40,f['tab']),(FONT+44,f['spacing']),(PRIMARY+8,f['rows']),(PRIMARY+20,f['glyphStride']),(PRIMARY+24,INDICES),(PRIMARY+28,GLYPHS)):self.put(p,v)
  u.mem_write(FONT+0x30,struct.pack('<4i',*f['clip']));u.mem_write(FONT+0x41,bytes([f['clipping']]));self.put(0x79a4a8,STUB)
  u.mem_write(SURFACE,struct.pack('<768H',*((i*29+0x1234)&65535 for i in range(768))));before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  try:self.checked_call(0x4318e0,[f['code'],f['x'],f['y'],f['color']],FONT,writes=[(SURFACE,1536)],inputs=[*RANGES.items(),(0x79a4a8,4)])
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE));after[SURFACE-ARENA:SURFACE-ARENA+1536]=before[SURFACE-ARENA:SURFACE-ARENA+1536];assert after==before,'Glyph changed font, padding or unrelated arena'
  return ['R',str(signed(u.reg_read(UC_X86_REG_EAX))),'B',digest(bytes(u.mem_read(SURFACE,1536))),'T',digest(self.trace)]
