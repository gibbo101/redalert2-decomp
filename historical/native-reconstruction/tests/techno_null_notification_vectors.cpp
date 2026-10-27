// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoNullNotification.hpp"
#include "sim/MissionTag.hpp"
#include "render/RadarMapNotification.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Null notification fixture differs");}
void run(std::istream& in){
 std::array<std::int32_t,14> f{};for(auto& v:f)require(bool(in>>v));std::string extra;require(!(in>>extra));
 require(f[0]>=0&&f[0]<=3&&f[2]>=0&&f[2]<=1&&f[13]>=0&&f[13]<=1);for(auto i:{1,3,4,5,10,11})require(f[i]>=0&&f[i]<=255);require(f[0]!=2||f[12]!=7);
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
 int actor=0,type=0;std::array<std::uint32_t,2> counts{std::uint32_t(f[7]),std::uint32_t(f[7])};
 std::uint8_t onMap=f[1],executing=f[3],enabled=f[4],destroyed=f[5],dirty=f[10],full=f[11],suppress=f[1];std::int32_t persistence=f[6],instances=4,frame=0,countryIndex=-9,kind=7,value=1,padding=-91;std::uint32_t occurred=0,empty=0x7fff7fff;
 RadarMapNotificationView map{f[8],f[9],dirty,full};
 MissionTriggerEvent* eventNext=nullptr;MissionTriggerEvent missionEvent{kind,value,eventNext};MissionTriggerEvent* firstEvent=&missionEvent;MissionTriggerAction* noAction=nullptr;
 MissionTriggerCountry country{countryIndex};MissionTriggerCountry* countryPtr=&country;MissionTriggerType triggerType{countryPtr,firstEvent,noAction};MissionTriggerType* triggerTypePtr=&triggerType;
 MissionEventTimer timer{-1,0};MissionTriggerState trigger{triggerTypePtr,destroyed,enabled,timer,padding,occurred};MissionTriggerServices triggerServices{frame,suppress};
 triggerServices.resolveHouse=[&](auto i)->const void*{require(i==-9);event(7,std::uint32_t(i));return nullptr;};
 triggerServices.event=[&](const auto&,const void* h,const auto& pulse){require(!h&&pulse.object==&actor);event(8,std::uint32_t(pulse.kind));};
 MissionTagTrigger* next=nullptr;MissionTagTrigger node{trigger,triggerServices,next};MissionTagTrigger* first=&node;MissionTagType tagType{persistence};MissionTagType* tagTypePtr=&tagType;MissionTagState tag{tagTypePtr,first,instances,executing};MissionTagState* actorTag=f[2]?&tag:nullptr;
 int capacity=0,count=0,growth=0;std::uint8_t owns=0;std::span<const void*> slots;MissionDeferredDelete deferred{capacity,owns,count,growth,slots};MissionTagServices tagServices{deferred,empty};
 tagServices.store=[&](const void* p,auto off,auto v,const void* ptr){require(p==&tag&&!ptr&&off==0x35);event(5,30,std::uint32_t(off),v);};
 const auto putMap=[&](auto off,auto v){event(5,40,std::uint32_t(off),v);};
 const auto queryMap=[&]{event(9);return std::uint32_t(radarMapNotificationMode(map));};const auto markMap=[&](std::uint32_t arg){event(10,arg);requestRadarMapNotification(map,arg,putMap);};
 TechnoNullNotificationActor a{&actor,onMap,[&]()->const void*{return actorTag;},[&]()->const void*{return &counts[f[13]];}};
 TechnoNullNotificationServices s{empty};s.type80=[&]()->const void*{event(1);return &type;};s.cost84=[&](const void* t,const void* h){require(t==&type&&h==&counts[f[13]]);event(2,f[13]+1);return std::uint32_t(f[12]);};s.kind2C=[&]{event(3);return 15;};
 s.raiseTag=[&](const void* p,auto pulse,const void* object,auto location){require(p==&tag&&object==&actor&&location==empty);event(4,std::uint32_t(pulse));MissionTagOwner owner{actorTag,&actor};raiseMissionTagEvent(tag,{pulse,&actor,0,0,nullptr},&owner,location,tagServices);};
 s.house5360=[&](const void* p)->std::uint32_t&{require(p==&counts[f[13]]);return counts[f[13]];};s.map6331A0=queryMap;s.map6331E0=markMap;s.store=[&](const void* p,auto off,auto v){require(p==&counts[f[13]]);event(5,f[13]+1,std::uint32_t(off),v);};
 std::uint32_t result=0;
 switch(f[0]){case 0:notifyTechnoNullAttacker(a,s);break;case 1:markMap(std::uint32_t(f[12]));break;case 2:event(8,std::uint32_t(f[12]));result=missionEventOccurred(7,1,f[12],suppress,0,&timer,{});break;case 3:result=queryMap();break;}
 std::cout<<"F "<<result<<' '<<counts[0]<<' '<<counts[1]<<' '<<unsigned(executing)<<' '<<unsigned(dirty)<<' '<<unsigned(full)<<' '<<occurred<<'\n';
}
void guards(){
 const auto refused=[&](auto fn){bool failed=false;try{fn();}catch(const std::invalid_argument&){failed=true;}require(failed);};
 require(!missionEventOccurred(7,1,48,0,0,nullptr,{})&&!missionEventOccurred(7,1,29,255,0,nullptr,{}));refused([&]{missionEventOccurred(7,1,7,0,0,nullptr,{});});
 int object=0;std::uint8_t on=0;std::uint32_t empty=0,count=~0u;TechnoNullNotificationActor a{&object,on,{},[&]{return &object;}};TechnoNullNotificationServices s{empty};refused([&]{notifyTechnoNullAttacker(a,s);});
 s.type80=[&]{return &object;};s.cost84=[](auto,auto){return 9u;};s.kind2C=[]{return 15;};s.house5360=[&](auto)->std::uint32_t&{return count;};s.map6331A0=[]{return 0x100u;};notifyTechnoNullAttacker(a,s);require(count==0);s.map6331A0=[]{return 0x101u;};refused([&]{notifyTechnoNullAttacker(a,s);});require(count==1);
 on=1;refused([&]{notifyTechnoNullAttacker(a,s);});
 std::cout<<"Techno null notification guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
