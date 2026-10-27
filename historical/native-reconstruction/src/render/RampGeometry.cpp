// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RampGeometry.hpp"
#include "render/Lighting.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>
namespace ra2 {
double tableTangent(const RampGeometryData& data,double radians) {
    if(!std::isfinite(radians)||std::abs(radians)>1e6||
       !std::isfinite(data.tangentScale)||data.tangentScale<=0||data.tangentScale>1000)
        throw std::invalid_argument("Tangent outside finite recovered domain");
    OriginalRounding rounding;
    const auto index=std::int32_t(radians*data.tangentScale);
    // Signed remainder plus a correction for negatives is the low twelve bits.
    return data.tangent[std::uint32_t(index)&4095];
}
double tableArctangent(const DirectionData& data,double slope) {
    if(!std::isfinite(slope)||std::abs(slope)>1e6||
       !std::isfinite(data.slopeStep)||data.slopeStep<.001f)
        throw std::invalid_argument("Arctangent outside finite recovered domain");
    OriginalRounding rounding;
    // The stored float decides the sign; the unrounded double is divided.
    const float sign=float(slope);
    const auto index=std::abs(std::int32_t(slope/double(data.slopeStep)));
    const double result=index<4097?data.atan[std::size_t(index)]:data.positiveHalfPi;
    return sign<0?-result:result;
}
StockRampGeometry stockRampGeometry(const RenderData& render,const RasterData& raster,
    const DirectionData& direction,const RampGeometryData& geometry) {
    OriginalRounding rounding;
    StockRampGeometry result;
    // Original CRT pow is entered with the fixed exact inputs 256 and 2.
    // Their exact product recovers this projection, not the general CRT function.
    result.diagonal=tableSqrt(render,2.0*(256.0*256.0));
    result.diagonalPer60=result.diagonal/60.0;
    result.inverseDiagonalPer60=1.0/result.diagonalPer60;
    result.angle45=raster.degrees*45.0;
    result.angle60=raster.degrees*60.0;
    result.angle90=raster.degrees*90.0;
    const double height=(tableTangent(geometry,result.angle90-result.angle60)*result.diagonal)*.5;
    if(!std::isfinite(height)||std::abs(height)>1e6)
        throw std::invalid_argument("Stock ramp geometry data outside recovered domain");
    result.levelHeight=std::int32_t(height);
    result.diagonalTilt=tableArctangent(direction,double(result.levelHeight)*(1.0/256.0));
    result.axisTilt=tableArctangent(direction,double(result.levelHeight*2)/result.diagonal);
    result.quadrupleHeight=std::int32_t(double(result.levelHeight*4)+.5);
    return result;
}
}
