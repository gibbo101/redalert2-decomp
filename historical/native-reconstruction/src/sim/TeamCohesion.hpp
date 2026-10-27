// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamRecruitmentSchedule.hpp"
namespace ra2 {
struct TeamCohesionFoot {
    const void* identity;
    const void* const& next4C8;
    const std::uint8_t& onMap7D;
    const std::int32_t& health6C;
    const std::uint8_t& flag76;
    std::uint8_t& leader579;
    const void* const& target494;
    const void* const& alternate228;
};
struct TeamCohesionServices {
    const std::int32_t& loading;
    std::size_t memberLimit;
    std::function<TeamCohesionFoot(const void*)> foot;
    std::function<std::int32_t()> script668870;
    std::function<std::int32_t(bool)> range;
    std::function<std::int32_t(const void*,const void*)> distance5D4C00;
    std::function<std::int32_t(const void*)> kind2C,mission16C;
    std::function<void(const void*,int,int)> queue1D0;
    std::function<void(const void*,const void*)> target370;
    std::function<void(const void*,const void*,int)> destination410;
    std::function<Coord(const void*)> coordinates48;
    std::function<TerrainCellPoint(const void*,TerrainCellPoint)> nearby4C8AF0;
    std::function<const void*(TerrainCellPoint)> map548070;
    MissionTagStore store;
};
// Complete6B9F40. Range, distance, mission/command and nearby children stay
// explicit. Follow live next/anchor/target fields after every child call.
inline bool regroupTeamMembers(TeamConstructionRecord& team,const TeamCohesionServices& s){
    bool ready=true;std::size_t visits=0;
    const auto range=[&]{const auto script=requireTeamAdmission(s.script668870)();return requireTeamAdmission(s.range)(script==53||script==54);};
    for(auto* cursor=team.value54;cursor;){
        if(++visits>s.memberLimit)throw std::invalid_argument("Team cohesion requires finite owned members");
        auto foot=requireTeamAdmission(s.foot)(cursor);
        if(foot.onMap7D&&foot.health6C&&(s.loading||!foot.flag76)&&!foot.leader579){
            const auto limit=range();
            if(requireTeamAdmission(s.distance5D4C00)(cursor,team.cell34)>limit){
                if(!foot.target494){
                    requireTeamAdmission(s.queue1D0)(cursor,2,0);
                    requireTeamAdmission(s.target370)(cursor,nullptr);
                    requireTeamAdmission(s.destination410)(cursor,team.cell34,1);
                }
            }else{foot.leader579=1;teamConstructionStore(s,cursor,0x579,1);}
        }
        if(foot.onMap7D&&foot.health6C&&(s.loading||!foot.flag76)&&
           (foot.leader579||requireTeamAdmission(s.kind2C)(cursor)==2)){
            const auto limit=range();
            if(requireTeamAdmission(s.distance5D4C00)(cursor,team.cell34)>limit){
                if(requireTeamAdmission(s.mission16C)(cursor)==11&&foot.alternate228){
                    // Original joins the near-side mission test here.
                    if(requireTeamAdmission(s.mission16C)(cursor)!=11){
                        requireTeamAdmission(s.queue1D0)(cursor,5,0);
                        requireTeamAdmission(s.destination410)(cursor,nullptr,1);
                    }
                }else if(!foot.target494){
                    ready=false;requireTeamAdmission(s.queue1D0)(cursor,2,0);
                    const auto p=requireTeamAdmission(s.coordinates48)(team.cell34);
                    const TerrainCellPoint cell{std::bit_cast<std::int16_t>(std::uint16_t(p.x/256)),std::bit_cast<std::int16_t>(std::uint16_t(p.y/256))};
                    const auto nearby=requireTeamAdmission(s.nearby4C8AF0)(cursor,cell);
                    const auto target=requireTeamAdmission(s.map548070)(nearby);
                    requireTeamAdmission(s.destination410)(cursor,target,1);
                }
            }else if(requireTeamAdmission(s.mission16C)(cursor)!=11){
                requireTeamAdmission(s.queue1D0)(cursor,5,0);
                requireTeamAdmission(s.destination410)(cursor,nullptr,1);
            }
        }
        cursor=foot.next4C8;
    }
    if(ready){team.flags74[1]=0;teamConstructionStore(s,&team,0x75);}
    return ready;
}
struct TeamActivationServices {
    std::size_t memberLimit;
    std::function<bool()> readiness6B8BB0;
    std::function<const void*(const void*)> next4C8;
    std::function<void(const void*,std::uint8_t)> leader579;
    std::function<void()> reset668900,anchor6B9610;
    std::function<std::uint32_t(const void*)> member1C0;
    std::function<std::uint32_t()> cohesion6B9F40;
    MissionTagStore store;
};
// Complete-to-return6B7AD0 activation -> regroup paths. The caller admits an
// originally pending full Team with changed7A, so7B takes the regroup return.
inline void activateRecruitedTeam(TeamConstructionRecord& team,const TeamActivationServices& s){
    if(team.flags74[14]||team.flags74[11]||!team.flags74[9]||!team.flags74[6])
        throw std::invalid_argument("Team activation outside pending initial domain");
    if(!requireTeamAdmission(s.readiness6B8BB0)())return;
    if(!team.flags74[5]&&!team.flags74[3])throw std::invalid_argument("Team activation requires full/forced readiness");
    const auto put=[&](int off,std::uint8_t value){team.flags74[std::size_t(off-0x74)]=value;teamConstructionStore(s,&team,off,value);};
    auto* cursor=team.value54;put(0x7f,1);put(0x78,1);put(0x7a,0);std::size_t visits=0;
    while(cursor){
        if(++visits>s.memberLimit)throw std::invalid_argument("Team activation requires finite owned members");
        if(team.flags74[7]||team.flags74[3])requireTeamAdmission(s.leader579)(cursor,1);
        cursor=requireTeamAdmission(s.next4C8)(cursor);
    }
    requireTeamAdmission(s.reset668900)();put(0x80,1);
    requireTeamAdmission(s.anchor6B9610)(); //7F is now nonzero.
    if(!team.value54)throw std::invalid_argument("Activated empty Team expiry unjoined");
    const auto blocked=std::uint8_t(requireTeamAdmission(s.member1C0)(team.value54));
    if(!team.flags74[7]&&!team.flags74[6]&&!blocked)
        throw std::invalid_argument("Immediate activation Script dispatch unjoined");
    put(0x7b,std::uint8_t(!std::uint8_t(requireTeamAdmission(s.cohesion6B9F40)())));
}
}
