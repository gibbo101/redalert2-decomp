// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefreshMarks.hpp"
#include "render/UnitTypeVisibility.hpp"
namespace ra2 {
enum class RadarColorActorKind { infantry,building };
struct RadarColorActor {
    RadarColorActorKind kind;
    const std::uint8_t& byte170;
    // Pure borrowed fields; resolving a view must not issue gameplay queries.
    std::function<const void*()> owner1B4,alternate410;
};
struct RadarColorHouse {const std::int32_t& index30;const std::uint32_t& allies5674;};
struct RadarColorWorld {
    const void* const& currentA35DB4;
    std::function<RadarColorActor(const void*)> actor;
    std::function<RadarColorHouse(const void*)> house;
    // Passive observer or authored diagnostic return probe, never a supplied
    // alliance decision. The actual recovered predicate always runs first.
    std::function<void(const void*,const void*,const void*,bool)> afterAlliance;
};
inline RadarColorActor radarColorActor(const RadarColorWorld& w,const void* p){
    if(!p||!w.actor)throw std::invalid_argument("Missing radar actor view");
    auto a=w.actor(p);
    if(a.kind!=RadarColorActorKind::infantry&&a.kind!=RadarColorActorKind::building)
        throw std::invalid_argument("Unsupported radar actor class");
    return a;
}
// Complete41B410, shared by both verified stock classes.
inline std::uint8_t actorRadarColorFlag(const void* p,const RadarColorWorld& w){return radarColorActor(w,p).byte170;}
// Actual4E5540 reuses the existing recovered predicate. Preserve its null and
// same-identity shortcuts without querying fields which the original skips.
inline bool radarColorAllied(const void* self,const void* other,const RadarColorWorld& w){
    if(!other)return unitOwnerAlliedToCurrent(false,false,0,0,0);
    if(self==other)return unitOwnerAlliedToCurrent(true,true,0,0,0);
    if(!self||!w.house)throw std::invalid_argument("Missing radar House view");
    const auto b=w.house(other);const auto currentIndex=b.index30;
    const auto a=w.house(self);const auto ownerIndex=a.index30;
    const auto mask=ownerIndex!=currentIndex&&currentIndex!=-1?a.allies5674:0u;
    return unitOwnerAlliedToCurrent(true,false,ownerIndex,currentIndex,mask);
}
// Complete Infantry509270 or Building41B2E0, selected by an explicit stock
// association. Building ignores all fields/arguments and returns null. Infantry
// always checks alliance before inspecting the argument's low byte, then reads
// the chosen owner/alternate/current fields late, after that child returns.
inline const void* actorRadarColorHouse(const void* p,std::uint32_t argument,const RadarColorWorld& w){
    const auto a=radarColorActor(w,p);
    if(a.kind==RadarColorActorKind::building)return nullptr;
    const auto savedCurrent=w.currentA35DB4;
    if(!a.owner1B4)throw std::invalid_argument("Missing radar actor Owner field");
    const auto owner=a.owner1B4();
    const auto allied=radarColorAllied(owner,savedCurrent,w);
    if(w.afterAlliance)w.afterAlliance(p,owner,savedCurrent,allied);
    if(allied&&std::uint8_t(argument)==0)return a.owner1B4();
    if(!a.alternate410)throw std::invalid_argument("Missing radar alternate House field");
    const auto alternate=a.alternate410();return alternate?alternate:w.currentA35DB4;
}
struct ActorRadarColorProbes {
    std::function<void(const void*,std::uint8_t)> flag;
    std::function<void(const void*,std::uint32_t,const void*)> house;
};
// Explicit C0/CC binding below the existing mark kernel; startup/kind association
// is supplied. No owner/House query occurs on construction; callbacks restore.
class ActorRadarColorBinding {
    SurfaceMarkServices& marks_;
    decltype(SurfaceMarkServices::actorC0) flag_;
    decltype(SurfaceMarkServices::actorCC) house_;
public:
    ActorRadarColorBinding(SurfaceMarkServices& marks,const RadarColorWorld& world,
            const ActorRadarColorProbes& probes):marks_(marks){
        decltype(flag_) flag=[&world,&probes](const void* p){
            const auto result=actorRadarColorFlag(p,world);if(probes.flag)probes.flag(p,result);return result;
        };
        decltype(house_) house=[&world,&probes](const void* p,std::uint32_t arg){
            const auto result=actorRadarColorHouse(p,arg,world);if(probes.house)probes.house(p,arg,result);return result;
        };
        flag_=std::move(marks_.actorC0);house_=std::move(marks_.actorCC);
        marks_.actorC0=std::move(flag);marks_.actorCC=std::move(house);
    }
    ~ActorRadarColorBinding(){marks_.actorC0=std::move(flag_);marks_.actorCC=std::move(house_);}
    ActorRadarColorBinding(const ActorRadarColorBinding&)=delete;
    ActorRadarColorBinding& operator=(const ActorRadarColorBinding&)=delete;
    ActorRadarColorBinding(ActorRadarColorBinding&&)=delete;
    ActorRadarColorBinding& operator=(ActorRadarColorBinding&&)=delete;
};
}
