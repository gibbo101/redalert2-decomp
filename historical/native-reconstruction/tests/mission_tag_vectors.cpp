// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTag.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Tag input");return v;}
void require(bool ok){if(!ok)throw std::invalid_argument("Tag fixture differs");}
struct TriggerRecord {
    int nextIndex=-1,result=0,mode=0;std::int32_t kind=4,value=13,padding=-91;std::uint32_t mask=0;
    std::uint8_t enabled=1,destroyed=0;MissionEventTimer timer;
    MissionTriggerEvent* nextEvent=nullptr;MissionTriggerAction* nextAction=nullptr;
    std::unique_ptr<MissionTriggerEvent> event;std::unique_ptr<MissionTriggerAction> action;
    MissionTriggerEvent* firstEvent=nullptr;MissionTriggerAction* firstAction=nullptr;
    std::unique_ptr<MissionTriggerType> type;MissionTriggerType* typePointer=nullptr;
    std::unique_ptr<MissionTriggerState> state;std::unique_ptr<MissionTriggerServices> services;
    std::unique_ptr<MissionTagTrigger> node;MissionTagTrigger* next=nullptr;
};
void run(std::istream& in){
    require(take<char>(in)=='G');
    std::array<std::int32_t,2> persistence{take<std::int32_t>(in),take<std::int32_t>(in)};
    std::array<std::int32_t,2> instances{take<std::int32_t>(in),take<std::int32_t>(in)};
    const int rawExecuting=take<int>(in),tagDestroyed=take<int>(in);require(rawExecuting>=0&&rawExecuting<=255&&tagDestroyed>=0&&tagDestroyed<=255);
    std::uint8_t executing=rawExecuting,otherExecuting=0;
    const int ownerId=take<int>(in),cellId=take<int>(in),fallbackId=take<int>(in);
    auto capacity=take<std::int32_t>(in),count=take<std::int32_t>(in),growth=take<std::int32_t>(in);
    const int ownsInput=take<int>(in);auto growResult=take<std::uint32_t>(in);const int growMode=take<int>(in),notifyMode=take<int>(in),mapSlot=take<int>(in);
    require(capacity>=0&&capacity<=128&&count>=0&&count<=128&&ownsInput>=0&&ownsInput<=255&&growMode>=0&&growMode<=2&&notifyMode>=0&&notifyMode<=1&&mapSlot>=-1&&mapSlot<262144);
    const std::uint8_t owns=ownsInput;std::array<std::array<const void*,128>,2> buffers{};int backing=0;
    std::span<const void*> slots(buffers[0]);MissionDeferredDelete deferred{capacity,owns,count,growth,slots};
    const int n=take<int>(in);require(n>=0&&n<=3);std::vector<TriggerRecord> triggers(n);
    std::int32_t frame=0,scratch=std::bit_cast<std::int32_t>(0xa5a5a5a5u),countryIndex=-9;std::uint8_t suppress=0;
    MissionTriggerCountry country{countryIndex};auto* countryPointer=&country;
    std::array<MissionTagType,2> tagTypes{{{persistence[0]},{persistence[1]}}};auto* type=&tagTypes[0];
    MissionTagTrigger* first=nullptr;MissionTagState tag{type,first,instances[0],executing};
    MissionTagTrigger* empty=nullptr;auto* otherType=&tagTypes[1];MissionTagState other{otherType,empty,instances[1],otherExecuting};
    const auto tagPointer=[&](int id)->MissionTagState*{require(id>=0&&id<=2);return id==0?nullptr:id==1?&tag:&other;};
    MissionTagState* ownerTag=tagPointer(ownerId);std::array<MissionTagState*,2> cellTags{tagPointer(cellId),tagPointer(fallbackId)};
    std::uint32_t fallbackPoint=0x1234abcd,emptyCell=0x7fff7fff;int object=0,sourceObject=0;
    MissionTagOwner owner{ownerTag,&object};
    const auto id=[&](const void* p){
        if(!p)return 0;if(p==&tag)return 10;if(p==&other)return 11;if(p==&object)return 20;
        if(p==&cellTags[0])return 30;if(p==&cellTags[1])return 31;if(p==&deferred)return 40;
        for(int i=0;i<n;++i)if(triggers[i].node.get()==p)return i+1;
        throw std::invalid_argument("Unknown Tag fixture identity");
    };
    MissionTagStore store=[&](const void* subject,auto offset,auto value,const void* pointer){std::cout<<"W "<<id(subject)<<' '<<offset<<' '<<(pointer?std::uint32_t(id(pointer)):value)<<' ';};
    deferred.grow=[&](std::int32_t requested){
        std::cout<<"V "<<requested<<' '<<growResult<<' ';if(std::uint8_t(growResult)){
            require(requested>=0&&requested<=128);capacity=requested;
            if(growMode==1)count=0;
            if(growMode==2){buffers[1]=buffers[0];backing=1;slots=buffers[1];}
        }return growResult;
    };
    MissionTagServices services{deferred,emptyCell};services.store=store;
    services.cellTag=[&](std::uint32_t packed)->MissionTagState*&{
        std::cout<<"L "<<packed<<' ';const int x=std::bit_cast<std::int16_t>(std::uint16_t(packed)),y=std::bit_cast<std::int16_t>(std::uint16_t(packed>>16));
        const int index=y*512+x;if(index==mapSlot&&index>=0)return cellTags[0];
        fallbackPoint=packed;std::cout<<"B "<<packed<<' ';return cellTags[1];
    };
    services.notifyExpired=[&](auto& t,auto raw){require(&t==&tag&&raw==1);std::cout<<"N "<<int(executing)<<' ';if(notifyMode)count=0;};
    for(int i=0;i<n;++i){auto& t=triggers[i];
        t.nextIndex=take<int>(in);const int e=take<int>(in),d=take<int>(in);require(e>=0&&e<=255&&d>=0&&d<=255);t.enabled=e;t.destroyed=d;
        t.kind=take<std::int32_t>(in);t.value=take<std::int32_t>(in);t.result=take<int>(in);t.mode=take<int>(in);
        require((t.nextIndex==-1||(t.nextIndex>i&&t.nextIndex<n))&&t.result>=0&&t.result<=255&&t.mode>=0&&t.mode<=8);
        t.event=std::make_unique<MissionTriggerEvent>(t.kind,t.value,t.nextEvent);t.action=std::make_unique<MissionTriggerAction>(t.nextAction);
        t.firstEvent=t.event.get();t.firstAction=t.action.get();t.type=std::make_unique<MissionTriggerType>(countryPointer,t.firstEvent,t.firstAction);t.typePointer=t.type.get();
        t.state=std::make_unique<MissionTriggerState>(t.typePointer,t.destroyed,t.enabled,t.timer,t.padding,t.mask);
        t.services=std::make_unique<MissionTriggerServices>(frame,suppress);
        t.services->resolveHouse=[](auto country)->const void*{std::cout<<"H "<<country<<' ';return nullptr;};
        t.services->resetPadding=[&]{return scratch;};
        t.services->store=[&,i](int off,auto value){store(triggers[i].node.get(),off,value,nullptr);};
        t.services->event=[&,i](const auto&,const void* house,const auto& pulse){require(!house);scratch=0x113ffe4;std::cout<<"E "<<i+1<<' '<<pulse.kind<<' '<<pulse.persistent<<' ';};
        t.services->executeAction=[&,i](auto&,const void* house,const void*,auto& state,std::uint32_t& location){
            auto& t=triggers[i];require(!house&&&state==t.state.get());std::cout<<"A "<<i+1<<' '<<location<<' ';
            // Supplied ABI scratch: FireActions' House call saves ESI here.
            scratch=0x2816000+i*0x100;
            if(t.mode==1)persistence[0]=2;if(t.mode==2)persistence[0]=0;if(t.mode==3)instances[0]=1;
            if(t.mode==4){t.nextIndex=i+1<n?n-1:-1;t.next=t.nextIndex<0?nullptr:triggers[t.nextIndex].node.get();}
            if(t.mode==5)executing=255;if(t.mode==6){ownerTag=&other;cellTags[0]=&other;cellTags[1]=&other;}
            if(t.mode==7){t.enabled=0;t.destroyed=255;}if(t.mode==8)location^=0x8001ffffu;
            return std::uint8_t(t.result);
        };
        t.node=std::make_unique<MissionTagTrigger>(*t.state,*t.services,t.next);
    }
    for(int i=0;i<n;++i)if(triggers[i].nextIndex!=-1)triggers[i].next=triggers[triggers[i].nextIndex].node.get();
    if(n)first=triggers[0].node.get();
    const int ops=take<int>(in);require(ops>0&&ops<=32);
    for(int k=0;k<ops;++k){
        const int operation=take<int>(in);frame=take<std::int32_t>(in);const int raw=take<int>(in);require(raw>=0&&raw<=255);suppress=raw;
        const auto pulse=take<std::int32_t>(in);const int present=take<int>(in);auto location=take<std::uint32_t>(in),force=take<std::uint32_t>(in);const int source=take<int>(in),subject=take<int>(in);
        require((present==0||present==1)&&(source==0||source==1));scratch=std::bit_cast<std::int32_t>(0xa5a5a5a5u);
        std::cout<<"O "<<operation<<' ';bool result=false;
        if(operation==0)result=raiseMissionTagEvent(tag,{pulse,present?&object:nullptr,force,0,source?&sourceObject:nullptr},present?&owner:nullptr,location,services);
        else if(operation==1){require(subject>=0&&subject<n);destroyMissionTrigger(*triggers[subject].node,deferred,store);std::cout<<"R void ";continue;}
        else if(operation==2)result=setMissionObjectTag(owner,tagPointer(subject),store);
        else if(operation==3){require(subject>=0&&subject<=1);clearMissionCellTag(cellTags[subject],store);std::cout<<"R void ";continue;}
        else throw std::invalid_argument("Unknown Tag fixture operation");
        std::cout<<"R "<<result<<' ';
    }
    std::string extra;require(!(in>>extra));
    std::cout<<"state "<<persistence[0]<<' '<<persistence[1]<<' '<<instances[0]<<' '<<instances[1]<<' '<<int(executing)<<' '<<tagDestroyed<<' '<<id(ownerTag)<<' '<<id(cellTags[0])<<' '<<id(cellTags[1])<<' '<<fallbackPoint<<' '<<capacity<<' '<<count<<' '<<backing;
    for(auto& t:triggers)std::cout<<' '<<int(t.enabled)<<' '<<int(t.destroyed)<<' '<<t.mask<<' '<<t.timer.start<<' '<<t.padding<<' '<<t.timer.remaining<<' '<<t.nextIndex;
    for(auto& b:buffers)for(auto* slot:b)std::cout<<' '<<id(slot);
    std::cout<<'\n';
}
void guards(){
    std::int32_t persistence=0,instances=1,capacity=1,count=0,growth=1;std::uint8_t executing=255,owns=0;
    MissionTagType type{persistence};auto* p=&type;MissionTagTrigger* head=nullptr;MissionTagState tag{p,head,instances,executing};
    std::array<const void*,4> backing{};std::span<const void*> slots(backing);MissionDeferredDelete q{capacity,owns,count,growth,slots};
    std::uint32_t empty=0x7fff7fff;MissionTagServices missing{q,empty};
    require(!raiseMissionTagEvent(tag,{},nullptr,0,missing)&&executing==255);
    executing=0;require(!raiseMissionTagEvent(tag,{},nullptr,0,missing)&&executing==0);
    appendMissionDeferredDelete(q,&tag);appendMissionDeferredDelete(q,&tag);require(count==1&&backing[0]==&tag);
    MissionTagState* ownerTag=&tag;MissionTagOwner owner{ownerTag,&ownerTag};
    require(setMissionObjectTag(owner,&tag)&&instances==1&&ownerTag==&tag);
    instances=-2147483648;require(!setMissionObjectTag(owner,nullptr)&&instances==2147483647);
    clearMissionCellTag(ownerTag);require(!ownerTag);
    capacity=0;count=0;bool refused=false;try{appendMissionDeferredDelete(q,&tag);}catch(const std::invalid_argument&){refused=true;}require(refused);
    int object=0;refused=false;try{raiseMissionTagEvent(tag,{.object=&object},nullptr,empty,missing);}catch(const std::invalid_argument&){refused=true;}require(refused&&executing==0);
    std::int32_t frame=0,padding=19,countryIndex=0;std::uint8_t suppress=0,enabled=1,destroyed=0;std::uint32_t mask=0;
    MissionTriggerCountry country{countryIndex};auto* countryPointer=&country;
    MissionTriggerEvent* noEvent=nullptr;MissionTriggerAction* noAction=nullptr;MissionTriggerType triggerType{countryPointer,noEvent,noAction};auto* triggerTypePointer=&triggerType;
    MissionEventTimer timer;MissionTriggerState trigger{triggerTypePointer,destroyed,enabled,timer,padding,mask};MissionTriggerServices triggerServices{frame,suppress};
    MissionTagTrigger* next=nullptr;MissionTagTrigger node{trigger,triggerServices,next};head=&node;capacity=4;count=0;
    refused=false;try{raiseMissionTagEvent(tag,{.force=1},nullptr,empty,missing);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&executing==0&&destroyed==1&&count==1&&backing[0]==&node);
    // Expiration happens after executing clears and may synchronously reenter.
    // The already-destroyed trigger must not fire or enqueue itself again.
    destroyed=0;count=0;int notifications=0;
    missing.notifyExpired=[&](auto&,auto raw){++notifications;require(raw==1&&executing==0);require(!raiseMissionTagEvent(tag,{.force=1},nullptr,empty,missing));};
    require(raiseMissionTagEvent(tag,{.force=1},nullptr,empty,missing)&&notifications==1&&count==2&&backing[0]==&node&&backing[1]==&tag);
    std::cout<<"mission-tag guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
