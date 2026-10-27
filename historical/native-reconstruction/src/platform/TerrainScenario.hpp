// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Renderer.hpp"
namespace ra2 {
// Bounded host preparation/placement around recovered kernels. No SDL dependency
// here: native integration diagnostics exercise exactly the same application bind.
void prepareTerrainAssets(GameAssets&);
// Host bounds/scenery/domain guard. Terrain speed/passability is decided by
// actual Unit admission, not by a native speed whitelist at command entry.
bool terrainCommandCell(const GameAssets&,int x,int y);
std::optional<Position> terrainPick(const GameAssets&,const Renderer&,double x,double y);
Simulation terrainSimulation(const GameAssets&,Position,int heading=0);
// Bounded mover plus allied inspection-only parked Unit on one owned map.
Simulation residentTerrainSimulation(const GameAssets&);
}
