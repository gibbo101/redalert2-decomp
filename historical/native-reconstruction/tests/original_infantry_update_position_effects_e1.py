# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified joined500AA0 -> 4C7220 -> 6C2B40 ordinary-E1 execution."""
import struct
from original_infantry_update_position_e1 import (InfantryUpdatePositionE1Oracle,
 ARENA,SIZE,ACTOR,TYPE,TARGET,LOCOMOTOR,CURRENT,TARGET_CELL,START)
from verify_infantry_position_effects_e1 import RANGES,HELPERS
from compare_post_sight_refresh import OFFSETS,SCALE
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
SLOTS=0x3c00000;MAP=0x8324e0;FALLBACK=0xa6f9f8;HOUSE=ARENA+0x8000
RULES=SLOTS+0x100000;COUNTRY=SLOTS+0x110000
NORMAL=(ARENA+0x9000,ARENA+0xa000);ELITE=(ARENA+0xb000,ARENA+0xc000)
JOINED_RANGES={0x548000:0x68,0x5d51e0:0x57,0x47ba50:0x49,0x4706c0:0x7bb,
 0x594c50:0x5c,0x6d5e90:0xa5,0x6d5c30:0x256,0x6c12c0:8,
 0x7133a0:0x27,0x713420:0x18,0x54a550:0x1c4,0x6a2970:0x3c,0x77f110:0x3e}
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
def word16(v):return ((int(v/256)+0x8000)&0xffff)-0x8000
class InfantryUpdatePositionEffectsE1Oracle(InfantryUpdatePositionE1Oracle):
 def __init__(self,exe):
  super().__init__(exe);self.u.mem_map(SLOTS,0x120000);self.stores=[];self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  if p==0xa6fa1c:
   if n!=4:raise AssertionError('Joined fallback coordinate store width differs')
   value&=0xffffffff;x,y=struct.unpack('<hh',struct.pack('<I',value))
   if self.post_phase:pass
   else:self.fallback_stores.append((x,y));self.trace.extend(('F',str(x),str(y)))
  elif p in (ACTOR+0x59c,ACTOR+0x59a,ACTOR+0x32d,0xa35e24):
   value&=(1<<(8*n))-1;self.stores.append((p,n,value))
   if p==0xa35e24:self.trace.extend(('G',str(value)))
 def code(self,u,a,n,ctx):
  if not self.active:return super().code(u,a,n,ctx)
  if a in (0x500ad4,0x5d520f,0x5d5232,0x501bf3):
   if u.reg_read(UC_X86_REG_EAX)!=self.expected_parent_cell:raise AssertionError(('Joined current Cell result differs',hex(a)))
  elif a==0x501591:
   if u.reg_read(UC_X86_REG_EAX)!=TARGET_CELL:raise AssertionError('Joined target map result differs')
  elif a==0x501586:
   q=self.point(u.reg_read(UC_X86_REG_EAX))
   if q!=self.target:raise AssertionError(('Joined target Cell coordinates differ',q,self.target))
   self.trace.extend(('T',*map(str,q)))
  if a==0x54a110:
   sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<8I',u.mem_read(sp+4,32));q=self.point(args[0])
   if args[2]!=HOUSE:raise AssertionError('Joined sight House identity differs')
   self.sight_reveals+=1;self.counts['supplied.reveal54A110']+=1;self.trace.extend(('S',*map(str,q),str(self.signed(args[1])),*[str(x) for x in args[3:]]));self.ret(32);return
  if a==0x6a8d40:
   sp=u.reg_read(UC_X86_REG_ESP);q=struct.unpack('<hh',u.mem_read(self.word(sp+4),4));value=(17+q[0]*3+q[1]*5)&255
   self.sight_masks+=1;self.counts['supplied.mask6A8D40']+=1;self.sight_mask_values.add(value);self.ret(8,value);return
  if a==0x6aadd0:self.sight_redraws+=1;self.counts['supplied.redraw6AADD0']+=1;self.ret(4);return
  if a==0x54a6bf:self.sight_fallback_stores+=1
  if a==0x54a550:
   if u.reg_read(UC_X86_REG_ECX)!=MAP:raise AssertionError('Joined post-sight map owner differs')
   sp=u.reg_read(UC_X86_REG_ESP);q=self.point(self.word(sp+4));self.trace.extend(('P',*map(str,q),str(self.signed(self.word(sp+8))),str(self.signed(self.word(sp+12))),str(self.word(sp+16))))
   if not self.f['fullPost']:
    self.counts['supplied.post_sight']+=1;self.ret(16);return
   self.counts['post_sight']+=1;self.post_phase=True
  if a==0x501bd0:self.post_phase=False
  if a==0x594770:return super().code(u,a,n,ctx)
  if a==0x4717b0 and self.word(u.reg_read(UC_X86_REG_ESP))!=0x4c7837:
   return super().code(u,a,n,ctx)
  if any(lo<=a<lo+size for lo,size in {**RANGES,**HELPERS,**JOINED_RANGES}.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   if a==0x508530:self.trace.extend(('Q',str(self.word(u.reg_read(UC_X86_REG_ESP)+4))))
   elif a==0x6c2990:self.trace.append('E')
   elif a==0x548070:
    q=struct.unpack('<hh',u.mem_read(self.word(u.reg_read(UC_X86_REG_ESP)+4),4));self.trace.extend(('c',*map(str,q)));self.counts['map']+=1
   elif a==0x47bb30:
    if u.reg_read(UC_X86_REG_ECX)!=self.expected_effect_cell:raise AssertionError('Joined dirty Cell identity differs')
    self.trace.extend(('D','1'))
   elif a==0x506950:
    self.counts['type']+=1;ret=self.word(u.reg_read(UC_X86_REG_ESP))
    if 0x6c1380<=ret<0x6c15d0 or 0x6d8540<=ret<0x6d8595:self.counts['selector_type']+=1
   elif a==0x6d8540:self.counts['selector_weapon']+=1
   elif a==0x41b320:self.trace.extend(('p',str(word16(self.signed(self.word(ACTOR+0x88)))),str(word16(self.signed(self.word(ACTOR+0x8c))))))
   elif a==0x4717b0:
    if u.reg_read(UC_X86_REG_ECX)!=self.expected_effect_cell:raise AssertionError('Joined resident Cell identity differs')
    self.trace.extend(('e6','1'))
   elif a==0x47c2c0:
    if u.reg_read(UC_X86_REG_ECX)!=self.expected_effect_cell:raise AssertionError('Joined cloak Cell identity differs')
   elif a==0x55a660:
    sp=u.reg_read(UC_X86_REG_ESP);q=struct.unpack('<hh',u.mem_read(self.word(sp+4),4));self.trace.extend(('B',*map(str,q),str(self.word(sp+8)&255)))
   elif a==0x4cafe0:self.counts['active']+=1
   elif a==0x594c50:
    if u.reg_read(UC_X86_REG_ECX)!=ACTOR:raise AssertionError('Joined Mission Commence actor differs')
    self.counts['mission_commence']+=1;self.trace.append('M');self.put(u.reg_read(UC_X86_REG_ESP)-8,0)
   elif a==0x6d5e90:
    if u.reg_read(UC_X86_REG_ECX)!=ACTOR:raise AssertionError('Joined sight-removal actor differs')
    self.counts['sight_remove']+=1;sp=u.reg_read(UC_X86_REG_ESP);self.trace.extend(('R',*[str(self.word(sp+4+i*4)) for i in range(4)]))
   elif a==0x6d5c30:
    if u.reg_read(UC_X86_REG_ECX)!=ACTOR:raise AssertionError('Joined sight-add actor differs')
    self.counts['sight_add']+=1;sp=u.reg_read(UC_X86_REG_ESP);self.trace.extend(('A',*[str(self.word(sp+4+i*4)) for i in range(4)]))
   elif a==0x5d51e0:
    if u.reg_read(UC_X86_REG_ECX)!=ACTOR:raise AssertionError('Joined current-Cell actor identity differs')
    self.counts['current_cell_getter']+=1;self.trace.append('H')
   elif a==0x548000:
    if u.reg_read(UC_X86_REG_ECX)!=MAP:raise AssertionError('Joined full-coordinate map owner differs')
    sp=u.reg_read(UC_X86_REG_ESP);ret=self.word(sp);q=self.point(self.word(sp+4));kind='W' if ret in (0x5d520f,0x5d5232) else 'C'
    if ret not in (0x5d520f,0x5d5232,0x500ad4,0x501591,0x501bf3):raise AssertionError(('Joined full-coordinate caller differs',hex(ret)))
    self.counts['full_map']+=1;self.trace.extend((kind,*map(str,q)))
   elif a==0x47ba50:
    if u.reg_read(UC_X86_REG_ECX)!=TARGET_CELL:raise AssertionError('Joined target coordinate Cell identity differs')
    self.counts['target_coordinates']+=1
   elif a==0x4706c0:
    if u.reg_read(UC_X86_REG_ECX)!=TARGET_CELL:raise AssertionError('Joined target floor Cell identity differs')
    self.counts['cell_floor']+=1
   elif a==0x77f110:self.counts['ftol']+=1
   return
  return super().code(u,a,n,ctx)
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));u.mem_write(SLOTS,bytes(0x120000));self.current=(f['x'],f['y'],f['z']);self.target=(f['tx']*256+128,f['ty']*256+128,int(f['tz']*104+0.5))
  self.put(ACTOR,0x7a3540);u.mem_write(ACTOR+0x88,pack(*self.current));self.put(ACTOR+0x98,2);self.put(ACTOR+0xa0,f['queued']);self.put(ACTOR+0x494,TARGET_CELL);self.put(ACTOR+0x5a8,TYPE);self.put(ACTOR+0x564,LOCOMOTOR);self.put(ACTOR+0x1f4,f['range']);self.put(ACTOR+0x418,-1)
  self.put(ACTOR+0x5ac,0);self.put(ACTOR+0x10c,-1);u.mem_write(ACTOR+0x118,struct.pack('<d',0.));self.put(ACTOR+0x1b4,HOUSE);self.put(HOUSE+0x30,0);self.put(HOUSE+0x34,COUNTRY);u.mem_write(COUNTRY+0x1a6,b'\0')
  u.mem_write(ACTOR+0x79,b'\0');u.mem_write(ACTOR+0x7d,bytes([f['onMap']]));u.mem_write(ACTOR+0x32d,bytes([f['enabled']]));u.mem_write(ACTOR+0x373,b'\0');u.mem_write(ACTOR+0x378,b'\0');u.mem_write(ACTOR+0x1e4,bytes([f['sightActive']]));u.mem_write(ACTOR+0x1e8,pack(111,-222,333));u.mem_write(ACTOR+0x59a,bytes([f['state59a']]));u.mem_write(ACTOR+0x59c,bytes([f['state59c']]))
  u.mem_write(TYPE+0x271,b'\0');u.mem_write(TYPE+0x283,b'\0');self.put(TYPE+0x530,5);self.put(0x839848,RULES);u.mem_write(RULES+0x5a0,struct.pack('<d',1.));self.put(RULES+0x1324,104);self.put(0xa40d2c,37)
  self.put(TARGET_CELL,0x79db04);self.put(LOCOMOTOR,0x7aead8);u.mem_write(LOCOMOTOR+0x30,b'\1');self.put(CURRENT+0xec,7);self.put(TARGET_CELL+0xec,9);self.put(FALLBACK+0xec,7);self.put(TYPE+0x538,0);self.put(TYPE+0x704,0)
  for i,p in enumerate(NORMAL):self.put(TYPE+0x74c+i*28,p)
  for i,p in enumerate(ELITE):self.put(TYPE+0x8f4+i*28,p)
  u.mem_write(NORMAL[1]+0x112,b'\0');u.mem_write(NORMAL[1]+0x126,b'\0');u.mem_write(ELITE[1]+0x112,b'\0');u.mem_write(ELITE[1]+0x126,b'\0')
  for c in (CURRENT,TARGET_CELL,FALLBACK):
   self.put(c+0xe4,0);self.put(c+0x78,0);self.put(c+0x44,-1)
  self.put(TARGET_CELL+0x24,(f['tx']&65535)|((f['ty']&65535)<<16));u.mem_write(TARGET_CELL+0x11b,bytes([f['tz']&255,0]))
  self.put(0xa40958,1);self.put(0xa35e24,0x12345678);self.put(0xa6fa1c,0x12345678)
  u.mem_write(0xa6f248,b''.join(struct.pack('<hh',*q) for q in OFFSETS));u.mem_write(0xabe490,struct.pack('<Q',SCALE))
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));self.put(0x850c40,104)
  shape=(56,3,19,50,44) if f['permission'] else (0,0,0,0,0)
  for off,value in zip((0xf0,0xf8,0xfc,0x100,0x104),shape):self.put(MAP+off,value)
  qx,qy=word16(f['x']),word16(f['y']);effect_index=qy*512+qx
  def divided(v):return v//256 if v>=0 else -((-v)//256)
  parent_index=((divided(f['y'])*512+divided(f['x']))+2**31)%2**32-2**31
  target_index=f['ty']*512+f['tx'];assert 0<=target_index<262144 and target_index not in (parent_index,effect_index)
  self.expected_parent_cell=CURRENT if 0<=parent_index<262144 else FALLBACK;self.expected_effect_cell=CURRENT if 0<=effect_index<262144 else FALLBACK
  if self.expected_parent_cell==CURRENT:self.put(SLOTS+parent_index*4,CURRENT)
  if self.expected_effect_cell==CURRENT:self.put(SLOTS+effect_index*4,CURRENT)
  self.put(SLOTS+target_index*4,TARGET_CELL)
  self.f=f;self.trace=[];self.stores=[];self.fallback_stores=[];self.post_phase=False;self.sight_fallback_stores=0;self.sight_reveals=0;self.sight_masks=0;self.sight_mask_values=set();self.sight_redraws=0;self.active=True
  actor_writes=[(ACTOR+o,n) for o,n in ((0x98,4),(0xa0,4),(0xa4,1),(0xa8,4),(0xac,4),(0xb0,4),(0xb4,4),(0xb8,4),(0x1e4,1),(0x1e8,12),(0x1f4,4),(0x32d,1),(0x378,1),(0x59a,1),(0x59c,1))]
  cell_writes=[(c+o,n) for c in (CURRENT,TARGET_CELL,FALLBACK) for o,n in ((0x120,1),(0x138,1))]
  cell_inputs=[]
  for c in (CURRENT,TARGET_CELL):cell_inputs.extend(((c,0x120),(c+0x121,0x17),(c+0x139,0xc7)))
  cell_inputs.extend(((FALLBACK,0x24),(FALLBACK+0x28,0xf8),(FALLBACK+0x121,0x17),(FALLBACK+0x139,0xc7)))
  try:self.checked_call(START,[2],ACTOR,writes=[*actor_writes,*cell_writes,(0xa35e24,4),(0xa6fa1c,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(0x7d27e8,800)],inputs=[(TYPE,0xc00),(LOCOMOTOR,0x100),*cell_inputs,(HOUSE,0x40),(COUNTRY,0x200),(RULES,0x2000),(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4),(0x839848,4),(0xa40d2c,4),(0xa6f248,len(OFFSETS)*4),(0xabe490,8),*((p,0x200) for p in (*NORMAL,*ELITE))])
  finally:self.active=False
  expected=[] if not f['onMap'] else [(ACTOR+0x59c,1,0),(ACTOR+0x59a,1,0),(0xa35e24,4,0)]+([(ACTOR+0x32d,1,1)] if f['permission'] and not f['enabled'] else [])
  if self.stores!=expected:raise AssertionError(('Joined Infantry E1 stores differ',self.stores))
  fallback_count=(8 if self.expected_parent_cell==FALLBACK else 0)+(6*f['onMap'] if self.expected_effect_cell==FALLBACK else 0)
  if len(self.fallback_stores)!=fallback_count:raise AssertionError(('Joined fallback store count differs',len(self.fallback_stores),fallback_count))
  mission=tuple(self.signed(self.word(ACTOR+o)) for o in (0x98,0xa0,0xa8,0xac,0xb0,0xb4,0xb8));last=self.point(ACTOR+0x1e8)
  self.trace.extend(('Y',*map(str,mission),str(u.mem_read(ACTOR+0xa4,1)[0]),str(struct.unpack('<b',u.mem_read(ACTOR+0x378,1))[0]),str(u.mem_read(ACTOR+0x1e4,1)[0]),*map(str,last),str(self.signed(self.word(ACTOR+0x1f4))),str(self.sight_reveals),str(self.sight_masks),str(self.sight_fallback_stores),str(self.sight_redraws),'X',str(u.mem_read(ACTOR+0x32d,1)[0])));self.counts[hex(START)]+=1;return self.trace
