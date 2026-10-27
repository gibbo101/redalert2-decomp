// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionWaypointReveal.hpp"
#include "sim/ScenarioWaypoint.hpp"
#include "sim/RevealArea.hpp"
namespace ra2 {
struct MissionWaypointRevealHouseBinding {
    MissionWaypointRevealHouse* waypoint=nullptr;
    RevealAreaHouse* area=nullptr;
};
// Authored composition of the single recovered waypoint/map/reveal kernels.
// Bindings identify views of the same logical House; they do not query the map.
// Initial scenario/House/type associations and final visibility children remain
// supplied. No production mission scheduling is enabled by this dependency.
inline std::uint8_t revealMissionWaypointArea(std::int32_t waypoint,
        std::span<const std::uint8_t> scenario,const MissionWaypointRevealWorld& globals,
        const RevealAreaWorld& map,const RevealAreaTables& tables,const RevealAreaState& state,
        const RevealAreaServices& areaServices,std::span<const MissionWaypointRevealHouseBinding> houses){
    MissionWaypointRevealServices services;
    services.waypoint=[&](auto index){return scenarioWaypoint(scenario,index);};
    services.cell=[&](auto point){
        if(map.primaryCells.data()!=map.secondaryCells.data()||map.primaryCells.size()!=map.secondaryCells.size())
            throw std::invalid_argument("Fixed waypoint map requires one shared Cell table");
        auto& c=revealAreaMapCell(point,map);return MissionWaypointRevealCell{c.flags140,c.level11b};};
    services.reveal=[&](Coord point,int range,MissionWaypointRevealHouse* house,
            auto a,auto b,auto c,auto d,auto e){
        RevealAreaHouse* target=nullptr;
        if(house){
            const MissionWaypointRevealHouseBinding* binding=nullptr;
            for(const auto& candidate:houses)if(candidate.waypoint==house){
                if(binding)throw std::invalid_argument("Repeated waypoint House identity");binding=&candidate;}
            if(!binding||!binding->area)throw std::invalid_argument("Unbound waypoint House identity");
            target=binding->area;
        }
        revealArea(point,range,target,a,b,c,d,e,map,tables,state,areaServices);
    };
    return revealMissionWaypoint(waypoint,globals,services);
}
}
