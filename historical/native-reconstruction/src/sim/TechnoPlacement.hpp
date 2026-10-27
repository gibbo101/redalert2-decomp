// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <array>
namespace ra2 {
struct UnitPlacementState {
    Coord position{}; // Supplied post-base-placement coordinates.
    Facing body,barrel;
    std::uint8_t onMap=1,bridge32D=0,flag190=0,field373=0,height378=0;
    int field1F4=0,field3EC=0,field3F0=0,field400=0,field114=-1;
    std::array<int,2> field1A0{};
};
struct UnitPlacementInputs {
    Coord requested{};
    int direction=0,fireAngle=8,currentFrame=0,heightDivisor=104;
    bool typeEffect=false;
};
// Service names with offsets deliberately retain unknown semantics. Base Object
// placement, map/house construction and these service effects remain supplied.
struct UnitPlacementServices {
    std::function<std::uint8_t(TerrainCellPoint)> bridge;
    std::function<std::uint8_t(Coord,int)> objectUnlimbo;
    std::function<void()> reset418,typeQuery,registerEffect,ownerPlacement,unitKind,notify414,notify1D4;
    std::function<void(Coord,int)> mapUpdate;
    std::function<std::uint8_t()> predicate1E8;
    std::function<bool()> cell1A4;
    std::function<int()> value2A0;
    std::function<int(int)> kind38;
    std::function<void(int)> associateCell;
    std::function<std::array<int,2>(Coord)> locate;
    std::function<int()> ownerDefault;
};
// Complete Techno Unlimbo wrapper, scoped to Unit kind 1. Does not construct or
// own the actor, execute base placement/map/house effects or update turret facing.
using UnitPlacementStore=std::function<void(int,int,int)>;
bool placeOrdinaryUnit(UnitPlacementState&,const UnitPlacementInputs&,const UnitPlacementServices&,
                       const UnitPlacementStore& store={});
}
