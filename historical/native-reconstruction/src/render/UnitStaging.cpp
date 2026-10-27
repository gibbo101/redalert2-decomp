// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitStaging.hpp"
#include <algorithm>
#include <cstdlib>
namespace ra2 {
IndexRemap stagingRemap(const Palette& source,const Palette& destination) {
    IndexRemap result{};
    for(unsigned i=1;i<256;++i) {
        int closest=2300;
        for(unsigned j=0;j<256;++j) {
            const int distance=2*std::abs(int(source[i].r)-destination[j].r)
                             +4*std::abs(int(source[i].g)-destination[j].g)
                             +3*std::abs(int(source[i].b)-destination[j].b);
            if(distance<closest){closest=distance;result[i]=std::uint8_t(j);}
        }
    }
    return result;
}
static void bounded(PixelRect r) {
    for(int v:{r.x,r.y,r.width,r.height})if(std::abs(std::int64_t(v))>1048576)throw std::invalid_argument("Staging rectangle outside bounded profile");
}
PixelRect stagingUnion(PixelRect a,PixelRect b) {
    bounded(a);bounded(b);
    if(a.width<=0||a.height<=0)return b;
    if(b.width<=0||b.height<=0)return a;
    const int right=a.x+a.width,bottom=a.y+a.height;
    a.x=std::min(a.x,b.x);a.y=std::min(a.y,b.y);
    a.width=right-a.x;a.height=bottom-a.y;
    // The original union includes one extra pixel only when extending right/bottom.
    if(right<b.x+b.width)a.width=b.x+b.width-a.x+1;
    if(bottom<b.y+b.height)a.height=b.y+b.height-a.y+1;
    return a;
}
void blitIndexed(const Bytes& source,int sw,int sh,PixelRect s,PixelPoint d,PixelRect clip,
                 const IndexRemap& remap,int w,int h,Bytes& destination) {
    if(sw<1||sh<1||sw>4096||sh>4096||w<1||h<1||w>4096||h>4096||source.size()!=std::size_t(sw)*sh||destination.size()!=std::size_t(w)*h)throw std::invalid_argument("Invalid indexed staging planes");
    bounded(s);bounded(clip);bounded({d.x,d.y,0,0});
    if(s.width<=0||s.height<=0||clip.width<=0||clip.height<=0)return;
    d.x+=clip.x;d.y+=clip.y;
    const int left=std::max({0,clip.x,d.x,d.x-s.x}),top=std::max({0,clip.y,d.y,d.y-s.y});
    const int right=std::min({w,clip.x+clip.width,d.x+s.width,d.x+sw-s.x});
    const int bottom=std::min({h,clip.y+clip.height,d.y+s.height,d.y+sh-s.y});
    for(int y=top;y<bottom;++y)for(int x=left;x<right;++x) {
        const auto index=source[std::size_t(s.y+y-d.y)*sw+s.x+x-d.x];
        if(index)destination[std::size_t(y)*w+x]=remap[index];
    }
}
void UnitStaging::clear(){std::fill(pixels.begin(),pixels.end(),0);dirty={};}
void UnitStaging::add(const RasterFrame& frame,const IndexRemap& remap) {
    const auto& b=frame.rectangle;const PixelRect part{128+b[0],128+b[1],b[4],b[5]};
    blitIndexed(frame.pixels,256,256,{b[2],b[3],b[4],b[5]},{part.x,part.y},{0,0,256,256},remap,256,256,pixels);
    dirty=stagingUnion(dirty,part);
}
}
