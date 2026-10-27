// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/RampPoseData.hpp"
#include "assets/PreparedData.hpp"
namespace ra2 {
RampPoseData readRampPoseData(const Data& data,std::string_view expectedSource){
    validatePreparedData(data,16456,"","7b104361249101badc8e5d893ff1b4982377510642779baf417fe96c5073eb69",expectedSource);
    RampPoseData result;
    for(std::size_t i=0;i<result.inverseSine.size();++i)result.inverseSine[i]=data.f32(40+i*4);
    result.inverseScale=data.f32(16428);
    auto number=[&](std::size_t p){return std::bit_cast<double>(std::uint64_t(data.u32(p))|(std::uint64_t(data.u32(p+4))<<32));};
    result.halfPi=number(16432);result.oppositeHalfPi=number(16440);result.epsilon=number(16448);return result;
}
}
