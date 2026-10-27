// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/RampGeometryData.hpp"
#include "assets/RasterData.hpp"
#include "assets/RenderData.hpp"
#include "sim/Targeting.hpp"
namespace ra2 {
// Bounded original table leaves; no host trigonometry. Restore caller FP mode.
double tableTangent(const RampGeometryData&,double radians);
double tableArctangent(const DirectionData&,double slope);
struct StockRampGeometry {
    double diagonal=0,diagonalPer60=0,inverseDiagonalPer60=0;
    double angle45=0,angle60=0,angle90=0;
    std::int32_t levelHeight=0;
    double diagonalTilt=0,axisTilt=0;
    std::int32_t quadrupleHeight=0;
};
// Final values from ten stock numeric initializers. This is not general CRT pow,
// startup ordering or actor placement; Cell and shadow globals are distinct.
StockRampGeometry stockRampGeometry(const RenderData&,const RasterData&,
    const DirectionData&,const RampGeometryData&);
}
