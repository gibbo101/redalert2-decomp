// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamConstruction.hpp"
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  TeamConstructionRecord r;std::int32_t frame=0;std::uint32_t empty=0;
  TeamConstructionServices s{frame,empty,{}};bool refused=false;
  try{constructTeam(r,nullptr,nullptr,0,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing Team registries accepted");
  int target=0;std::array<const void*,1> actualBacking{};std::span<const void*> noBacking;
  std::int32_t count=0,capacity=1,increment=10;std::uint8_t allocated=1;
  TeamConstructionRegistry projection{{count,noBacking,&count},capacity,allocated,increment,{},
   [&](std::int32_t index,const void* p){
    if(count!=1||index!=0)throw std::runtime_error("Team count must publish before projected slot");
    actualBacking.at(index)=p;
   }};
  registerConstructedTeam(projection,&target,s);
  if(count!=1||actualBacking[0]!=&target)throw std::runtime_error("Team append did not borrow actual backing");
  r.tag70=&target;r.value54=&target;refused=false;
  try{expireConstructedTeamTag(r,&target,1);}catch(const std::invalid_argument&){refused=true;}
  if(!refused||r.tag70!=&target)throw std::runtime_error("Unsupported populated Team expiry mutated state");
  r.value54=0;expireConstructedTeamTag(r,&target,257);
  if(r.tag70)throw std::runtime_error("Constructed Team did not expire its Tag reference");
  std::cout<<"Team construction guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,18> f{};std::istringstream in(line);for(auto& n:f)in>>n;
  if(!in)throw std::invalid_argument("Invalid Team construction input");
  TeamConstructionRecord r;r.index10=0x5a5a5a5a;r.flags14=std::uint8_t(f[6]);r.byte20=0x5a;
  r.value18=r.value1C=0x5a5a5a5a;
  std::array<int,7> identities{};const void* tag1=&identities[3];const void* tag2=&identities[4];
  const void* script1=f[10]?&identities[5]:nullptr;const void* script2=&identities[6];
  std::uint8_t flag=std::uint8_t(f[2]),flag2=0;std::int32_t count=std::int32_t(f[3]),count2=-1;
  const void* tag=f[9]?tag1:nullptr;
  TeamConstructionType t1{&identities[0],flag,count,tag,script1},t2{&identities[1],flag2,count2,tag2,script2};
  std::uint32_t houseCount=0xffffffffu;TeamConstructionHouse house{&identities[2],houseCount};
  std::array<int,5> registryIds{};std::array<int,8> priorOwners{};
  std::array<std::array<const void*,8>,5> backing{},alt{};
  std::array<std::span<const void*>,5> slots;
  std::array<std::int32_t,5> counts{},capacities{},growth{};std::array<std::uint8_t,5> allocated{};
  const std::array<std::array<std::int32_t,4>,6> profiles{{{2,6,1,3},{2,2,0,3},{2,2,1,0},{2,2,128,3},{0,0,0,3},{2,2,1,2147483647}}};
  std::array<std::unique_ptr<TeamConstructionRegistry>,5> registries;
  for(int i=0;i<5;++i){auto p=f[14]==6?std::array<std::int32_t,4>{i==1?6:i==2?2:0,i==2?4:8,1,10}:profiles[(f[14]+i)%6];counts[i]=p[0];capacities[i]=p[1];allocated[i]=std::uint8_t(p[2]);growth[i]=p[3];for(int j=0;j<8;++j)backing[i][j]=&priorOwners[j];alt[i].fill(nullptr);slots[i]=backing[i];
   registries[i]=std::make_unique<TeamConstructionRegistry>(TeamConstructionRegistry{{counts[i],slots[i],&registryIds[i]},capacities[i],allocated[i],growth[i],{}});}
  int cellId=0,tagStorage=0,scriptStorage=0,otherTag=0,otherScript=0,objectTag=0;
  if(f[14]==6){backing[1][5]=&objectTag;backing[2][0]=&priorOwners[6];backing[2][1]=&priorOwners[7];}
  const auto pid=[&](const void* p)->int{
   if(!p)return 0;if(p==&r)return 1;for(int i=0;i<8;++i)if(p==&priorOwners[i])return 15+i;for(int i=0;i<7;++i)if(p==&identities[i])return 2+i;
   if(p==&cellId)return 9;if(p==&tagStorage)return 10;if(p==&scriptStorage)return 11;if(p==&otherTag)return 12;if(p==&otherScript)return 13;if(p==&objectTag)return 14;
   for(int i=0;i<5;++i)if(p==&registryIds[i])return 31+i;throw std::invalid_argument("Unknown Team pointer");};
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
  std::int32_t frame=std::int32_t(f[4]);std::uint32_t empty=0x7fff7fffu;bool mutated=false;int waypoint=0,resizing=0;
  auto mutate=[&](int where){if(mutated||f[16]!=where)return;mutated=true;event(8,where);
   if(where==1)frame=-2;
   if(where==2){slots[0]=alt[0];}
   if(where==3||where==4||where==5)r.type24=&t2;
   if(where==6)counts[resizing]=1;
   if(where==7)empty=std::uint32_t(f[7]);};
  TeamConstructionServices s{frame,empty,{registries[0].get(),registries[1].get(),registries[2].get(),registries[3].get(),registries[4].get()}};
  for(int i=0;i<5;++i)registries[i]->resize=[&,i](std::int32_t cap,std::uint32_t zero){resizing=i;event(7,31+i,cap,zero,f[15]);if(std::uint8_t(f[15])){std::copy(slots[i].begin(),slots[i].end(),alt[i].begin());slots[i]=alt[i];capacities[i]=cap;allocated[i]=1;}mutate(6);return std::uint32_t(f[15]);};
  s.projectInterfaces=[&](auto&,unsigned kind){if(kind==2){event(1,1,8,4,8);event(1,1,12,4,9);}else for(int i=0;i<4;++i)event(1,1,4*i,4,int(kind)*4+i);};
  s.store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* pointer){const int id=pid(p);const int width=id==1&&(off==0x14||off==0x20||(off>=0x74&&off<=0x83))?1:4;
   const bool ptr=(id==1&&(off==0x24||off==0x28||off==0x2c||off==0x34||off==0x70))||(id>=31&&off>=0x100);
   event(1,id,off,width,ptr?pid(pointer):value);if(id==1&&off==0x50)mutate(1);if(id==31&&off==16)mutate(2);};
  s.waypoint6BFA90=[&](auto& t){++waypoint;event(2,pid(t.identity),waypoint);if(waypoint==1){mutate(3);mutate(7);}return std::uint32_t(f[waypoint==1?7:8]);};
  s.map548070=[&](auto p)->const void*{event(3,p);return &cellId;};
  s.allocate=[&](std::uint32_t size)->void*{const bool tagAllocation=size==56;void* p=f[11]&(tagAllocation?1:2)?(tagAllocation?static_cast<void*>(&tagStorage):static_cast<void*>(&scriptStorage)):nullptr;event(4,size,pid(p));if(tagAllocation)mutate(4);return p;};
  s.constructTag6B3870=[&](void* storage,const void* type)->const void*{const void* result=f[12]==0?nullptr:f[12]==1?storage:&otherTag;event(5,pid(storage),pid(type),pid(result));mutate(5);return result;};
  s.constructScript668730=[&](void* storage,const void* type)->const void*{const void* result=f[13]==0?nullptr:f[13]==1?storage:&otherScript;event(6,pid(storage),pid(type),pid(result));return result;};
  const auto* result=constructTeam(r,f[0]?&t1:nullptr,f[1]?&house:nullptr,std::uint32_t(f[5]),s);
  if(f[17]){
   const std::array<const void*,8> subjects{nullptr,&objectTag,r.tag70?r.tag70:static_cast<const void*>(&objectTag),t1.identity,house.identity,&scriptStorage,&cellId,&otherTag};
   expireConstructedTeamTag(r,subjects.at(f[17]),257,s.store);
  }
  std::cout<<trace.str()<<"F "<<pid(result)<<' '<<mutated<<' '<<std::uint32_t(frame)<<' '<<empty<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(count2)<<' '<<houseCount<<' ';
  for(int i=0;i<5;++i){std::cout<<std::uint32_t(counts[i])<<' '<<std::uint32_t(capacities[i])<<' '<<unsigned(allocated[i])<<' '<<(slots[i].data()==alt[i].data())<<' ';for(auto* p:slots[i])std::cout<<pid(p)<<' ';}
  std::cout<<std::uint32_t(r.index10)<<' '<<unsigned(r.flags14)<<' '<<r.value18<<' '<<r.value1C<<' '<<unsigned(r.byte20)<<' '<<pid(r.type24?r.type24->identity:nullptr)<<' '<<pid(r.script28)<<' '<<pid(r.house2C?r.house2C->identity:nullptr)<<' '<<r.value30<<' '<<pid(r.cell34)<<' '<<pid(r.value38)<<' '<<std::uintptr_t(r.value3C)<<' '<<std::uintptr_t(r.value40)<<' '<<r.argument44<<' '<<r.value48<<' '<<r.value4C<<' '<<r.timer50<<' '<<pid(r.value54)<<' '<<r.timer58<<' '<<r.value60<<' '<<r.timer64<<' '<<r.value6C<<' '<<pid(r.tag70)<<' ';
  for(auto b:r.flags74)std::cout<<unsigned(b)<<' ';for(auto n:r.values84)std::cout<<n<<' ';std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
