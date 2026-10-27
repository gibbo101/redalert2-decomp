// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseAlliance.hpp"
#include "sim/HouseThreat.hpp"
#include "sim/TargetReference.hpp"
#include "sim/MissionTextAction.hpp"
namespace ra2 {
struct HouseMakeAllyFields {
    std::uint32_t& mask120;
    const std::uint8_t& flag134;
    const std::uint8_t& flag135;
    std::uint32_t& allies5674;
};
struct HouseMakeAllyActor {const std::uint8_t& flag76;const void* const& target228;};
struct HouseMakeAllyRules {const std::uint8_t& flag1424;const double& messageDelay1128;};
struct HouseMakeAllyWorld {
    const HouseAllianceWorld& alliance;
    const HouseThreatWorld& threat;
    const TargetReferenceWorld& targets;
    const std::int32_t& actorCount;
    const std::span<const void*>& actors;
    const void* const& currentHouse;
    const std::int32_t& quietA3D548;
    // Pure views over the same House/actor/rules owners as the three kernels.
    std::function<HouseMakeAllyFields(const void*)> house;
    std::function<HouseMakeAllyActor(const void*)> actor;
    std::function<HouseMakeAllyRules()> rules;
    // Named service boundaries. Bind actual recovered children on production
    // owners before adoption; a missing entered effect must never be a no-op.
    std::function<void(bool)> mapSight;
    std::function<void(const void*)> rebuildGrid;
    std::function<void()> allianceNotification;
    std::function<std::int32_t(const void*)> country38;
    std::function<const void*(const void*)> owner3C;
    std::function<void(const void*)> clear370;
    // Localize6F9EC0 then format783764. Names are stable House-owned identities;
    // the child adapters supply the inline+15F16 addresses without copying names.
    std::function<const void*()> localizeNotice;
    std::function<const void*(const void*,const void*,const void*)> formatNotice;
    std::function<void(const void*,std::int32_t,std::uint32_t)> displayNotice;
    std::function<std::int32_t(const void*)> colorC0;
    // Exact original speech key VA supplied as a semantic token, never read here.
    std::function<void(std::uint32_t)> speech;
    std::function<void()> redraw0;
};
template<class F>inline void requireHouseMakeAllyService(const F& f){
    if(!f)throw std::invalid_argument("House MakeAlly needs an entered service");
}
inline bool houseMakeAllyLocal(const void* p,const HouseMakeAllyWorld& w){
    requireHouseMakeAllyService(w.house);const auto h=w.house(p);
    return w.alliance.mode?h.flag134!=0:bool(h.flag134||h.flag135);
}
// Inline identity/index/alliance predicate used by4E5660, distinct from the
// mode-dependent local predicate and from CanMakeAlly eligibility.
inline bool houseMakeAllyAllied(const void* self,const void* other,const HouseMakeAllyWorld& w){
    if(!other)return false;
    if(self==other)return true;
    const auto a=houseAllianceRecord(w.alliance,self),b=houseAllianceRecord(w.alliance,other);
    if(a.index30==b.index30)return true;
    return b.index30!=-1&&(a.allies5674&(std::uint32_t(1)<<(std::uint32_t(b.index30)&31u)));
}
// Complete4E5660 orchestration. Scratch is the caller's single reused token;
// initial padding/association are supplied, not an original stack constructor.
inline void makeHouseAlly(const void* current,const void* target,std::uint8_t announce,
        TargetReference& scratch,const HouseMakeAllyWorld& w){
    if(!canMakeHouseAlliance(current,target,w.alliance))return;
    requireHouseMakeAllyService(w.house);const auto self=w.house(current);
    requireHouseMakeAllyService(w.mapSight);w.mapSight(false);
    const auto targetIndex=[&]{return houseAllianceRecord(w.alliance,target).index30;};
    self.allies5674|=std::uint32_t(1)<<(std::uint32_t(targetIndex())&31u);
    requireHouseMakeAllyService(w.rebuildGrid);w.rebuildGrid(current);
    const auto threat=houseThreatHouse(w.threat,current);
    const auto count=threat.count5504;
    if(count>0){
        const auto entries=threat.scores54F8;
        for(std::int32_t i=0;i<count;++i){
            const auto& entry=houseThreatScoreAt(entries,i);
            if(entry.house==target){
                const auto delta=std::bit_cast<std::int32_t>(0u-std::uint32_t(entry.value));
                updateHouseThreatScore(current,delta,target,w.threat);break;
            }
        }
    }
    if(threat.enemy54F0==targetIndex())threat.enemy54F0=-1;
    if(w.alliance.unrestricted)self.mask120|=std::uint32_t(1)<<(std::uint32_t(targetIndex())&31u);
    if(w.alliance.mode!=4&&w.alliance.unrestricted){w.mapSight(true);return;}
    if(houseMakeAllyLocal(current,w)){
        requireHouseMakeAllyService(w.rules);
        if(w.rules().flag1424&&!houseAllianceType(w.alliance,houseAllianceRecord(w.alliance,target).type34).passive1A6&&w.alliance.mode){
            requireHouseMakeAllyService(w.allianceNotification);w.allianceNotification();
        }
    }
    // Unlike the sight scans, this loop rereads both count and backing after
    // each slot, including callbacks on rejected/non-Techno objects.
    for(std::int32_t i=0;i<w.actorCount;++i){
        if(std::size_t(i)>=w.actors.size())throw std::invalid_argument("House MakeAlly actor backing too small");
        const auto p=w.actors[std::size_t(i)];if(!p||!castTargetTechno(p,w.targets))continue;
        requireHouseMakeAllyService(w.actor);const auto actor=w.actor(p);if(actor.flag76)continue;
        requireHouseMakeAllyService(w.country38);
        if(w.country38(p)!=houseAllianceRecord(w.alliance,current).index30)continue;
        makeTargetReference(scratch,actor.target228,w.targets);
        if(!scratch.tag||!resolveTargetReference(scratch,w.targets))continue;
        const auto resolved=resolveTargetReference(scratch,w.targets);if(!resolved)continue;
        requireHouseMakeAllyService(w.owner3C);const auto owner=w.owner3C(resolved);
        if(houseMakeAllyAllied(current,owner,w)){
            requireHouseMakeAllyService(w.clear370);w.clear370(p);
        }
    }
    if(houseMakeAllyLocal(current,w)&&w.alliance.mode&&
       !houseAllianceType(w.alliance,houseAllianceRecord(w.alliance,target).type34).passive1A6){
        requireHouseMakeAllyService(w.localizeNotice);const auto localized=w.localizeNotice();
        requireHouseMakeAllyService(w.formatNotice);const auto text=w.formatNotice(localized,current,target);
        requireHouseMakeAllyService(w.rules);const auto duration=missionTextDuration(w.rules().messageDelay1128);
        requireHouseMakeAllyService(w.colorC0);const auto color=w.colorC0(houseAllianceRecord(w.alliance,current).type34);
        requireHouseMakeAllyService(w.displayNotice);w.displayNotice(text,color,duration);
        if(announce){
            std::uint32_t key=0;
            if(houseMakeAllyAllied(target,current,w)){
                if(!w.quietA3D548){
                    key=houseMakeAllyAllied(w.currentHouse,target,w)&&houseMakeAllyAllied(w.currentHouse,current,w)?0x7da314u:0x7da2fcu;
                }
            }else if(w.alliance.mode){
                if(current==w.currentHouse)key=0x7da2e4u;
                else if(target==w.currentHouse)key=0x7da2ccu;
            }else{
                if(houseMakeAllyLocal(current,w))key=0x7da2e4u;
                else if(houseMakeAllyLocal(target,w))key=0x7da2ccu;
            }
            if(key){requireHouseMakeAllyService(w.speech);w.speech(key);}
        }
    }
    requireHouseMakeAllyService(w.redraw0);w.redraw0();w.mapSight(true);
}
}
