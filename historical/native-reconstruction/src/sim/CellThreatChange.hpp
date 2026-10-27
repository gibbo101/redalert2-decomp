// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "HouseThreat.hpp"
namespace ra2 {
// Complete4F52F0 and4E5500. Nonzero mode returns the raw byte134.
inline std::uint8_t cellThreatControlled(const HouseThreatHouse& h,std::int32_t mode){
    return mode?h.flag134:std::uint8_t(bool(h.flag134||h.flag135));
}
inline bool cellThreatAlliedIndex(const HouseThreatHouse& h,std::int32_t index){
    if(index==h.index30)return true;
    if(index==-1)return false;
    return bool(h.allies5674&(std::uint32_t(1)<<(std::uint32_t(index)&31u)));
}
using CellThreatStore=std::function<void(const void*,std::int32_t,std::int32_t)>;
// Complete4E5DC0. Each arithmetic store precedes the optional zero clamp store.
// The observer is diagnostic only; it runs after each corresponding real store.
inline void changeHouseCellThreat(HouseThreatHouse h,std::int32_t index,std::int32_t delta,
    std::span<const std::int32_t,9> offsets,std::span<const std::int32_t,9> shifts,
    const CellThreatStore& stored={}){
    const bool subtract=delta<0;
    const auto magnitude=subtract?std::bit_cast<std::int32_t>(0u-std::uint32_t(delta)):delta;
    for(std::size_t i=0;i<9;++i){
        const auto slot=houseThreatAdd(index,offsets[i]);
        if(slot<0||std::size_t(slot)>=h.grid56D0.size())throw std::invalid_argument("Cell threat stencil outside owned grid");
        const auto part=magnitude>>(std::uint32_t(shifts[i])&31u); // C++20 arithmetic right shift.
        auto& value=h.grid56D0[std::size_t(slot)];
        value=houseThreatAdd(value,subtract?std::bit_cast<std::int32_t>(0u-std::uint32_t(part)):part);
        if(stored)stored(h.identity,slot,value);
        if(value<0){value=0;if(stored)stored(h.identity,slot,value);}
    }
}
struct CellThreatWorld {
    const std::int32_t& mode;
    const std::int32_t& count;
    const std::span<const void*>& houses;
    std::span<const std::int32_t,9> offsets,shifts;
    std::function<HouseThreatHouse(const void*)> house;
    CellThreatStore stored;
};
// Complete476B20 and its four complete children. Snapshot Cell24 before projection;
// walk forward, rereading count/backing after every admitted or skipped House.
inline void changeCellThreat(HouseThreatCell cell,std::int32_t ownerIndex,std::int32_t delta,const CellThreatWorld& w){
    const std::int16_t x=cell.x,y=cell.y;
    const auto index=projectHouseThreatCell({x,y});
    for(std::int32_t i=0;i<w.count;++i){
        if(std::size_t(i)>=w.houses.size())throw std::invalid_argument("Cell threat House registry outside owned backing");
        const auto p=w.houses[std::size_t(i)];if(!p)continue;
        if(!w.house)throw std::invalid_argument("Cell threat needs an owned House view");
        const auto h=w.house(p);if(h.identity!=p)throw std::invalid_argument("Cell threat House identity differs");
        if(h.index30==ownerIndex)continue;
        if(cellThreatControlled(h,w.mode)&&cellThreatAlliedIndex(h,ownerIndex))continue;
        changeHouseCellThreat(h,index,delta,w.offsets,w.shifts,w.stored);
    }
}
}
