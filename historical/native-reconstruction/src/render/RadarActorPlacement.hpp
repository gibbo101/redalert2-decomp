// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarActorMarkers.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
struct RadarActorPlacementFields {
    Coord& coordinates88;
    std::uint8_t& discovery373;
    RadarActorMarkerFields marker;
    const std::uint8_t& flags14;
    const std::int8_t& secondary574;
    std::function<const void*()> owner1B4; // Pure logical owner association, read late.
    const std::int32_t &timerStart13C,&timerRemaining144;
};
struct RadarActorPlacementWorld {
    const std::int32_t &loadingA3D298,&frameA40D2C;
    const void* const& currentHouseA35DB4;
};
struct RadarActorPlacementServices {
    std::function<Coord()> coordinates48;
    std::function<std::uint32_t(Coord)> discovery568140;
    std::function<std::int32_t()> kind2C;
    std::function<RadarShapePoint(Coord,std::uint8_t)> project631BA0;
    // The single argument addresses a status word initialized to0, not x/y.
    std::function<std::uint32_t(std::int32_t&)> permission2F8;
    std::function<RefreshRect()> rectangle78;
    // Inspected event-list proximity/allocation parent; not a Cell visibility setter.
    // Constructor effects remain unjoined. The placement caller ignores its AL.
    std::function<void(std::int32_t,std::uint32_t)> radarEvent63B5B0;
    std::function<const void*(std::int32_t)> cell1AC;
    std::function<std::uint32_t(const void*)> permitted55A740;
    std::function<void()> remove424,insert420,dirty428;
    std::function<std::int32_t()> flashDivisor90;
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
// Complete6D8120. Child boundaries must be explicitly bound; this parent never
// invents permission, discovery, placement/registration or screen behavior.
inline void placeActorRadar(std::uint32_t argument,RadarActorPlacementFields a,
        RadarActorPlacementWorld w,const RadarActorPlacementServices& s){
    const auto need=[](bool v){if(!v)throw std::invalid_argument("Radar actor placement child unbound");};
    const auto store=[&](unsigned off,unsigned size,std::uint32_t value){if(s.store)s.store(off,size,value);};
    if(!a.discovery373&&!w.loadingA3D298){
        need(bool(s.coordinates48)&&bool(s.discovery568140));const auto point=s.coordinates48();
        a.discovery373=(s.discovery568140(point)&255u)==0;store(0x373,1,a.discovery373);
    }
    need(bool(s.kind2C));RadarShapePoint point;
    if(s.kind2C()==6&&(argument&255u)==0)point={a.marker.x1A0,a.marker.y1A4};
    else{need(bool(s.project631BA0));point=s.project631BA0(a.coordinates88,0);}
    std::int32_t status=0;need(bool(s.permission2F8));
    auto permission=std::uint8_t(s.permission2F8(status));
    need(bool(s.rectangle78));const auto rect=s.rectangle78();
    if(status&&permission&&(!(a.flags14&4u)||a.secondary574<0)){
        need(bool(s.radarEvent63B5B0));
        const auto x=std::uint16_t(a.coordinates88.x/256),y=std::uint16_t(a.coordinates88.y/256);
        s.radarEvent63B5B0(5,std::uint32_t(x)|(std::uint32_t(y)<<16));
    }
    if((point.x<rect[0]||point.x>=fillAdd(rect[0],rect[2])||
            point.y<rect[1]||point.y>=fillAdd(rect[1],rect[3]))&&permission){
        need(bool(s.cell1AC)&&bool(s.permitted55A740));const auto* cell=s.cell1AC(1);
        permission=std::uint8_t(s.permitted55A740(cell));
        if(permission){need(bool(s.project631BA0));point=s.project631BA0(a.coordinates88,1);}
    }
    if(a.marker.registered37B&&(point.x!=a.marker.x1A0||point.y!=a.marker.y1A4||!permission)){
        need(bool(s.remove424));s.remove424();
    }
    a.marker.x1A0=point.x;store(0x1a0,4,std::uint32_t(point.x));
    // Original reads37B between the two coordinate stores.
    const auto registered=a.marker.registered37B;
    a.marker.y1A4=point.y;store(0x1a4,4,std::uint32_t(point.y));
    if(!registered&&permission){need(bool(s.insert420));s.insert420();}
    need(bool(a.owner1B4));if(a.owner1B4()!=w.currentHouseA35DB4)return;
    auto start=a.timerStart13C,remaining=a.timerRemaining144;
    const auto frame=w.frameA40D2C;
    if(start!=-1){const auto elapsed=fillSub(frame,start);if(elapsed>=remaining)return;remaining=fillSub(remaining,elapsed);}
    if(remaining<=0)return;
    start=a.timerStart13C;remaining=a.timerRemaining144;
    if(start!=-1){const auto elapsed=fillSub(frame,start);remaining=elapsed>=remaining?0:fillSub(remaining,elapsed);}
    need(bool(s.flashDivisor90));const auto divisor=s.flashDivisor90();
    if(!divisor||(remaining==INT32_MIN&&divisor==-1))throw std::invalid_argument("Radar actor flash division fault");
    if(remaining%divisor==0){need(bool(s.dirty428));s.dirty428();}
}
}
