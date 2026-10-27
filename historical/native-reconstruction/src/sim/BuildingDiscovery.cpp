// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/BuildingDiscovery.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
template<class T> bool radioLinks(std::int32_t count,std::span<T> links){
    for(std::int32_t i=0;i<count;++i){
        if(std::size_t(i)>=links.size())throw std::invalid_argument("Building radio count exceeds bound storage");
        if(links[std::size_t(i)])return true;
    }
    return false;
}
}
bool buildingHasRadioLinks(std::int32_t count,std::span<const std::uintptr_t> links){return radioLinks(count,links);}
bool buildingHasRadioPointerLinks(std::int32_t count,std::span<const void* const> links){return radioLinks(count,links);}
bool discoverBuilding(UnitDiscoveryActor& actor,int discoverer,UnitDiscoveryWorld& world,
        const BuildingDiscoveryServices& s){
    if(!discoverUnit(actor,discoverer,world))return false;
    const auto store=[&](int house,int offset,std::uint32_t value){if(world.store)world.store(house+1,offset,value);};
    if(!world.loading){
        if(!s.typeIndexB90)throw std::invalid_argument("Building discovery needs live type index");
        // Original saves Owner before reading typeB90 and rereads Owner for18D.
        const int owner=actor.owner;const auto type=s.typeIndexB90();
        world.houses.at(owner).buildingType1b4=type;store(owner,0x1b4,std::uint32_t(type));
        const int lateOwner=actor.owner;world.houses.at(lateOwner).building18d=1;store(lateOwner,0x18d,1);
    }
    const int owner=actor.owner;world.houses.at(owner).building144=1;store(owner,0x144,1);
    if(!s.radioLinks)throw std::invalid_argument("Building discovery needs actual radio vector");
    const auto controlled=[&]{
        if(world.trace)world.trace('h',actor.owner);
        return discoveryHouseControlled(world.houses.at(actor.owner),world.mode)!=0;
    };
    const auto mission=[&]{if(world.trace)world.trace('g',0);return unitDiscoveryMission(actor);};
    bool secondBranch=true;
    if(!s.radioLinks()&&controlled()&&mission()!=18&&actor.queuedA0!=18)secondBranch=false;
    if(!secondBranch||(!s.radioLinks()&&!controlled()&&discoverer==actor.owner&&mission()!=18)){
        if(!s.activate)throw std::invalid_argument("Building discovery activation4426D0 is unbound");
        s.activate(0);
    }
    return true;
}
}
