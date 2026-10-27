// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTagObjectExpiration.hpp"
#include <array>
#include <iostream>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::runtime_error("Mission Tag expiration composition differs");}
void exercise(std::int32_t persistence) {
    std::int32_t instances=1,otherInstances=0;std::uint8_t executing=0,otherExecuting=0;
    MissionTagType type{persistence},otherType{persistence};auto* typePointer=&type;auto* otherTypePointer=&otherType;
    MissionTagTrigger* first=nullptr;MissionTagTrigger* none=nullptr;
    MissionTagState tag{typePointer,first,instances,executing},other{otherTypePointer,none,otherInstances,otherExecuting};
    std::int32_t eventKind=4,eventValue=0,countryIndex=0,frame=0,timerPadding=0;std::uint8_t destroyed=0,enabled=1,suppress=0;
    MissionTriggerEvent* noEvent=nullptr;MissionTriggerEvent event{eventKind,eventValue,noEvent};MissionTriggerAction* noAction=nullptr;MissionTriggerAction action{noAction};
    MissionTriggerCountry country{countryIndex};MissionTriggerType triggerType{&country,&event,&action};auto* triggerTypePointer=&triggerType;
    MissionEventTimer timer{};std::uint32_t occurred=0;MissionTriggerState triggerState{triggerTypePointer,destroyed,enabled,timer,timerPadding,occurred};
    MissionTriggerServices triggerServices{frame,suppress};triggerServices.resolveHouse=[](auto){return static_cast<const void*>(nullptr);};
    triggerServices.resetPadding=[] {return 17;};triggerServices.executeAction=[](auto&,auto,auto,auto&,auto&){return std::uint8_t(1);};
    MissionTagTrigger* next=nullptr;MissionTagTrigger trigger{triggerState,triggerServices,next};first=&trigger;
    std::array<const void*,8> deferredBacking{};std::span<const void*> deferredSlots=deferredBacking;std::int32_t capacity=8,count=0,growth=2;std::uint8_t owns=1;
    MissionDeferredDelete deferred{capacity,owns,count,growth,deferredSlots,{}};std::uint32_t empty=0x7fff7fff;
    MissionTagState* cellTag=nullptr;MissionTagServices base{deferred,empty};base.cellTag=[&](auto)->MissionTagState*&{return cellTag;};
    int objectIdentity=0;MissionTagState* objectTag=&tag;const void* objectLink=&tag;const void* tagNext=&other;
    MissionTagObjectReferences object{objectTag,objectLink,&objectIdentity};MissionTagExpiredAbstract expired{tag,&tag,tagNext};
    auto recipient=bindMissionTagObjectExpiration(object,expired);std::array<MissionTagExpirationRecipient*,1> recipientBacking{&recipient};
    std::span<MissionTagExpirationRecipient*> recipientSlots=recipientBacking;std::int32_t recipientCount=1;int recipientIdentity=0;
    MissionExpirationVector<MissionTagExpirationRecipient*> recipients{recipientCount,recipientSlots,&recipientIdentity};
    std::array<std::uint32_t,1> pointBacking{};std::span<std::uint32_t> pointSlots=pointBacking;std::int32_t pointCount=0;int pointIdentity=0;
    MissionExpirationVector<std::uint32_t> points{pointCount,pointSlots,&pointIdentity};
    std::array<const void*,1> tagBacking{};std::span<const void*> tagSlots=tagBacking;std::int32_t mapCount=0,logicCount=0;int mapIdentity=0,logicIdentity=0;
    MissionExpirationVector<const void*> mapTags{mapCount,tagSlots,&mapIdentity},logicTags{logicCount,tagSlots,&logicIdentity};
    std::uint32_t fallbackPoint=0;MissionTagState* fallbackTag=nullptr;const void* fallbackA=nullptr;const void* fallbackB=nullptr;const void* fallbackContent=nullptr;int fallbackIdentity=0;
    MissionExpirationCell fallback{fallbackPoint,fallbackTag,fallbackA,fallbackB,fallbackContent,&fallbackIdentity};std::array<MissionExpirationCell*,1> cells{nullptr};
    MissionTagExpirationMap map{points,mapTags,cells,fallback,{}};const void* global0=nullptr;const void* global1=nullptr;
    MissionTagExpirationServices expiration{global0,global1,recipients,map,logicTags};expiration.abstractType=[](auto&){return false;};
    MissionTagOwner owner{objectTag,&objectIdentity};
    require(raiseMissionTagEventWithExpiration(tag,{4,&objectIdentity,1,0,nullptr},&owner,empty,base,expiration));
    require(destroyed==1&&executing==0&&instances==0&&objectTag==nullptr&&objectLink==tagNext&&count==2);
    require(deferredBacking[0]==&trigger&&deferredBacking[1]==&tag);
}
}
int main(){try{exercise(1);exercise(0);std::cout<<"mission tag expiration world PASS\n";return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
