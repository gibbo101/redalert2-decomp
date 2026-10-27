// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarActorPlacement.hpp"
namespace ra2 {
struct RadarPermissionType {
    const std::uint8_t &flagAA6,&flagAA7,&veteran277,&elite289;
};
struct RadarPermissionActor {
    const Coord& coordinates88;
    const std::uint8_t &flag325,&discovery373;
    const double& veterancy118;
    const std::int32_t& mode1B8;
    const std::uint8_t &field5BD,&field5B7;
};
struct RadarPermissionWorld {
    const std::int32_t& modeB263D8;
    const std::uint32_t& sessionFlags;
    const void* const& currentHouseA35DB4;
};
struct RadarPermissionServices {
    std::function<RadarPermissionType()> type80;
    std::function<const void*()> owner1B4;
    std::function<std::uint32_t(const void*)> local4F52B0;
    std::function<std::int32_t()> height1B0;
    std::function<std::uint32_t(Coord)> primary568140,secondary5683C0;
    std::function<std::uint32_t()> eligible2FC;
    std::function<bool(const void*,const void*)> allied4E5540;
    std::function<std::int32_t(std::uint8_t)> foundationHeight458940;
    std::function<std::int32_t()> foundationWidth458930;
    std::function<void(char)> probe;
    std::function<void(std::int32_t)> statusStore;
};
inline void radarPermissionNeed(bool value){if(!value)throw std::invalid_argument("Radar permission child unbound");}
inline bool radarPermissionLocal(const RadarPermissionServices& s){
    radarPermissionNeed(bool(s.owner1B4)&&bool(s.local4F52B0));return (s.local4F52B0(s.owner1B4())&255u)!=0;
}
inline bool finishRadarPermission(std::int32_t& status,std::int32_t value,const RadarPermissionServices& s){
    status=value;if(s.statusStore)s.statusStore(value);return true;
}
// Complete6D7A10. Status is an output only on the original encountered branch;
// early true/false returns must leave the caller's prior word untouched.
inline bool infantryRadarPermission(std::int32_t& status,RadarPermissionActor a,
        RadarPermissionWorld w,const RadarPermissionServices& s){
    radarPermissionNeed(bool(s.type80));const auto type=s.type80();
    if(type.flagAA6||a.flag325)return false;
    if(type.flagAA7)return true;
    if(radarPermissionLocal(s))return a.discovery373!=0;
    radarPermissionNeed(bool(s.height1B0));const auto height=s.height1B0();
    const auto veteran=[&]{if(s.probe)s.probe('V');return a.veterancy118>=1.&&a.veterancy118<2.;};
    const auto elite=[&]{if(s.probe)s.probe('E');return a.veterancy118>=2.;};
    bool promoted=false;
    if(veteran()||elite()){
        const auto promotedType=s.type80();
        if(veteran()&&promotedType.veteran277)promoted=true;
        else if(elite()&&(promotedType.veteran277||promotedType.elite289))promoted=true;
    }
    radarPermissionNeed(bool(s.primary568140));
    const bool hidden=(s.primary568140(a.coordinates88)&255u)!=0&&w.modeB263D8!=0;
    bool secondary=false;
    if(w.sessionFlags&0x1000u){
        radarPermissionNeed(bool(s.secondary5683C0));secondary=(s.secondary5683C0(a.coordinates88)&255u)!=0;
    }
    if(!secondary&&a.mode1B8!=2&&height>=-20&&!promoted&&!hidden)return true;
    radarPermissionNeed(bool(s.eligible2FC));if(!(s.eligible2FC()&255u))return false;
    radarPermissionNeed(bool(s.allied4E5540)&&bool(s.owner1B4));
    const auto* owner=s.owner1B4();const auto* current=w.currentHouseA35DB4;
    if(!s.allied4E5540(current,owner)&&!promoted&&!secondary&&!hidden)
        return finishRadarPermission(status,height<-20?2:1,s);
    return true;
}
// Complete452220. The second visibility point uses a fresh88 snapshot after the
// first query and wrapped ((dimension<<8)-256) offsets, not its center virtual48.
inline bool buildingRadarPermission(std::int32_t& status,RadarPermissionActor a,
        RadarPermissionWorld w,const RadarPermissionServices& s){
    radarPermissionNeed(bool(s.type80));const auto type=s.type80();
    if(type.flagAA6)return false;if(type.flagAA7)return true;
    if(radarPermissionLocal(s))return a.discovery373!=0;
    radarPermissionNeed(bool(s.foundationHeight458940)&&bool(s.foundationWidth458930));
    const auto h=s.foundationHeight458940(0),width=s.foundationWidth458930();
    const auto extent=[](std::int32_t n){return fillSub(std::bit_cast<std::int32_t>(std::uint32_t(n)<<8),256);};
    const auto dy=extent(h),dx=extent(width);
    radarPermissionNeed(bool(s.primary568140));bool hidden=false;
    if(s.primary568140(a.coordinates88)&255u){
        const auto point=a.coordinates88;
        hidden=(s.primary568140({fillAdd(point.x,dx),fillAdd(point.y,dy),point.z})&255u)!=0&&w.modeB263D8!=0;
    }
    if(a.mode1B8!=2&&a.field5BD!=15&&!a.field5B7&&!hidden)return true;
    radarPermissionNeed(bool(s.eligible2FC));if(!(s.eligible2FC()&255u))return false;
    radarPermissionNeed(bool(s.allied4E5540)&&bool(s.owner1B4));
    const auto* owner=s.owner1B4();const auto* current=w.currentHouseA35DB4;
    if(!s.allied4E5540(current,owner)&&!a.field5B7&&!hidden)
        return finishRadarPermission(status,1,s);
    return true;
}
}
