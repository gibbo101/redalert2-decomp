// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamConstruction.hpp"
#include "sim/TeamAdmission.hpp"
#include <optional>
namespace ra2 {
struct TeamRemovalFoot {
    const void* identity;
    const void*& team4C4;const void*& next4C8;
    std::uint8_t& flag5A2;
    std::int32_t& field9C;
    const void*& link498;const void*& target22C;
    std::uint8_t& leader579;
    const std::uint8_t& onMap7D;const std::uint8_t& flag37D;const std::uint8_t& flag76;
};
struct TeamRemovalTask {
    const std::int32_t& count9C;
    std::span<const void* const> typesA8; // Inline TaskForce entries, not another registry.
};
struct TeamRemovalServices {
    const std::int32_t& loading;
    std::size_t memberLimit;
    std::function<TeamRemovalFoot(const void*)> foot;
    std::function<const void*(const void*)> tag34,house1B4;
    std::function<std::uint32_t(const void*)> controlled4F52F0;
    std::function<void(const void*)> clearTag5D4430;
    // Pure live Type24 -> TaskForceDC association; null for either null pointer.
    std::function<std::optional<TeamRemovalTask>()> task;
    std::function<const void*(const void*)> type84;
    std::function<std::uint32_t(const void*)> threat2A0;
    std::function<void(const void*,const void*,std::uint32_t)> resume414;
    MissionTagStore store;
};
// Complete6B8FB0. Saved TaskForce per query, live later Type/task, signed scan
// and unsigned final slot test, saved unlink successor and late resume gates.
inline bool removeTeamMember(TeamConstructionRecord& team,const void* identity,
        std::int32_t slot,std::uint32_t suppressResume,const TeamRemovalServices& s){
    if(!identity)throw std::invalid_argument("Team removal requires nonnull Foot");
    auto foot=requireTeamAdmission(s.foot)(identity);
    if(foot.identity!=identity)throw std::invalid_argument("Team removal Foot identity differs");
    const auto put=[&](const void* p,std::int64_t off,std::uint32_t value=0,const void* pointer=nullptr){
        if(s.store)s.store(p,off,value,pointer);
    };
    foot.flag5A2=1;put(identity,0x5a2,1);
    if(foot.team4C4!=&team)return true;
    if(requireTeamAdmission(s.tag34)(identity)==team.tag70){
        const auto house=requireTeamAdmission(s.house1B4)(identity);
        if(house&&!std::uint8_t(requireTeamAdmission(s.controlled4F52F0)(house)))
            requireTeamAdmission(s.clearTag5D4430)(identity);
    }
    if(slot==-1){
        if(const auto initial=requireTeamAdmission(s.task)()){
            slot=0;
            if(initial->count9C>0){
                for(;;){
                    const auto saved=requireTeamAdmission(s.task)();
                    if(!saved)throw std::invalid_argument("Team removal scan lost TaskForce");
                    const auto type=requireTeamAdmission(s.type84)(identity);
                    if(slot<0||std::size_t(slot)>=saved->typesA8.size())
                        throw std::invalid_argument("Team removal scan exceeds inline TaskForce backing");
                    if(saved->typesA8[std::size_t(slot)]==type)break;
                    slot=std::bit_cast<std::int32_t>(std::uint32_t(slot)+1u);
                    if(slot>=saved->count9C)break;
                }
            }
        }
    }
    if(const auto task=requireTeamAdmission(s.task)();task&&std::uint32_t(slot)<std::uint32_t(task->count9C)){
        if(std::uint32_t(slot)>=team.values84.size())throw std::invalid_argument("Team removal count slot outside actual six fields");
        --team.values84[std::size_t(slot)];put(&team,0x84+4*slot,team.values84[std::size_t(slot)]);
    }
    bool found=false,leader=false;const void* previous=nullptr;const void* cursor=team.value54;std::size_t visits=0;
    while(cursor&&!(found&&leader)){
        if(++visits>s.memberLimit)throw std::invalid_argument("Team removal needs finite owned members");
        auto member=requireTeamAdmission(s.foot)(cursor);
        if(cursor==identity){
            if(previous){auto before=s.foot(previous);before.next4C8=member.next4C8;put(previous,0x4c8,0,before.next4C8);}
            else{team.value54=member.next4C8;put(&team,0x54,0,team.value54);}
            const auto next=member.next4C8;
            member.next4C8=nullptr;put(cursor,0x4c8);
            member.team4C4=nullptr;put(cursor,0x4c4);
            member.field9C=-1;put(cursor,0x9c,0xffffffffu);
            member.link498=nullptr;put(cursor,0x498);
            member.target22C=nullptr;put(cursor,0x22c);
            --team.value48;put(&team,0x48,team.value48);
            cursor=next;found=true;
            const auto threat=requireTeamAdmission(s.threat2A0)(identity);
            team.value4C-=threat;put(&team,0x4c,team.value4C);
        }else{
            leader=leader||member.leader579!=0;previous=cursor;cursor=member.next4C8;
        }
    }
    if(foot.team4C4){foot.team4C4=nullptr;put(identity,0x4c4);}
    if(!s.loading&&foot.onMap7D&&!foot.flag37D&&!foot.flag76&&!std::uint8_t(suppressResume))
        requireTeamAdmission(s.resume414)(identity,nullptr,1);
    if(!leader&&team.value54){auto head=s.foot(team.value54);head.leader579=1;put(head.identity,0x579,1);team.cell34=nullptr;put(&team,0x34);}
    team.flags74[10]=1;put(&team,0x7e,1);
    team.flags74[9]=1;put(&team,0x7d,1);
    return true;
}
}
