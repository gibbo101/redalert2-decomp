# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged theater root, absent images, selected type projection."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from verify_theater_tile_inputs import verify,RANGES,DEPTH_GLOBALS,KEYS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
ARENA=0x2400000;PRIMARY=0x2c00000;ALL_TYPES=PRIMARY+0x40000;SHIFTS=PRIMARY+0x80000
FIELDS=((0x264,4),(0x270,4),(0x268,4),(0x26c,4),(0x290,4),(0x294,4),
 (0x2b0,1),(0x2b1,1),(0x2b2,1),(0x2b3,1),(0x2d5,1),(0x2d6,1))
GLOBAL_WRITES=(0xa52e74,0xa52e78,0xa52e7c,0xa52e80,0xa52e84,0xa6e38c,
 0xa52eb0,0xa52eb4,0xa52eb8,0xa52ebc,0xa52ed8,0xa6e390,
 0xa6e018,0xa52ea8,0xa52eec,0xa52f00,0xa6e0e8,0xa6cf4c,0xa52c60,0xa6e0e0,
 0xa52ef4,0xa52f84,0xa52c70,0xa52590,0xa52ef8,0xa5258c,0xa6e0fc,0xa52c74,
 0xa6cb68,0xa52e68,0xa6cb74,0xa52580,0xa6e038,0xa52ee8,0xa52e6c,0xa52ea4,
 0xa6cf50,0xa52f04,0xa6cb78,0xa52584,0xa6cf58,0xa52ef0,0xa52ea0,0xa6dd00,
 0xa6dd0c,0xa6dd08,0xa52c68,0xa52c64,0xa6cb6c,0xa6e014,0xa52efc,0xa6e0f8,
 0xa6cb70,0xa52e64,0xa52ee4,0xa6dd04,0xa6cf54,0xa52ee0,
 0xa6e0e4,0xa52f80,0xa6e028,0xa52c80,0xa53394,0xa52588,0xa6e010,0xa53390,0xa6cb7c,0xa52e70,
 0xac0cc0,0xa40ce0)
class TheaterTileInputOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x900000);self.services={0x40e160,0x40e180,0x69a430,0x468f50,0x469150,
          0x782017,0x469060,0x470150,0x4691a0,0x529720,0x4696b0,0x50d7f0,0x50f410,
          0x50e9a0,0x50c9b0,0x7820f4,0x7823d0,0x7831f0,0x5956c0,0x438410,0x42f350,
          0x50b8d0,0x5d57f0,0x481fb0}
        self.vector_clear=words(self.u,0x7a524c+12,1)[0];self.services.add(self.vector_clear)
        self.u.hook_add(UC_HOOK_CODE,self.service);self.root_entries=self.constructor_entries=self.ini_calls=self.store_count=0
    def va(self,a):return a
    def string(self,p):
        if not p:return ''
        return bytes(self.u.mem_read(p,512)).split(b'\0')[0].decode('ascii')
    def write(self,p,data):
        assert any(lo<=p and p+len(data)<=hi for lo,hi in self.allowed),f'Unallowed service write {p:#x}/{len(data)}'
        if ARENA<=p<PRIMARY:assert any(lo<=p and p+len(data)<=lo+size for lo,size in self.allocations),'Service write outside allocation'
        self.u.mem_write(p,data)
    def service(self,u,a,n,ctx):
        if a in self.services:
            sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
            if a in (0x40e160,0x469150,0x529720,0x438410,0x42f350,0x50b8d0,0x481fb0,self.vector_clear):
                ret(u,0,16 if a==0x469150 else ecx)
            elif a==0x69a430:ret(u,0,0)
            elif a in (0x40e180,0x468f50,0x470150,0x5d57f0):ret(u,4,ecx)
            elif a==0x782017:
                size=words(u,sp+4,1)[0];assert size in (8,16,0x2dc)
                p=self.cursor;self.cursor+=(size+15)&~15;assert self.cursor<PRIMARY
                self.allocations.append((p,size));self.write(p,bytes(size));ret(u,0,p)
            elif a==0x469060:
                p,size=words(u,sp+4,2);assert size==16;self.write(p,bytes(size));ret(u,8,size)
            elif a==0x4691a0:ret(u,4,0)
            elif a==0x4696b0:ret(u,12,1)
            elif a in (0x50d7f0,0x50f410):
                section,key,default=words(u,sp+4,3);section=self.string(section);key=self.string(key);value=default
                if section=='General':
                    assert default==(0xfffffffe if key=='DestroyableCliffs' else 0xffffffff)
                    if key in KEYS:value=self.numbers[KEYS.index(key)]
                else:
                    assert section.startswith('TileSet');i=int(section[7:]);row=self.sets[i]
                    mapping={'TilesInSet':0,'LastTilesInSet':1,'MarbleMadness':2,'NonMarbleMadness':3,'ToSnowTheater':4,'ToTemperateTheater':5,'ShadowTiles':7}
                    bools={'Morphable':1,'AllowToPlace':2,'AllowBurrowing':4,'AllowTiberium':8,'RequiredForRMG':16,'ShadowCaster':32}
                    assert default==({'MarbleMadness':65535,'NonMarbleMadness':65535,'ShadowTiles':0,
                      'Morphable':0,'AllowToPlace':1,'AllowBurrowing':1,'AllowTiberium':0,'RequiredForRMG':0,'ShadowCaster':0}.get(key,0xffffffff))
                    if key in mapping:value=row[mapping[key]]
                    elif key in bools:value=int(bool(row[6]&bools[key]))
                    else:raise AssertionError('Unexpected INI key '+key)
                self.requests.append((section,key,default,value&0xffffffff));self.ini_calls+=1;ret(u,12,value)
            elif a==0x50e9a0:
                section,key,default,p,size=words(u,sp+4,5);key=self.string(key)
                assert key in ('SetName','FileName');value=self.string(default).encode();assert len(value)<size
                self.write(p,value+b'\0');ret(u,20,len(value))
            elif a==0x50c9b0:ret(u,4,0) # No animation section at this boundary.
            elif a==0x7820f4:
                p,fmt=words(u,sp+4,2);fmt=self.string(fmt);args=words(u,sp+12,3)
                if fmt in ('SLOP01Z.%s','ISO%s.PAL','%s.INI'):value=fmt%self.string(args[0])
                elif fmt in ('TileSet%04d','%02d'):value=fmt%args[0]
                elif fmt=='%.28s %02d':value='%.28s %02d'%(self.string(args[0]),args[1])
                else:raise AssertionError('Unexpected formatter '+fmt)
                self.write(p,value.encode()+b'\0');ret(u,0,len(value))
            elif a==0x7823d0:
                p,source,size=words(u,sp+4,3);value=self.string(source).encode();self.write(p,value[:size].ljust(size,b'\0'));ret(u,0,p)
            elif a==0x7831f0:
                p,drive,directory,name,extension=words(u,sp+4,5);assert drive==directory==0
                ext=self.string(extension);value=self.string(name)+('' if ext.startswith('.') else '.')+ext
                self.write(p,value.encode()+b'\0');ret(u,0)
            elif a==0x5956c0:self.image_requests.append(self.string(ecx));ret(u,0,0)
            else:raise AssertionError(hex(a))
            return
        if not any(start<=a and a+n<=start+size for start,size in RANGES.items()):raise AssertionError(f'Uninspected theater instruction {a:#x}')
        if a==0x529870:self.root_entries+=1
        if a==0x528ee0:self.constructor_entries+=1
    def run(self,numbers,sets):
        self.numbers=numbers;self.sets=sets;self.cursor=ARENA;self.allocations=[];self.requests=[];self.image_requests=[]
        assert sets[-1][0]==-1 and sum(bool(r[6]&32) for r in sets[:-1])<=5
        capacity=max(1,sum(max(0,r[0]) for r in sets));assert capacity<=65536
        self.allowed=[(STACK-0x2000,STACK),(ARENA,PRIMARY),(PRIMARY,PRIMARY+capacity*4),
          (ALL_TYPES,ALL_TYPES+capacity*4),(SHIFTS,SHIFTS+len(sets)*4),(0xa52f90,len(sets)*4+0xa52f90),
          *[(p,p+4) for p in GLOBAL_WRITES]]
        self.u.mem_write(ARENA,bytes(0x900000))
        for p in GLOBAL_WRITES:self.put(p,0x13572468)
        for p,value in ((0xa52ed8,0),(0xa40ce0,0),(0xac0cc0,0),(0xa52ecc,SHIFTS),(0xa52ed0,len(sets)),
          (0xa40cd4,PRIMARY),(0xa40cd8,capacity),(0xac0cb4,ALL_TYPES),(0xac0cb8,capacity),
          (0xa6e38c,0),(0xa52eb0,0),(0xa52eb4,0),(0xa52eb8,0),(0xa52ebc,0)):
            self.put(p,value)
        self.u.mem_write(0xa52f90,b'\xa7'*(4*len(sets)+64))
        self.u.mem_write(PRIMARY,b'\xa7'*(capacity*4+64));self.u.mem_write(ALL_TYPES,b'\xa7'*(capacity*4+64));self.u.mem_write(SHIFTS,b'\xa7'*(len(sets)*4+64))
        immutable=[(0xa52ecc,8),(0xa40cd4,8),(0xac0cb4,8)]
        def stores(u,access,p,n,v,ctx):
            if ARENA<=p<PRIMARY:assert any(lo<=p and p+n<=lo+size for lo,size in self.allocations),'Guest write outside allocation'
            self.store_count+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(0x529870,ecx=0,edx=0,writes=[(lo,hi-lo) for lo,hi in self.allowed if lo!=STACK-0x2000],inputs=immutable)
        finally:self.u.hook_del(hook)
        count=words(self.u,0xa40ce0,1)[0];assert count==capacity or count==0
        assert words(self.u,0xac0cc0,1)[0]==count
        starts=words(self.u,0xa52f90,len(sets));assert words(self.u,0xa6e390,1)[0]==len(sets)
        shift_count=words(self.u,0xa52ed8,1)[0];assert shift_count<=len(sets)
        values=[words(self.u,p,1)[0] for p in DEPTH_GLOBALS]
        values += [len(starts),*starts,shift_count]
        for p in words(self.u,SHIFTS,shift_count):values+=words(self.u,p,2)
        values.append(count)
        pointers=words(self.u,PRIMARY,count);assert words(self.u,ALL_TYPES,count)==pointers
        for p in pointers:
            assert (p,0x2dc) in self.allocations
            values += [int.from_bytes(self.u.mem_read(p+off,n),'little') for off,n in FIELDS]
            # Additional selected default/image invariants, outside the digest.
            assert words(self.u,p+0x298,1)==[0xffffffff] and words(self.u,p+0x2b4,2)==[0,0]
            assert words(self.u,p+0xa4,1)==[0] and bytes(self.u.mem_read(p+0xa8,1))==b'\0'
            record=bytearray(self.u.mem_read(p,0x2dc))
            for first,end in ((0,16),(0x64,0x95),(0xa4,0xa9),(0x1ff,0x204),(0x205,0x206),
              (0x264,0x2c6),(0x2d5,0x2dc)):record[first:end]=bytes(end-first)
            assert not any(record),'Unmodeled type bytes changed'
        for p,n in ((PRIMARY,count*4),(ALL_TYPES,count*4),(SHIFTS,shift_count*4),(0xa52f90,len(sets)*4)):
            assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64,'Capacity tail changed'
        return [count,hashlib.sha256(b''.join(struct.pack('<I',v&0xffffffff) for v in values)).hexdigest()]
