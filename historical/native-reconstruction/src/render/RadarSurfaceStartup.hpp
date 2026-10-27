// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefresh.hpp"
#include "render/SurfaceFill.hpp"
namespace ra2 {
struct RadarSurfaceStartupFields {
    RefreshSurface*& first1218;
    RefreshSurface*& second121C;
    const void*& colors1238;
    const void*& bitmap1270;
    RefreshRect& rectangle1498;
    const std::int32_t& originX11EC;
    const std::int32_t& originY11F0;
};
struct RadarSurfaceStartupServices {
    std::function<void(RefreshSurface*,std::uint32_t)> destroy;
    std::function<void(const void*)> release;
    // Bind complete630B70 on the same owners; both rectangle arguments alias.
    std::function<void(RefreshRect&,RefreshRect&,RefreshRect&,std::uint8_t)> buildSecond;
    std::function<RefreshSurface*(std::uint32_t)> allocateFirst;
    std::function<RefreshSurface*(RefreshSurface*,std::int32_t,std::int32_t,std::uint8_t)> initializeFirst;
    std::function<void(RefreshSurface&,std::uint32_t)> clear;
    std::function<void()> finish632700;
    std::function<void(unsigned,std::int32_t)> store;
};
// Complete630A00. Uses the existing refresh geometry owners, not a parallel
// surface record. Allocation/projection/device/clear/finish remain named services.
inline void initializeRadarSurfaces(RadarSurfaceStartupFields s,
        const RadarSurfaceStartupServices& services){
    if(s.rectangle1498[2]<=0||s.rectangle1498[3]<=0)return;
    const auto store=[&](unsigned off,std::int32_t value){if(services.store)services.store(off,value);};
    const auto width=[](RefreshSurface* p){if(!p||!p->table||!p->table->width7C)throw std::invalid_argument("Unbound radar width getter");return p->table->width7C(*p);};
    const auto height=[](RefreshSurface* p){if(!p||!p->table||!p->table->height80)throw std::invalid_argument("Unbound radar height getter");return p->table->height80(*p);};
    // The original saves the second receiver before these first two stores.
    auto* second=s.second121C;
    s.rectangle1498[1]=0;store(0x149c,0);s.rectangle1498[0]=0;store(0x1498,0);
    if(second){if(!services.destroy)throw std::invalid_argument("Unbound radar destruction");services.destroy(second,1);s.second121C=nullptr;store(0x121c,0);}
    if(s.colors1238){if(!services.release)throw std::invalid_argument("Unbound radar release");services.release(s.colors1238);s.colors1238=nullptr;store(0x1238,0);}
    if(s.bitmap1270){if(!services.release)throw std::invalid_argument("Unbound radar release");services.release(s.bitmap1270);s.bitmap1270=nullptr;store(0x1270,0);}
    if(!services.buildSecond)throw std::invalid_argument("Unbound radar projection builder");
    RefreshRect scratch{}; // The supplied child owns all produced scratch values.
    services.buildSecond(scratch,s.rectangle1498,s.rectangle1498,1);
    const auto initialWidth=width(s.second121C);s.rectangle1498[2]=initialWidth;store(0x14a0,initialWidth);
    const auto h=height(s.second121C);
    const auto w=s.rectangle1498[2];
    const auto savedOriginX=s.originX11EC;s.rectangle1498[3]=h;store(0x14a4,h);
    s.rectangle1498[0]=savedOriginX;store(0x1498,savedOriginX);
    if(w<140){s.rectangle1498[0]=fillAdd(savedOriginX,fillSub(140,w)/2);store(0x1498,s.rectangle1498[0]);}
    const auto savedOriginY=s.originY11F0;s.rectangle1498[1]=savedOriginY;store(0x149c,savedOriginY);
    if(h<108){s.rectangle1498[1]=fillAdd(savedOriginY,fillSub(108,h)/2);store(0x149c,s.rectangle1498[1]);}
    if(s.first1218){if(!services.destroy)throw std::invalid_argument("Unbound radar destruction");services.destroy(s.first1218,1);s.first1218=nullptr;store(0x1218,0);}
    if(!services.allocateFirst)throw std::invalid_argument("Unbound radar first allocation");
    auto* allocated=services.allocateFirst(36);RefreshSurface* first=nullptr;
    if(allocated){
        auto* saved=s.second121C;const auto newHeight=height(saved);const auto newWidth=width(saved);
        if(!services.initializeFirst)throw std::invalid_argument("Unbound radar first initializer");
        first=services.initializeFirst(allocated,newWidth,newHeight,1);
    }
    s.first1218=first;store(0x1218,first?1:0);
    if(!first||!services.clear)throw std::invalid_argument("Radar first surface allocation/clear unavailable");
    services.clear(*first,0);
    if(!services.finish632700)throw std::invalid_argument("Unbound radar startup finish");services.finish632700();
}
}
