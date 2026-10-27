# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual complete Cell/LAT/classifier/passability over one shared guest Cell."""
from original_map_cell_preparation import MapCellPreparationOracle,STATE,FIELD_MAP
from original_foot_lit import words,ret
from verify_resident_cell import verify
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
OVERLAY=0x2418000;OVERLAYS=0x2419000;RESOURCE=0x241a000;RESOURCE_IMAGE=0x241b000;RESOURCES=0x241c000

class ResidentCellOracle(MapCellPreparationOracle):
    state_fields=(*STATE,(0x44,4))
    store_fields={**FIELD_MAP,0x44:(8,4),0x11e:(9,1)}
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes());self.classifier_calls=self.log_calls=0
    def service(self,u,a,n,ctx):
        if 0x5dc0b0<=a and a+n<=0x5dc16e:
            if a==0x5dc0b0:
                self.actual_entries[hex(a)]=self.actual_entries.get(hex(a),0)+1
                self.events.extend([105,u.reg_read(UC_X86_REG_ECX)]);self.classifier_calls+=1
            return
        if a==0x4068f0:
            sp=u.reg_read(UC_X86_REG_ESP);assert words(u,sp+4,1)==[0x7e8b60] and bytes(u.mem_read(sp+8,49))==bytes(49)
            self.events.extend([106,self.overlay&0xffffffff]);self.log_calls+=1;ret(u,0,0);return
        super().service(u,a,n,ctx)
    def configure_cell(self):
        overlay,land,tiberium,no_use,crushable,wall,rubble,rock,image,images,slopes=self.overlay_profile;self.overlay=overlay
        u=self.u;self.put(self.cell+0x44,overlay);u.mem_write(OVERLAY,bytes(0x500));self.put(OVERLAY+0x268,land)
        for off,value in zip((0x279,0x27c,0x1fd,0x278,0x284,0x285),(tiberium,no_use,crushable,wall,rubble,rock)):
            u.mem_write(OVERLAY+off,bytes([value&255]))
        for i in range(64):self.put(OVERLAYS+i*4,OVERLAY)
        self.put(0xa35dec,OVERLAYS);self.put(0xac0b34,RESOURCES);self.put(0xac0b40,1);self.put(RESOURCES,RESOURCE)
        u.mem_write(RESOURCE,bytes(0x100));self.put(RESOURCE+0x98,0);self.put(RESOURCE+0xe0,RESOURCE_IMAGE)
        self.put(RESOURCE+0xe8,images);self.put(RESOURCE+0xec,slopes);u.mem_write(RESOURCE_IMAGE,bytes(0x300));self.put(RESOURCE_IMAGE+0x264,image)
    def checked_call(self,*args,**kwargs):
        if args[0]==0x472540:
            kwargs['inputs']=[*kwargs['inputs'],(OVERLAY,0x500),(OVERLAYS,256),(0xa35dec,4),(0xac0b34,16),
              (RESOURCE,0x100),(RESOURCE_IMAGE,0x300),(RESOURCES,4)]
        return super().checked_call(*args,**kwargs)
    def run(self,v,profile):
        self.overlay_profile=profile
        return super().run(v)
