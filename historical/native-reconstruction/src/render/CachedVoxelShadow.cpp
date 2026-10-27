// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/CachedVoxelShadow.hpp"
#include "render/VoxelShadow.hpp"
#include <algorithm>
#include <bit>
#include <stdexcept>
namespace ra2 {
void drawOrdinaryCachedVoxelShadow(const Bytes& pool,std::size_t snapshot,
    PixelPoint at,PixelRect clip,const CachedVoxelPartServices& s,int width,int height,
    std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,PixelRect& dirty){
    auto require=[](bool ok,const char* reason){if(!ok)throw std::invalid_argument(reason);};
    require(snapshot<=pool.size()&&pool.size()-snapshot>=12,"Invalid shadow snapshot header");
    require(width>0&&height>0&&width<=4096&&height<=4096&&colors.size()==std::size_t(width)*height&&depth.size()==colors.size(),"Invalid cached shadow planes");
    for(int n:{at.x,at.y,clip.x,clip.y,clip.width,clip.height,dirty.x,dirty.y,dirty.width,dirty.height})
        require(std::abs(std::int64_t(n))<=1048576,"Cached shadow rectangle outside bounded profile");
    auto word=[&](std::size_t p){require(p<=pool.size()&&pool.size()-p>=2,"Truncated shadow snapshot word");return unsigned(pool[p])|(unsigned(pool[p+1])<<8);};
    const int w=int(word(snapshot+4)),h=int(word(snapshot+6));
    require(w<=256&&h<=256,"Cached shadow dimensions outside bounded profile");
    const int x=at.x+std::bit_cast<std::int16_t>(std::uint16_t(word(snapshot)));
    const int y=at.y+std::bit_cast<std::int16_t>(std::uint16_t(word(snapshot+2)));
    s.kind();s.selectBlitter(0x2001);s.kind();dirty=stagingUnion(dirty,{x,y,w,h});
    const auto gradient=s.value2C4();const auto z=s.value2C0();
    require(gradient==2,"Alternate cached shadow gradient requires recovery");
    if(w==0||h==0||clip.width<=0||clip.height<=0)return;
    Bytes pixels(std::size_t(w)*h);
    std::size_t p=std::uint32_t(word(snapshot+8))|(std::uint32_t(word(snapshot+10))<<16);
    for(int row=0;row<h;++row){
        const auto n=word(p);require(n>=2&&n<=pool.size()-p,"Invalid shadow snapshot row");
        const auto decoded=decodeVoxelRow(std::span<const std::uint8_t>(pool).subspan(p,n));
        require(decoded.size()>=std::size_t(w),"Truncated shadow snapshot pixels");
        std::copy_n(decoded.begin(),w,pixels.begin()+std::size_t(row)*w);p+=n;
    }
    blitShadow(pixels,w,h,{0,0,w,h},{x,y},clip,z,width,height,colors,depth);
}
}
