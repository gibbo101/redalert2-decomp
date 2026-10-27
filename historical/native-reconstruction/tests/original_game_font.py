# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original successful fonT constructor/load/fallback and metric consumers."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_game_font import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x600000;FONT=ARENA+0x1000;NAME=ARENA+0x2000;FILE=ARENA+0x3000;VT=ARENA+0x3100;DEF=ARENA+0x4000;INDICES=ARENA+0x10000;GLYPHS=ARENA+0x40000;FALLBACK=ARENA+0x300000;TEXT=ARENA+0x310000;OUT=ARENA+0x310500;STUB=ARENA+0x580000
def digest(data):return hashlib.sha256(data).hexdigest()
def signed(v):return v if v<2**31 else v-2**32
class GameFontOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
  if a in (0x782017,0x782630):
   size=self.word(sp+4);slot=len(self.allocations);address=(FILE,DEF,INDICES,GLYPHS,FALLBACK)[slot];bound=(0x100,0x100,0x20000,0x200000,0x10000)[slot];assert size<=bound and (a==0x782630)==(slot==4)
   self.allocations.append((address,size));self.counts['supplied.allocate']+=1;self.ret(0,address);return
  if a==0x468f50:
   assert receiver==FILE and self.word(sp+4)==NAME;self.counts['supplied.file_constructor']+=1;self.ret(4,FILE);return
  if a==STUB:
   assert receiver==FILE and self.word(sp+4)==1;self.counts['supplied.file_destructor']+=1;self.ret(4);return
  if a in (STUB+0x10,STUB+0x20):
   assert receiver==FILE and self.word(sp+4)==(0 if a==STUB+0x10 else 1);self.counts['supplied.file_exists_or_open']+=1;self.ret(4,1);return
  if a==STUB+0x30:
   assert receiver==FILE;p,size=self.word(sp+4),self.word(sp+8);assert any(lo<=p and p+size<=lo+n for lo,n in self.allocations) or size==28
   data=self.file[self.cursor:self.cursor+size];
   if data:u.mem_write(p,data)
   self.cursor+=len(data);self.counts['supplied.file_read']+=1;self.ret(8,len(data));return
  if a==STUB+0x40:
   p=self.word(sp+4);assert p==FONT+0x30;u.mem_write(p,bytes(16));assert [self.word(sp+i) for i in (8,12,16,20)]==[0]*4;self.counts['supplied.SetRect']+=1;self.ret(20,1);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected game font path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  u=self.u;self.file=f['file'];assert self.file[:4]==b'fonT';self.cursor=0;self.allocations=[];u.mem_write(ARENA,bytes([f['fill']])*SIZE)
  self.put(FILE,VT)
  for offset,target in ((0,STUB),(0x14,STUB+0x10),(0x1c,STUB+0x20),(0x24,STUB+0x30)):self.put(VT+offset,target)
  self.put(0x79a4a8,STUB+0x40);u.mem_write(NAME,b'GAME.FNT\0');before=bytes(u.mem_read(ARENA,SIZE));self.active=True
  inputs=[*RANGES.items(),*TABLES.items(),(0x79a4a8,4),(FILE,4),(VT,0x28),(NAME,9)]
  try:
   self.checked_call(0x431040,[NAME],FONT,writes=[(FONT,0x44),(DEF,0x24),(INDICES,0x20000),(GLYPHS,0x200000),(FALLBACK,0x10000)],inputs=inputs)
   assert u.reg_read(UC_X86_REG_EAX)==FONT and self.word(FONT+4)==DEF and self.word(FONT+8)==FALLBACK and len(self.allocations)==5
   fields=[self.word(DEF+i*4) for i in range(6)];glyphSize=self.allocations[3][1];fallbackSize=self.allocations[4][1]
   result=['D',*[str(v) for v in fields],str(self.word(DEF+0x20)),'I',digest(bytes(u.mem_read(INDICES,131072))),'G',digest(bytes(u.mem_read(GLYPHS,glyphSize))),'F',digest(bytes(u.mem_read(FALLBACK,fallbackSize)))]
   after=bytearray(u.mem_read(ARENA,SIZE))
   for p,n in [(FONT,0x44),*self.allocations]:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
   assert after==before,'Font loader changed unowned arena storage'
   for text in ('Hello','a\tb\r\nx','a b','\uffffX'):
    raw=text.encode('utf-16le');u.mem_write(TEXT,raw+b'\0\0');snapshot=bytes(u.mem_read(ARENA,SIZE))
    self.checked_call(0x4314b0,[TEXT,OUT,OUT+4,0],FONT,writes=[(OUT,8)],inputs=inputs)
    width,height=signed(self.word(OUT)),signed(self.word(OUT+4))
    self.checked_call(0x431710,[TEXT,32,111,1],FONT,inputs=inputs);fit=signed(u.reg_read(UC_X86_REG_EAX))
    self.checked_call(0x431690,[TEXT,0],FONT,inputs=inputs);wrapper=signed(u.reg_read(UC_X86_REG_EAX))
    result.extend(('Q',str(width),str(height),str(fit),str(wrapper)))
    check=bytearray(u.mem_read(ARENA,SIZE));check[OUT-ARENA:OUT-ARENA+8]=snapshot[OUT-ARENA:OUT-ARENA+8];assert check==snapshot,'Font metrics changed font owner/input'
   result.extend(('R','1'));return result
  finally:self.active=False
