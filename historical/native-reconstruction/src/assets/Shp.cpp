// SPDX-License-Identifier: GPL-3.0-or-later
// Format interpretation informed by OpenRA (The OpenRA Developers and
// Contributors), e7e9e4ad270221d7fb9725b348c75504d48c1ebd. See THIRD_PARTY.md.
#include "assets/Shp.hpp"
#include <algorithm>
namespace ra2 {
ShpImage readShp(const Data& d) {
    if(d.u16(0)!=0)throw std::runtime_error("Unsupported SHP signature/reference");
    ShpImage image{int(d.u16(2)),int(d.u16(4)),{}};
    const auto count=d.u16(6);
    if(image.width<1||image.height<1||image.width>4096||image.height>4096||count<1||count>4096)
        throw std::runtime_error("SHP dimensions outside bounded profile");
    d.check(8,std::size_t(count)*24);std::size_t total=0;
    for(unsigned i=0;i<count;++i) {
        const std::size_t h=8+i*24;
        ShpFrame f{int(d.u16(h)),int(d.u16(h+2)),int(d.u16(h+4)),int(d.u16(h+6)),{}};
        f.format=int(d.u32(h+8));
        if(f.format!=3&&f.format!=1)throw std::runtime_error("Only SHP formats 1 and 3 are recovered");
        if(f.x+f.width>image.width||f.y+f.height>image.height)throw std::runtime_error("SHP crop outside canvas");
        const auto size=std::size_t(f.width)*f.height;total+=size;
        if(total>64*1024*1024)throw std::runtime_error("SHP decoded size limit");
        f.pixels.assign(size,0);std::size_t p=d.u32(h+20);
        if(p) {
            if(p<8+std::size_t(count)*24)throw std::runtime_error("SHP pixels overlap headers");
            if(f.format==1) {
                const auto bytes=d.ptr(p,size);std::copy(bytes,bytes+size,f.pixels.begin());
            } else for(int y=0;y<f.height;++y) {
                const auto length=d.u16(p);
                if(length<2)throw std::runtime_error("Invalid SHP row length");
                d.check(p,length);const auto end=p+length;p+=2;int x=0;
                f.rleRows.emplace_back(d.ptr(p,end-p),d.ptr(end,0));
                while(p<end) {
                    const auto value=d.u8(p++);
                    if(value) {
                        if(x>=f.width)throw std::runtime_error("SHP literal outside row");
                        f.pixels[std::size_t(y)*f.width+x++]=value;
                    } else {
                        if(p==end)throw std::runtime_error("Truncated SHP zero run");
                        const auto run=d.u8(p++);
                        if(!run)throw std::runtime_error("Empty SHP zero run");
                        x+=run;
                        // The owned encoder sometimes ends with a zero run one
                        // pixel beyond the crop. Original spans stop at width.
                        if(x>f.width&&(p!=end||x>f.width+1))throw std::runtime_error("SHP zero run outside row");
                    }
                }
                if(x<f.width)throw std::runtime_error("Incomplete SHP row");
            }
        }
        image.frames.push_back(std::move(f));
    }
    return image;
}
}
