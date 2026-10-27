// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WaypointTaggedDiscovery.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Tagged Infantry discovery fixture differs");}
void run(std::istream& in){
 std::array<int,19> f{};for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[2]>=0&&f[2]<2&&f[3]>=0&&f[3]<2&&f[4]>=-1&&f[4]<2&&f[11]>=0&&f[11]<=1);for(int i:{5,6,7,10,12,13,14,16,17})require(f[i]>=0&&f[i]<=255);require(f[18]==-9||f[18]==13||f[18]==19);
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
 int object=0;UnitDiscoveryActor a;a.owner=f[3];a.field372=f[5];a.current373=f[6];a.other374=f[7];a.mission98=f[8];a.queuedA0=f[9];a.queuedA4=f[10];a.hasTag=f[11];
 UnitDiscoveryWorld world;world.mode=f[0];world.loading=f[1];world.currentHouse=f[2];world.tagContext=0x7fff7fff;
 for(int i=0;i<2;++i){auto& h=world.houses[i];h.human134=f[16];h.control135=f[17];h.discovered13c=128;h.field5668=129;h.field5669=130;}
 world.trace=[&](char k,int v){event(k=='d'?1:k=='b'?2:k=='h'?3:k=='g'?4:9,k=='d'||k=='b'||k=='h'?std::uint32_t(v+1):std::uint32_t(v));};
 world.store=[&](int subject,int off,std::uint32_t v){event(6,subject,std::uint32_t(off),v);};
 std::uint8_t executing=f[12],enabled=f[13],destroyed=f[14],suppress=0;std::int32_t persistence=f[15],instances=4,frame=0,countryIndex=f[18],kind=7,value=1,padding=-91;std::uint32_t occurred=0,empty=0x7fff7fff;
 MissionTriggerEvent* eventNext=nullptr;MissionTriggerEvent missionEvent{kind,value,eventNext};MissionTriggerEvent* firstEvent=&missionEvent;MissionTriggerAction* noAction=nullptr;
 MissionTriggerCountry country{countryIndex};MissionTriggerCountry* countryPtr=&country;MissionTriggerType triggerType{countryPtr,firstEvent,noAction};MissionTriggerType* triggerTypePtr=&triggerType;
 MissionEventTimer timer{-1,0};MissionTriggerState trigger{triggerTypePtr,destroyed,enabled,timer,padding,occurred};MissionTriggerServices triggerServices{frame,suppress};
 triggerServices.resolveHouse=[&](int country)->const void*{event(7,std::uint32_t(country));return country==13?&world.houses.at(0):country==19?&world.houses.at(1):nullptr;};
 triggerServices.event=[&](const auto&,const void* h,const auto& pulse){require(pulse.kind==4&&pulse.object==&object&&h==(f[18]==13?&world.houses.at(0):f[18]==19?&world.houses.at(1):nullptr));event(8,4);};
 MissionTagTrigger* next=nullptr;MissionTagTrigger node{trigger,triggerServices,next};MissionTagTrigger* first=&node;MissionTagType tagType{persistence};MissionTagType* tagTypePtr=&tagType;MissionTagState tag{tagTypePtr,first,instances,executing};MissionTagState* actorTag=f[11]?&tag:nullptr;
 int capacity=0,count=0,growth=0;std::uint8_t owns=0;std::span<const void*> slots;MissionDeferredDelete deferred{capacity,owns,count,growth,slots};MissionTagServices tagServices{deferred,empty};
 tagServices.store=[&](const void* p,auto off,auto v,const void* ptr){require(p==&tag&&!ptr&&off==0x35);event(6,30,std::uint32_t(off),v);};
 for(int i=0;i<2;++i){
  const WaypointTaggedDiscoveryBinding binding{{0,&a,nullptr},actorTag,&object};
  bool result=discoverWaypointTaggedResident(0,f[4],world,std::span(&binding,1),tagServices,[&]{event(5,4);});event(10,result);
 }
 std::cout<<"F "<<unsigned(a.current373)<<' '<<unsigned(a.other374)<<' '<<std::uint32_t(a.queuedA0)<<' '<<unsigned(a.queuedA4)<<' ';
 for(const auto& [id,h]:world.houses)std::cout<<unsigned(h.discovered13c)<<' '<<unsigned(h.field5668)<<' '<<unsigned(h.field5669)<<' ';
 std::cout<<unsigned(executing)<<' '<<instances<<' '<<occurred<<'\n';
}
void guards(){UnitDiscoveryWorld w;UnitDiscoveryActor a;int id=0;MissionTagState* tag=nullptr;std::uint32_t empty=0;int n=0,c=0,g=0;std::uint8_t allocated=0;std::span<const void*> b;MissionDeferredDelete d{c,allocated,n,g,b};MissionTagServices s{d,empty};bool refused=false;try{discoverWaypointTaggedResident(0,0,w,{},s);}catch(const std::invalid_argument&){refused=true;}require(refused);const WaypointTaggedDiscoveryBinding binding{{0,&a,nullptr},tag,&id};a.current373=1;w.currentHouse=0;auto previous=[](int){throw std::runtime_error("Prior callback invoked");};w.tagEvent=previous;require(!discoverWaypointTaggedResident(0,0,w,std::span(&binding,1),s)&&bool(w.tagEvent));std::cout<<"Tagged Infantry discovery guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
