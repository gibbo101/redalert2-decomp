// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Shp.hpp"
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
class GameAssets;
struct TerrainLifeServices;
// Native immutable map preparation; supplies ground/projection and map-load
// policy to the recovered SDL-free ordinary lifecycle. No global scheduler.
void prepareStaticScenery(GameAssets&);
TerrainLifeServices staticSceneryServices(const GameAssets&);
struct TerrainDrawInputs {int frame=0,flags=0,zAdjust=0,gradient=0,brightness=0;};
struct SpriteDepthInput {
    const ShpImage* image=nullptr;
    std::int32_t frame=0;
    PixelPoint offset{}; // Original wrapper offsets, before canvas/crop adjustment.
};
// Healthy, nonanimated, ordinary terrain converter profile only.
std::array<TerrainDrawInputs,2> staticTerrainDrawInputs(int frames,int heightInPixels,std::int16_t cellTerrainLight);
// Ordinary valid raw/RLE SHP body/shadow profile: terrain4E00/4E01 and
// Building6E00/6E01, body gradients0/2, shadow0. Converter lifetime remains external.
BlitStats blitOrdinarySpriteFrame(const ShpImage&,const TerrainDrawInputs&,PixelPoint location,PixelRect clip,
                       const std::vector<Palette16>& palettes,int width,int height,
                       std::vector<std::uint16_t>& colors,std::vector<std::uint16_t>& depth,
                       const std::vector<std::uint16_t>& alpha,SpriteDepthInput auxiliary={});
// Borrowed converter state; observer is diagnostics only and runs after the
// actual store, before pixel dispatch. No converter/cache is allocated here.
struct SpriteConverterFields {
    std::int32_t& field17c;
    const std::vector<Palette16>& palettes;
    std::function<void()> stored;
};
//49EEA0 null-image return and ordinary fixed-zero word store, then the verified ordinary
// valid-image pixel profile. Other wrapper/converter effects remain separate.
BlitStats blitConvertedSpriteFrame(SpriteConverterFields,const ShpImage*,const TerrainDrawInputs&,
    PixelPoint,PixelRect,int width,int height,std::vector<std::uint16_t>& colors,
    std::vector<std::uint16_t>& depth,const std::vector<std::uint16_t>& alpha,SpriteDepthInput auxiliary={});
BlitStats blitTerrainFrame(const ShpImage&,const TerrainDrawInputs&,PixelPoint location,PixelRect clip,
                       const std::vector<Palette16>& palettes,int width,int height,
                       std::vector<std::uint16_t>& colors,std::vector<std::uint16_t>& depth,
                       const std::vector<std::uint16_t>& alpha);
}
