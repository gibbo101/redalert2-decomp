// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <bit>
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct TechnoThreatServices {
    std::function<const void*()> type80;
    std::function<std::int32_t()> kind2C;
    // Pure borrowed type field lookup; no query, synchronization or copying.
    std::function<const std::int32_t&(const void*)> value598;
};
// Complete4532F0. The field's startup and gameplay writer are separate work.
inline std::int32_t buildingThreatValue564(const std::int32_t& value){return value;}
// Complete6D3E50. Save type before kind, keep both Building getter calls and
// sample BE8 before the second getter. Neither multiplication nor return clamps.
inline std::int32_t technoThreat(const std::int32_t& field564,const std::int32_t& rulesBE8,const TechnoThreatServices& s){
    if(!s.type80)throw std::invalid_argument("Techno threat needs type80");
    const auto type=s.type80();if(!type)return 0;
    if(!s.kind2C)throw std::invalid_argument("Techno threat needs kind2C");
    if(s.kind2C()==6&&buildingThreatValue564(field564)>0){
        const auto multiplier=rulesBE8;
        return std::bit_cast<std::int32_t>(std::uint32_t(buildingThreatValue564(field564))*std::uint32_t(multiplier));
    }
    if(!s.value598)throw std::invalid_argument("Techno threat needs saved type field598");
    return s.value598(type);
}
}
