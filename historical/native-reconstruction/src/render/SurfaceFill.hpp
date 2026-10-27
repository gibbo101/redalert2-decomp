// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
namespace ra2 {
using FillRect=std::array<std::int32_t,4>; // X,Y,width,height; not inclusive edges.
inline std::int32_t fillAdd(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
inline std::int32_t fillSub(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
// Complete41FDF0 with the fill caller's null optional adjustment pointers.
inline FillRect intersectFillRect(const FillRect& clip,FillRect r){
    if(clip[2]<=0||clip[3]<=0||r[2]<=0||r[3]<=0)return {};
    if(r[0]<clip[0]){r[2]=fillAdd(r[2],fillSub(r[0],clip[0]));r[0]=clip[0];}
    if(r[2]<1)return {};
    if(r[1]<clip[1]){r[3]=fillAdd(r[3],fillSub(r[1],clip[1]));r[1]=clip[1];}
    if(r[3]<1)return {};
    if(fillAdd(r[2],r[0])>fillAdd(clip[0],clip[2]))r[2]=fillAdd(fillSub(clip[0],r[0]),clip[2]);
    if(r[2]<1)return {};
    if(fillAdd(r[3],r[1])>fillAdd(clip[1],clip[3]))r[3]=fillSub(fillAdd(clip[1],clip[3]),r[1]);
    if(r[3]<1)return {};
    return r;
}
// Logical BSurface backing. Initial allocation/geometry are supplied. Buffer byte
// offset retains original pointer alignment independently of host allocation.
struct FillSurface {
    std::int32_t width=0,height=0,bytesPerPixel=2,lockLevel=0;
    std::span<std::uint8_t> storage;
    std::uint32_t bufferOffset=0;
    // Optional numeric word backing for the font canvas; preserves little-endian
    // raster semantics on any host without aliasing a uint16_t allocation.
    std::span<std::uint16_t> words;
};
// Synchronous borrowed form for existing pixel/lock/geometry owners.
struct FillSurfaceView {
    const std::int32_t& width;
    const std::int32_t& height;
    const std::int32_t& bytesPerPixel;
    std::int32_t& lockLevel;
    std::span<std::uint8_t> storage;
    const std::uint32_t& bufferOffset;
    std::span<std::uint16_t> words;
};
inline FillSurfaceView fillSurfaceView(FillSurface& s){return {s.width,s.height,s.bytesPerPixel,s.lockLevel,s.storage,s.bufferOffset,s.words};}
using FillStoreTrace=std::function<void(std::uint32_t,unsigned,std::uint32_t)>;
// Complete7743C0 over ordinary 1/2-byte BSurface virtuals. Other pixel formats
// and unsafe backing offsets refuse rather than emulate invalid memory accesses.
inline bool fillSurfaceRectExThrough(FillSurfaceView s,const FillRect& clip,const FillRect& fill,
        std::uint32_t color,const FillStoreTrace& trace={}){
    if(s.bytesPerPixel!=1&&s.bytesPerPixel!=2)throw std::invalid_argument("Surface fill pixel format");
    if(!s.storage.empty()&&!s.words.empty())throw std::invalid_argument("Ambiguous surface fill backing");
    if(fill[2]<=0||fill[3]<=0)return false;
    const FillRect bounds={0,0,s.width,s.height};
    const auto clipped=intersectFillRect(clip,bounds);
    const FillRect translated={fillAdd(clip[0],fill[0]),fillAdd(clip[1],fill[1]),fill[2],fill[3]};
    const auto r=intersectFillRect(clipped,translated);
    if(r[2]<=0||r[3]<=0)return false;
    const auto pitch=std::uint32_t(s.width)*std::uint32_t(s.bytesPerPixel);
    auto at=s.bufferOffset+std::uint32_t(r[0])*std::uint32_t(s.bytesPerPixel)+std::uint32_t(r[1])*pitch;
    s.lockLevel=fillAdd(s.lockLevel,1);
    // This owner requires a nonnull backing allocation. Offset zero is valid.
    const auto alignment=at%4;
    const auto store=[&](std::uint32_t p,unsigned n,std::uint32_t value){
        const auto bytes=s.words.empty()?std::uint64_t(s.storage.size()):std::uint64_t(s.words.size())*2;
        if(std::uint64_t(p)+n>bytes)throw std::invalid_argument("Surface fill backing bounds");
        for(unsigned i=0;i<n;++i){
            const auto byte=std::uint8_t(value>>(8*i));
            if(s.words.empty())s.storage[p+i]=byte;
            else {const auto at=p+i,shift=(at&1)*8;auto& word=s.words[at/2];word=std::uint16_t((word&~(255u<<shift))|(std::uint32_t(byte)<<shift));}
        }
        if(trace)trace(p,n,value);
    };
    for(std::int32_t y=0;y<r[3];++y){
        auto p=at;
        if(s.bytesPerPixel==1){
            const auto byte=color&255u,word=byte*0x01010101u;
            for(std::int32_t x=0;x<r[2]/4;++x){store(p,4,word);p+=4;}
            for(std::int32_t x=0;x<(r[2]&3);++x)store(p++,1,byte);
        }else if(alignment==0||alignment==2){
            auto count=r[2];
            if(alignment==2){store(p,2,color&65535u);p+=2;--count;}
            // Original aligned paths OR the full color into the replicated word.
            const auto pair=(color<<16)|color;
            for(std::int32_t x=0;x<count/2;++x){store(p,4,pair);p+=4;}
            if(count&1)store(p,2,color&65535u);
        }else{
            const auto pair=(color&65535u)*0x00010001u;
            for(std::int32_t x=0;x<r[2]/2;++x){store(p,4,pair);p+=4;}
            if(r[2]&1)store(p,2,color&65535u);
        }
        at+=pitch;
    }
    s.lockLevel=fillSub(s.lockLevel,1);return true;
}
inline bool fillSurfaceRectEx(FillSurface& s,const FillRect& clip,const FillRect& fill,
        std::uint32_t color,const FillStoreTrace& trace={}){
    return fillSurfaceRectExThrough(fillSurfaceView(s),clip,fill,color,trace);
}
inline bool fillSurfaceRectThrough(FillSurfaceView s,const FillRect& rect,std::uint32_t color,
        const FillStoreTrace& trace={}){
    return fillSurfaceRectExThrough(s,rect,{0,0,s.width,s.height},color,trace);
}
// Complete774390: obtains bounds, then calls the extended fill with requested
// rectangle as clip and bounds as fill. Preserve this seemingly reversed order.
inline bool fillSurfaceRect(FillSurface& s,const FillRect& rect,std::uint32_t color,
        const FillStoreTrace& trace={}){
    return fillSurfaceRectEx(s,rect,{0,0,s.width,s.height},color,trace);
}
// Complete4AB4F0 and4AB520's nonnull-surface/hardware-enable-byte-zero profile.
// Its clip/fill order differs from774390. DirectDraw/device recovery is excluded.
inline bool fillDisplaySoftwareRect(FillSurface& s,const FillRect& rect,std::uint32_t color,
        const FillStoreTrace& trace={}){
    return fillSurfaceRectEx(s,{0,0,s.width,s.height},rect,color,trace);
}
}
