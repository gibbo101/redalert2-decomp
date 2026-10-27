// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/AdvanceNearbyScatterWorld.hpp"
#include "assets/AdvanceTerminalWorld.hpp"
namespace ra2 {
// Complete ordinary Advance with the actual target/coordinate/clear/return tree.
// Mission effects remain named supplied services; Process/runtime remain separate.
template<class Admission,class Motion>
inline bool advanceWithTerminalScatter(int mover,int speed,double percentage,
    bool suppressSpeed,const GroundDriveAdvanceServices& services,
    const GroundDriveAdvanceAdmissionServices& admission,int heightDivisor,
    std::uint32_t& scratch,BasicCellUnitScatterView<Admission,Motion> world,const CellUnitScatterInputs& input,
    CellNearbySearchInputs nearby,AdvanceTerminalFlags flags,
    AdvanceTerminalServices effects,const GroundStateStore& actorStore={},
    const ScatterWorldTrace& trace={},const NearbyLocationMapTrace& nearbyTrace={},
    const AdvanceTerminalTrace& terminalTrace={}) {
    if(mover<0||std::size_t(mover)>=world.units.size()||!world.units[mover]||
       world.units[mover]->mover!=mover||!flags.onMap7d||flags.flag76||flags.flag7a)
        throw std::invalid_argument("Terminal Advance requires explicit mover binding");
    auto& actor=*world.units[mover];
    std::vector<MapCellInput*> targets;
    for(const auto& b:actor.bindings)targets.push_back(b.cell);
    AdvanceTerminalWorld terminal{actor.unit,flags,actor.extra.registry574,actor.registry,
        targets,actor.floor,actor.floorHeight};
    const auto continuation=[&](int residual){
        return finishAdvanceTerminalOnMap(terminal,heightDivisor,residual,effects,terminalTrace);
    };
    return advanceNearbyScatterWorld(mover,speed,percentage,suppressSpeed,services,admission,
        heightDivisor,scratch,world,input,nearby,actorStore,trace,nearbyTrace,continuation);
}
}
