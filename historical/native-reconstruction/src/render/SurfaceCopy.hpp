// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceClip.hpp"
#include "render/SurfacePixel.hpp"
#include "render/SurfaceRefresh.hpp"
namespace ra2 {
// Stable stock software-surface association is supplied. The geometry and pixel
// view borrow the same width; this owner neither duplicates fields nor owns pixels.
struct CopySurface {
    RefreshSurface& geometry;
    SurfacePixelView pixels;
    std::function<void(char,std::int32_t,std::int32_t)> observe;
    FillStoreTrace stores;
    PixelLockTrace locks;
    // Optional actual stock getter binding, including caller diagnostic probes.
    std::function<std::int32_t()> width7C;
    // Explicit alternate virtuals for the actual device-surface receiver.
    // Empty callbacks retain the original software-surface chain.
    std::function<std::int32_t()> bytes70;
    std::function<std::uint32_t()> pitch74;
    std::function<std::optional<std::uint32_t>(std::int32_t,std::int32_t)> lock5C;
    std::function<void()> unlock60;
};
inline void copyObserve(CopySurface& s,char kind,std::int32_t x=0,std::int32_t y=0){
    if(s.observe)s.observe(kind,x,y);
}
inline RefreshRect copySurfaceRect(CopySurface& s){
    copyObserve(s,'R');RefreshRect r;refreshSurfaceRect(s.geometry,r);return r;
}
inline std::int32_t copySurfaceBpp(CopySurface& s){copyObserve(s,'B');return s.bytes70?s.bytes70():s.pixels.bytes10;}
inline std::uint32_t copySurfacePitch(CopySurface& s){
    copyObserve(s,'P');if(s.pitch74)return s.pitch74();return surfacePixelPitch(s.pixels,[&]{copyObserve(s,'W');return s.width7C?s.width7C():refreshSurfaceWidth(s.geometry);});
}
inline std::optional<std::uint32_t> copySurfaceLock(CopySurface& s,std::int32_t x,std::int32_t y){
    copyObserve(s,'K',x,y);if(s.lock5C)return s.lock5C(x,y);
    return lockSurfacePixels(s.pixels,x,y,{},s.locks,[&]{return copySurfaceBpp(s);},[&]{return copySurfacePitch(s);});
}
inline void copySurfaceUnlock(CopySurface& s){copyObserve(s,'U');if(s.unlock60)s.unlock60();else unlockSurfacePixels(s.pixels,s.locks);}
inline void validateCopySurface(const CopySurface& s){
    if(&s.geometry.width!=&s.pixels.width4)throw std::invalid_argument("Copy surface width association");
    if(!s.pixels.storage.empty()&&!s.pixels.words.empty())throw std::invalid_argument("Ambiguous copy backing");
}
inline std::uint32_t copyPixelRead(const CopySurface& s,std::uint32_t at,unsigned n){
    const auto p=s.pixels;const auto size=p.words.empty()?std::uint64_t(p.storage.size()):std::uint64_t(p.words.size())*2;
    if(std::uint64_t(at)+n>size)throw std::invalid_argument("Copy read outside backing");
    std::uint32_t v=0;for(unsigned i=0;i<n;++i){const auto index=at+i;
        v|=std::uint32_t(p.words.empty()?p.storage[index]:std::uint8_t(p.words[index/2]>>(8*(index&1))))<<(8*i);
    }return v;
}
inline void copyPixelStore(CopySurface& s,std::uint32_t at,unsigned n,std::uint32_t v){
    const auto p=s.pixels;const auto size=p.words.empty()?std::uint64_t(p.storage.size()):std::uint64_t(p.words.size())*2;
    if(std::uint64_t(at)+n>size)throw std::invalid_argument("Copy store outside backing");
    for(unsigned i=0;i<n;++i){const auto index=at+i;const auto byte=std::uint8_t(v>>(8*i));
        if(p.words.empty())p.storage[index]=byte;
        else {auto& word=p.words[index/2];const auto shift=8*(index&1);word=std::uint16_t((word&~(255u<<shift))|(std::uint32_t(byte)<<shift));}
    }if(s.stores)s.stores(at,n,v);
}
inline bool copySameBacking(const CopySurface& a,const CopySurface& b){
    if(!a.pixels.words.empty()||!b.pixels.words.empty())return !a.pixels.words.empty()&&a.pixels.words.data()==b.pixels.words.data();
    return a.pixels.storage.data()==b.pixels.storage.data();
}
// Recovered783290 data movement: destination alignment bytes, ordered dwords,
// remaining bytes. Backward only for overlapping higher destination addresses.
// Offsets carry original allocation alignment, independent of host allocation.
template<class Transfer>
inline void transferSurfaceOverlapBytes(bool sameBacking,std::uint32_t dst,
        std::uint32_t src,std::uint32_t count,const Transfer& move){
    if(sameBacking&&dst>src&&dst<src+count){
        dst+=count;src+=count;
        auto prefix=count<4?count:dst%4;
        for(std::uint32_t i=0;i<prefix;++i){move(--dst,--src,1);--count;}
        while(count>=4){dst-=4;src-=4;move(dst,src,4);count-=4;}
        while(count){move(--dst,--src,1);--count;}
    }else{
        auto prefix=count<4?count:(4-dst%4)%4;
        for(std::uint32_t i=0;i<prefix;++i){move(dst++,src++,1);--count;}
        while(count>=4){move(dst,src,4);dst+=4;src+=4;count-=4;}
        while(count){move(dst++,src++,1);--count;}
    }
}
inline void copySurfaceOverlapBytes(CopySurface& d,std::uint32_t dst,
        CopySurface& s,std::uint32_t src,std::uint32_t count){
    transferSurfaceOverlapBytes(copySameBacking(d,s),dst,src,count,
        [&](auto to,auto from,unsigned n){copyPixelStore(d,to,n,copyPixelRead(s,from,n));});
}
enum class SurfaceCopyBlitter { transparentByte,transparentWord,opaqueByte,opaqueWord };
// Complete selected stock blitters. The reverse transparent entries forward to
// the forward leaf; opaque forward uses unaligned rep-movsd then rep-movsb.
inline void copySurfaceSpan(CopySurface& d,std::uint32_t dst,CopySurface& s,
        std::uint32_t src,std::int32_t count,SurfaceCopyBlitter blitter,bool reverse){
    const bool transparent=blitter==SurfaceCopyBlitter::transparentByte||blitter==SurfaceCopyBlitter::transparentWord;
    const unsigned pixelBytes=blitter==SurfaceCopyBlitter::transparentByte||blitter==SurfaceCopyBlitter::opaqueByte?1:2;
    if(blitter==SurfaceCopyBlitter::transparentWord&&count<=0)return;
    const auto bytes=std::uint32_t(count)*pixelBytes;
    if(std::uint32_t(count)>1048576||bytes>1048576)throw std::invalid_argument("Copy span exceeds native execution bound");
    if(transparent){
        for(std::int32_t i=0;i<count;++i){const auto v=copyPixelRead(s,src,pixelBytes);
            if(v)copyPixelStore(d,dst,pixelBytes,v);src+=pixelBytes;dst+=pixelBytes;}
    }else if(reverse)copySurfaceOverlapBytes(d,dst,s,src,bytes);
    else {auto n=bytes;while(n>=4){copyPixelStore(d,dst,4,copyPixelRead(s,src,4));src+=4;dst+=4;n-=4;}
        while(n){copyPixelStore(d,dst++,1,copyPixelRead(s,src++,1));--n;}}
}
struct SurfaceCopyLocks {
    bool reverse=false;
    std::optional<std::uint32_t> destination,source;
};
// Complete7753B0 with actual linked clip and ordinary stock lock/unlock.
inline bool prepareSurfaceCopy(CopySurface& d,const FillRect& db,FillRect& dr,
        CopySurface& s,const FillRect& sb,FillRect& sr,SurfaceCopyLocks& locks){
    locks.reverse=false;locks.destination.reset();locks.source.reset();
    if(dr[2]<=0||dr[3]<=0||db[2]<=0||db[3]<=0||sr[2]<=0||sr[3]<=0||sb[2]<=0||sb[3]<=0)return false;
    if(!clipSurfacePair(dr,db,sr,sb))return false;
    locks.reverse=false;
    if(&d==&s&&sr[0]<fillAdd(dr[0],dr[2])&&sr[1]<fillAdd(dr[1],dr[3])&&
       fillAdd(sr[0],sr[2])>dr[0]&&fillAdd(sr[1],sr[3])>dr[1]&&
       (sr[1]<dr[1]||(sr[1]==dr[1]&&sr[0]<dr[0])))locks.reverse=true;
    locks.destination=copySurfaceLock(d,fillAdd(db[0],dr[0]),fillAdd(db[1],dr[1]));
    if(!locks.destination)return false;
    locks.source=copySurfaceLock(s,fillAdd(sb[0],sr[0]),fillAdd(sb[1],sr[1]));
    if(!locks.source){copySurfaceUnlock(d);return false;}
    return true;
}
//434B40 ordinary copy profile with both optional alpha/depth globals zero.
// Nonzero entered planes refuse after actual clip/lock effects, without rollback.
inline bool transferSurfaceCopy(CopySurface& d,const FillRect& db,FillRect& dr,
        CopySurface& s,FillRect sb,FillRect sr,SurfaceCopyBlitter blitter,
        bool alphaPresent=false,bool depthPresent=false){
    SurfaceCopyLocks locks;if(!prepareSurfaceCopy(d,db,dr,s,sb,sr,locks))return false;
    if(alphaPresent||depthPresent)throw std::invalid_argument("Copy alpha/depth planes unrecovered");
    auto dst=*locks.destination,src=*locks.source;
    const auto dbytes=std::uint32_t(copySurfaceBpp(d))*std::uint32_t(dr[2]);
    bool flat=false;
    if(dbytes==copySurfacePitch(d)){
        const auto dp=copySurfacePitch(d),sp=copySurfacePitch(s);flat=dp==sp;
    }
    if(flat){
        const auto sa=std::bit_cast<std::int32_t>(std::uint32_t(sr[2])*std::uint32_t(sr[3]));
        const auto da=std::bit_cast<std::int32_t>(std::uint32_t(dr[2])*std::uint32_t(dr[3]));
        copySurfaceSpan(d,dst,s,src,sa<da?sa:da,blitter,locks.reverse);
    }else{
        auto sp=copySurfacePitch(s),dp=copySurfacePitch(d);
        if(locks.reverse){
            sp=0u-sp;dp=0u-dp;
            src+=copySurfacePitch(s)*std::uint32_t(fillSub(sr[3],1));
            dst+=copySurfacePitch(d)*std::uint32_t(fillSub(dr[3],1));
        }
        const auto rows=sr[3]<dr[3]?sr[3]:dr[3];
        if(rows>1048576)throw std::invalid_argument("Copy rows exceed native execution bound");
        for(std::int32_t row=0;row<rows;++row){
            // Original row width is source width, even when clipped sizes differ.
            copySurfaceSpan(d,dst,s,src,sr[2],blitter,locks.reverse);dst+=dp;src+=sp;
        }
    }
    copySurfaceUnlock(d);copySurfaceUnlock(s);return true;
}
// Complete434AE0 wrapper, preserving repeated source/destination rectangle queries.
inline bool copySurfaceWrapped(CopySurface& d,FillRect& dr,CopySurface& s,FillRect& sr,
        SurfaceCopyBlitter blitter,bool alphaPresent=false,bool depthPresent=false){
    auto sb=copySurfaceRect(s);auto db=copySurfaceRect(d);
    return transferSurfaceCopy(d,db,dr,s,sb,sr,blitter,alphaPresent,depthPresent);
}
// Complete774F00 for stock BSurface rect/format and transfer children. flag2 is
// unused; only flag1's low byte chooses transparent. Input rectangles are copied.
inline bool copySurface(CopySurface& d,const FillRect& destination,CopySurface& s,
        const FillRect& source,std::uint32_t flag1,std::uint32_t flag2,
        bool alphaPresent=false,bool depthPresent=false){
    validateCopySurface(d);validateCopySurface(s);(void)flag2;
    const auto sb=copySurfaceRect(s);const auto db=copySurfaceRect(d);
    auto dr=destination,sr=source;if(!clipSurfacePair(dr,db,sr,sb))return false;
    const bool byte=copySurfaceBpp(d)==1;
    const auto blitter=(flag1&255)?(byte?SurfaceCopyBlitter::transparentByte:SurfaceCopyBlitter::transparentWord):
        (byte?SurfaceCopyBlitter::opaqueByte:SurfaceCopyBlitter::opaqueWord);
    return copySurfaceWrapped(d,dr,s,sr,blitter,alphaPresent,depthPresent);
}
}
