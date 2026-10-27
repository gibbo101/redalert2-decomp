// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoTypeCost.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <bit>
#include <stdexcept>
namespace ra2 {
float houseTechnoCostMultiplier(const void* type,const void* house,const TechnoTypeCostServices& s){
    if(!type||!house||!s.kind2C)throw std::invalid_argument("Cost multiplier requires Type/House/kind");
    const auto kind=s.kind2C(type);
    std::int64_t offset=0;
    switch(kind){
    case 3:offset=0x11c;break;
    case 7:
        if(!s.speedTypeBA0)throw std::invalid_argument("Kind7 cost requires speed type");
        offset=s.speedTypeBA0(type)==5?0x124:0x120;break;
    case 16:offset=0x114;break;
    case 40:offset=0x118;break;
    default:return 1.f;
    }
    if(!s.countryFactor)throw std::invalid_argument("Cost requires live country factor");
    return s.countryFactor(house,offset);
}
std::uint32_t technoTypeCost(const void* type,const void* house,const TechnoTypeCostServices& s){
    if(!type||!s.baseCostAC)throw std::invalid_argument("Techno cost requires Type/base cost");
    if(!house)return std::uint32_t(s.baseCostAC(type));
    OriginalRounding rounding;
    // Force the original stack float32 store before the late virtualAC read.
    volatile float factor=houseTechnoCostMultiplier(type,house,s);
    if(s.trace)s.trace('f',std::bit_cast<std::uint32_t>(float(factor)));
    const auto base=s.baseCostAC(type);
    volatile double product=double(base)*double(factor);
    const double value=product;
    if(s.trace)s.trace('c',0);
    // FISTP writes signed64 integer-indefinite on NaN/overflow. The caller uses
    // EAX, so those cases yield0, not INT_MIN or a saturated signed32 value.
    if(!std::isfinite(value)||value<-0x1p63||value>=0x1p63)return 0;
    return std::uint32_t(std::int64_t(value));
}
}
