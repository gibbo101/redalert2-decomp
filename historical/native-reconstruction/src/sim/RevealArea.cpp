// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/RevealArea.hpp"
#include "sim/Facing.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
std::int16_t word(std::uint32_t n){return std::bit_cast<std::int16_t>(std::uint16_t(n));}
std::uint32_t packed(TerrainCellPoint p){return std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16);}
std::int32_t integer(double value){
    constexpr double limit=9223372036854775808.0;
    if(!std::isfinite(value)||value<-limit||value>=limit)return 0;
    return signed32(std::uint32_t(std::uint64_t(std::int64_t(value))));
}
std::int32_t add(std::int32_t a,std::int32_t b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
RevealAreaCell& lookup(TerrainCellPoint p,std::span<RevealAreaCell* const> cells,
        RevealAreaCell& fallback,char kind,const RevealAreaWorld& world){
    if(cells.size()!=262144)throw std::invalid_argument("Reveal area requires complete Cell tables");
    const auto index=signed32(std::uint32_t(std::int32_t(p.y))*512u+std::uint32_t(std::int32_t(p.x)));
    RevealAreaCell* result=nullptr;
    if(index>=0&&index<262144)result=cells[std::size_t(index)];
    if(!result){fallback.point=p;if(world.fallbackStore)world.fallbackStore(kind,p);result=&fallback;}
    if(world.query)world.query(kind,p,result->identity);
    return *result;
}
}
std::int32_t projectVisibilityHeight(std::int32_t z,double scale){
    OriginalRounding rounding;
    volatile double a=double(z)*scale;
    volatile double b=a+double(z>=728);
    volatile double c=b+.5;
    return integer(c);
}
RevealAreaCell& revealAreaMapCell(TerrainCellPoint point,const RevealAreaWorld& world){
    if(!world.fallback)throw std::invalid_argument("Waypoint map requires fallback");
    return lookup(point,world.primaryCells,*world.fallback,'P',world);
}
void revealArea(Coord coordinates,std::int32_t range,RevealAreaHouse* house,
        std::uint32_t trimMode4,std::uint32_t,std::uint32_t fogMode6,
        std::uint32_t heightCheck7,std::uint32_t childArgument8,
        const RevealAreaWorld& world,const RevealAreaTables& tables,
        const RevealAreaState& state,const RevealAreaServices& services){
    if(!world.fallback||state.heightDivisor==0||
       (coordinates.z==std::numeric_limits<std::int32_t>::min()&&state.heightDivisor==-1))
        throw std::invalid_argument("Reveal area requires fallback and valid height divisor");
    if(tables.counts.size()<11)throw std::invalid_argument("Reveal area requires radius counts");
    OriginalRounding rounding;
    const auto event=[&](char k,int a=0,int b=0,int c=0){if(services.trace)services.trace(k,a,b,c);};
    const auto height=[&]{const auto v=projectVisibilityHeight(coordinates.z,state.heightProjectionScale);event('H',v);return v;};
    const auto heightQuotient=coordinates.z/state.heightDivisor;
    const auto shift1=signed32(0u-std::uint32_t(height()/30));
    const auto adjustedX=add(coordinates.x,signed32(std::uint32_t(shift1)*256u));
    const auto shift2=signed32(0u-std::uint32_t(height()/30));
    const auto adjustedY=add(coordinates.y,signed32(std::uint32_t(shift2)*256u));
    const TerrainCellPoint center{word(adjustedX/256),word(adjustedY/256)};
    const TerrainCellPoint raw{word(coordinates.x/256),word(coordinates.y/256)};
    const auto packedDifference=std::uint32_t(packed(center)-packed(raw));
    const TerrainCellPoint heightDifference{word(std::uint32_t(std::uint16_t(packedDifference))-2u),
        word(std::uint32_t(std::uint16_t(packedDifference>>16))-2u)};
    const auto sum=add(center.x,center.y),differenceXY=add(center.x,-std::int32_t(center.y)),differenceYX=add(center.y,-std::int32_t(center.x));
    if(sum<=world.mapOriginF0||differenceXY>=world.mapOriginF0||differenceYX>=world.mapOriginF0||
       sum>add(world.mapOriginF0,signed32(std::uint32_t(world.mapExtentF4)*2u))||range==0)return;
    if(range>=11)range=10;
    if(range<0)throw std::invalid_argument("Reveal area negative radius outside bounded profile");
    if(!state.currentHouse)return;
    auto* resolved=house;
    if(resolved&&resolved!=state.currentHouse){
        const auto bit=std::uint32_t(1u)<<unsigned(state.currentHouse->countryIndex&31);
        if(resolved->allianceMask&bit)resolved=state.currentHouse;
        else {
            if(!services.housePredicate)throw std::invalid_argument("Reveal area House predicate required");
            const bool accepted=services.housePredicate(*resolved,*state.currentHouse);event('A',resolved->identity,accepted);
            if(accepted&&state.rules142b)resolved=state.currentHouse;
        }
    }
    if(resolved!=state.currentHouse)return;
    std::int32_t skip=0,count=tables.counts[std::size_t(range)];
    if(!state.rules1432&&trimMode4&&range>2){skip=tables.counts[std::size_t(range-3)];count=signed32(std::uint32_t(count)-std::uint32_t(skip));}
    if(count<0||skip<0||std::size_t(skip)+std::size_t(count)>tables.offsets.size()||std::size_t(skip)+std::size_t(count)>tables.heightOffsets.size())
        throw std::invalid_argument("Reveal area supplied spread table outside bounded profile");
    for(int i=0;i<count;++i){
        const auto offset=tables.offsets[std::size_t(skip+i)];
        const TerrainCellPoint candidate{word(std::uint32_t(std::uint16_t(center.x))+std::uint32_t(std::uint16_t(offset.x))),
            word(std::uint32_t(std::uint16_t(center.y))+std::uint32_t(std::uint16_t(offset.y)))};
        const auto candidateSum=add(candidate.x,candidate.y);
        if(candidateSum<=world.mapOriginF0||add(candidate.x,-std::int32_t(candidate.y))>=world.mapOriginF0||
           add(candidate.y,-std::int32_t(candidate.x))>=world.mapOriginF0||
           candidateSum>add(world.mapOriginF0,signed32(std::uint32_t(world.mapExtentF4)*2u)))continue;
        auto dx=add(candidate.x,-std::int32_t(center.x));if(dx<0)dx=signed32(0u-std::uint32_t(dx));if(dx>range)continue;
        const auto sx=word(std::uint32_t(std::uint16_t(candidate.x))-std::uint32_t(std::uint16_t(center.x)));
        const auto sy=word(std::uint32_t(std::uint16_t(candidate.y))-std::uint32_t(std::uint16_t(center.y)));
        if(!services.squareRoot)throw std::invalid_argument("Reveal area square-root service required");
        const double squared=double(sx)*double(sx)+double(sy)*double(sy);
        const auto distance=word(std::uint32_t(integer(services.squareRoot(squared))));event('D',distance);
        if(distance>range)continue;
        auto& cell=lookup(candidate,world.primaryCells,*world.fallback,'C',world);
        if(heightCheck7&&state.rules1432){
            const auto elevated=tables.heightOffsets[std::size_t(skip+i)];
            const TerrainCellPoint heightPoint{word(std::uint32_t(std::uint16_t(candidate.x))-std::uint32_t(std::uint16_t(heightDifference.x))+std::uint32_t(std::uint16_t(elevated.x))),
                word(std::uint32_t(std::uint16_t(candidate.y))-std::uint32_t(std::uint16_t(heightDifference.y))+std::uint32_t(std::uint16_t(elevated.y)))};
            auto& heightCell=lookup(heightPoint,world.secondaryCells,*world.fallback,'G',world);
            if(std::int32_t(heightCell.level11b)>add(heightQuotient,3))continue;
        }
        const auto old=cell.flags140;cell.flags140&=~0x40u;event('W',cell.identity,signed32(old),signed32(cell.flags140));
        if(fogMode6){
            if(!(cell.flags140&1u)||(cell.flags140&2u)||!(cell.flags12c&8u))continue;
            if(!services.fogCell)throw std::invalid_argument("Reveal area fog child required");services.fogCell(candidate,*resolved);
        }else{
            if(!services.revealCell)throw std::invalid_argument("Reveal area reveal child required");services.revealCell(candidate,*resolved,childArgument8);
        }
    }
}
}
