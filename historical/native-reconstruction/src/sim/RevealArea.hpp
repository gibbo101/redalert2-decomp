// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellVisibilityState.hpp"
#include "sim/HouseIndexAlliance.hpp"
#include <cstdint>
#include <functional>
#include <span>

namespace ra2 {
using RevealAreaCell=CellVisibilityState;
using RevealAreaHouse=HouseIndexAlliance;
struct RevealAreaWorld {
    int mapOriginF0=0,mapExtentF4=0;
    std::span<RevealAreaCell* const> primaryCells,secondaryCells;
    RevealAreaCell* fallback=nullptr;
    std::function<void(char,TerrainCellPoint,int)> query;
    std::function<void(char,TerrainCellPoint)> fallbackStore;
};
struct RevealAreaTables {
    std::span<const std::int32_t> counts;
    std::span<const TerrainCellPoint> offsets,heightOffsets;
};
struct RevealAreaState {
    std::int32_t heightDivisor=0;
    double heightProjectionScale=0.;
    std::uint8_t rules1432=0,rules142b=0;
    RevealAreaHouse* currentHouse=nullptr;
};
struct RevealAreaServices {
    std::function<bool(const RevealAreaHouse&,const RevealAreaHouse&)> housePredicate;
    std::function<double(double)> squareRoot;
    std::function<void(TerrainCellPoint,const RevealAreaHouse&)> fogCell;
    std::function<void(TerrainCellPoint,const RevealAreaHouse&,std::uint32_t)> revealCell;
    std::function<void(char,std::int32_t,std::int32_t,std::int32_t)> trace;
};

// Complete6A2970 height projection with explicit borrowed scale.
std::int32_t projectVisibilityHeight(std::int32_t z,double scale);

// Complete548070 pointer lookup over the same primary table/fallback used by
// reveal-area. 'P' telemetry identifies this caller's separate map query.
RevealAreaCell& revealAreaMapCell(TerrainCellPoint,const RevealAreaWorld&);

// Complete base54A110 parent around supplied House predicate and visibility
// children. Startup CellSpread arrays/scale and all owners are explicit inputs.
void revealArea(Coord,std::int32_t range,RevealAreaHouse*,std::uint32_t trimMode4,
    std::uint32_t unused5,std::uint32_t fogMode6,std::uint32_t heightCheck7,
    std::uint32_t childArgument8,const RevealAreaWorld&,const RevealAreaTables&,
    const RevealAreaState&,const RevealAreaServices&);
}
