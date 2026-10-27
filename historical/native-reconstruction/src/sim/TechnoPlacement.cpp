// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoPlacement.hpp"
#include <stdexcept>
namespace ra2 {
bool placeOrdinaryUnit(UnitPlacementState& a,const UnitPlacementInputs& in,const UnitPlacementServices& s,
                       const UnitPlacementStore& store) {
    const auto write=[&](int offset,int bytes,int value){if(store)store(offset,bytes,value);};
    if(in.heightDivisor<=0)throw std::invalid_argument("Positive placement height divisor required");
    a.bridge32D=s.bridge(terrainCellPoint(in.requested));write(0x32d,1,a.bridge32D);
    if(!s.objectUnlimbo(in.requested,in.direction))return false;
    if(!a.onMap)return true;
    s.reset418();
    s.mapUpdate(a.position,signed32(std::uint32_t(a.field1F4)+3u));
    s.typeQuery();if(in.typeEffect)s.registerEffect();
    s.ownerPlacement();
    a.body.setCurrent(std::uint16_t(std::uint32_t(in.direction)<<8),in.currentFrame);
    a.barrel.setCurrent(0x4000,in.currentFrame);
    s.typeQuery();
    const auto adjustment=std::uint32_t(std::uint8_t(in.fireAngle))<<8;
    a.barrel.setDesired(std::uint16_t(0x4000u-adjustment),in.currentFrame);
    a.field3EC=1;write(0x3ec,4,1);a.field3F0=0;write(0x3f0,4,0);s.unitKind(); // Actual Unit kind is 1, not 15.
    s.notify414();a.flag190=0;write(0x190,1,0);
    if(s.predicate1E8()!=0)s.notify1D4();
    const int height=in.requested.z/in.heightDivisor;
    a.height378=std::uint8_t(std::uint32_t(height)*10u);write(0x378,1,a.height378);
    if(s.bridge(terrainCellPoint(in.requested))==0){a.field373=0;write(0x373,1,0);}
    if(s.cell1A4()) {
        const int value=s.value2A0();a.field400=value;write(0x400,4,value);
        s.associateCell(s.kind38(value));
    }
    const auto location=s.locate(a.position);
    a.field1A0[0]=location[0];write(0x1a0,4,location[0]);a.field1A0[1]=location[1];write(0x1a4,4,location[1]);
    if(a.field114==-1){a.field114=s.ownerDefault();write(0x114,4,a.field114);}
    return true;
}
}
