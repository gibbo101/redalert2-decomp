# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Unit split root with actual contact reads and final pixels."""
from original_foot_depth import FootDepthOracle
from original_unit_surface import ARENA,UNIT,TYPE,VT,WORLD,SOURCE,DEPTH
from original_foot_lit import words,ret
from verify_unit_surface_split import verify
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
CONTACT=ARENA+0xb000;CONTACT_TYPE=ARENA+0xc000;CONTACT_VT=ARENA+0x3d000
CONTACTS=ARENA+0x3e000;KIND=CONTACTS+0x100
class UnitSurfaceSplitOracle(FootDepthOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe)
        self.split_active=False;self.prefix=None;self.world_values=None
        self.split_roots=0;self.contact_getters=0;self.kind_calls=0;self.gradient_calls={0:0,2:0}
    def route(self,u,a,n,ctx):
        if getattr(self,'split_active',False):
            sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
            if a==0x636e20:
                assert ecx==UNIT and words(u,sp+4,1)==[0]
                self.event('contact');self.contact_getters+=1
            elif a==KIND:
                assert ecx==CONTACT;self.event('kind');self.kind_calls+=1
                ret(u,0,self.prefix[5]);return
            elif a==0x6ff436:self.event('ctype')
            elif a==DEPTH:
                self.event('depth');value=self.depth_values[min(self.depth_index,1)];self.depth_index+=1
                ret(u,0,value);return
            elif a==0x434b40 and self.pixel_mode:
                assert ecx==WORLD
                args=words(u,sp+4,9);assert args[1]==SOURCE and args[4]==0x1600900 and args[6] in (0,2) and args[8]==0
                self.final_children+=1;self.gradient_calls[args[6]]+=1;return
        super().route(u,a,n,ctx)
    def setup(self,values,pixels=False):
        result=super().setup(values,pixels)
        if self.prefix is not None:
            flag,p100,p0,field494,present,kind,typeflag=self.prefix
            self.u.mem_write(TYPE+0xbae,bytes([flag&255]));self.put(UNIT+0x494,field494)
            self.put(UNIT+0xcc,CONTACTS);self.put(CONTACTS,CONTACT if present else 0)
            self.put(CONTACT,CONTACT_VT);self.put(CONTACT_VT+0x2c,KIND);self.put(CONTACT+0x418,CONTACT_TYPE)
            self.u.mem_write(CONTACT_TYPE+0x1357,bytes([typeflag&255]))
            if self.world_values is not None:self.world(self.world_values)
            self.capture_predicates=self.world_values is None;self.predicates=[p0,0,0,p100,0]
            self.depth_index=0;self.actual_base=False;self.base_return=None
        return result
    def forwarding(self,v,world=None):
        self.prefix=v[:7];self.world_values=world
        layer,first,second,extra,l4,z,z2,gradient,*geometry=v[7:]
        self.depth_values=[z,z2];self.depth_active=True;self.split_active=True
        try:
            result=super().draw([layer,l4,first,second,0,0,0,0,0,0,0,-1,0,0,extra,z,gradient,0,*geometry])
        finally:self.depth_active=False;self.split_active=False;self.prefix=None;self.world_values=None
        self.split_roots+=1;return result
    def pixels(self,v):
        self.prefix=v[:7];self.world_values=None;values=v[7:];self.depth_values=[values[-3]]*2
        self.depth_active=True;self.split_active=True
        # Use the surface parent directly: FootDepthOracle's pixel entry selects
        # another actual-base fixture. This suite supplies both depth values.
        from original_unit_surface import UnitSurfaceOracle
        try:result=UnitSurfaceOracle.pixels(self,values)
        finally:self.depth_active=False;self.split_active=False;self.prefix=None
        self.split_roots+=1;return result
