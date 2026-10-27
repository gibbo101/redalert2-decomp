// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/WaypointResidentDiscovery.hpp"
#include "sim/MissionTag.hpp"
namespace ra2 {
struct WaypointTaggedDiscoveryBinding {
    WaypointResidentDiscoveryBinding resident;
    MissionTagState*& tag;
    const void* object;
};
// Common6C2440 passes4/object/packed-location/force0/source0 to6B3DF0.
// Scope the callback to this actual owner; preserve prior bindings on every exit.
inline bool discoverWaypointTaggedResident(int identity,int house,UnitDiscoveryWorld& world,
        std::span<const WaypointTaggedDiscoveryBinding> bindings,const MissionTagServices& services,
        const std::function<void()>& tagEntered={}){
    const WaypointTaggedDiscoveryBinding* selected=nullptr;
    for(const auto& b:bindings)if(b.resident.identity==identity){
        if(selected)throw std::invalid_argument("Ambiguous tagged waypoint resident");selected=&b;
    }
    if(!selected||!selected->resident.actor||!selected->object)
        throw std::invalid_argument("Foreign tagged waypoint resident");
    auto& actor=*selected->resident.actor;actor.hasTag=selected->tag!=nullptr;
    auto previous=std::move(world.tagEvent);
    world.tagEvent=[&](int location){
        if(!selected->tag)throw std::invalid_argument("Reached null waypoint Tag");
        if(tagEntered)tagEntered(); // Read-only protocol observation at actual entry.
        MissionTagOwner owner{selected->tag,selected->object};
        (void)raiseMissionTagEvent(*selected->tag,{4,selected->object,0,0,nullptr},&owner,std::uint32_t(location),services);
    };
    try{const bool result=discoverWaypointResident(identity,house,world,std::span(&selected->resident,1));
        world.tagEvent=std::move(previous);return result;
    }catch(...){world.tagEvent=std::move(previous);throw;}
}
}
