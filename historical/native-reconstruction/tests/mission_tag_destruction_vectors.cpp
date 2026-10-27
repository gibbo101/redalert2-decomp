// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTagDestruction.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission Tag destruction fixture outside domain");}
struct Input {std::int32_t instances=0,qcount=0,first=0,next2=0,next3=0;std::array<int,8> q{};std::array<std::int32_t,3> rcount{};std::array<std::array<int,6>,3> r{};};
Input parse(std::istream& in){Input f;char op;require(bool(in>>op)&&op=='D');require(bool(in>>f.instances>>f.qcount));require(f.qcount>=0&&f.qcount<=8);for(auto& x:f.q){require(bool(in>>x));require(x>=0&&x<=4);}require(bool(in>>f.first>>f.next2>>f.next3));require(f.first==0||f.first==2||f.first==3);require(f.next2>=0&&f.next2<=3&&f.next3>=0&&f.next3<=3);require(f.next2!=2&&f.next3!=3);if(f.first==2)require(f.next2!=2&&(f.next2!=3||f.next3==0));if(f.first==3)require(f.next3!=3&&(f.next3!=2||f.next2==0));for(int j=0;j<3;++j){require(bool(in>>f.rcount[j]));require(f.rcount[j]>=0&&f.rcount[j]<=6);for(auto& x:f.r[j]){require(bool(in>>x));require(x>=0&&x<=3);}}std::string extra;require(!(in>>extra));return f;}
void run(std::istream& in){auto f=parse(in);std::int32_t persistence=0;std::uint8_t executing=0,session=0;MissionTagType type{persistence};auto* typePointer=&type;
    std::int32_t frame=0,padding=0,countryIndex=0;std::uint8_t destroyed=0,enabled=0,suppress=0;std::uint32_t occurred=0;MissionTriggerCountry country{countryIndex};
    MissionTriggerEvent* event=nullptr;MissionTriggerAction* action=nullptr;MissionTriggerType triggerType{&country,event,action};auto* triggerTypePointer=&triggerType;MissionEventTimer timer{};
    MissionTriggerState state2{triggerTypePointer,destroyed,enabled,timer,padding,occurred},state3{triggerTypePointer,destroyed,enabled,timer,padding,occurred};MissionTriggerServices services2{frame,suppress},services3{frame,suppress};
    MissionTagTrigger* next2=nullptr;MissionTagTrigger* next3=nullptr;MissionTagTrigger trigger2{state2,services2,next2},trigger3{state3,services3,next3};
    auto trigger=[&](int id)->MissionTagTrigger*{return id==2?&trigger2:id==3?&trigger3:nullptr;};next2=trigger(f.next2);next3=trigger(f.next3);MissionTagTrigger* first=trigger(f.first);MissionTagState tag{typePointer,first,f.instances,executing};
    int releaseZero=0;std::int32_t capacity=12,growth=1;std::uint8_t owns=1;std::array<const void*,12> qback{};std::span<const void*> qslots=qback;MissionDeferredDelete queue{capacity,owns,f.qcount,growth,qslots,{}};
    auto pointer=[&](int id)->const void*{if(id==1)return &tag;if(id==2)return &trigger2;if(id==3)return &trigger3;if(id==4)return &releaseZero;return nullptr;};
    for(std::size_t i=0;i<f.q.size();++i)qback[i]=pointer(f.q[i]);std::array<std::array<const void*,8>,3> rback{};std::array<std::span<const void*>,3> rslots{rback[0],rback[1],rback[2]};int ridentities[3]{};
    std::array<MissionExpirationVector<const void*>,3> registries{{{f.rcount[0],rslots[0],&ridentities[0]},{f.rcount[1],rslots[1],&ridentities[1]},{f.rcount[2],rslots[2],&ridentities[2]}}};for(int j=0;j<3;++j)for(int i=0;i<6;++i)rback[j][i]=pointer(f.r[j][i]);
    auto id=[&](const void* p){if(!p)return 0;if(p==&tag)return 1;if(p==&trigger2)return 2;if(p==&trigger3)return 3;if(p==&releaseZero)return 4;if(p==&queue)return 40;for(int j=0;j<3;++j)if(p==&ridentities[j])return 50+j;throw std::invalid_argument("Unknown destruction identity");};
    MissionTagStore store=[&](const void* p,auto off,auto value,const void* pv){std::cout<<"W "<<id(p)<<' '<<off<<' '<<(pv?id(pv):int(value))<<' ';};
    MissionTagDestructionServices destruction{queue,{&registries[0],&registries[1],&registries[2]},{},{},{},store,session};
    destruction.expire=[&](auto& subject,auto removed){require(&subject==&tag&&removed==1);std::cout<<"N 1 ";};destruction.destroyBase=[&](auto& subject){require(&subject==&tag);std::cout<<"B 1 ";};destruction.freeRecord=[&](auto& subject){require(&subject==&tag);std::cout<<"F 1 ";};
    auto tagRecord=bindMissionTagDestruction(tag,destruction);auto active=[&](const void* identity){MissionDeferredCleanupRecord r{};r.identity=identity;r.inactive=[] {return false;};return r;};auto a2=active(&trigger2),a3=active(&trigger3);MissionDeferredCleanupRecord zero{};zero.identity=&releaseZero;zero.inactive=[] {return true;};zero.release=[] {return std::uint32_t(0);};
    MissionDeferredCleanupServices cleanup{queue};cleanup.store=store;cleanup.resolve=[&](const void* p)->MissionDeferredCleanupRecord&{if(p==&tag)return tagRecord;if(p==&trigger2)return a2;if(p==&trigger3)return a3;if(p==&releaseZero)return zero;throw std::invalid_argument("Unknown deferred record");};
    drainMissionDeferredCleanup(cleanup);std::cout<<"state "<<f.instances<<' '<<f.qcount;for(auto* p:qback)std::cout<<' '<<id(p);for(int j=0;j<3;++j){std::cout<<' '<<f.rcount[j];for(auto* p:rback[j])std::cout<<' '<<id(p);}std::cout<<'\n';
}
void guards(){
    std::int32_t persistence=0,instances=0,capacity=2,count=1,growth=1;std::uint8_t executing=0,owns=1,session=0;
    MissionTagType type{persistence};auto* typePointer=&type;MissionTagTrigger* first=nullptr;MissionTagState tag{typePointer,first,instances,executing};
    std::array<const void*,2> backing{&tag,nullptr};std::span<const void*> slots=backing;MissionDeferredDelete q{capacity,owns,count,growth,slots,{}};
    MissionDeferredCleanupServices missing{q};bool refused=false;try{drainMissionDeferredCleanup(missing);}catch(const std::invalid_argument&){refused=true;}require(refused&&count==1);
    std::array<std::array<const void*,1>,3> registryBacking{};std::array<std::span<const void*>,3> registrySlots{registryBacking[0],registryBacking[1],registryBacking[2]};std::array<std::int32_t,3> registryCounts{};int registryIdentity[3]{};
    std::array<MissionExpirationVector<const void*>,3> registries{{{registryCounts[0],registrySlots[0],&registryIdentity[0]},{registryCounts[1],registrySlots[1],&registryIdentity[1]},{registryCounts[2],registrySlots[2],&registryIdentity[2]}}};
    std::int32_t recipientCount=0,pointCount=0,mapTagCount=0,logicCount=0;std::array<MissionTagExpirationRecipient*,1> recipientBacking{};std::span<MissionTagExpirationRecipient*> recipientSlots=recipientBacking;int recipientIdentity=0;
    MissionExpirationVector<MissionTagExpirationRecipient*> recipients{recipientCount,recipientSlots,&recipientIdentity};std::array<std::uint32_t,1> pointBacking{};std::span<std::uint32_t> pointSlots=pointBacking;int pointIdentity=0;
    MissionExpirationVector<std::uint32_t> points{pointCount,pointSlots,&pointIdentity};std::array<const void*,1> tagBacking{};std::span<const void*> tagSlots=tagBacking;int mapIdentity=0,logicIdentity=0;
    MissionExpirationVector<const void*> mapTags{mapTagCount,tagSlots,&mapIdentity},logicTags{logicCount,tagSlots,&logicIdentity};std::uint32_t fallbackPoint=0;MissionTagState* fallbackTag=nullptr;const void* fallbackA=nullptr;const void* fallbackB=nullptr;const void* fallbackContent=nullptr;int fallbackIdentity=0;
    MissionExpirationCell fallback{fallbackPoint,fallbackTag,fallbackA,fallbackB,fallbackContent,&fallbackIdentity};std::array<MissionExpirationCell*,1> cells{nullptr};MissionTagExpirationMap map{points,mapTags,cells,fallback,{}};const void* global0=nullptr;const void* global1=nullptr;
    MissionTagExpirationServices expiration{global0,global1,recipients,map,logicTags};expiration.abstractType=[](auto&){return false;};
    int expired=0,base=0,freed=0;MissionTagDestructionServices destruction{q,{&registries[0],&registries[1],&registries[2]},{},{},{},{},session};
    destruction.expire=[&](auto& subject,auto removed){++expired;broadcastMissionTagExpiration(subject,removed,expiration);};destruction.destroyBase=[&](auto&){++base;};destruction.freeRecord=[&](auto&){++freed;};
    session=1;refused=false;try{destroyMissionTag(tag,1,destruction);}catch(const std::invalid_argument&){refused=true;}require(refused&&expired==1&&base==0&&freed==0);
    session=0;count=1;backing[0]=&tag;auto record=bindMissionTagDestruction(tag,destruction);MissionDeferredCleanupServices cleanup{q};cleanup.resolve=[&](auto)->MissionDeferredCleanupRecord&{return record;};drainMissionDeferredCleanup(cleanup);
    require(count==0&&expired==3&&base==1&&freed==1);std::cout<<"mission tag destruction guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
