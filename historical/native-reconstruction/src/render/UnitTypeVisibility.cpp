// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitTypeVisibility.hpp"
#include "sim/Facing.hpp"
namespace ra2 {
namespace {
int sub(int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));}
}
bool unitDrawTimerHasRemainder(int start,int duration,int frame){
    if(start==-1)return duration!=0;
    const int elapsed=sub(frame,start);
    if(elapsed>=duration)return false;
    return sub(duration,elapsed)!=0;
}
UnitDrawingDefaults initialUnitDrawingFields(int frame){
    UnitDrawingDefaults fields;
    fields.disguise.timerStart=frame;fields.timerStart=frame;
    return fields;
}
bool unitOwnerTypeVisible(int mode,std::uint8_t a,std::uint8_t b,bool current){
    return mode?current:(a||b);
}
bool unitOwnerAlliedToCurrent(bool present,bool same,int ownerIndex,int currentIndex,std::uint32_t alliances){
    if(!present)return false;
    if(same||ownerIndex==currentIndex)return true;
    return currentIndex!=-1&&(alliances&(std::uint32_t(1)<<(std::uint32_t(currentIndex)&31)))!=0;
}
bool originalUnitTypeVisible(const UnitDisguiseState& a,int frame,
                            const std::function<bool()>& ownerVisible,
                            const std::function<std::optional<std::int16_t>()>& getCell,
                            const UnitTypeTrace& trace){
    auto disguised=[&]{if(trace)trace('d');return a.disguised!=0;};
    if(unitDrawTimerHasRemainder(a.timerStart,a.timerDuration,frame)&&!ownerVisible())return true;
    if(ownerVisible()&&disguised()){
        const int phase=signed32(std::uint32_t(sub(frame,a.creationFrame))+64)%256;
        return phase<72||phase>119;
    }
    const auto cell=getCell();
    if(!disguised()||!cell)return true;
    if(trace)trace('s');
    return *cell>0;
}
int selectUnitDisplayType(int originalType,int alternateType,int argument,const std::function<bool()>& allied){
    const bool isAllied=allied(); // Original always queries the house first.
    return isAllied&&std::uint8_t(argument)==0?originalType:alternateType;
}
}
