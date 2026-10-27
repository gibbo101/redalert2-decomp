// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <array>
namespace ra2 {
struct UnitFoundationState {
    std::uint8_t objectFlag=0,unitFlag=0;
    TerrainCellPoint fallback{32767,32767};
    std::array<TerrainCellPoint,2> unit{{{0,0},{32767,32767}}};
};
struct UnitMembershipActor {
    Coord position;
    int next=-1;
    std::uint8_t alternate=0,eligible=1,typeMapFlag=1;
    int kind=1;
};
struct UnitMembershipCell {TerrainCellPoint point;int head=-1,alternateHead=-1;};
// Logical selected stores: actor ids, Cell ids +100, foundation globals 200.
// Global offsets 0/4/8/12/16 denote Object flag/fallback/Unit flag/origin/end.
using UnitMembershipStore=std::function<void(int,int,std::uint32_t)>;
using UnitMembershipTrace=std::function<void(char,int,int)>;
struct UnitMembershipServices {
    std::function<int(int)> centerFloor;
    std::function<int(const Coord&)> visible,visibleSecondary;
    std::function<void(int,int)> notify;
    std::function<void(int,const Coord&,bool)> occupation;
    std::function<void(int,int)> recalculate;
    int visibilityGate=0,notificationArgument=0;
    // Optional live global associations. The gate is queried only after a
    // successful visibility predicate; the argument only when notifying.
    std::function<int()> liveVisibilityGate,liveNotificationArgument;
};
// Unit kind 1, nonnull UnitType, nonnull Drive (layer 2), stock single-Cell
// foundation. Construction and the visibility/notification/recalculation services
// remain supplied. Callers bind occupation and floor to the recovered children.
// Map table access is bounded BEFORE the original's speculative slot read; this
// explicit native safety domain excludes original out-of-table inputs.
class UnitMembershipWorld {
public:
    UnitFoundationState foundation;
    std::map<int,UnitMembershipActor> actors;
    std::map<int,UnitMembershipCell> cells;
    std::map<int,int> slots;
    int fallbackCell=-1;
    UnitMembershipServices services;
    UnitMembershipStore store;
    UnitMembershipTrace trace;
    void cellInsert(int actor,int cell);
    void cellRemove(int actor,int cell);
    void mapInsert(int actor,TerrainCellPoint);
    void mapRemove(int actor,TerrainCellPoint);
};
}
