// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceFill.hpp"
#include <optional>
namespace ra2 {
// Borrowed ordinary BSurface fields. The allocation and geometry association
// are supplied; width can be the very same field used by refresh/marks.
struct SurfacePixelView {
    const std::int32_t& width4;
    std::int32_t& lockC;
    const std::int32_t& bytes10;
    const std::uint32_t& bufferOffset14;
    std::span<std::uint8_t> storage;
    std::span<std::uint16_t> words;
    bool allocationPresent=true;
};
inline SurfacePixelView surfacePixelView(FillSurface& s){
    return {s.width,s.lockLevel,s.bytesPerPixel,s.bufferOffset,s.storage,s.words,true};
}
using PixelLockTrace=std::function<void(std::int32_t)>;
// Stock4113C0: width virtual executes before the late format read.
inline std::uint32_t surfacePixelPitch(SurfacePixelView s,
        const std::function<std::int32_t()>& width7C={}){
    const auto width=width7C?width7C():s.width4;
    return std::uint32_t(width)*std::uint32_t(s.bytes10);
}
// Stock411370: preserve saved allocation, early X format and late pitch.
inline std::optional<std::uint32_t> lockSurfacePixels(SurfacePixelView s,
        std::int32_t x,std::int32_t y,const std::function<std::int32_t()>& width7C={},
        const PixelLockTrace& locks={},const std::function<std::int32_t()>& bpp70={},
        const std::function<std::uint32_t()>& pitch74={}){
    s.lockC=fillAdd(s.lockC,1);if(locks)locks(s.lockC);
    const auto savedBuffer=s.bufferOffset14;
    const auto bpp=bpp70?bpp70():s.bytes10;
    const auto xBytes=std::uint32_t(bpp)*std::uint32_t(x);
    const auto pitch=pitch74?pitch74():surfacePixelPitch(s,width7C);
    const auto at=savedBuffer+xBytes+pitch*std::uint32_t(y);
    if(!s.allocationPresent){
        if(at==0)return std::nullopt;
        throw std::invalid_argument("Pixel null-base nonzero address unsupported");
    }
    return at;
}
inline void unlockSurfacePixels(SurfacePixelView s,const PixelLockTrace& locks={}){
    s.lockC=fillSub(s.lockC,1);if(locks)locks(s.lockC);
}
struct SurfacePixelBacking {
    std::span<std::uint8_t> storage;
    std::span<std::uint16_t> words;
};
struct SurfacePixelServices {
    std::function<std::optional<std::uint32_t>(std::int32_t,std::int32_t)> lock;
    std::function<std::int32_t()> bytes70;
    std::function<void()> unlock;
};
// Complete774220 on explicit surface virtuals. Lock normalizes a nonnull logical
// address to a backing offset; offset0 is valid, unlike an original null pointer.
inline bool setSurfacePixelThrough(SurfacePixelBacking s,std::int32_t x,std::int32_t y,
        std::uint32_t color,const SurfacePixelServices& services,const FillStoreTrace& trace={}){
    if(!s.storage.empty()&&!s.words.empty())throw std::invalid_argument("Ambiguous pixel backing");
    if(!services.lock)throw std::invalid_argument("Missing pixel lock");
    const auto address=services.lock(x,y);
    if(!address)return false; // Original null return skips bpp/store/unlock.
    const auto at=*address;
    if(!services.bytes70)throw std::invalid_argument("Missing pixel format");
    const auto n=services.bytes70()==2?2u:1u;
    const auto count=s.words.empty()?std::uint64_t(s.storage.size()):std::uint64_t(s.words.size())*2;
    if(std::uint64_t(at)+n>count)throw std::invalid_argument("Pixel outside backing");
    const auto value=color&(n==2?65535u:255u);
    for(unsigned i=0;i<n;++i){
        const auto byte=std::uint8_t(value>>(8*i));const auto p=at+i;
        if(s.words.empty())s.storage[p]=byte;
        else {const auto shift=(p&1)*8;auto& word=s.words[p/2];word=std::uint16_t((word&~(255u<<shift))|(std::uint32_t(byte)<<shift));}
    }
    if(trace)trace(at,n,value);
    if(!services.unlock)throw std::invalid_argument("Missing pixel unlock");services.unlock();
    return true;
}
// Complete7741D0 on the same virtual contract. Capture before Unlock.
inline std::uint32_t getSurfacePixelThrough(SurfacePixelBacking s,std::int32_t x,std::int32_t y,
        const SurfacePixelServices& services){
    if(!s.storage.empty()&&!s.words.empty())throw std::invalid_argument("Ambiguous pixel backing");
    if(!services.lock)throw std::invalid_argument("Missing pixel lock");
    const auto address=services.lock(x,y);
    if(!address)return 0;
    if(!services.bytes70)throw std::invalid_argument("Missing pixel format");
    const auto at=*address,n=services.bytes70()==2?2u:1u;
    const auto count=s.words.empty()?std::uint64_t(s.storage.size()):std::uint64_t(s.words.size())*2;
    if(std::uint64_t(at)+n>count)throw std::invalid_argument("Pixel read outside backing");
    std::uint32_t value=0;
    for(unsigned i=0;i<n;++i){const auto p=at+i;const auto byte=s.words.empty()?s.storage[p]:std::uint8_t(s.words[p/2]>>(8*(p&1)));value|=std::uint32_t(byte)<<(8*i);}
    if(!services.unlock)throw std::invalid_argument("Missing pixel unlock");services.unlock();return value;
}
// Ordinary BSurface facade retains the same stock lock/format/pitch/width/unlock
// chain and supplied allocation association; no second pixel writer/reader.
inline bool setSurfacePixel(SurfacePixelView s,std::int32_t x,std::int32_t y,
        std::uint32_t color,const FillStoreTrace& trace={},
        const std::function<std::int32_t()>& width7C={},const PixelLockTrace& locks={}){
    SurfacePixelServices services;
    services.lock=[&](auto a,auto b){return lockSurfacePixels(s,a,b,width7C,locks);};
    services.bytes70=[&]{return s.bytes10;};services.unlock=[&]{unlockSurfacePixels(s,locks);};
    return setSurfacePixelThrough({s.storage,s.words},x,y,color,services,trace);
}
inline std::uint32_t getSurfacePixel(SurfacePixelView s,std::int32_t x,std::int32_t y,
        const std::function<std::int32_t()>& width7C={},const PixelLockTrace& locks={}){
    SurfacePixelServices services;
    services.lock=[&](auto a,auto b){return lockSurfacePixels(s,a,b,width7C,locks);};
    services.bytes70=[&]{return s.bytes10;};services.unlock=[&]{unlockSurfacePixels(s,locks);};
    return getSurfacePixelThrough({s.storage,s.words},x,y,services);
}

}
