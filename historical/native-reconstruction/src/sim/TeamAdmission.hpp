// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <span>
#include <functional>
#include <stdexcept>
#include <bit>
namespace ra2 {
struct TeamAdmissionEntry { std::int32_t required;const void* type; };
struct TeamAdmissionTaskForce { const std::int32_t& count9C;std::span<const TeamAdmissionEntry> entries; };
struct TeamAdmissionType {
    const std::uint8_t& byteA9;
    const std::int32_t& priorityB4;
    TeamAdmissionTaskForce* const& taskForceDC;
};
struct TeamAdmissionTeam {
    const void* identity;
    // Resolvers project the current actual Team Type/House on every query.
    std::function<TeamAdmissionType&()> type24;
    const void* const& script28;
    std::function<const void*()> house2C;
    std::span<const std::uint32_t> counts84;
};
struct TeamAdmissionFoot {
    const void* identity;
    const void* const& team4C4;
    const std::uint8_t& onMap7D;
    const std::int32_t& health6C;
    const std::uint8_t& flag76;
    std::function<const void*()> house1B4;
    const std::uint8_t& byte379;
    const std::uint8_t& byte37A;
    const std::uint8_t& aircraftTypeBA3;
    const std::uint32_t& target254;
};
struct TeamAdmissionServices {
    const std::int32_t& loadingA40774;
    std::function<std::uint32_t()> radio636F10,kind2C;
    std::function<std::int32_t()> mission16C;
    std::function<std::uint32_t(std::int32_t)> mission594DB0;
    std::function<std::int32_t(const void*)> script668870;
    std::function<std::int32_t(const void*)> teamPriorityB4;
    std::function<std::int32_t(std::uint32_t)> aircraft39C;
    std::function<const void*()> type84;
    std::function<void(std::int32_t)> outputStore;
};
template<class F> inline const F& requireTeamAdmission(const F& callback){
    if(!callback)throw std::invalid_argument("Entered Team admission child unbound");return callback;
}
inline TeamAdmissionType& admissionType(const TeamAdmissionTeam& t){return requireTeamAdmission(t.type24)();}
inline const TeamAdmissionTaskForce& admissionTask(const TeamAdmissionTeam& t){
    auto* task=admissionType(t).taskForceDC;
    if(!task)throw std::invalid_argument("Team admission TaskForce would dereference null");return *task;
}
inline const TeamAdmissionEntry& admissionEntry(const TeamAdmissionTaskForce& task,std::int32_t index){
    if(index<0||std::size_t(index)>=task.entries.size())throw std::invalid_argument("Team admission outside actual TaskForce backing");
    return task.entries[std::size_t(index)];
}
// Complete supplied-base6B8DC0 parent. Children remain explicit live services.
// Original dereferences Foot+4C4 before its null test; null Foot is refused.
inline bool canAdmitTeamFoot(const TeamAdmissionTeam& t,TeamAdmissionFoot f,
        std::int32_t& output,const TeamAdmissionServices& s){
    if(!f.identity)throw std::invalid_argument("Original admission would dereference null Foot");
    if(f.team4C4==t.identity)return false;
    if(!f.onMap7D||!f.health6C)return false;
    if(!s.loadingA40774&&f.flag76)return false;
    if(requireTeamAdmission(f.house1B4)()!=requireTeamAdmission(t.house2C)())return false;
    if(std::uint8_t(requireTeamAdmission(s.radio636F10)())){
        if(requireTeamAdmission(s.kind2C)()!=2||!f.aircraftTypeBA3)return false;
    }
    if(requireTeamAdmission(s.mission16C)()!=-1){
        const auto mission=s.mission16C();
        if(!std::uint8_t(requireTeamAdmission(s.mission594DB0)(mission)))return false;
    }
    if(!f.byte379&&!admissionType(t).byteA9)return false;
    bool special=false;
    const auto script=t.script28;
    if(script)special=requireTeamAdmission(s.script668870)(script)==8;
    if(requireTeamAdmission(s.kind2C)()==2)special=true;
    if(!f.byte37A&&admissionType(t).byteA9&&!special)return false;
    const auto prior=f.team4C4;
    if(prior){
        const auto previous=requireTeamAdmission(s.teamPriorityB4)(prior);
        if(previous>=admissionType(t).priorityB4)return false;
    }
    if(requireTeamAdmission(s.kind2C)()==2){
        if(requireTeamAdmission(s.aircraft39C)(0)!=0&&!f.target254)return false;
    }
    const auto put=[&](std::int32_t v){output=v;if(s.outputStore)s.outputStore(v);};
    put(0);
    if(admissionTask(t).count9C>0){
        do{
            const auto saved=output;
            const auto type=requireTeamAdmission(s.type84)();
            if(admissionEntry(admissionTask(t),saved).type==type)break;
            put(std::bit_cast<std::int32_t>(std::uint32_t(saved)+1));
        }while(output<admissionTask(t).count9C);
    }
    const auto& task=admissionTask(t);const auto slot=output;
    if(slot==task.count9C)return false;
    if(slot<0||std::size_t(slot)>=t.counts84.size())throw std::invalid_argument("Team admission outside actual count backing");
    const auto current=std::bit_cast<std::int32_t>(t.counts84[std::size_t(slot)]);
    return current<admissionEntry(task,slot).required;
}
}
