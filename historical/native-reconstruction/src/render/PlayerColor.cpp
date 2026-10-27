// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/PlayerColor.hpp"
#include "render/VoxelRaster.hpp"
#include "sim/OriginalMath.hpp"
namespace ra2 {
Color originalHsvToRgb(HsvColor hsv) {
    const int sector=6*int(hsv.hue)/255,fraction=6*int(hsv.hue)%255;
    const int v=hsv.value,s=hsv.saturation;
    const auto p=std::uint8_t(v*(255-s)/255);
    const auto q=std::uint8_t(v*(255-fraction*s/255)/255);
    const auto t=std::uint8_t(v*(255-(255-fraction)*s/255)/255);
    switch(sector) {
        case 0:case 6:return {hsv.value,t,p};
        case 1:return {q,hsv.value,p};
        case 2:return {p,hsv.value,t};
        case 3:return {p,q,hsv.value};
        case 4:return {t,p,hsv.value};
        default:return {hsv.value,p,q};
    }
}
Palette playerPalette(const RasterData& data,const Palette& source,HsvColor color) {
    OriginalRounding rounding;auto result=source;
    // Stored binary64 coefficients from the pinned base ColorScheme builder.
    // The first value angle has its own original pi/16 override.
    for(int i=0;i<16;++i) {
        const double saturationAngle=i*0.046542113386515455+0.8726646259971648;
        const double valueAngle=i?i*0.08144869842640204+0.3490658503988659:0.19634954084936207;
        const auto s=std::uint8_t(int(double(tableSine(data,saturationAngle))*color.saturation));
        const auto v=std::uint8_t(int(double(tableCosine(data,valueAngle))*color.value));
        result[16+i]=originalHsvToRgb({color.hue,s,v});
    }
    return result;
}
}
