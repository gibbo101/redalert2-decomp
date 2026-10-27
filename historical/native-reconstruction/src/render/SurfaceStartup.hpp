// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
namespace ra2 {
using SurfaceDescriptor=std::span<std::uint32_t,27>;
struct DeviceSurfaceStartup {
    std::int32_t width4=0,height8=0,lockC=0;
    std::uint32_t bytes10=0,offset14=0;
    std::uint8_t flag18=0,video19=0;
    std::uintptr_t surface1C=0;
    std::span<std::uint32_t> descriptor20;
};
struct SurfaceStartupServices {
    std::function<std::span<std::uint32_t>(std::uint32_t)> allocate;
    std::function<void(SurfaceDescriptor,std::uintptr_t&)> create;
    std::function<void(std::uintptr_t,SurfaceDescriptor)> describe;
    // Diagnostic observers only. Vtable and pointers use logical identities.
    std::function<void(unsigned,unsigned,std::uint32_t)> objectStore,descriptorStore;
};
// Complete base4AA4A0 policy. Allocation/device calls remain explicit platform
// services; this does not implement DirectDraw or claim radar caller startup.
// Record may borrow geometry fields from an existing RefreshSurface owner.
template<class Record>
inline void initializeDeviceSurface(Record& s,std::int32_t width,
        std::int32_t height,std::uint8_t requestedVideo,const std::uint8_t& forcedSystem,
        const SurfaceStartupServices& services){
    const auto object=[&](unsigned off,unsigned n,std::uint32_t v){if(services.objectStore)services.objectStore(off,n,v);};
    s.width4=width;object(4,4,std::uint32_t(width));s.height8=height;object(8,4,std::uint32_t(height));
    s.lockC=0;object(12,4,0);s.bytes10=0;object(16,4,0);s.offset14=0;object(20,4,0);
    s.flag18=0;object(24,1,0);s.video19=0;object(25,1,0);s.surface1C=0;object(28,4,0);
    s.descriptor20={};object(32,4,0);object(0,4,3); // Device-surface virtual identity.
    if(!services.allocate)throw std::invalid_argument("Unbound surface descriptor allocation");
    s.descriptor20=services.allocate(108);object(32,4,s.descriptor20.empty()?0:2);
    if(s.descriptor20.empty())return;
    if(s.descriptor20.size()!=27)throw std::invalid_argument("Surface descriptor extent differs");
    const auto put=[&](unsigned off,std::uint32_t v){s.descriptor20[off/4]=v;if(services.descriptorStore)services.descriptorStore(off,4,v);};
    const auto clear=[&]{for(unsigned off=0;off<108;off+=4)put(off,0);};
    clear();put(0,108);put(4,7);put(12,std::uint32_t(width));put(8,std::uint32_t(height));
    if(requestedVideo==1)put(104,s.descriptor20[26]|0x800);
    if(forcedSystem)put(104,0x2040); // Overwrite, not an OR with requested caps.
    if(!services.create)throw std::invalid_argument("Unbound surface creation");
    services.create(SurfaceDescriptor(s.descriptor20),s.surface1C);
    if(!s.surface1C)return;
    clear();put(0,108);
    if(!services.describe)throw std::invalid_argument("Unbound surface description");
    services.describe(s.surface1C,SurfaceDescriptor(s.descriptor20));
    s.bytes10=(s.descriptor20[21]+std::uint32_t(7))>>3;object(16,4,s.bytes10);
    s.video19=std::uint8_t((s.descriptor20[26]>>14)&1);object(25,1,s.video19);
}
}
