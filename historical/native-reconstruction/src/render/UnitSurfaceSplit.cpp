// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitSurfaceSplit.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
void drawBridgeUnitSurface(const UnitSurfaceInputs& in,std::uint32_t actor494,
                           const UnitSurfaceBridgeServices& b,const UnitSurfaceServices& s) {
    bool split=false;
    if(in.typeBAE) {
        if(b.flag100()!=0&&b.predicate0()==0)split=true;
        else {
            const bool contact=b.firstContact(); // Before the actor field test.
            if(actor494&&contact&&b.contactKind()==6&&b.contactType1357()!=0)split=true;
        }
    }
    auto top=in;top.typeBAE=0;
    if(!split||in.dirty.height<=16) {drawOrdinaryUnitSurface(top,s);return;}
    const int upper=in.dirty.height-16;
    top.dirty.height=upper;
    auto draw=s;
    draw.gradient=[]{return 0;}; // Split path does not query the actor gradient.
    draw.draw=[&](const UnitSurfaceRequest& first) {
        auto r=first;
        r.depth=signed32(std::uint32_t(r.depth)-5u);
        s.draw(r);
        r.destination.y=signed32(std::uint32_t(r.destination.y)+std::uint32_t(upper));
        r.source.y=signed32(std::uint32_t(r.source.y)+std::uint32_t(upper));
        r.destination.height=r.source.height=16;
        r.gradient=2;r.depth=s.depth();r.sourceBounds=s.sourceBounds();
        s.draw(r);
    };
    drawOrdinaryUnitSurface(top,draw);
}
BlitStats blitUnitTopGradient(const Bytes& source,int sw,int sh,PixelRect s,PixelPoint d,
    PixelRect clip,int z,int brightness,const std::vector<Palette16>& palettes,int width,int height,
    std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,
    const std::vector<std::uint16_t>& alpha) {
    if(width<1||height<1||width>4096||height>4096||sw<1||sh<1||sw>4096||sh>4096||
       source.size()!=std::size_t(sw)*sh||colors.size()!=std::size_t(width)*height||
       depth.size()!=colors.size()||alpha.size()!=colors.size())throw std::invalid_argument("Invalid top-gradient planes");
    for(int v:{s.x,s.y,s.width,s.height,d.x,d.y,clip.x,clip.y,clip.width,clip.height,z})
        if(std::abs(std::int64_t(v))>1048576)throw std::invalid_argument("Top-gradient rectangle outside bounded profile");
    BlitStats stats;
    if(s.width<=0||s.height<=0||clip.width<=0||clip.height<=0)return stats;
    d.x+=clip.x;d.y+=clip.y;
    const int left=std::max({0,clip.x,d.x,d.x-s.x}),top=std::max({0,clip.y,d.y,d.y-s.y});
    const int right=std::min({width,clip.x+clip.width,d.x+s.width,d.x+sw-s.x});
    const int bottom=std::min({height,clip.y+clip.height,d.y+s.height,d.y+sh-s.y});
    if(left>=right||top>=bottom)return stats;
    int candidate=int(std::uint16_t(32768-top))+z;
    for(int y=top;y<bottom;++y,--candidate)for(int x=left;x<right;++x) {
        const auto at=std::size_t(y)*width+x;
        const auto index=source[std::size_t(s.y+y-d.y)*sw+s.x+x-d.x];
        if(index&&candidate<int(depth[at])) {
            colors[at]=palettes.at(std::size_t(alphaShadeRow(alpha[at],brightness,int(palettes.size()))))[index];
            ++stats.visible;
        } else if(index)++stats.rejected;
    }
    return stats;
}
}
