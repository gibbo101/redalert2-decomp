// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySubcell.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>

namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
void store(const InfantryOccupationStore& s,InfantryOccupationCell c,int off,int width,std::uint32_t value){if(s)s(c,off,width,value);}
void lowByte(std::uint32_t& word,std::uint8_t byte){word=(word&0xffffff00u)|byte;}
}
std::array<Coord,5> initialInfantrySubcellOffsets(){
    std::array<Coord,5> result{};result[0]={128,128,0};
    for(int i=0;i<4;++i)result[std::size_t(i+1)]={64+128*(i&1),64+128*((i>>1)&1),0};
    return result;
}
int infantrySubcell(const Coord& p,const std::function<double(double)>& sqrt){
    if(!sqrt)throw std::invalid_argument("Infantry subcell requires original square root");
    OriginalRounding rounding;
    const int x=std::uint32_t(p.x)&255u,y=std::uint32_t(p.y)&255u;
    const int dx=x-128,dy=y-128;const auto distance=sqrt(double(dx)*dx+double(dy)*dy);
    if(!std::isfinite(distance)||distance<0||distance>=2147483648.)throw std::invalid_argument("Infantry subcell numeric result outside finite domain");
    if(int(distance)<60)return 0;
    const int quadrant=(x>128?1:0)|(y>128?2:0);
    return quadrant?quadrant+1:0;
}
void occupyInfantrySubcell(const Coord& p,const int& house,const int& threshold,
    const InfantrySubcellServices& s,const InfantryOccupationStore& w){
    OriginalRounding rounding;
    const int subcell=infantrySubcell(p,s.squareRoot);
    if(!s.cell)throw std::invalid_argument("Infantry occupation requires Cell lookup");
    const auto c=s.cell(p);
    if(!s.floor)throw std::invalid_argument("Infantry occupation requires floor");
    const int floor=s.floor(p);
    const bool elevated=add(floor,threshold)<=p.z&&(c.flags&0x100u);
    auto& word=elevated?c.elevated:c.ground;
    lowByte(word,std::uint8_t(word)|std::uint8_t(1u<<subcell));
    store(w,c,elevated?0x128:0x124,1,std::uint8_t(word));
    if(s.houseQuery)s.houseQuery();
    auto& owner=elevated?c.elevatedHouse58:c.groundHouse54;owner=house;
    store(w,c,elevated?0x58:0x54,4,std::uint32_t(owner));
}
void releaseInfantrySubcell(const Coord& p,const int& threshold,
    const InfantrySubcellServices& s,const InfantryOccupationStore& w){
    OriginalRounding rounding;
    const int subcell=infantrySubcell(p,s.squareRoot);
    if(!s.cell)throw std::invalid_argument("Infantry release requires Cell lookup");
    const auto c=s.cell(p);
    if(!s.floor)throw std::invalid_argument("Infantry release requires floor");
    const int floor=s.floor(p);
    // Release deliberately omits the bridge-flag predicate used by occupy.
    const bool elevated=add(floor,threshold)<=p.z;
    auto& word=elevated?c.elevated:c.ground;
    const auto remaining=std::uint8_t(std::uint8_t(word)&std::uint8_t(~(1u<<subcell)));
    lowByte(word,remaining);
    store(w,c,elevated?0x128:0x124,1,remaining);
    if(!(remaining&0x1c)){
        auto& owner=elevated?c.elevatedHouse58:c.groundHouse54;owner=-1;
        store(w,c,elevated?0x58:0x54,4,std::uint32_t(owner));
    }
}
Coord chooseInfantrySubcell(InfantryOccupationCell cell,const Coord& point,
    std::uint8_t force,std::uint8_t elevated,const InfantrySubcellData& data,
    OriginalRandomState& rng,const int& bridgeHeight,const InfantrySubcellServices& s,
    const OriginalRandomRangeObserver& observe,Coord empty){
    OriginalRounding rounding;
    int selected=infantrySubcell(point,s.squareRoot);
    // Original saves the aligned base before any RNG or floor effects. This
    // masks off low bytes, unlike signed truncating division by256 elsewhere.
    const int baseX=signed32(std::uint32_t(point.x)&0xffffff00u);
    const int baseY=signed32(std::uint32_t(point.y)&0xffffff00u);
    const auto occupied=[&](int slot){return ((elevated?cell.elevated:cell.ground)&(1u<<slot))!=0;};
    if(!force){
        if(occupied(5))return empty;
        if(cell.ground&0x40u)throw std::invalid_argument("Infantry subcell building admission requires recovery");
        if(selected==0||selected==1||occupied(selected)){
            const auto row=selected==0?5+rangedOriginalRandom(rng,0,3,observe):selected;
            bool found=false;
            for(const auto slot:data.orders.at(std::size_t(row))){
                if(slot>4)throw std::invalid_argument("Infantry subcell order outside supplied profile");
                if(slot==0||slot==1||occupied(slot))continue;
                selected=slot;found=true;break;
            }
            if(!found)return empty;
        }
    }
    const auto offset=initialInfantrySubcellOffsets().at(std::size_t(selected));
    const int x=add(baseX,offset.x),y=add(baseY,offset.y);
    if(!s.floor)throw std::invalid_argument("Infantry subcell selection requires floor");
    const int floor=s.floor(point);
    return {x,y,elevated?add(floor,bridgeHeight):floor};
}
}
