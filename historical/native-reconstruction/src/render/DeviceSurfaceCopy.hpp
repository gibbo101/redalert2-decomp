// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceCopy.hpp"
#include "render/DeviceSurfacePixels.hpp"
namespace ra2 {
struct DeviceSurfaceCopyServices {
    DeviceSurfacePixelServices pixels;
    // Stock BSurface411310 returns low byte0. Device/hardware sources are an
    // explicit entered refusal until their distinct path is recovered.
    std::function<std::uint8_t(CopySurface&)> sourceDevice84;
};
// Complete4AAFD0 path for a software source: positive dimensions, source kind,
// enable gates, lost-device recovery, then actual774F00 with second flag1.
// The unused device/hardware branch is deliberately not reinterpreted as memcpy.
inline bool copyDeviceSurfaceRegion(CopySurface& d,DeviceSurfacePixelView device,
        const FillRect& db,const FillRect& dr,CopySurface& s,const FillRect& sb,
        const FillRect& sr,std::uint32_t first,std::uint32_t second,
        const DeviceSurfaceCopyServices& services){
    (void)second;
    if(db[2]<=0||db[3]<=0||sb[2]<=0||sb[3]<=0||dr[2]<=0||dr[3]<=0||sr[2]<=0||sr[3]<=0)return false;
    if(!services.sourceDevice84)throw std::invalid_argument("Device copy source kind unbound");
    if(services.sourceDevice84(s))throw std::invalid_argument("Device copy hardware source unrecovered");
    const auto& p=services.pixels;
    if(!p.enabled851CB0&&!p.enabledA40D28)return false;
    if(!device_pixel_detail::recover(device,p,0))return false;
    return copySurface(d,dr,s,sr,first,1);
}
// Complete4AAF80 on its stock device +0C association. Preserve source bounds
// before destination bounds; the fallback child independently queries them again.
inline bool copyDeviceSurface(CopySurface& d,DeviceSurfacePixelView device,
        const FillRect& dr,CopySurface& s,const FillRect& sr,
        std::uint32_t first,std::uint32_t second,const DeviceSurfaceCopyServices& services){
    const auto sb=copySurfaceRect(s);const auto db=copySurfaceRect(d);
    return copyDeviceSurfaceRegion(d,device,db,dr,s,sb,sr,first,second,services);
}
}
