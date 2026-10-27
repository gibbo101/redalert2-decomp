# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual resource children nested inside the unchanged decoded overlay reader."""
from original_overlay_map_preparation import OverlayMapPreparationOracle,ACTORS
from original_map_overlay_loading import ROOT,TYPES,MAP,pack
from original_foot_lit import words,ret
from verify_overlay_map_resources import verify,RANGES,CHILDREN
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
from unicorn import UC_HOOK_MEM_WRITE
RESOURCE_TABLE=ACTORS+0xb0000
RESOURCE_RECORDS=RESOURCE_TABLE+0x1000
class OverlayMapResourceOracle(OverlayMapPreparationOracle):
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes())
        self.roots.update({hex(a):0 for a in CHILDREN});self.resource_entries=self.classifier_entries=self.missing_logs=0
        self.resource_stack=[];self.classifier_overlay=-1
        self.frames=list(self.u.mem_read(0x7d2c10,36))[::4]
    def code(self,u,a,n,ctx):
        if a==ROOT:
            # Parent fixture setup is complete. Verify the supplied records were
            # installed before the audited call, rather than writing them here.
            assert [u.mem_read(TYPES+i*1024+0x279,1)[0] for i in range(len(self.flags))]==self.flags
        if any(lo<=a and a+n<=lo+size for lo,size in CHILDREN.items()):
            if a in CHILDREN:self.roots[hex(a)]+=1
            if a==0x476ba0:
                receiver=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
                assert words(u,sp+4,1)==[0]
                caller=words(u,sp,1)[0];assert any(lo<=caller<lo+size for lo,size in RANGES.items())
                id=self.cell_id(receiver);self.resource_stack.append(id);self.events.extend([51,id,0]);self.resource_entries+=1
            elif a in (0x476ca5,0x476caf):
                id=self.resource_stack.pop();self.events.extend([66,id,u.reg_read(UC_X86_REG_EAX)])
            elif a==0x5dc0b0:
                self.classifier_overlay=u.reg_read(UC_X86_REG_ECX);self.events.extend([65,self.classifier_overlay]);self.classifier_entries+=1
            return
        if a==0x4068f0:
            sp=u.reg_read(UC_X86_REG_ESP);assert words(u,sp+4,1)==[0x7e8b60]
            assert bytes(u.mem_read(sp+8,49))==bytes(49)
            self.events.extend([67,self.classifier_overlay]);self.missing_logs+=1;self.service_calls+=1;ret(u,0,0);return
        return super().code(u,a,n,ctx)
    def checked_call(self,*args,**kwargs):
        if args[0]==ROOT:
            # The inherited run() installs base types immediately before this
            # call. Resource fields/globals are fixture inputs, not guest stores.
            for i,flag in enumerate(self.flags):self.u.mem_write(TYPES+i*1024+0x279,bytes([flag]))
            self.u.mem_write(RESOURCE_TABLE,pack([RESOURCE_RECORDS+i*0x180 for i in range(len(self.resources))]))
            self.u.mem_write(RESOURCE_RECORDS,b'\xa5'*0x1000)
            for i,(index,image,images,slopes,frames,value) in enumerate(self.resources):
                p=RESOURCE_RECORDS+i*0x180
                for off,v in ((0x98,index),(0xb8,value),(0xe0,TYPES+image*1024),(0xe4,frames),(0xe8,images),(0xec,slopes)):self.put(p+off,v)
            self.put(0xac0b34,RESOURCE_TABLE);self.put(0xac0b40,len(self.resources))
            kwargs['inputs']=[*kwargs['inputs'],(RESOURCE_TABLE,0x2000),(0xac0b34,16),(0x7d2c10,36)]
            before=bytes(self.u.mem_read(RESOURCE_RECORDS,0x1000))
            # Also reject writes restored before final snapshots. Stack/selected
            # Cell/actor writes retain the inherited ordered/capacity audits.
            def guard(u,access,p,n,value,ctx):
                assert not (RESOURCE_TABLE<=p<RESOURCE_RECORDS+0x1000 or 0xac0b34<=p<0xac0b44 or 0x7d2c10<=p<0x7d2c34),'Resource input write'
            hook=self.u.hook_add(UC_HOOK_MEM_WRITE,guard)
            try:result=super().checked_call(*args,**kwargs)
            finally:self.u.hook_del(hook)
            assert not self.resource_stack
            assert bytes(self.u.mem_read(RESOURCE_RECORDS,0x1000))==before
            return result
        return super().checked_call(*args,**kwargs)
    def run(self,op,v):
        assert op=='N';count=v[0];at=1+count*6;self.resources=[v[i:i+6] for i in range(1,at,6)]
        flag_count=v[at];at+=1;self.flags=v[at:at+flag_count];at+=flag_count
        assert v[at:at+9]==self.frames;at+=9
        return super().run('M',v[at:])
