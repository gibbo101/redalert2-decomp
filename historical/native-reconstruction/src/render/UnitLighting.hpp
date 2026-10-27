// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/PlayerColor.hpp"
#include "render/Lighting.hpp"
namespace ra2 {
// Rules numeric-load block, distinct from the static light type's +0.1 bias.
int extraUnitLight(double value);
struct UnitLightCell { std::int16_t x=0,y=0; bool operator==(const UnitLightCell&) const = default; };
UnitLightCell unitLightCell(int x,int y);
// Cell +0x10A is a signed word, before terrain tint normalization. Preserve the
// unnamed cell flag/predicate branch without assigning it invented semantics.
int ordinaryUnitBrightness(std::int16_t ambient,int extra,std::uint32_t cellFlags=0,bool predicate=false);
int unitBrightnessEffect(int brightness,std::uint32_t actorFlags);
struct UnitLightConverter {
    std::vector<Palette16> shades;
    std::int32_t field17c=0; // Supplied startup;49EEA0 writes the fixed wrapper word.
};
// Ordinary ColorScheme initialization: neutral RGB, 53 rows, affected mask with
// entries 240..254 excluded. Local source tints are not converter inputs.
UnitLightConverter unitLightConverter(const RasterData&,const RenderData&,const Palette&,HsvColor);
const UnitLightConverter& houseUnitConverter(std::span<const UnitLightConverter>,std::size_t colorScheme);
}
