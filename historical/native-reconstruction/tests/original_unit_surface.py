# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged final Unit wrapper, initialized selector and ordinary pixels.

Depth/gradient, alternate layers and layer-four extra are services. Healthy layer
fixtures also execute actual Foot/Drive/Techno layer; actor/house/planes remain
supplied storage. No original construction/ownership or full frame is claimed.
"""
import hashlib,struct
from original_unit_light import UnitLightOracle
from original_presentation import STACK
from original_foot_lit import words,ints,ret
from verify_unit_surface import verify
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EAX
ARENA=0x2300000;UNIT=ARENA;TYPE=ARENA+0x1000;LOCO=ARENA+0x2000;VT=ARENA+0x3000
HOUSE=ARENA+0x8000;ARRAY=ARENA+0x20000;SCHEMES=ARENA+0x21000;CVTS=ARENA+0x24000
LAYER=ARENA+0x3f000;EXTRA=LAYER+16;GRADIENT=LAYER+32;DEPTH=LAYER+48
DIRTY=0xad0490;SOURCE=0x1600100;WORLD=0x1600000
def hashwords(v):return hashlib.sha256(struct.pack('<'+'H'*len(v),*v)).hexdigest()
class UnitSurfaceOracle(UnitLightOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x40000);self.active=False;self.pixel_mode=False
        self.root_calls=0;self.final_children=0;self.span_calls=0;self.layer_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.route)
    def va(self,a):
        if a in (0x6ff3e0,0x6d8c30):return a
        return super().va(a)
    def event(self,*v):self.events.extend(v)
    def route(self,u,a,n,ctx):
        if not self.active:return
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        arg=lambda i:words(u,sp+4+4*i,1)[0]
        if a in (LAYER,0x4c8fa0):
            assert ecx==UNIT and words(u,sp+4,2)==[0,0];self.event('layer',0,0)
            if a==LAYER:ret(u,8,self.layer)
            else:self.layer_calls+=1
        elif a==0x53d4c0:self.event('drive_layer')
        elif a==0x6c12c0:self.event('type')
        elif a==0x6d6750:self.event('extra');ret(u,0,self.extra)
        elif a==GRADIENT:self.event('gradient');ret(u,0,self.gradient)
        elif a==DEPTH:self.event('depth');ret(u,0,self.depth)
        elif a==0x6d6df0:self.event('flag204')
        elif a==0x6d6e00:self.event('flag205')
        elif a==0x4f52b0:
            assert ecx==HOUSE;self.event('owner')
        elif a==0x41b410:self.event('disguised')
        elif a==0x6d8c30 and not self.standalone:self.event('disguise',arg(0))
        elif a==0x485aa0:
            assert ecx==CVTS+self.scheme*0x200;self.event('select',self.scheme,arg(0))
        elif a==0x411290 and ecx==SOURCE:self.event('bounds')
        elif a==0x434b40:
            assert ecx==WORLD
            dest,source,bounds,box,blitter,z,gradient,brightness,extra=words(u,sp+4,9)
            assert source==SOURCE
            assert STACK-0x2000<=dest and dest+16<=STACK
            self.final_children+=1
            if self.pixel_mode:
                assert gradient==2 and extra==0 and blitter==0x1600900
            else:
                self.event('draw',*ints(u,dest,4),*ints(u,bounds,4),*ints(u,box,4),
                           *ints(u,u.reg_read(UC_X86_REG_EDX),4),blitter,*[struct.unpack('<i',struct.pack('<I',v))[0] for v in (z,gradient,brightness,extra)])
                ret(u,36)
        elif a==0x488870:self.span_calls+=1
    def setup(self,values,pixels=False):
        (self.layer,layer4,first,second,mode,f134,f135,current,disguised,frame,origin,start,duration,
         self.scheme,self.extra,self.depth,self.gradient,actual,x,y,dx,dy,dw,dh,cx,cy,cw,ch,brightness)=values
        assert 0<=self.scheme<8
        self.u.mem_write(ARENA,bytes(0x40000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        for p,v in ((UNIT,VT),(UNIT+0x5ac,TYPE),(UNIT+0x564,LOCO+4),(LOCO+4,0x7a04cc),
                    (VT+0x64,0x4c8fa0 if actual else LAYER),(VT+0x2c4,GRADIENT),(VT+0x2c0,DEPTH),
                    (UNIT+0x1bc,layer4),(UNIT+0x1b4,HOUSE),(UNIT+0x174,origin),(UNIT+0x184,start),
                    (UNIT+0x18c,duration),(HOUSE+0x15f40,self.scheme),(0xab6efc,ARRAY),
                    (0xa40d2c,frame),(0xa3d298,mode),(0xa35db4,HOUSE if current else HOUSE+4),
                    (0x83995c,SOURCE),(0xa40d13,0)):
            self.put(p,v)
        self.u.mem_write(UNIT+0x204,bytes([first&255,second&255]));self.u.mem_write(UNIT+0x170,bytes([disguised&255]))
        self.u.mem_write(HOUSE+0x134,bytes([f134&255,f135&255]));self.u.mem_write(DIRTY,struct.pack('<4i',dx,dy,dw,dh))
        for i in range(8):
            self.put(ARRAY+4*i,SCHEMES+i*0x400);self.put(SCHEMES+i*0x400+0x30c,CVTS+i*0x200)
            self.put(CVTS+i*0x200+8,1)
            for off in (0x98,0xa0,0xa4,0xa8,0xac,0xb0,0xb4):self.put(CVTS+i*0x200+off,1000+i*256+off)
        if pixels:self.put(CVTS+self.scheme*0x200+0x98,0x1600900)
        else:self.surface(SOURCE,256,256,1,0x1880000)
        self.events=[];self.pixel_mode=pixels;self.standalone=False
        return [WORLD,x,y,cx,cy,cw,ch,brightness]
    def inputs(self):
        return [(ARENA,0x40000),(DIRTY,16),(0x83995c,4),(0xa40d2c,4),
                (0xa3d298,4),(0xa35db4,4),(0xab6efc,4),(0xa40d13,1)]
    def draw(self,values):
        args=self.setup(values);self.active=True
        try:self.checked_call(0x6ff3e0,args,UNIT,inputs=[*self.inputs(),(SOURCE,28)])
        finally:self.active=False
        self.root_calls+=1;return self.events
    def flags(self,values):
        frame,origin,start,duration,flags,owner=values
        self.setup([0,0,0,0,0,owner,0,0,0,frame,origin,start,duration,0,0,0,2,0,*([0]*11)])
        self.standalone=True;self.active=True
        try:self.checked_call(0x6d8c30,[flags],UNIT,inputs=self.inputs())
        finally:self.active=False
        self.root_calls+=1;return self.events+['flags',self.u.reg_read(UC_X86_REG_EAX)]
    def pixels(self,values):
        n,w,h,sw,sh,dx,dy,dw,dh,x,y,cx,cy,cw,ch,z,brightness,scheme=values
        args=self.setup([0,0,0,0,0,0,0,0,0,0,0,-1,0,scheme,0,z,2,1,x,y,dx,dy,dw,dh,cx,cy,cw,ch,brightness],True)
        for obj,bpp,data in ((WORLD,2,0x1700000),(SOURCE,1,0x1880000),(0x1600200,2,0x1780000),(0x1600300,2,0x1800000)):
            self.surface(obj,sw if obj==SOURCE else w,sh if obj==SOURCE else h,bpp,data)
        for obj,surface,data in ((0x1600400,0x1600200,0x1780000),(0x1600500,0x1600300,0x1800000)):
            for off,v in ((4,0),(16,0),(20,surface),(24,data),(28,data+w*h*2),(32,w*h*2),(36,32768),(40,w),(44,h)):self.put(obj+off,v)
        self.put(self.va(0x821f8c),0x1600400);self.put(self.va(0x8198d4),0x1600500)
        source=[(i*13+n)%256 if i%7 else 0 for i in range(sw*sh)]
        colors=[(i*37+n*91)&65535 for i in range(w*h)]
        depth=[(0,32720,32740,32760,32768,32780,65535)[(i+n)%7] for i in range(w*h)]
        alpha=[(i*17+n*11)&255 for i in range(w*h)]
        palette=[(scheme*257+row*599+i*131)&65535 for row in range(53) for i in range(256)]
        self.u.mem_write(0x1880000,bytes(source))
        for p,data in ((0x1700000,colors),(0x1780000,depth),(0x1800000,alpha),(0x1900000,palette)):
            self.u.mem_write(p,struct.pack('<'+'H'*len(data),*data))
        self.put(0x1600900,self.va(0x78920c));self.put(0x1600904,0x1900000);self.put(0x1600908,self.alpha_map)
        surfaces=[(obj,28) for obj in (WORLD,SOURCE,0x1600200,0x1600300)]
        self.active=True
        try:self.checked_call(0x6ff3e0,args,UNIT,
                writes=[(0x1700000,w*h*2),*[(obj+12,4) for obj,_ in surfaces]],
                inputs=[*self.inputs(),(0x1880000,len(source)),(0x1780000,w*h*2),(0x1800000,w*h*2),
                        (0x1900000,len(palette)*2),(0x1600400,48),(0x1600500,48),(0x1600900,12),
                        *surfaces,*self.heap_inputs()])
        finally:self.active=False
        self.root_calls+=1
        assert all(self.u.mem_read(obj+12,4)==bytes(4) for obj,_ in surfaces),'Surface lock not restored'
        result=bytes(self.u.mem_read(0x1700000,w*h*2));self.changed_pixels=getattr(self,'changed_pixels',0)+sum(a!=b for a,b in zip(struct.unpack('<'+'H'*(w*h),result),colors))
        return ['pixels',hashlib.sha256(result).hexdigest(),hashwords(depth)]
