// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionConstruction.hpp"
namespace ra2 {
struct MissionScriptAction {std::int32_t action=-1,argument=0;};
struct MissionScriptTypeState {
    const std::int32_t& countA0;
    std::span<const MissionScriptAction> actionsA4;
};
using MissionScriptTypeResolver=std::function<MissionScriptTypeState(const void*)>;
inline MissionScriptAction scriptActionAt(const MissionScriptTypeState& type,std::int32_t index){
    // The getter itself does not compare the declared command count. Keep
    // backing bounds separate: malformed original addresses are not C++ access.
    if(index<0||std::size_t(index)>=type.actionsA4.size())throw std::invalid_argument("Original Script access outside bound backing");
    return type.actionsA4[std::size_t(index)];
}
// Complete668870. Cursor -1 bypasses the Type load.
inline MissionScriptAction currentMissionScriptAction(const MissionScriptConstructionRecord& script,const MissionScriptTypeResolver& type){
    if(script.cursor2C==-1)return {-1,0};
    if(!type)throw std::invalid_argument("Script Type owner unbound");return scriptActionAt(type(script.type24),script.cursor2C);
}
// Complete6688B0: signed next-index comparison, distinct from668920/668940.
inline MissionScriptAction nextMissionScriptAction(const MissionScriptConstructionRecord& script,const MissionScriptTypeResolver& type){
    if(!type)throw std::invalid_argument("Script Type owner unbound");const auto view=type(script.type24);
    const auto next=std::bit_cast<std::int32_t>(std::uint32_t(script.cursor2C)+1u);
    return next<view.countA0?scriptActionAt(view,next):MissionScriptAction{-1,0};
}
inline bool resetMissionScript(MissionScriptConstructionRecord& script,const MissionTagStore& store={}){
    script.cursor2C=-1;if(store)store(&script,0x2c,0xffffffffu,nullptr);return true;
}
// Complete668920: publish wrapped cursor before loading current Type/count.
inline bool advanceMissionScript(MissionScriptConstructionRecord& script,const MissionScriptTypeResolver& type,const MissionTagStore& store={}){
    script.cursor2C=std::bit_cast<std::int32_t>(std::uint32_t(script.cursor2C)+1u);
    if(store)store(&script,0x2c,std::uint32_t(script.cursor2C),nullptr);
    if(!type)throw std::invalid_argument("Script Type owner unbound");
    return std::uint32_t(script.cursor2C)<std::uint32_t(type(script.type24).countA0);
}
// Complete668940: the comparison is unsigned, including negative cursors/counts.
inline bool missionScriptHasCurrent(const MissionScriptConstructionRecord& script,const MissionScriptTypeResolver& type){
    if(!type)throw std::invalid_argument("Script Type owner unbound");
    return std::uint32_t(script.cursor2C)<std::uint32_t(type(script.type24).countA0);
}
}
