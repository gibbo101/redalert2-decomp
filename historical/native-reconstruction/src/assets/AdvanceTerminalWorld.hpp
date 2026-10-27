// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapFloorHeight.hpp"
#include "sim/FootCoordinates.hpp"
#include "sim/GroundDriveTerminal.hpp"

namespace ra2 {
// Borrow actual actor/Drive, Cell identities and mutable floor cache. Binding
// performs no queries. The actor query uses Foot's head/registry selection,
// independently of its location and of the target Cell's generic wrapper.
struct AdvanceTerminalWorld {
    UnitDestinationView unit;
    AdvanceTerminalFlags flags;
    const std::int8_t& registry574;
    std::span<const TerrainCellPoint> registry;
    std::span<MapCellInput* const> targets;
    MapFloorHeightState& floor;
    const int& floorHeight;
};
using AdvanceTerminalTrace=std::function<void(char,int,int,int)>;
inline bool finishAdvanceTerminalOnMap(AdvanceTerminalWorld v,int divisor,int residual,
    AdvanceTerminalServices supplied,const AdvanceTerminalTrace& trace={}) {
    const auto event=[&](char k,int a=0,int b=0,int c=0){if(trace)trace(k,a,b,c);};
    supplied.targetCoordinates=[&](const void* target) {
        int id=-1;
        for(std::size_t i=0;i<v.targets.size();++i)if(v.targets[i]==target)id=int(i);
        if(id<0)throw UnsupportedAdvanceTerminal("Terminal target is not a bound Cell identity");
        event('Q',id);
        const auto p=mapCellCenterHeight(v.floor,v.floorHeight,*v.targets[std::size_t(id)]);
        event('q',p.x,p.y,p.z);return p;
    };
    supplied.actorCell=[&]{
        const auto p=v.unit.drive.movement.actor.position;
        const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));};
        const auto x=word(p.x),y=word(p.y);event('C',x,y);return std::pair{x,y};
    };
    supplied.actorCoordinates=[&]{
        event('U');
        FootCoordinateServices coordinates;
        coordinates.locomotor=[&]{return driveSecondaryCoordinates(
            v.unit.drive.movement.actor.position,v.unit.drive.movement.head);};
        coordinates.coordinates=[&]{return v.unit.drive.movement.actor.position;};
        const auto p=footSecondaryCoordinates(v.registry574,v.registry,coordinates);
        event('u',p.x,p.y,p.z);return p;
    };
    return finishOrdinaryAdvanceTerminal(v.unit,v.flags,divisor,residual,supplied);
}
}
