// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseAllianceNotification.hpp"
#include "sim/HouseMakeAlly.hpp"
#include "sim/HouseMakeEnemy.hpp"
namespace ra2 {
// Scoped borrowed composition. All three worlds must name the same owners.
// Stable lifetime and fresh per-entry scratch are supplied by the caller; this
// does not implement startup, effect services or an original frame scheduler.
class HouseDiplomacy {
    HouseAllianceNotificationWorld& notification_;
    HouseMakeAllyWorld& ally_;
    const HouseMakeEnemyWorld& enemy_;
    std::function<TargetReference()> scratch_;
    std::function<void()> priorNotification_;
    std::function<void(const void*,const void*,std::uint8_t)> priorAlly_,priorEnemy_;
public:
    // Nonmutating entry telemetry; not a gameplay service.
    std::function<void(char,const void*,const void*)> entered;
    HouseDiplomacy(HouseAllianceNotificationWorld& notification,HouseMakeAllyWorld& ally,
            const HouseMakeEnemyWorld& enemy,std::function<TargetReference()> scratch)
        :notification_(notification),ally_(ally),enemy_(enemy),scratch_(std::move(scratch)){
        if(!scratch_)throw std::invalid_argument("House diplomacy needs per-entry scratch");
        // Build closures before modifying owners, so allocation failure cannot
        // leave a partially installed binding referring to this object.
        std::function<void()> notify=[this]{this->notify();};
        std::function<void(const void*,const void*,std::uint8_t)> a=[this](auto self,auto other,auto announce){
            auto token=scratch_();makeAlly(self,other,announce,token);
        };
        std::function<void(const void*,const void*,std::uint8_t)> e=[this](auto self,auto other,auto announce){makeEnemy(self,other,announce);};
        priorNotification_=std::move(ally_.allianceNotification);
        priorAlly_=std::move(notification_.makeAlly);priorEnemy_=std::move(notification_.makeEnemy);
        ally_.allianceNotification=std::move(notify);notification_.makeAlly=std::move(a);notification_.makeEnemy=std::move(e);
    }
    ~HouseDiplomacy(){
        ally_.allianceNotification=std::move(priorNotification_);
        notification_.makeAlly=std::move(priorAlly_);notification_.makeEnemy=std::move(priorEnemy_);
    }
    HouseDiplomacy(const HouseDiplomacy&)=delete;HouseDiplomacy& operator=(const HouseDiplomacy&)=delete;
    HouseDiplomacy(HouseDiplomacy&&)=delete;HouseDiplomacy& operator=(HouseDiplomacy&&)=delete;
    void notify(){if(entered)entered('N',nullptr,nullptr);notifyHouseAlliances(notification_);}
    void makeAlly(const void* self,const void* other,std::uint8_t announce,TargetReference& scratch){
        if(entered)entered('A',self,other);makeHouseAlly(self,other,announce,scratch,ally_);
    }
    void makeEnemy(const void* self,const void* other,std::uint8_t announce){
        if(entered)entered('E',self,other);makeHouseEnemy(self,other,announce,enemy_);
    }
};
}
