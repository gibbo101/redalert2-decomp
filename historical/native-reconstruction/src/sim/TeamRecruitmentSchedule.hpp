// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamReadiness.hpp"
#include <optional>
namespace ra2 {
struct TeamRecruitmentScheduleServices {
    const std::int32_t& frame;
    const std::int32_t& scenarioActive;
    const std::int32_t& emptyTimeoutE68;
    std::function<bool()> readiness6B8BB0;
    std::function<void()> anchor6B9610;
    std::function<std::uint32_t()> house4F52F0;
    std::function<TeamAdmissionTaskForce()> taskForceDC;
    std::function<void(std::int32_t)> recruit6B91C0;
    std::function<std::uint32_t(const void*)> member1C0;
    std::function<void()> continuation6BA1A0;
    MissionTagStore store;
};
// Complete-to-return6BA1A0 empty-head/null-target paths. A nonempty target
// enters range/command children and is deliberately refused, not skipped.
inline void continueUntargetedTeam(TeamConstructionRecord& team,const MissionTagStore& store={}){
    if(!team.value54)return;
    if(team.value40||team.value3C)throw std::invalid_argument("Team member continuation target path unjoined");
    team.value40=team.value3C;
    if(store)store(&team,0x40,0,team.value40);
}
// Complete-to-return6B7AD0 initial pre-ready path, including its continuation.
// Script activation/active-team/empty expiration paths remain explicit refusals.
// Child exceptions can follow original writes; this seam is not transactional.
inline void tickRecruitingTeam(TeamConstructionRecord& team,const TeamRecruitmentScheduleServices& s){
    if(team.flags74[14]){
        auto remaining=team.value6C;
        if(team.timer64!=0xffffffffu){
            const auto elapsed=std::uint32_t(s.frame)-team.timer64;
            if(std::bit_cast<std::int32_t>(elapsed)>=std::bit_cast<std::int32_t>(remaining))remaining=0;
            else remaining-=elapsed;
        }
        if(remaining)return;
        team.flags74[14]=0;teamConstructionStore(s,&team,0x82);
    }
    if(team.flags74[9]&&!requireTeamAdmission(s.readiness6B8BB0)())return;
    if(team.flags74[11]||team.flags74[5]||team.flags74[3])
        throw std::invalid_argument("Team AI activation/active Script path unjoined");
    if(team.flags74[7]||!team.cell34||!team.value38)requireTeamAdmission(s.anchor6B9610)();
    // House is queried even though the filled78 gate can bypass recruitment.
    if(!std::uint8_t(requireTeamAdmission(s.house4F52F0)())||!team.flags74[4]){
        std::optional<TeamAdmissionTaskForce> task;task.emplace(requireTeamAdmission(s.taskForceDC)());
        for(std::int32_t i=0;i<task->count9C;){
            if(i<0||std::size_t(i)>=team.values84.size())throw std::invalid_argument("Team AI TaskForce outside count backing");
            if(std::bit_cast<std::int32_t>(team.values84[std::size_t(i)])<admissionEntry(*task,i).required)
                requireTeamAdmission(s.recruit6B91C0)(i);
            i=std::bit_cast<std::int32_t>(std::uint32_t(i)+1u);
            task.emplace(requireTeamAdmission(s.taskForceDC)()); // Live Type/TaskForce reload after each slot.
        }
    }
    if(!team.value54){
        const auto elapsed=std::bit_cast<std::int32_t>(std::uint32_t(s.frame)-team.timer50);
        if(team.flags74[4]||(s.scenarioActive&&elapsed>s.emptyTimeoutE68))
            throw std::invalid_argument("Empty Team expiry/notification path unjoined");
    }else{
        // The returned low byte is evaluated by the original; on this admitted
        // pre-ready path it cannot select Script dispatch, but the query occurs.
        (void)std::uint8_t(requireTeamAdmission(s.member1C0)(team.value54));
    }
    requireTeamAdmission(s.continuation6BA1A0)();
}
}
