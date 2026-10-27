// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include "sim/ObjectLayers.hpp"
namespace ra2 {
struct TerrainLifeState {
    std::uint8_t active=1,typeLogic=1,veinhole=0;
    std::int32_t resourceCountA=0,resourceCountB=0,screenX=0,screenY=0;
};
struct TerrainLifeServices {
    std::function<std::int32_t(Coord)> groundHeight;
    std::function<bool(TerrainCellPoint)> placementAllowed;
    std::function<std::array<std::int32_t,2>(Coord)> projectWorld;
    std::array<std::int32_t,2> screenOrigin{};
};
Coord terrainPlacementPosition(Coord,const std::function<std::int32_t(Coord)>&,
                               const ObjectLayerTrace& trace={});
// Healthy ordinary ground Terrain, empty resource handles, no selection,
// AlphaImage or radial indicator. Global cleanup/logic/redraw effects are supplied.
class TerrainLifecycle {
    void emitMark(int,int,const ObjectLayerTrace&);
public:
    TerrainOccupationWorld occupation;
    ObjectLayers objects;
    std::map<int,TerrainLifeState> actors;
    std::uint8_t enabled=1;
    std::int32_t loading=0;
    bool unlimbo(int,Coord,const TerrainLifeServices&,const ObjectLayerTrace& trace={});
    bool limbo(int,const TerrainLifeServices&,const ObjectLayerTrace& trace={});
};
}
