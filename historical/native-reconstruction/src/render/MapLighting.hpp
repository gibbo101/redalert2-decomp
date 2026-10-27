// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Lighting.hpp"
namespace ra2 {
inline constexpr std::uint16_t VisibleAlpha=127; // complete original alpha-buffer constructor
// Scenario integers after the original INI conversion. No host float formula
// participates after this boundary. Ordinary lighting only, no time-of-day state.
struct MapLightSettings {
    int ambient=100;
    std::array<int,3> tint{100,100,100};
    int ground=0,level=0;
};
MapLightSettings mapLightSettings(double ambient,std::array<double,3> tint,double ground,double level);
struct LightSource {
    int x=0,y=0,z=0,radius=1;
    int intensity=0;
    std::array<int,3> tint{};
    bool active=true;
    int minimumDetail=0; // graphics-detail threshold, not a frame/time delay
};
struct CellLight {
    int scale=65536,sourceIntensity=0,ambient=1000,terrain=1000,bridge=1000;
    std::array<int,3> tint{1000,1000,1000};
};
// Complete ordinary cell input calculation, including supplied ordered sources.
// Source creation/lifetime and actor/house converter association are separate.
CellLight cellLight(const RenderData&,const MapLightSettings&,int x,int y,int elevation,
                   std::span<const LightSource> sources={},int detail=0);
// Original LightConvert normalization has distinct red and green/blue divisions.
void normalizeLight(int& scale,int& brightness,std::array<int,3>& tint);
}
