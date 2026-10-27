// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FrameDepthRefresh.hpp"
namespace ra2 {
// Entered41E477 retained-hit increment and41E510 nonfree release. Initial
// association is supplied; cache lookup/construction/removal are not generalized.
inline void retainTerrainDepthAlpha(std::int32_t& references){references=fillAdd(references,1);}
inline void releaseTerrainDepthAlpha(std::int32_t& references){
    references=fillSub(references,1);
    if(!references)throw std::invalid_argument("Terrain cache free outside retained profile");
}
// Complete776340/411230 on the same borrowed fields/stock services as7761C0.
// Offset zero represents a nonnull allocation; subtraction is single-wrap32.
inline std::uint32_t framePlaneAddress(FrameDepthView v,PixelPoint p,const FrameDepthServices& s){
    if(!s.lock5c||!s.unlock60)throw std::invalid_argument("Terrain plane service unbound");
    const auto locked=s.lock5c(p.x,p.y);s.unlock60();
    if(!locked)throw std::invalid_argument("Terrain plane null lock outside profile");
    auto at=v.offset10+*locked;if(at>=v.end1c)at-=v.bytes20;return at;
}
struct TerrainDepthServices {
    // Prepared retained-hit cache; miss/construction/free remain outside profile.
    std::function<void()> acquire41e3e0,release41e510;
    std::function<std::int32_t()> bytes70;
    std::function<bool()> header9c;
    std::function<std::uint32_t()> pitch74;
    std::function<std::optional<std::uint32_t>(std::int32_t,std::int32_t)> lock5c;
    std::function<void()> unlock60;
    std::function<std::uint32_t(PixelPoint)> depth776340,alpha411230;
};
// Entered52C230 profile from complete4754B0: sub0, depth1, variant0,
// fill0, depth-only1, checker0, color0. Fixed60x30 header, resident subtile
// with depth bit2. Compact diamond tables replace scratch only, not pixel order.
// Color/alpha pointers are still obtained; neither plane is written here.
inline void drawTerrainDepth(FrameDepthView depth,PixelPoint point,PixelRect clip,
        std::int32_t viewportY,std::uint32_t flags,bool converterPresent,
        const TerrainDepthServices& s,const FillStoreTrace& stores={}){
    if(!converterPresent)return;
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Terrain depth child unbound");return f;};
    need(s.acquire41e3e0)();
    const auto release=[&]{need(s.release41e510)();};
    if(need(s.bytes70)()!=2){release();return;}
    if(!need(s.header9c)()){release();return;}
    // Accepted bounded geometry excludes overflowing clip arithmetic and invalid
    // dimensions. Original faults/alternate paths are not malformed-input support.
    if(clip.width<0||clip.height<0||std::abs(std::int64_t(point.x))>1048576||std::abs(std::int64_t(point.y))>1048576||
        std::abs(std::int64_t(clip.x))>1048576||std::abs(std::int64_t(clip.y))>1048576||clip.width>1048576||clip.height>1048576)
        throw std::invalid_argument("Terrain depth clip outside bounded profile");
    int left=std::max(point.x,clip.x),top=std::max(point.y,clip.y);
    const int right=std::min(point.x+60,clip.x+clip.width),bottom=std::min(point.y+29,clip.y+clip.height);
    if(right<=left||bottom<=top){release();return;}
    (void)need(s.pitch74)();const auto color=need(s.lock5c)(left,top);
    if(!color){release();return;} // Original skips Unlock on a null destination.
    if(!(flags&2))throw std::invalid_argument("Terrain depth requires resident depth-enabled subtile");
    auto row=need(s.depth776340)({left,fillSub(top,viewportY)});
    const auto stride=depth.rowWords28;
    (void)need(s.alpha411230)({left,fillSub(top,viewportY)});
    const auto probe=row+(std::uint32_t(depth.rowWords28)*std::uint32_t(bottom-top)+std::uint32_t(right-left))*2+4;
    const bool wrapped=probe>=depth.end1c;
    if(!depth.plane.storage.empty()&&!depth.plane.words.empty())throw std::invalid_argument("Ambiguous terrain depth backing");
    const auto size=depth.plane.words.empty()?std::uint64_t(depth.plane.storage.size()):std::uint64_t(depth.plane.words.size())*2;
    const auto store=[&](std::uint32_t at){
        if(std::uint64_t(at)+2>size)throw std::invalid_argument("Terrain depth store exceeds backing");
        for(unsigned i=0;i<2;++i){auto p=at+i;if(depth.plane.words.empty())depth.plane.storage[p]=255;
            else depth.plane.words[p/2]|=std::uint16_t(255u<<(8*(p&1)));}
        if(stores)stores(at,2,65535);
    };
    for(int y=top;y<bottom;++y){
        const auto dy=y-point.y;const int span=4*(dy<15?dy+1:29-dy),edge=(60-span)/2;
        const int prefix=std::max(0,edge-(left-point.x));
        const int count=std::max(0,std::min(edge+span,right-point.x)-std::max(edge,left-point.x));
        auto at=row+std::uint32_t(prefix)*2;
        if(wrapped&&at>=depth.end1c)at-=depth.bytes20; // Even a zero span wraps its prefix.
        for(int x=0;x<count;++x){store(at);at+=2;if(wrapped&&at>=depth.end1c)at-=depth.bytes20;}
        // The wrapped branch normalizes at each prefix, not at the row advance.
        row+=std::uint32_t(stride)*2;
    }
    need(s.unlock60)();release();
}
}
