// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/CellNearbyScatterWorld.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "sim/Facing.hpp"
#include <limits>

namespace ra2 {
// Only Advance's result-6 dispatch block. The enclosing admission, placement,
// index continuation and Process are not implemented by this entry. The caller
// supplies the retained stack word and the separately initialized height divisor.
template<class Admission,class Motion>
inline void scatterAdvanceCellOnMap(const Coord& candidate,const Coord& actorLocation,
    const Coord& head,int heightDivisor,std::uint32_t& retainedScratch,
    BasicCellUnitScatterView<Admission,Motion> v,const CellUnitScatterInputs& input,
    CellNearbySearchInputs nearby,const ScatterWorldTrace& trace={},
    const NearbyLocationMapTrace& nearbyTrace={}) {
    if(v.units.empty()||!v.units[0]||heightDivisor<=0||
       v.units[0]->slots.size()>std::size_t(std::numeric_limits<int>::max()))
        throw std::invalid_argument("Advance Scatter requires a map owner and positive height divisor");
    const auto& first=*v.units[0];
    const auto event=[&](char k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0){
        if(trace)trace('g',k,a,b,c);
    };
    MapFloorHeightWorld map{first.slots,&first.fallback,[&](MapInputPosition p){
        if constexpr(requires {v.admission.gates.forwardAssignedFallback;}){
            if(!v.admission.gates.forwardAssignedFallback)
                throw std::invalid_argument("Advance Scatter requires prepared fallback associations");
            v.admission.gates.forwardAssignedFallback({p.x,p.y});
        }
        if(trace)trace('w','W',std::uint32_t(std::uint16_t(p.x))|
            (std::uint32_t(std::uint16_t(p.y))<<16),0,0);
    }};
    const auto query=[&](const Coord& point)->MapCellInput&{
        if(trace)trace('w','K',point.x,point.y,point.z);
        return mapCoordinateCell(point,map,int(first.slots.size()));
    };
    const auto low=[&](std::uint8_t value){
        retainedScratch=(retainedScratch&0xffffff00u)|value;event('E',retainedScratch);
    };
    if(query(candidate).flags&0x100u){
        // Save all three source words before the independent second Cell query.
        // Only saved Z participates in the signed divide/level difference.
        const auto saved=actorLocation;event('P',saved.x,saved.y,saved.z);
        const int level=query(candidate).level;
        low(1);
        const int difference=signed32(std::uint32_t(saved.z/heightDivisor)-std::uint32_t(level));
        const int magnitude=difference<0?signed32(0u-std::uint32_t(difference)):difference;
        if(magnitude<=2)low(0);
    }else low(0);
    // Final lookup uses the actual late Drive head, never the queued candidate.
    auto& destination=query(head);int cell=-1;
    for(const auto& binding:first.bindings)if(binding.cell==&destination){cell=binding.id;break;}
    if(cell<0)throw std::invalid_argument("Advance Scatter Cell lacks its actual shared binding");
    event('S',cell,retainedScratch);
    scatterCellUnitsWithNearbyOnMap(cell,{},1,1,std::uint8_t(retainedScratch),
        v,input,nearby,trace,nearbyTrace);
}
}
