// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceStartup.hpp"
#include "render/SurfaceFill.hpp"
#include <bit>
namespace ra2 {
// Borrow the device initializer's actual fields. Addresses are 32-bit logical
// buffer addresses, mapped to native backing by the platform adapter.
struct DeviceSurfacePixelView {
    std::int32_t& lockC;
    std::uint32_t& bytes10;
    std::uint32_t& address14;
    std::uint8_t& video19;
    std::uintptr_t& surface1C;
    std::span<std::uint32_t>& descriptor20;
};
struct DeviceSurfacePixelServices {
    const std::uint8_t &enabled851CB0,&enabledA40D28;
    std::function<std::uint32_t(std::uintptr_t)> lost,restore;
    std::function<std::uint32_t(std::uintptr_t,SurfaceDescriptor,std::uint32_t)> lock;
    std::function<void(std::uintptr_t,std::uint32_t)> unlock;
    std::function<void(unsigned,unsigned,std::uint32_t)> objectStore,descriptorStore;
    std::function<std::uint32_t()> pitch74,bytes70;
    std::function<void(std::int32_t,std::int32_t)> lockEntry;
    std::function<void()> unlockEntry;
};
inline std::uint32_t lockDeviceSurfacePixels(DeviceSurfacePixelView,
    std::int32_t,std::int32_t,const DeviceSurfacePixelServices&,unsigned=0);
inline bool unlockDeviceSurfacePixels(DeviceSurfacePixelView,
    const DeviceSurfacePixelServices&,unsigned=0);
namespace device_pixel_detail {
inline void need(bool v){if(!v)throw std::invalid_argument("Device pixel owner/service/domain");}
inline void depth(unsigned v){need(v<16);} // Host recursion bound, not an original clamp.
inline void storeLock(DeviceSurfacePixelView s,std::int32_t v,const DeviceSurfacePixelServices& p){
    s.lockC=v;if(p.objectStore)p.objectStore(12,4,std::uint32_t(v));
}
inline bool recover(DeviceSurfacePixelView s,const DeviceSurfacePixelServices& p,unsigned depth){
    if(!s.surface1C)return true;
    need(bool(p.lost));if(p.lost(s.surface1C)!=0x887601c2u)return true;
    need(bool(p.restore));if(p.restore(s.surface1C)!=0)return false;
    if(p.lost(s.surface1C)!=0)return false;
    const auto saved=s.lockC;
    if(saved>0){
        storeLock(s,0,p);(void)lockDeviceSurfacePixels(s,0,0,p,depth+1);
        storeLock(s,fillAdd(s.lockC,1),p);(void)unlockDeviceSurfacePixels(s,p,depth+1);
        storeLock(s,saved,p);
    }
    return true;
}
}
// Complete4AAC80, using actual4AAC60/4AAC70 getters unless explicit diagnostic
// virtuals are supplied. OS status/restore/Lock are native platform services.
inline std::uint32_t lockDeviceSurfacePixels(DeviceSurfacePixelView s,
        std::int32_t x,std::int32_t y,const DeviceSurfacePixelServices& p,unsigned depth){
    using namespace device_pixel_detail;device_pixel_detail::depth(depth);
    if(p.lockEntry)p.lockEntry(x,y);
    if(!p.enabled851CB0&&!p.enabledA40D28)return 0;
    if(!recover(s,p,depth)||x<0||y<0)return 0;
    if(s.lockC==0){
        std::array<std::uint32_t,27> temporary{};temporary[0]=108;
        need(s.surface1C&&bool(p.lock));if(p.lock(s.surface1C,temporary,1)!=0)return 0;
        need(s.descriptor20.size()==27);
        for(unsigned i=0;i<27;++i){s.descriptor20[i]=temporary[i];if(p.descriptorStore)p.descriptorStore(i*4,4,temporary[i]);}
        s.bytes10=(s.descriptor20[21]+std::uint32_t(7))>>3;
        if(p.objectStore)p.objectStore(16,4,s.bytes10);
        s.video19=std::uint8_t((s.descriptor20[26]>>14)&1);
        if(p.objectStore)p.objectStore(25,1,s.video19);
        s.address14=s.descriptor20[9];if(p.objectStore)p.objectStore(20,4,s.address14);
    }
    storeLock(s,fillAdd(s.lockC,1),p);
    need(bool(p.pitch74)||s.descriptor20.size()==27);
    const auto pitch=p.pitch74?p.pitch74():s.descriptor20[4];
    const auto row=pitch*std::uint32_t(y);
    const auto bytes=p.bytes70?p.bytes70():s.bytes10;
    return s.address14+row+bytes*std::uint32_t(x);
}
// Complete4AAE40. Disabled/lost/restore-failed cases still reach the ordinary
// decrement tail; a failed recovery is not an early return from Unlock.
inline bool unlockDeviceSurfacePixels(DeviceSurfacePixelView s,
        const DeviceSurfacePixelServices& p,unsigned depth){
    using namespace device_pixel_detail;device_pixel_detail::depth(depth);
    if(p.unlockEntry)p.unlockEntry();
    if(p.enabled851CB0||p.enabledA40D28)(void)recover(s,p,depth);
    if(s.lockC<=0)return false;
    const auto left=fillSub(s.lockC,1);storeLock(s,left,p);
    if(left==0){
        need(s.surface1C&&bool(p.unlock));p.unlock(s.surface1C,s.address14);
        s.address14=0;if(p.objectStore)p.objectStore(20,4,0);
    }
    return true;
}
}
