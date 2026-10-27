// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionWaypointRevealArea.hpp"
#include "sim/CellVisibilityChange.hpp"
#include "sim/CellVisibilityMask.hpp"
namespace ra2 {
// One borrowed map/fallback through waypoint, area, counter changes and masks.
// Startup associations, refresh-rule input and redraw/discovery/refresh leaves
// remain supplied; caller callbacks must retain their independently proven scope.
inline std::uint8_t revealMissionWaypointVisibility(std::int32_t waypoint,
        std::span<const std::uint8_t> scenario,const MissionWaypointRevealWorld& globals,
        const RevealAreaWorld& map,const RevealAreaTables& tables,const RevealAreaState& state,
        const RevealAreaServices& areaServices,std::span<const MissionWaypointRevealHouseBinding> houses,
        std::span<const std::int8_t> results,std::uint32_t refreshRules,
        const CellVisibilityChangeServices& leafServices){
    CellVisibilityChangeWorld changeWorld{map.primaryCells,map.fallback};
    changeWorld.fallbackStore=[&](auto point){if(map.fallbackStore)map.fallbackStore('V',point);};
    changeWorld.query=[&](auto point,int id){if(map.query)map.query('V',point,id);};
    CellVisibilityMaskWorld maskWorld{map.primaryCells,map.fallback};
    maskWorld.fallbackStore=[&](auto point){if(map.fallbackStore)map.fallbackStore('M',point);};
    maskWorld.query=[&](auto point,int id){if(map.query)map.query('M',point,id);};
    auto changeServices=leafServices;
    changeServices.visibilityValue=[&](auto point,bool mode){return std::uint8_t(cellVisibilityMask(point,mode,results,maskWorld));};
    auto services=areaServices;
    services.revealCell=[&](auto point,const RevealAreaHouse& house,std::uint32_t child){
        (void)changeCellVisibility(point,house.identity,child,changeWorld,refreshRules,changeServices);
    };
    return revealMissionWaypointArea(waypoint,scenario,globals,map,tables,state,services,houses);
}
}
