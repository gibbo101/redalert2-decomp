// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/RampGeometryData.hpp"
#include "assets/PreparedData.hpp"
namespace ra2 {
RampGeometryData readRampGeometryData(const Data& data,std::string_view expectedSource) {
    validatePreparedData(data,16432,"",
        "2168b23a8a6b2e86a2c1fa6d2447aceef39c8f5c2d8fdf42537ae4dbd76b2b6b",expectedSource);
    RampGeometryData result;
    for(std::size_t i=0;i<result.tangent.size();++i)result.tangent[i]=data.f32(40+i*4);
    result.tangentScale=std::bit_cast<double>(std::uint64_t(data.u32(16424))|
        (std::uint64_t(data.u32(16428))<<32));
    return result;
}
}
