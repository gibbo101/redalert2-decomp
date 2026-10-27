# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual unchanged Cell selector, first-use RNG table and XOR generator step."""
import hashlib,struct
from original_presentation import PresentationOracle,ARG
from original_foot_lit import words
from verify_tile_variants import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX
CELL=ARG+0x1000;TYPE=ARG+0x2000;IMAGE=ARG+0x3000;REGISTRY=ARG+0x4000
RNG=0x839218;CACHE=0x850aa8;FLAG=0x850c47
def digest(values):return hashlib.sha256(struct.pack('<'+'I'*len(values),*[v&0xffffffff for v in values])).hexdigest()
class TileVariantOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.entries={hex(a):0 for a in RANGES};self.u.hook_add(UC_HOOK_CODE,self.code)
    def va(self,a):return a
    def code(self,u,a,n,ctx):
        if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected variant instruction {a:#x}')
        if a in RANGES:self.entries[hex(a)]+=1
        if a==0x638840:self.rng_calls+=1
    def setup_rng(self,disabled,first,second,table):
        self.rng_calls=0;self.u.mem_write(RNG,bytes([disabled,0xa5,0xa5,0xa5])+struct.pack('<252I',first,second,*table))
    def rng_digest(self):return digest([self.u.mem_read(RNG,1)[0],*words(self.u,RNG+4,252)])
    def random(self,disabled,first,second,count,table):
        self.setup_rng(disabled,first,second,table);output=[]
        for i in range(count):
            self.checked_call(0x638840,ecx=RNG,writes=[(RNG+4,1008)],inputs=[(RNG,4)])
            output.append(self.u.reg_read(UC_X86_REG_EAX))
        return [count,digest(output),self.rng_digest(),self.rng_calls]
    def variant(self,initialized,disabled,first,second,table,cache,small,neighbors,x,y,sub,count,columns,rows,present):
        self.setup_rng(disabled,first,second,table);self.u.mem_write(FLAG,bytes([initialized]));self.u.mem_write(CACHE,struct.pack('<64I',*[v&0xffffffff for v in cache]))
        self.u.mem_write(CELL,bytes(0x150));self.put(CELL+0x24,(x&65535)|((y&65535)<<16));self.u.mem_write(CELL+0x11a,bytes([sub]))
        self.u.mem_write(TYPE,bytes(0x2dc));self.put(TYPE,0x7a51a8);self.put(TYPE+0xa4,IMAGE if present else 0)
        self.put(0xa40cd4,REGISTRY);self.put(REGISTRY,TYPE);self.u.mem_write(IMAGE,struct.pack('<4i',columns,rows,60,30))
        self.u.mem_write(0x7d2b90,struct.pack('<16i',*small));self.u.mem_write(0x7d2bd0,struct.pack('<16i',*[n for pair in neighbors for n in pair]))
        self.checked_call(0x4767a0,[0,count],CELL,writes=[(FLAG,1),(CACHE,256),(RNG+4,1008)],
          inputs=[(RNG,4),(CELL,0x150),(TYPE,0x2dc),(IMAGE,16),(0xa40cd4,4),(REGISTRY,4),(0x7d2b90,128)])
        result=self.u.reg_read(UC_X86_REG_EAX)
        return [result,digest([self.u.mem_read(FLAG,1)[0],*words(self.u,CACHE,64)]),self.rng_digest(),self.rng_calls]
