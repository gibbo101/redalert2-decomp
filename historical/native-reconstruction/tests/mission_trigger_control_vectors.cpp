// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTriggerControl.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission Trigger control fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
struct Raw {int type=0,enabled=0;std::int32_t start=0,padding=0,remaining=0;std::uint32_t mask=0;};
struct Owner {
    int id=0;MissionTriggerType* typePointer=nullptr;std::uint8_t destroyed=0,enabled=0;MissionEventTimer timer{};std::int32_t padding=0;std::uint32_t occurred=0;
    MissionTriggerServices services;MissionTriggerState state;
    Owner(int index,MissionTriggerType* type,std::uint8_t e,MissionEventTimer t,std::int32_t p,std::uint32_t mask,const std::int32_t& frame,const std::uint8_t& suppress):
        id(index),typePointer(type),enabled(e),timer(t),padding(p),occurred(mask),services{frame,suppress},state{typePointer,destroyed,enabled,timer,padding,occurred}{}
};
void run(std::istream& in) {
    require(take<char>(in)=='C');const char op=take<char>(in);require(op=='E'||op=='D');
    const int targetMode=take<int>(in);require(targetMode>=0&&targetMode<=2);std::int32_t difficulty=take<std::int32_t>(in);
    std::array<std::uint8_t,3> allowed{};for(auto& x:allowed){const int v=take<int>(in);require(v>=0&&v<=255);x=std::uint8_t(v);}
    const int eventMode=take<int>(in);require(eventMode>=0&&eventMode<=1);std::int32_t timerValue=take<std::int32_t>(in),frame=take<std::int32_t>(in),scratch=take<std::int32_t>(in);
    const int count=take<int>(in);require(count>=0&&count<=4);std::array<Raw,4> raw{};
    for(auto& r:raw){r.type=take<int>(in);r.enabled=take<int>(in);r.start=take<std::int32_t>(in);r.padding=take<std::int32_t>(in);r.remaining=take<std::int32_t>(in);r.mask=take<std::uint32_t>(in);require(r.type>=1&&r.type<=2&&r.enabled>=0&&r.enabled<=255);}
    std::string extra;require(!(in>>extra));
    std::int32_t countryIndex=0,eventKind=13;MissionTriggerCountry country{countryIndex};MissionTriggerCountry* countryPointer=&country;
    MissionTriggerEvent* eventNext=nullptr;MissionTriggerEvent timerEvent{eventKind,timerValue,eventNext};MissionTriggerEvent* targetEvents=eventMode?&timerEvent:nullptr;MissionTriggerEvent* noEvents=nullptr;
    MissionTriggerAction* noActions=nullptr;MissionTriggerType targetType{countryPointer,targetEvents,noActions},otherType{countryPointer,noEvents,noActions},missingType{countryPointer,noEvents,noActions};
    std::uint8_t suppress=0;std::array<std::uint8_t,3> otherAllowed{1,1,1};std::vector<std::unique_ptr<Owner>> owners;std::vector<std::unique_ptr<MissionTriggerControlRecord>> records;
    for(int i=0;i<4;++i){auto* type=raw[i].type==1?&targetType:&otherType;owners.push_back(std::make_unique<Owner>(i,type,std::uint8_t(raw[i].enabled),MissionEventTimer{raw[i].start,raw[i].remaining},raw[i].padding,raw[i].mask,frame,suppress));
        auto& owner=*owners.back();owner.services.resetPadding=[&scratch]{return scratch;};owner.services.store=[i](int off,std::uint32_t value){std::cout<<"W "<<i<<' '<<off<<' '<<value<<' ';};
        records.push_back(std::make_unique<MissionTriggerControlRecord>(MissionTriggerControlRecord{owner.state,owner.services,raw[i].type==1?allowed:otherAllowed,&owner}));}
    std::array<MissionTriggerControlRecord*,4> backing{};for(int i=0;i<4;++i)backing[i]=records[i].get();std::span<MissionTriggerControlRecord*> slots=backing;std::int32_t liveCount=count;
    MissionTriggerControlRegistry registry{liveCount,slots};MissionTriggerType* target=targetMode==0?nullptr:targetMode==1?&targetType:&missingType;
    const bool result=setMissionTriggerTypeEnabled(target,op=='E',difficulty,registry,[](const void* identity,std::int32_t off,std::uint32_t value){
        const auto* owner=static_cast<const Owner*>(identity);std::cout<<"W "<<owner->id<<' '<<off<<' '<<value<<' ';});
    std::cout<<"R "<<result<<" state "<<liveCount;
    for(int i=0;i<4;++i){const auto& o=*owners[i];std::cout<<' '<<raw[i].type<<' '<<int(o.enabled)<<' '<<o.timer.start<<' '<<o.padding<<' '<<o.timer.remaining<<' '<<o.occurred;}
    std::cout<<'\n';
}
void guards(){
    std::int32_t frame=0,difficulty=0,count=1,countryIndex=0,pad=0;std::uint8_t suppress=0,destroyed=0,enabled=0;std::uint32_t mask=0;MissionEventTimer timer{};
    MissionTriggerCountry country{countryIndex};auto* cp=&country;MissionTriggerEvent* events=nullptr;MissionTriggerAction* actions=nullptr;MissionTriggerType type{cp,events,actions};auto* tp=&type;
    MissionTriggerState state{tp,destroyed,enabled,timer,pad,mask};MissionTriggerServices services{frame,suppress};std::array<std::uint8_t,3> allowed{1,1,1};MissionTriggerControlRecord record{state,services,allowed,&state};
    std::array<MissionTriggerControlRecord*,1> backing{&record};std::span<MissionTriggerControlRecord*> slots=backing;MissionTriggerControlRegistry registry{count,slots};
    MissionTriggerType* target=nullptr;require(setMissionTriggerTypeEnabled(target,true,difficulty,registry)&&!enabled);target=&type;
    services.resetPadding=[] {return 0;};require(setMissionTriggerTypeEnabled(target,true,difficulty,registry)&&enabled);require(setMissionTriggerTypeEnabled(target,false,difficulty,registry)&&!enabled);
    count=2;bool refused=false;try{setMissionTriggerTypeEnabled(target,false,difficulty,registry);}catch(const std::invalid_argument&){refused=true;}require(refused);
    std::span<MissionTriggerControlRecord*> noMirror;count=1;int queries=0;
    MissionTriggerControlRegistry actual{count,noMirror,[&](std::int32_t index)->MissionTriggerControlRecord*{
        ++queries;if(index!=0)throw std::invalid_argument("Unowned live Trigger slot");return &record;
    }};
    require(setMissionTriggerTypeEnabled(target,true,difficulty,actual)&&enabled&&queries==1);
    actual.resolveSlot=[](auto)->MissionTriggerControlRecord*{return nullptr;};refused=false;
    try{setMissionTriggerTypeEnabled(target,false,difficulty,actual);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&enabled);
    std::cout<<"mission trigger control guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
