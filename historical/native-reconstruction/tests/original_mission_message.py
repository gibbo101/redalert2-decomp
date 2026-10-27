# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action11 -> fixed original message receiver -> actual text pixels."""
import struct,hashlib
from original_message_pipeline import MessagePipelineOracle,RULES
from original_mission_text_action import ARENA as MISSION,SIZE as MISSION_SIZE,ACTION,SCENARIO
from original_string_lookup import ARENA as LOOKUP,SIZE as LOOKUP_SIZE,LABELS,TEXT as SLOTS,EXTRA
from original_font_glyph import FONT,SURFACE,STUB,digest,signed
from original_presentation import STOP
from verify_message_text_lookup import RANGES as LOOKUP_RANGES
from verify_mission_message import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
LIST=0xa3dc70;PAYLOAD=LOOKUP+0x8000
class MissionMessageOracle(MessagePipelineOracle):
 def __init__(self,exe):
  super().__init__(exe,list_address=LIST);self.inspection=verify(exe.read_bytes());self.u.mem_map(MISSION,MISSION_SIZE);self.u.mem_map(LOOKUP,LOOKUP_SIZE)
 def initialize_extra(self,f):
  u=self.u;u.mem_write(MISSION,b'\xa5'*MISSION_SIZE);u.mem_write(LOOKUP,b'\xa5'*LOOKUP_SIZE)
  self.put(LIST,0);u.mem_write(LIST+0x2c8,bytes(14*324));u.mem_write(LIST+0x1480,struct.pack('<14H',*[1]*14))
  self.put(FONT+16,0);self.put(FONT+36,0);u.mem_write(FONT+48,bytes(16));self.put(0xb263ec,0);self.put(0xb263f0,0)
  self.put(0xa3d290,SCENARIO);self.put(0xad0440,LABELS);self.put(0xad0438,len(f['labels']));self.put(0xad0444,SLOTS);self.put(0xad0448,EXTRA);self.put(0xb2b098,0)
  u.mem_write(0x7f3224,bytes(c&255 for c in f['colorTable']))
  for i,(key,index,payload) in enumerate(f['labels']):
   u.mem_write(LABELS+i*40,bytes(40));u.mem_write(LABELS+i*40,key+b'\0');self.put(LABELS+i*40+36,index)
   u.mem_write(PAYLOAD+i*1024,payload+b'\0\0');self.put(SLOTS+i*4,PAYLOAD+i*1024)
  self.sounds=[];self.fills=[];self.lines=[]
 def extra_inputs(self):return [*RANGES.items(),*TABLES.items(),(0x7f3224,9),(0xad0438,20),(0xb2b098,4),(0x79b608,8),(0x7d8964,4),(0xa3d290,4)]
 def guarded_regions(self):return (*super().guarded_regions(),(LIST,0x149c),(MISSION,MISSION_SIZE),(LOOKUP,LOOKUP_SIZE))
 def prepare_action(self,op,values):
  if op!='M':return
  alternate,bits,key=values;u=self.u
  u.mem_write(ACTION+0x54,bytes(32));u.mem_write(ACTION+0x54,key+b'\0');self.put(ACTION+0x2c,11)
  u.mem_write(SCENARIO+0x2239,bytes([alternate]));u.mem_write(RULES+0x1128,struct.pack('<Q',bits))
 def additional_action(self,op,values,writes,inputs):
  assert op=='M'
  self.checked_call(0x6adae0,[0,0,ACTION+0xc0,ACTION+0x80],ACTION,writes=writes,inputs=[*inputs,(ACTION,0x100),(SCENARIO+0x2239,1),(RULES+0x1128,8)])
  return self.u.reg_read(UC_X86_REG_EAX)&255
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a==0x713db0:
   sp=u.reg_read(UC_X86_REG_ESP);self.sounds.append((signed(u.reg_read(UC_X86_REG_ECX)),u.reg_read(UC_X86_REG_EDX),self.word(sp+4),self.word(sp+8)))
  if a==STUB+96:
   sp=u.reg_read(UC_X86_REG_ESP);self.fills.append((*struct.unpack('<4i',u.mem_read(self.word(sp+4),16)),self.word(sp+8)))
  if any(lo<=a and a+n<=lo+size for lo,size in LOOKUP_RANGES.items()):
   if a in LOOKUP_RANGES:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def snapshot(self):
  u=self.u;nodes=[];p=self.word(LIST)
  while p:assert len(nodes)<256;p0=p;nodes.append(p0);p=self.word(p0+4)
  def ident(p):return nodes.index(p)+1 if p else 0
  out=['H',len(nodes),'U',*struct.unpack('<14H',u.mem_read(LIST+0x1480,28)),'B',digest(bytes(u.mem_read(LIST+0x2c8,14*324))),'G',*[ident(self.word(0x865ff0+i*4)) for i in range(3)]]
  for p in nodes:
   b=bytes(u.mem_read(p,76));w=lambda off:struct.unpack_from('<I',b,off)[0];slot=(w(48)-LIST-0x2c8)//324
   out.extend(['O',ident(w(4)),ident(w(8)),*[signed(w(o)) for o in (12,16,20,24)],*b[28:32],*[w(o) for o in (32,36,40,44)],slot,signed(w(52)),signed(w(56)),w(60),b[64],b[65],struct.unpack_from('<H',b,66)[0],w(68),w(72)])
  out.extend(['L',*[signed(self.word(LIST+o)) for o in (4,8,0x2c4,0x14,0xc)],*u.mem_read(LIST+0x19,2),signed(self.word(0xa3d298)),*u.mem_read(0xa3f208,2),self.word(0x839980),self.word(0x839988),signed(self.word(RULES+0x5cc))])
  out.extend(['S',struct.unpack('<H',u.mem_read(FONT+36,2))[0],signed(self.word(FONT+16)),signed(self.word(FONT+32)),int(bool(self.word(FONT+12))),*struct.unpack('<4i',u.mem_read(FONT+48,16)),int(bool(u.mem_read(FONT+65,1)[0])),'P',digest(bytes(u.mem_read(SURFACE,1536)))])
  for r in self.sounds:out.extend(['A',*r])
  for r in self.fills:out.extend(['B',*r])
  return digest(' '.join(map(str,out)).encode())

 def run(self,f):return super().run(f)[:-2]
