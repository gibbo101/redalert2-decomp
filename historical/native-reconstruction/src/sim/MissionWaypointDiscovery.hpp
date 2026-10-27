// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionWaypointVisibility.hpp"
#include "sim/CellVisibilityDiscovery.hpp"
namespace ra2 {
// Borrowed identity registry and actual resident services, not a Cell snapshot.
// Notification and object DiscoveredBy remain supplied leaves at this join.
inline std::uint8_t revealMissionWaypointDiscovery(std::int32_t waypoint,
        std::span<const std::uint8_t> scenario,const MissionWaypointRevealWorld& globals,
        const RevealAreaWorld& map,const RevealAreaTables& tables,const RevealAreaState& state,
        const RevealAreaServices& areaServices,std::span<const MissionWaypointRevealHouseBinding> houses,
        std::span<const std::int8_t> results,std::uint32_t refreshRules,
        const CellVisibilityChangeServices& leafServices,
        std::span<CellVisibilityState* const> registry,
        const std::function<CellClosestResidentServices(int)>& residents,
        const std::function<void(TerrainCellPoint)>& notify,
        const std::function<void(int,int)>& discoveredBy){
    const auto identity=[&](int id)->CellVisibilityState&{
        if(map.fallback&&id==map.fallback->identity)return *map.fallback;
        if(id<0||std::size_t(id)>=registry.size()||!registry[std::size_t(id)]||registry[std::size_t(id)]->identity!=id)
            throw std::invalid_argument("Waypoint discovery foreign Cell identity");
        return *registry[std::size_t(id)];
    };
    auto discoveryMap=map;
    discoveryMap.query=[&](char,auto point,int id){if(map.query)map.query('Q',point,id);};
    discoveryMap.fallbackStore=[&](char,auto point){if(map.fallbackStore)map.fallbackStore('Q',point);};
    auto services=leafServices;
    services.discover=[&](int starting,int house,bool notification){
        CellVisibilityDiscoveryServices discovery;
        discovery.point=[&](int id){return identity(id).point;};
        discovery.level=[&](int id){return identity(id).level11b;};
        discovery.cellAt=[&](auto point){auto& cell=revealAreaMapCell(point,discoveryMap);
            if(&identity(cell.identity)!=&cell)throw std::invalid_argument("Waypoint discovery shadow Cell record");
            return cell.identity;};
        discovery.residents=residents;discovery.notifyCell=notify;discovery.discoveredBy=discoveredBy;
        discoverVisibleCellResidents(starting,house,notification,discovery);
    };
    return revealMissionWaypointVisibility(waypoint,scenario,globals,map,tables,state,areaServices,houses,
        results,refreshRules,services);
}
}
