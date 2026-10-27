// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitLighting.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
int extraUnitLight(double value) {
    if(!std::isfinite(value)||std::abs(value)>10)throw std::invalid_argument("ExtraUnitLight outside bounded profile");
    OriginalRounding rounding;return int(value*1000.0);
}
UnitLightCell unitLightCell(int x,int y) {
    if(std::abs(std::int64_t(x))>1048576||std::abs(std::int64_t(y))>1048576)throw std::invalid_argument("Unit light coordinate outside bounded profile");
    return {std::int16_t(x/256),std::int16_t(y/256)};
}
int ordinaryUnitBrightness(std::int16_t ambient,int extra,std::uint32_t flags,bool predicate) {
    const int adjustment=(flags&0x10000)&&!predicate?-500:0;
    return std::bit_cast<std::int32_t>(std::uint32_t(int(ambient)+adjustment)+std::uint32_t(extra));
}
int unitBrightnessEffect(int brightness,std::uint32_t flags) {
    return flags&2?(brightness<=1500?2000:500):brightness;
}
UnitLightConverter unitLightConverter(const RasterData& raster,const RenderData& render,const Palette& base,HsvColor color) {
    std::array<std::uint8_t,256> affected;affected.fill(1);
    for(int i=240;i<255;++i)affected[i]=0;
    return {lightPalette(render,playerPalette(raster,base,color),{1000,1000,1000},53,affected)};
}
const UnitLightConverter& houseUnitConverter(std::span<const UnitLightConverter> converters,std::size_t scheme) {
    if(scheme>=converters.size())throw std::invalid_argument("House ColorScheme outside supplied registry");
    return converters[scheme];
}
}
