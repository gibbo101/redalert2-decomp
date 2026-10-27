// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
using TechnoAbilityTrace=std::function<void(char,const void*,std::uint32_t)>;
struct TechnoAbilityServices {
    std::function<const void*()> type80;
    // Pure live field view on the saved Type. Original offset arithmetic wraps;
    // the owner must refuse addresses outside its supported field backing.
    std::function<std::uint8_t(const void*,std::uint32_t)> typeByte;
    TechnoAbilityTrace trace;
};
// Complete6D7910 with complete7133A0/713420 promotion predicates. Preserve the
// repeated predicates, saved Type identity, byte truth and elite inheritance.
inline std::uint8_t technoHasAbility(const double& veterancy,int index,const TechnoAbilityServices& s){
    const auto event=[&](char k,const void* type=nullptr,std::uint32_t off=0){if(s.trace)s.trace(k,type,off);};
    const auto veteran=[&]{event('V');return veterancy>=1.&&veterancy<2.;};
    const auto elite=[&]{event('E');return veterancy>=2.;};
    if(!veteran()&&!elite())return 0;
    if(!s.type80)throw std::invalid_argument("Ability requires actual Type80");
    event('T');const auto type=s.type80();event('S',type);
    const auto read=[&](std::uint32_t base){
        if(!s.typeByte)throw std::invalid_argument("Ability requires actual Type byte");
        const auto off=base+std::uint32_t(index);event('B',type,off);return s.typeByte(type,off);
    };
    if(veteran()&&read(0x26c))return 1;
    if(elite()&&(read(0x26c)||read(0x27e)))return 1;
    return 0;
}
}
