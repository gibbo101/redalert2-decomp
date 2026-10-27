// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamConstruction.hpp"
#include "sim/TeamAdmission.hpp"
#include "sim/WalkMovement.hpp"
namespace ra2 {
struct TeamMembershipType {
    const std::int32_t& group9C;
    const std::int32_t* taskForceGroup98;
    const std::uint8_t& flagB3;
    const std::uint8_t& recruitableED;
    const std::uint8_t& weightA7;
};
struct TeamMemberFoot {
    const void* identity;
    const void*& team4C4;
    const void*& next4C8;
    std::uint8_t& leader579;
    std::int32_t& group1AC;
    std::uint8_t& recruitable37A;
    MissionTagState*& tag34;
};
struct TeamAnchorFoot {
    const void* identity;
    const void* const& next4C8;
    const std::uint8_t& onMap7D;
    const std::int32_t& health6C;
    const std::uint8_t& flag76;
    const std::uint8_t& leader579;
    const std::uint8_t& active32D;
    const Coord& coordinates88;
};
struct TeamMembershipServices {
    std::function<TeamMembershipType&()> type24;
    std::function<std::uint32_t(TeamMemberFoot&,std::int32_t&)> admission6B8DC0;
    std::function<void(const void*,TeamMemberFoot&,std::int32_t,std::uint32_t)> remove6B8FB0;
    std::function<std::int32_t(TeamMemberFoot&)> type80Count52C;
    std::function<void(TeamMemberFoot&,const void*)> setTag5D4430;
    std::function<std::int32_t(TeamMemberFoot&)> threat2A0;
    std::function<void()> anchor6B9610;
    MissionTagStore store;
};
// Complete6BFA60. Keep -2 distinct from -1 and null TaskForce.
inline std::int32_t teamMembershipGroup(const TeamMembershipType& t){
    const auto value=t.group9C;
    return value==-1&&t.taskForceGroup98?*t.taskForceGroup98:value;
}
// Complete6B8CC0 parent. Children bind actual borrowed owners synchronously.
inline bool addTeamMember(TeamConstructionRecord& team,TeamMemberFoot* foot,const TeamMembershipServices& s){
    if(!foot)return false;
    std::int32_t slot=0;
    if(!std::uint8_t(requireTeamAdmission(s.admission6B8DC0)(*foot,slot)))return false;
    const auto old=foot->team4C4;
    if(old)requireTeamAdmission(s.remove6B8FB0)(old,*foot,-1,0);
    if(slot<0||std::size_t(slot)>=team.values84.size())throw std::invalid_argument("AddMember outside actual TaskForce count fields");
    ++team.values84[std::size_t(slot)];teamConstructionStore(s,&team,0x84+4*slot,team.values84[std::size_t(slot)]);
    foot->leader579=std::uint8_t(!team.value54);teamConstructionStore(s,foot->identity,0x579,foot->leader579);
    foot->next4C8=team.value54;teamConstructionStore(s,foot->identity,0x4c8,0,foot->next4C8);
    team.value54=foot->identity;teamConstructionStore(s,&team,0x54,0,foot->identity);
    foot->team4C4=&team;teamConstructionStore(s,foot->identity,0x4c4,0,&team);
    foot->group1AC=teamMembershipGroup(requireTeamAdmission(s.type24)());
    teamConstructionStore(s,foot->identity,0x1ac,std::uint32_t(foot->group1AC));
    if(team.tag70){
        bool attach=true;
        if(requireTeamAdmission(s.type24)().flagB3&&requireTeamAdmission(s.type80Count52C)(*foot)<=0)attach=false;
        if(attach)requireTeamAdmission(s.setTag5D4430)(*foot,team.tag70);
    }
    ++team.value48;teamConstructionStore(s,&team,0x48,team.value48);
    const auto threat=requireTeamAdmission(s.threat2A0)(*foot);
    team.value4C+=std::uint32_t(threat);teamConstructionStore(s,&team,0x4c,team.value4C);
    if(!team.cell34)requireTeamAdmission(s.anchor6B9610)();
    const auto& type=requireTeamAdmission(s.type24)(); // Saved Type precedes both flag stores.
    team.flags74[10]=1;teamConstructionStore(s,&team,0x7e,1);
    team.flags74[9]=1;teamConstructionStore(s,&team,0x7d,1);
    foot->recruitable37A=type.recruitableED;teamConstructionStore(s,foot->identity,0x37a,foot->recruitable37A);
    return true;
}
struct TeamAnchorServices {
    const std::int32_t& loading;
    std::size_t memberLimit;
    std::function<TeamMembershipType&()> type24;
    std::function<std::int32_t(const void*)> script668870;
    std::function<TeamAnchorFoot(const void*)> foot;
    std::function<std::int32_t(const void*)> kind2C;
    std::function<std::uint32_t(const void*)> weighted46C;
    std::function<std::int32_t(const void*)> type80Count52C;
    std::function<std::uint8_t(const void*)> type80FlagADA;
    std::function<std::int32_t(const void*,const void*)> distance5D4DA0;
    std::function<const void*(Coord)> map548000;
    std::function<std::int32_t(const void*,const void*,int,int,int,int)> permission194;
    MissionTagStore store;
};
inline std::int32_t teamAnchorDivide(std::uint32_t sum,std::uint32_t count){
    const auto a=std::bit_cast<std::int32_t>(sum),b=std::bit_cast<std::int32_t>(count);
    if(!b||(a==INT32_MIN&&b==-1))throw std::invalid_argument("Original Team anchor division would fault");return a/b;
}
// Complete6B9610 normal-script path. Script10 scans unrelated global actor
// registries and remains explicitly refused. All accepted paths run to RET8.
inline void selectTeamMemberAnchor(TeamConstructionRecord& team,const TeamAnchorServices& s){
    const auto put=[&](const void*& field,std::int64_t offset,const void* value){field=value;if(s.store)s.store(&team,offset,0,value);};
    put(team.value38,0x38,nullptr);put(team.cell34,0x34,nullptr);
    const auto head=team.value54;if(!head)return;
    if(requireTeamAdmission(s.script668870)(team.script28)==10)throw std::invalid_argument("Team anchor Script10 path unjoined");
    std::uint32_t sumX=0,sumY=0,count=0;std::int32_t bestDistance=0;const void* selected=nullptr;std::size_t visits=0;
    for(auto* cursor=head;cursor;){
        if(++visits>s.memberLimit)throw std::invalid_argument("Team anchor requires a finite owned member list");
        auto member=requireTeamAdmission(s.foot)(cursor);
        if(member.onMap7D&&member.health6C&&(s.loading||!member.flag76)&&
           (member.leader579||requireTeamAdmission(s.kind2C)(cursor)==2)&&member.active32D){
            sumX+=std::uint32_t(member.coordinates88.x);sumY+=std::uint32_t(member.coordinates88.y);++count;
            if(requireTeamAdmission(s.type24)().weightA7&&std::uint8_t(requireTeamAdmission(s.weighted46C)(cursor))){
                sumX+=std::uint32_t(member.coordinates88.x);sumY+=std::uint32_t(member.coordinates88.y);++count;
            }
            const auto passengers=requireTeamAdmission(s.type80Count52C)(cursor);
            if(passengers<=0||!requireTeamAdmission(s.type80FlagADA)(cursor)){
                const auto distance=requireTeamAdmission(s.distance5D4DA0)(cursor,team.value40);
                if(!bestDistance||distance<bestDistance){bestDistance=distance;selected=cursor;}
            }
        }
        cursor=member.next4C8;
    }
    if(count){
        const Coord average{teamAnchorDivide(sumX,count),teamAnchorDivide(sumY,count),0};
        const auto cell=requireTeamAdmission(s.map548000)(average);put(team.cell34,0x34,cell);
        if(!selected)selected=team.value54;
        if(!selected)throw std::invalid_argument("Original anchor fallback would dereference null member");
        if(requireTeamAdmission(s.permission194)(selected,cell,-1,-1,0,1))put(team.cell34,0x34,selected);
    }
    if(selected)put(team.value38,0x38,selected);
}
// Complete6B9590 for the constructed/populated domain with other reference words
// still null. The low-byte head splice is distinct from member unlink/counts.
inline void expireMemberTeamTag(TeamConstructionRecord& r,const void* subject,std::uint32_t removed,
        const std::function<const void*(const void*)>& next,const MissionTagStore& store={}){
    if(!subject||r.value40||r.value3C||r.argument44||r.value30)
        throw std::invalid_argument("Team expiration outside bound reference domain");
    const auto clear=[&](std::int64_t off){if(store)store(&r,off,0,nullptr);};
    if(r.tag70==subject){r.tag70=nullptr;clear(0x70);}
    if(r.value54==subject&&std::uint8_t(removed)){
        r.value54=requireTeamAdmission(next)(subject);if(store)store(&r,0x54,0,r.value54);
    }
    if(r.house2C&&r.house2C->identity==subject){r.house2C=nullptr;clear(0x2c);}
    if(r.script28==subject){r.script28=nullptr;clear(0x28);}
    if(r.cell34==subject){r.cell34=nullptr;clear(0x34);}
    if(r.type24&&r.type24->identity==subject){r.type24=nullptr;clear(0x24);}
    if(r.value38==subject){r.value38=nullptr;clear(0x38);}
}
}
