// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/Targeting.hpp"
#include "sim/Drive.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>

namespace ra2 {
std::uint16_t destinationDirection(const DirectionData& data,Coord from,Coord target) {
    const auto dx=std::int64_t(target.x)-from.x;
    const auto up=std::int64_t(from.y)-target.y;
    if(std::abs(dx)>(1<<20)||std::abs(up)>(1<<20)||!(data.slopeStep>0))
        throw std::invalid_argument("Bearing outside recovered coordinate/data bounds");
    OriginalRounding rounding;
    // The original stores both input deltas as float32 before division.
    const float x=float(dx),y=float(up);
    double angle;
    if(x==0) {
        angle=y==0?0.0:(y>0?double(data.positiveHalfPi):double(data.negativeHalfPi));
    } else {
        // Original FTOL, absolute index, and saturating table branch. This is a
        // quantized lookup, not atan2 or an evenly quantized angular formula.
        const int index=std::abs(int((double(y)/x)/data.slopeStep));
        angle=index<4097?double(data.atan[std::size_t(index)]):double(data.positiveHalfPi);
        if(x<0) angle=data.pi-angle;
        if(y<0) angle=-angle;
    }
    return std::uint16_t(int((angle-data.halfPi)*data.angleScale));
}
}
