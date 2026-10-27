// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionConstruction.hpp"
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
struct TypeOwner {
 std::int32_t kind=7,value=1;MissionTriggerEvent* noEvent=nullptr;MissionTriggerEvent event{kind,value,noEvent};
 MissionTriggerEvent* events=&event;MissionTriggerCountry* country=nullptr;MissionTriggerAction* actions=nullptr;
 MissionTriggerType type{country,events,actions};std::array<std::uint8_t,4> flags{};
 MissionTriggerConstructionType* next=nullptr;MissionTriggerConstructionType construction{&type,flags,next};
};
struct TriggerOwner {
 MissionConstructionBase base;MissionTriggerType* type=nullptr;MissionTagTrigger* next=nullptr;
 std::uint8_t destroyed=0,enabled=1,suppress=0;MissionEventTimer timer{0,0};std::int32_t padding=0x5a5a5a5a;std::uint32_t occurred=0;
 MissionTriggerServices services;MissionTriggerState state{type,destroyed,enabled,timer,padding,occurred};
 MissionTagTrigger trigger{state,services,next};MissionTriggerConstructionView construction{base,trigger,type,next};
 explicit TriggerOwner(const std::int32_t& frame):services{frame,suppress}{}
};
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  std::int32_t frame=0,difficulty=0;const void* link=nullptr;
  MissionConstructionServices s{frame,difficulty,link,{},{},nullptr};MissionScriptConstructionRecord r;bool refused=false;
  try{constructMissionScript(r,nullptr,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing Script registry accepted");
  std::array<std::int32_t,3> counts{};std::int32_t cap=4,growth=10;std::uint8_t allocated=1;
  std::array<std::array<const void*,4>,3> backing{};std::array<std::span<const void*>,3> slots{backing[0],backing[1],backing[2]};
  std::array<TeamConstructionRegistry,3> registries{{{{counts[0],slots[0],&counts[0]},cap,allocated,growth,{},{}},{{counts[1],slots[1],&counts[1]},cap,allocated,growth,{},{}},{{counts[2],slots[2],&counts[2]},cap,allocated,growth,{},{}}}};
  s.tagRegistries={&registries[0],&registries[1],&registries[2]};
  TypeOwner type;MissionTriggerConstructionType* firstType=&type.construction;
  std::int32_t policy=0,instances=0;MissionTagType tagType{policy};MissionTagType* typePointer=nullptr;
  MissionTagTrigger* first=nullptr;std::uint8_t executing=0,destroyed=0;const void* tagLink=nullptr;
  MissionTagState tag{typePointer,first,instances,executing};MissionConstructionBase base;
  MissionTagConstructionView record{base,tag,typePointer,first,tagLink,destroyed};MissionTagConstructionType source{&tagType,firstType};
  s.allocate=[](auto)->void*{return nullptr;};refused=false;
  try{constructMissionTag(record,&source,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused||first||counts!=std::array<std::int32_t,3>{1,1,1})throw std::runtime_error("Unsafe Tag allocation was accepted or earlier effects lost");
  int storage=0;s.allocate=[&](auto)->void*{return &storage;};s.constructTrigger=[](auto,auto&)->MissionTriggerConstructionView*{return nullptr;};refused=false;
  try{constructMissionTag(record,&source,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused||first)throw std::runtime_error("Unsafe null Trigger child was accepted");
  std::cout<<"Mission construction guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,14> f{};std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid mission construction input");
  std::int32_t frame=std::int32_t(f[8]),difficulty=std::int32_t(f[3]);
  std::array<TypeOwner,2> types;for(auto& t:types){t.kind=int(f[6]);t.value=int(f[7]);for(int i=0;i<4;++i)t.flags[i]=(f[4]&(1<<i))?std::uint8_t(f[5]):0;}
  types[0].next=f[2]==2?&types[1].construction:nullptr;
  std::array<std::unique_ptr<TriggerOwner>,3> triggers;for(auto& t:triggers)t=std::make_unique<TriggerOwner>(frame);
  MissionConstructionBase tagBase;std::int32_t persistence=0,instances=0;
  MissionTagType tagType{persistence},otherTagType{persistence};MissionTagType* tagTypePointer=nullptr;MissionTagTrigger* first=nullptr;
  std::uint8_t executing=0,destroyed=0;const void* tagLink=nullptr;MissionTagState tag{tagTypePointer,first,instances,executing};
  MissionTagConstructionView tagView{tagBase,tag,tagTypePointer,first,tagLink,destroyed};
  MissionTriggerConstructionType* firstType=f[2]?&types[0].construction:nullptr;MissionTagConstructionType tagSource{&tagType,firstType};
  MissionScriptConstructionRecord script;int scriptType=0,globalLinkIdentity=0;const void* globalLink=f[10]==5?nullptr:&globalLinkIdentity;
  auto poison=[&](auto& b){b.index10=0x5a5a5a5a;b.flags14=std::uint8_t(f[9]);b.value18=b.value1C=0x5a5a5a5a;b.byte20=0x5a;};
  poison(tagBase);poison(script);for(auto& t:triggers)poison(t->base);
  std::array<int,5> registryIds{};std::array<int,16> previous{};
  std::array<std::array<const void*,16>,5> backing{},alt{};std::array<std::span<const void*>,5> slots;
  std::array<std::int32_t,5> count{},capacity{},increment{};std::array<std::uint8_t,5> allocated{};
  const std::array<std::array<std::int32_t,4>,5> profiles{{{1,16,1,10},{1,1,0,10},{1,1,1,0},{1,1,128,10},{0,0,0,10}}};
  std::array<std::unique_ptr<TeamConstructionRegistry>,5> registries;
  for(int i=0;i<5;++i){auto p=f[10]==5?std::array<std::int32_t,4>{std::array<int,5>{1,7,6,5,0}[i],16,1,10}:profiles[(f[10]+i)%5];count[i]=p[0];capacity[i]=p[1];allocated[i]=std::uint8_t(p[2]);increment[i]=p[3];
   for(int j=0;j<16;++j)backing[i][j]=&previous[j];slots[i]=backing[i];
   registries[i]=std::make_unique<TeamConstructionRegistry>(TeamConstructionRegistry{{count[i],slots[i],&registryIds[i]},capacity[i],allocated[i],increment[i],{},{}});}
  auto pid=[&](const void* p)->int{
   if(!p)return 0;if(p==&tag)return 1;for(int i=0;i<3;++i)if(p==&triggers[i]->trigger)return 2+i;if(p==&script)return 5;
   if(p==&tagType)return 6;if(p==&otherTagType)return 7;for(int i=0;i<2;++i)if(p==&types[i].type)return 8+i;
   if(p==&scriptType)return 10;if(p==&globalLinkIdentity)return 11;for(int i=0;i<5;++i)if(p==&registryIds[i])return 31+i;
   for(int i=0;i<16;++i)if(p==&previous[i])return 41+i;throw std::invalid_argument("Unknown mission construction pointer");};
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
  bool mutated=false;int allocations=0,resizing=0;
  auto mutate=[&](int where){if(mutated||f[12]!=where)return;mutated=true;event(4,where);
   if(where==1){difficulty=2;types[0].flags[2]=0;}
   if(where==2)first=&triggers[2]->trigger;
   if(where==3)types[0].next=nullptr;
   if(where==4)tagTypePointer=&otherTagType;
   if(where==5)count[resizing]=1;};
  MissionConstructionServices s{frame,difficulty,globalLink,{registries[0].get(),registries[1].get(),registries[2].get()},{registries[1].get(),registries[2].get(),registries[3].get()},registries[4].get()};
  for(int i=0;i<5;++i)registries[i]->resize=[&,i](std::int32_t cap,std::uint32_t zero){resizing=i;event(3,31+i,cap,zero,f[11]);if(std::uint8_t(f[11])){std::copy(slots[i].begin(),slots[i].end(),alt[i].begin());slots[i]=alt[i];capacity[i]=cap;allocated[i]=1;}mutate(1);mutate(5);return std::uint32_t(f[11]);};
  s.store=[&](const void* owner,std::int64_t off,std::uint32_t value,const void* pointer){const int id=pid(owner);bool byte=(off==0x14||off==0x20)||(id==1&&(off==0x34||off==0x35))||(id>=2&&id<=4&&(off==0x2c||off==0x40));
   const bool ptr=(id==1&&(off==0x24||off==0x28||off==0x30))||(id>=2&&id<=4&&(off==0x24||off==0x28))||(id==5&&off==0x24)||(id>=31&&off>=0x100);
   event(1,id,off,byte?1:4,ptr?pid(pointer):value);};
  s.projectInterfaces=[&](const void* owner,unsigned kind,unsigned phase){if(phase==2){event(1,pid(owner),8,4,16);event(1,pid(owner),12,4,17);}else for(int i=0;i<4;++i)event(1,pid(owner),4*i,4,phase==1?12+i:4*(kind-1)+i);};
  s.resolveTriggerType=[&](auto* p)->const MissionTriggerConstructionType&{for(auto& t:types)if(p==&t.type)return t.construction;throw std::invalid_argument("Unknown Trigger permission Type");};
  for(int i=0;i<3;++i){triggers[i]->services.resetPadding=[&]{return std::int32_t(f[13]);};triggers[i]->services.store=[&,i](int off,std::uint32_t value){event(1,2+i,off,4,value);};}
  s.allocate=[&](std::uint32_t size)->void*{if(size!=68||allocations>=2)throw std::invalid_argument("Unbounded Trigger allocation");auto* storage=&triggers[allocations++]->trigger;event(2,size,pid(storage));mutate(2);mutate(3);mutate(4);return storage;};
  s.constructTrigger=[&](void* storage,auto& type)->MissionTriggerConstructionView*{for(auto& t:triggers)if(storage==&t->trigger){constructMissionTrigger(t->construction,&type,s);return &t->construction;}throw std::invalid_argument("Unknown Trigger allocation");};
  if(f[0]==0)constructMissionScript(script,f[1]?&scriptType:nullptr,s);
  if(f[0]==1)constructMissionTrigger(triggers[0]->construction,f[1]?&types[0].construction:nullptr,s);
  if(f[0]==2||f[0]==3)constructMissionTag(tagView,f[1]?&tagSource:nullptr,s);
  if(f[0]==3)constructMissionScript(script,f[1]?&scriptType:nullptr,s);
  std::cout<<trace.str()<<"F "<<mutated<<' '<<allocations<<' '<<std::uint32_t(difficulty)<<' '<<(types[0].next!=nullptr)<<' ';for(auto b:types[0].flags)std::cout<<unsigned(b)<<' ';
  for(int i=0;i<5;++i){std::cout<<std::uint32_t(count[i])<<' '<<std::uint32_t(capacity[i])<<' '<<unsigned(allocated[i])<<' '<<(slots[i].data()==alt[i].data())<<' ';for(auto* p:slots[i])std::cout<<pid(p)<<' ';}
  auto base=[&](auto& b){std::cout<<std::uint32_t(b.index10)<<' '<<unsigned(b.flags14)<<' '<<b.value18<<' '<<b.value1C<<' '<<unsigned(b.byte20)<<' ';};
  base(tagBase);std::cout<<pid(tagTypePointer)<<' '<<pid(first)<<' '<<std::uint32_t(instances)<<' '<<pid(tagLink)<<' '<<unsigned(executing)<<' '<<unsigned(destroyed)<<' ';
  for(auto& t:triggers){base(t->base);std::cout<<pid(t->type)<<' '<<pid(t->next)<<' '<<unsigned(t->destroyed)<<' '<<unsigned(t->enabled)<<' '<<std::uint32_t(t->timer.start)<<' '<<std::uint32_t(t->padding)<<' '<<std::uint32_t(t->timer.remaining)<<' '<<t->occurred<<' ';}
  base(script);std::cout<<pid(script.type24)<<' '<<script.value28<<' '<<std::uint32_t(script.cursor2C)<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
