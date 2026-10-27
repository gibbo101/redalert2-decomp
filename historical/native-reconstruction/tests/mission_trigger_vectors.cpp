// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTrigger.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing trigger input");return v;}
void require(bool ok){if(!ok)throw std::invalid_argument("Trigger fixture differs");}
struct EventRecord {std::int32_t kind=0,value=0;int link=-1;MissionTriggerEvent* next=nullptr;std::unique_ptr<MissionTriggerEvent> view;};
struct ActionRecord {int link=-1,result=0,mode=0;MissionTriggerAction* next=nullptr;std::unique_ptr<MissionTriggerAction> view;};

void run(std::istream& in) {
    require(take<char>(in)=='T');
    const int enabledInput=take<int>(in),destroyedInput=take<int>(in);
    require(enabledInput>=0&&enabledInput<=255&&destroyedInput>=0&&destroyedInput<=255);
    std::uint8_t enabled=enabledInput,destroyed=destroyedInput;
    auto occurred=take<std::uint32_t>(in);
    MissionEventTimer timer{take<std::int32_t>(in),0};auto padding=take<std::int32_t>(in);
    timer.remaining=take<std::int32_t>(in);const auto initialScratch=take<std::int32_t>(in);
    std::array<std::int32_t,2> countryValues{take<std::int32_t>(in),take<std::int32_t>(in)};
    std::array<MissionTriggerCountry,2> countries{{{countryValues[0]},{countryValues[1]}}};
    const int houseCount=take<int>(in);require(houseCount>=0&&houseCount<=16);
    std::vector<std::int32_t> houses(houseCount);for(auto& v:houses)v=take<std::int32_t>(in);
    const int eventCount=take<int>(in);require(eventCount>=0&&eventCount<=65);
    std::vector<EventRecord> events(eventCount);
    for(auto& e:events){e.kind=take<std::int32_t>(in);e.value=take<std::int32_t>(in);e.link=take<int>(in);e.view=std::make_unique<MissionTriggerEvent>(e.kind,e.value,e.next);}
    for(int i=0;i<eventCount;++i){const auto n=events[i].link;require(n==-1||(n>i&&n<eventCount));if(n!=-1)events[i].next=events[n].view.get();}
    const int actionCount=take<int>(in);require(actionCount>=0&&actionCount<=16);
    std::vector<ActionRecord> actions(actionCount);
    for(auto& a:actions){a.link=take<int>(in);a.result=take<int>(in);a.mode=take<int>(in);require(a.result>=0&&a.result<=255&&a.mode>=0&&a.mode<=5);a.view=std::make_unique<MissionTriggerAction>(a.next);}
    for(int i=0;i<actionCount;++i){const auto n=actions[i].link;require(n==-1||(n>i&&n<actionCount));if(n!=-1)actions[i].next=actions[n].view.get();}
    MissionTriggerEvent* firstEvent=events.empty()?nullptr:events[0].view.get();
    MissionTriggerAction* firstAction=actions.empty()?nullptr:actions[0].view.get();
    MissionTriggerCountry* country0=&countries[0];MissionTriggerCountry* country1=&countries[1];
    std::array<MissionTriggerType,2> types{{{country0,firstEvent,firstAction},{country1,firstEvent,firstAction}}};
    auto* type=&types[0];MissionTriggerState trigger{type,destroyed,enabled,timer,padding,occurred};
    std::int32_t frame=0,scratch=initialScratch;std::uint8_t suppress=0;int operation=0;
    std::array<int,2> objects{};
    const auto object=[&](std::uint32_t id)->const void*{require(id<=2);return id?&objects[id-1]:nullptr;};
    const auto objectId=[&](const void* p){return !p?0:p==&objects[0]?1:2;};
    const auto houseId=[&](const void* p){for(int i=0;i<houseCount;++i)if(p==&houses[i])return i;require(!p);return -1;};
    MissionTriggerServices services{frame,suppress};
    services.resolveHouse=[&](auto index)->const void*{
        std::cout<<"H "<<index<<' ';const void* found=nullptr;
        for(int i=0;i<houseCount;++i)if(houses[i]==index){found=&houses[i];break;}
        std::cout<<"I "<<houseId(found)<<' ';
        // Supplied fixture ABI: after RegisterEvent's actual event call, the
        // ResetTimers scratch slot retains the &persistent argument pointer.
        if(operation==1)scratch=0x1140010;
        return found;
    };
    services.resetPadding=[&]{return scratch;};
    services.store=[](int offset,std::uint32_t value){std::cout<<"W "<<offset<<' '<<value<<' ';};
    services.event=[&](const auto& e,const void* house,const auto& pulse){
        int index=-1;for(int i=0;i<eventCount;++i)if(events[i].view.get()==&e)index=i;require(index>=0);
        std::cout<<"E "<<index<<' '<<pulse.kind<<' '<<houseId(house)<<' '<<objectId(pulse.object)<<' '<<pulse.persistent<<' '<<objectId(pulse.source)<<' ';
    };
    services.executeAction=[&](auto& view,const void* house,const void* owner,auto& state,std::uint32_t& location){
        require(&state==&trigger);int index=-1;for(int i=0;i<actionCount;++i)if(actions[i].view.get()==&view)index=i;require(index>=0);
        auto& a=actions[index];std::cout<<"A "<<index<<' '<<houseId(house)<<' '<<objectId(owner)<<' '<<location<<' ';
        if(a.mode==1){enabled=0;destroyed=255;}
        if(a.mode==2){type=&types[1];a.link=index+1<actionCount?actionCount-1:-1;a.next=a.link<0?nullptr:actions[a.link].view.get();}
        if(a.mode==3)location^=0x8001ffffu;
        if(a.mode==4)enabled=0;
        if(a.mode==5)country0=&countries[1];
        return std::uint8_t(a.result);
    };
    const int count=take<int>(in);require(count>0&&count<=64);
    for(int i=0;i<count;++i){
        operation=take<int>(in);frame=take<std::int32_t>(in);const int raw=take<int>(in);require(raw>=0&&raw<=255);suppress=raw;
        std::array<std::uint32_t,5> a{};for(auto& v:a)v=take<std::uint32_t>(in);scratch=initialScratch;
        std::cout<<"O "<<operation<<' ';
        if(operation==0){resetMissionTriggerTimers(trigger,services);std::cout<<"R reset ";}
        else if(operation==1){const auto result=registerMissionTriggerEvent(trigger,{std::bit_cast<std::int32_t>(a[0]),object(a[1]),a[2],a[3],object(a[4])},services);std::cout<<"R "<<result<<' ';}
        else if(operation==2){const auto result=fireMissionTriggerActions(trigger,object(a[0]),a[1],services);std::cout<<"R "<<result<<' ';}
        else throw std::invalid_argument("Unknown trigger operation");
    }
    std::string extra;require(!(in>>extra));
    std::cout<<"state "<<int(enabled)<<' '<<int(destroyed)<<' '<<occurred<<' '<<timer.start<<' '<<padding<<' '<<timer.remaining<<' '<<(type==&types[0]?0:1)<<' '<<(country0==&countries[0]?0:1);
    for(auto& a:actions)std::cout<<' '<<a.link;
    std::cout<<'\n';
}

