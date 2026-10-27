// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfacePixel.hpp"
#include "render/TerrainVisibility.hpp"
namespace ra2 {
struct FrameDepthView {
    const std::uint32_t& offset10;
    const std::uint32_t& begin18;
    const std::uint32_t& end1c;
    const std::uint32_t& bytes20;
    const std::int32_t& rowWords28;
    SurfacePixelBacking plane;
};
struct FrameDepthServices {
    // Each callback resolves the live surface14 independently. The ordinary
    // facade binds the existing stock lock/pitch/width/format/unlock kernels.
    std::function<std::optional<std::uint32_t>(std::int32_t,std::int32_t)> lock5c;
    std::function<void()> unlock60;
};
using FrameDepthReadTrace=std::function<void(int,std::uint32_t)>;
// Shared original bit1 prefix/pairs/conditional-tail span. Unprefixed one-word
// spans write nothing. Color truncation is retained for the scrolling caller.
inline void fillFrameDepthSpan(SurfacePixelBacking plane,std::uint32_t at,std::uint32_t count,
        std::uint32_t color,const FillStoreTrace& stores={}){
    if(!plane.storage.empty()&&!plane.words.empty())throw std::invalid_argument("Ambiguous frame span backing");
    const auto store=[&](std::uint32_t at,unsigned n){
        const auto size=plane.words.empty()?std::uint64_t(plane.storage.size()):std::uint64_t(plane.words.size())*2;
        if(std::uint64_t(at)+n>size)throw std::invalid_argument("Frame depth store exceeds backing");
        for(unsigned i=0;i<n;++i){const auto k=at+i;
            if(plane.words.empty())plane.storage[k]=std::uint8_t(color>>(8*(i&1)));
            else {const auto shift=8*(k&1);auto& word=plane.words[k/2];word=std::uint16_t((word&~(255u<<shift))|(std::uint32_t(std::uint8_t(color>>(8*(i&1))))<<shift));}
        }
        if(stores)stores(at,n,n==4?((color&65535u)*0x10001u):(color&65535u));
    };

    if(count>1048576)throw std::invalid_argument("Frame depth span exceeds execution bound");
    if((at&2)&&count){store(at,2);at+=2;--count;}
    const auto pairs=count/2;
    for(std::uint32_t i=0;i<pairs;++i){store(at,4);at+=4;}
    // Original initializes the tail pointer to null and only sets it after
    // rep-stosd. An unprefixed one-word span therefore writes nothing.
    if((count&1)&&pairs)store(at,2);
}
// Complete7761C0, including its late block after the first return. Offsets are
// relative to one nonnull backing allocation; null/fault compatibility refuses.
// Traces are observational. No clipping, queue clearing or frame scheduling.
inline void refreshFramePlaneRegion(FrameDepthView v,PixelRect r,const FrameDepthServices& s,
        std::uint16_t clearColor,const FillStoreTrace& stores={},const FrameDepthReadTrace& reads={}){
    if(!s.lock5c)throw std::invalid_argument("Frame depth lock unbound");
    const auto locked=s.lock5c(r.x,r.y);
    if(!s.unlock60)throw std::invalid_argument("Frame depth unlock unbound");
    s.unlock60(); // Original unlocks even if Lock returned null.
    if(!locked)throw std::invalid_argument("Frame depth null lock outside profile");
    const auto read=[&](int field,std::uint32_t value){if(reads)reads(field,value);return value;};
    auto p=read(0x10,v.offset10)+*locked;
    auto end=read(0x1c,v.end1c);
    if(p>=end)p-=read(0x20,v.bytes20);
    if(r.height<=0)return;
    if(r.width<0||r.width>1048576||r.height>1048576||std::uint64_t(r.width)*std::uint32_t(r.height)>67108864)
        throw std::invalid_argument("Frame depth extent exceeds execution bound");
    if(!v.plane.storage.empty()&&!v.plane.words.empty())throw std::invalid_argument("Ambiguous frame depth backing");
    const auto span=[&](std::uint32_t at,std::uint32_t count){fillFrameDepthSpan(v.plane,at,count,clearColor,stores);};
    for(int row=0;row<r.height;++row){
        if(p+std::uint32_t(r.width)*2>=end){
            const auto first=(end-p)>>1;
            span(p,first);
            const auto second=std::uint32_t(r.width)-first;
            const auto begin=read(0x18,v.begin18);span(begin,second);
        }else span(p,std::uint32_t(r.width));
        p+=read(0x28,std::uint32_t(v.rowWords28))*2;
        end=read(0x1c,v.end1c);
        if(p>=end)p-=read(0x20,v.bytes20);
    }
}
// Complete7761C0 and4110B0 share control flow; both original entry points are
// tested independently. Keep the recovered alpha sentinel separate from depth.
inline void refreshFrameDepth(FrameDepthView v,PixelRect r,const FrameDepthServices& s,
        const FillStoreTrace& stores={},const FrameDepthReadTrace& reads={}){
    refreshFramePlaneRegion(v,r,s,65535,stores,reads);
}
inline void refreshFrameAlpha(FrameDepthView v,PixelRect r,const FrameDepthServices& s,
        const FillStoreTrace& stores={},const FrameDepthReadTrace& reads={}){
    refreshFramePlaneRegion(v,r,s,127,stores,reads);
}
}
