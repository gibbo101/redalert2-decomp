// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <functional>
#include <stdexcept>
namespace ra2 {
struct MissionWaypointRevealHouse {std::uint8_t disabled188=0;};
struct MissionWaypointRevealRules {std::int32_t range54c=0;};
struct MissionWaypointRevealCell {const std::uint32_t& flags140;const std::int8_t& level11b;};
struct MissionWaypointRevealWorld {
    MissionWaypointRevealHouse* const& currentHouse;
    MissionWaypointRevealRules* const& rules;
    const std::int32_t& heightScale;
};
struct MissionWaypointRevealServices {
    std::function<TerrainCellPoint(std::int32_t)> waypoint;
    std::function<MissionWaypointRevealCell(TerrainCellPoint)> cell;
    std::function<void(Coord,std::int32_t,MissionWaypointRevealHouse*,std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t)> reveal;
};
// Complete base6B0670 around supplied waypoint663180, map548070 and reveal54A110.
// The four dispatcher arguments are unused. Borrow live globals; first reveal
// may replace their owners before the second call. No visibility effect claimed.
inline std::uint8_t revealMissionWaypoint(std::int32_t waypoint,
        const MissionWaypointRevealWorld& w,const MissionWaypointRevealServices& s){
    if(!w.currentHouse)throw std::invalid_argument("Waypoint reveal requires current House");
    if(w.currentHouse->disabled188)return 1;
    if(!s.waypoint||!s.cell||!s.reveal)throw std::invalid_argument("Waypoint reveal services required");
    const auto p=s.waypoint(waypoint);
    int bridge=0;
    if(s.cell(p).flags140&0x100u)bridge=4;
    else if(s.cell(p).flags140&0x400u)bridge=4;
    const auto height=std::int32_t(s.cell(p).level11b)+bridge;
    const auto half=height/2; // Original signed truncation toward zero, not floor.
    const auto x=signed16(std::uint16_t(std::uint16_t(p.x)-std::uint16_t(half)));
    const auto y=signed16(std::uint16_t(std::uint16_t(p.y)-std::uint16_t(half)));
    const auto point=[&]{return Coord{std::int32_t(x)*256+128,std::int32_t(y)*256+128,
        signed32(std::uint32_t(w.heightScale)*std::uint32_t(height))};};
    auto position=point();auto* rules=w.rules;auto* house=w.currentHouse;
    if(!rules)throw std::invalid_argument("Waypoint reveal requires rules");
    s.reveal(position,rules->range54c,house,0,0,0,1,0);
    position=point();rules=w.rules;house=w.currentHouse;
    if(!rules)throw std::invalid_argument("Waypoint reveal requires late rules");
    s.reveal(position,rules->range54c,house,0,0,0,1,1);
    return 1;
}
}