void guards(){
    std::int32_t frame=0,kind=51,value=1,index=0,pad=19;std::uint8_t enabled=0,destroyed=0,suppress=0;std::uint32_t mask=0;
    MissionTriggerEvent* next=nullptr;MissionTriggerEvent event{kind,value,next};auto* first=&event;
    MissionTriggerAction* action=nullptr;MissionTriggerCountry country{index};auto* c=&country;
    MissionTriggerType type{c,first,action};auto* p=&type;MissionEventTimer timer;
    MissionTriggerState trigger{p,destroyed,enabled,timer,pad,mask};MissionTriggerServices services{frame,suppress};
    require(!registerMissionTriggerEvent(trigger,{},services)&&!fireMissionTriggerActions(trigger,nullptr,0,services));
    enabled=255;destroyed=128;require(!registerMissionTriggerEvent(trigger,{},services));destroyed=0;
    auto refuses=[&](auto call){bool caught=false;try{call();}catch(const std::invalid_argument&){caught=true;}require(caught);};
    refuses([&]{resetMissionTriggerTimers(trigger,services);});
    refuses([&]{registerMissionTriggerEvent(trigger,{},services);});
    require(registerMissionTriggerEvent(trigger,{.force=255},services));
    kind=13;refuses([&]{resetMissionTriggerTimers(trigger,services);});require(timer.start==0&&pad==19);
    services.resetPadding=[]{return -7;};value=2147483647;resetMissionTriggerTimers(trigger,services);require(timer.remaining==2147483633&&pad==-7);
    // Cached unsupported conditions skip evaluation, but an entered persistence
    // helper still refuses. Force with low byte zero does not bypass queries.
    kind=9;mask=1;require(registerMissionTriggerEvent(trigger,{},services));
    refuses([&]{registerMissionTriggerEvent(trigger,{.persistent=1},services);});mask=0;
    refuses([&]{registerMissionTriggerEvent(trigger,{.force=256},services);});
    services.resolveHouse=[](auto)->const void*{throw std::runtime_error("registry fault");};
    bool propagated=false;try{registerMissionTriggerEvent(trigger,{},services);}catch(const std::runtime_error&){propagated=true;}require(propagated);
    // An empty action list performs no House lookup; an entered action requires
    // its dispatcher. Callback faults retain prior writes and are not rollback.
    require(!fireMissionTriggerActions(trigger,nullptr,0,services));
    MissionTriggerAction* tail=nullptr;MissionTriggerAction one{tail};action=&one;
    int lookups=0;services.resolveHouse=[&](auto)->const void*{++lookups;return nullptr;};
    refuses([&]{fireMissionTriggerActions(trigger,nullptr,0,services);});require(lookups==1);
    services.executeAction=[&](auto&,auto*,auto*,auto&,auto&)->std::uint8_t{enabled=0;throw std::runtime_error("action fault");};
    propagated=false;try{fireMissionTriggerActions(trigger,nullptr,0,services);}catch(const std::runtime_error&){propagated=true;}
    require(propagated&&enabled==0&&lookups==2);
    std::cout<<"mission-trigger guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
