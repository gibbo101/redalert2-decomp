// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/MapLighting.hpp"
#include "assets/Formats.hpp"
namespace ra2 {
struct LightTypeInputs {
    int radius=0,intensity=0;
    std::array<int,3> tint{};
};
LightTypeInputs lightTypeInputs(int radius,double intensity,std::array<double,3> tint);
// Original source constructor starts inactive and requires graphics detail 2.
LightSource makeStaticLight(const LightTypeInputs&,int x,int y,int z);
bool changeLightActive(LightSource&,bool active);
// Immediate (mode 0) update: original y-major traversal and table-sqrt inclusion.
// Supplied map membership is the asset/map boundary, not original map construction.
std::vector<std::size_t> affectedLightCells(const RenderData&,const LightSource&,
    std::span<const MapCell>,int detail=2,bool lightingEnabled=true);
struct TerrainConverterInputs {
    std::array<int,3> tint{};
    int shades=53;
};
// Successful ordinary factory inputs, with an existing neutral converter.
// Original allocation, reference counts and shared converter lifetime are separate.
TerrainConverterInputs terrainConverterInputs(std::array<int,3> tint,int detail=2);
}
