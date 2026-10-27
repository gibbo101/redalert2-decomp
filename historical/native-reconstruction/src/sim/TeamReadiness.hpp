// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamMembership.hpp"
namespace ra2 {
struct TeamReadinessType {
    const std::uint8_t& flagAB;
    const std::uint8_t& flagA7;
    const TeamAdmissionTaskForce& taskForceDC;
};
struct TeamReadinessServices {
    std::function<TeamReadinessType&()> type24;
    std::function<std::int32_t()> tagCount;
    std::function<const void*(std::int32_t)> tagSlot;
    std::function<std::uint32_t(const void*,int,int,std::uint32_t,int,int)> raise6B3DF0;
    std::function<void(std::uint32_t)> destroy20;
    const std::uint32_t& emptyCell;
    MissionTagStore store;
};
// Complete6B6B30. The saved signed count controls the scan; additions wrap.
inline std::int32_t teamRequiredQuantity(const TeamAdmissionTaskForce& task){
    const auto count=task.count9C;std::uint32_t sum=0;
    for(std::int32_t i=0;i<count;++i)sum+=std::uint32_t(admissionEntry(task,i).required);
    return std::bit_cast<std::int32_t>(sum);
}
// Complete6B8BB0. Flags are byte fields in the existing Team owner. Destruction
// and scenario Tag notification remain explicit children, never silent no-ops.
inline bool refreshTeamReadiness(TeamConstructionRecord& team,const TeamReadinessServices& s){
    const auto put=[&](int offset,std::uint8_t value){team.flags74[std::size_t(offset-0x74)]=value;teamConstructionStore(s,&team,offset,value);};
    const auto old=team.flags74[6];
    const auto required=teamRequiredQuantity(requireTeamAdmission(s.type24)().taskForceDC);
    const auto quantity=std::bit_cast<std::int32_t>(team.value48);
    if(quantity>0){
        put(0x79,std::uint8_t(quantity==required));
        if(team.flags74[5])put(0x78,1);
        auto& type=requireTeamAdmission(s.type24)();
        if(type.flagAB)put(0x7a,std::uint8_t(required>2?quantity<=required/3:quantity<required));
        else put(0x7a,std::uint8_t(!team.flags74[4]));
        if(type.flagA7)put(0x76,std::uint8_t(!team.flags74[6]));
        put(0x7e,0);put(0x7d,0);
    }else{
        put(0x76,0);put(0x7a,1);put(0x79,0);
        team.cell34=nullptr;teamConstructionStore(s,&team,0x34);
        if(team.flags74[4]){
            if(team.flags74[13]){
                auto i=std::bit_cast<std::int32_t>(std::uint32_t(requireTeamAdmission(s.tagCount)())-1u);
                while(i>=0){
                    const auto* tag=requireTeamAdmission(s.tagSlot)(i);
                    const auto result=requireTeamAdmission(s.raise6B3DF0)(tag,23,0,s.emptyCell,0,0);
                    if(std::uint8_t(result)&&requireTeamAdmission(s.tagCount)()==0)break;
                    --i;
                }
            }
            requireTeamAdmission(s.destroy20)(1);return false;
        }
    }
    if(old!=team.flags74[6])put(0x7b,1);
    return true;
}
}
