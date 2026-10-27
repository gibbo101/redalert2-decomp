# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete resource classifier on the same overlay owner as radar colors."""
from original_radar_demand_color import RadarDemandColorOracle
from original_cell_radar_color import TYPES,OVERLAY
from original_presentation import STOP
from verify_radar_resource_color import RANGE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
TABLE=TYPES+0xc800;RECORDS=TYPES+0xd000;IMAGES=TYPES+0xe000
class RadarResourceColorOracle(RadarDemandColorOracle):
 def setup(self):
  super().setup()
  for i,(index,image,images,slopes,frames,value) in enumerate(self.resources):
   record=RECORDS+i*0x100;imageType=IMAGES+i*0x300
   self.put(TABLE+i*4,record)
   for off,v in ((0x98,index),(0xb8,value),(0xe0,imageType),(0xe4,frames),(0xe8,images),(0xec,slopes)):self.put(record+off,v)
   self.put(imageType+0x264,image)
  self.put(0xac0b34,TABLE);self.put(0xac0b40,len(self.resources));self.typeExpected=bytearray(self.u.mem_read(TYPES,0x10000))
 def code(self,u,a,n,ctx):
  if self.active and a!=STOP:
   if a==RANGE[0]:
    self.classified=u.reg_read(UC_X86_REG_ECX);assert self.classified==self.currentOverlay;self.emit('E',self.classified);self.counts['actual_resource']+=1
   if a in (0x5dc158,0x5dc164,0x5dc16d):self.emit('Y',u.reg_read(UC_X86_REG_EAX));self.counts['resource_return']+=1
   if RANGE[0]<=a and a+n<=RANGE[0]+RANGE[1]:return
   if a==0x4068f0 and self.word(u.reg_read(UC_X86_REG_ESP))==0x5dc14e:
    sp=u.reg_read(UC_X86_REG_ESP);assert self.word(sp+4)==0x7e8b60 and bytes(u.mem_read(sp+8,49))==bytes(u.mem_read(OVERLAY+0x64,49))
    self.emit('Z',self.classified);self.counts['missing_resource_log']+=1
  super().code(u,a,n,ctx)
 def checked_call(self,*args,**kwargs):
  kwargs['inputs']=[*kwargs.get('inputs',[]),RANGE,(0xac0b34,16)];super().checked_call(*args,**kwargs)
 def run(self,f):
  self.resources=f['resources'];return super().run(f)
