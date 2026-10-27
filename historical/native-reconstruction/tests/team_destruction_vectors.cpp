// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamDestruction.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team destruction fixture differs");}
void run(std::istream& in){
 std::array<int,15> f{};for(auto& v:f)require(bool(in>>v));std::string extra;require(!(in>>extra));
 TeamConstructionRecord team;int typeIds[2]{},houseId=0,tag=0,other=0;std::array<int,4> feet{},observers{};std::array<int,5> registryIds{};
 std::array<std::uint8_t,2> ee{std::uint8_t(f[2]),255};std::array<int,2> typeCounts{f[10],INT32_MIN};const void* unused=nullptr;
 TeamConstructionType types[2]{{&typeIds[0],ee[0],typeCounts[0],unused,unused},{&typeIds[1],ee[1],typeCounts[1],unused,unused}};
 std::uint32_t houseCount=std::uint32_t(f[9]);TeamConstructionHouse house{&houseId,houseCount};
 const auto id=[&](const void* p){if(!p)return 0;if(p==&team)return 1;for(int i=0;i<2;++i)if(p==&typeIds[i])return 2+i;if(p==&houseId)return 4;if(p==&tag)return 5;if(p==&other)return 6;for(int i=0;i<4;++i){if(p==&feet[i])return 10+i;if(p==&observers[i])return 20+i;}for(int i=0;i<5;++i)if(p==&registryIds[i])return 30+i;throw std::invalid_argument("Foreign destructor fixture pointer");};
 std::vector<std::uint64_t> trace;const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 team.type24=f[0]?&types[0]:nullptr;team.house2C=f[1]?&house:nullptr;team.value54=f[4]?&feet[0]:nullptr;team.tag70=f[5]==0?nullptr:f[5]==1?&tag:&other;team.flags74[0]=std::uint8_t(f[7]);team.flags74[15]=std::uint8_t(f[8]);
 std::array<const void*,4> next{};for(int i=0;i<4;++i)next[i]=i+1<f[4]?&feet[i+1]:nullptr;
 std::array<const void*,4> observerTypes{&typeIds[0],nullptr,&typeIds[1],&typeIds[0]};
 std::array<TeamDestructionObserver,4> views{{{&observers[0],observerTypes[0]},{&observers[1],observerTypes[1]},{&observers[2],observerTypes[2]},{&observers[3],observerTypes[3]}}};
 std::array<TeamDestructionObserver*,4> oback{},oalt{};for(int i=0;i<4;++i){oback[i]=&views[i];oalt[i]=&views[3-i];}
 std::span<TeamDestructionObserver*> observerSlots=oback;int observerCount=f[12];MissionExpirationVector<TeamDestructionObserver*> observerVector{observerCount,observerSlots,oback.data()};
 std::array<std::array<const void*,8>,5> slots{},alt{};std::array<int,5> counts{};std::array<std::span<const void*>,5> backing{};
 std::array<MissionExpirationVector<const void*>,5> regs{{{counts[0],backing[0],&registryIds[0]},{counts[1],backing[1],&registryIds[1]},{counts[2],backing[2],&registryIds[2]},{counts[3],backing[3],&registryIds[3]},{counts[4],backing[4],&registryIds[4]}}};
 const std::array<std::array<const void*,8>,4> patterns{{{&other,&team,&team,&other,&team,nullptr,nullptr,nullptr},{&team,&other,&team,nullptr,nullptr,nullptr,nullptr,nullptr},{&other,&other,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},{&other,&team,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}}};
 const int initialCounts[]{5,3,2,2};for(int i=0;i<5;++i){int profile=(f[11]+i)%4;counts[i]=initialCounts[profile];slots[i]=patterns[profile];alt[i]={&team,&other,&team,&other,&team,nullptr,nullptr,nullptr};backing[i]=slots[i];}
 int mutated=0;const auto mutate=[&](int where){if(mutated||f[13]!=where)return;mutated=1;event(9,where);
 if(where==1){team.type24=&types[1];team.flags74[15]=0;observerSlots=oalt;observerCount=4;}
 if(where==2){team.type24=&types[1];team.tag70=&other;}
 if(where==3){team.type24=&types[1];team.flags74[0]=128;}
 if(where==4){backing[0]=alt[0];counts[0]=5;}
 if(where==5){backing[0]=alt[0];counts[0]=1;}};
 const auto store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* pointer){bool ptr=p==&team&&off==0x70;for(auto& r:registryIds)if(p==&r&&off>=0x100)ptr=true;event(1,id(p),std::uint32_t(off),4,ptr?id(pointer):value);if(p==&registryIds[0]&&off==0x100)mutate(5);};
 const std::uint8_t active=std::uint8_t(f[3]);TeamDestructionServices s{observerVector,active,4};s.store=store;
 s.projectDerivedInterfaces=[&](auto& t){require(&t==&team);for(int i=0;i<4;++i)event(1,1,4*i,4,i);};
 s.notifyObserver=[&](const void* p,bool enabled){event(2,id(p),enabled);mutate(1);};
 s.removeMember=[&](auto& t,const void* p,int slot,std::uint32_t suppress){require(&t==&team&&slot==-1&&!suppress);event(3,id(p),0xffffffffu,0);t.value54=next[id(p)-10];mutate(2);};
 s.tagInstances=[&](const void* p){return p==&tag?f[6]:0;};s.destroyTag=[&](const void* p){event(4,id(p));};
 s.expire=[&](auto& t,std::uint32_t flag){require(&t==&team&&flag==1);event(5,1,1);mutate(3);};
 for(int i=0;i<5;++i)s.removeFromRegistry[i]=[&,i](const void* p){const int found=findMissionExpiration(regs[i],p);event(6,30+i,std::uint32_t(found));if(i==0)mutate(4);eraseMissionExpiration(regs[i],found,store);};
 s.destroyType=[&](auto& t,std::uint32_t flag){require(flag==1);event(7,id(t.identity),1);};s.destroyBase=[&](auto& t){require(&t==&team);event(8,1);};s.freeRecord=[&](auto& t){require(&t==&team);event(10,1);};
 const auto result=deleteTeam(team,std::uint32_t(f[14]),s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<id(result)<<' '<<mutated<<' '<<id(team.type24?team.type24->identity:nullptr)<<' '<<id(team.value54)<<' '<<id(team.tag70)<<' '<<houseCount<<' '<<std::uint32_t(typeCounts[0])<<' '<<std::uint32_t(typeCounts[1])<<' '<<int(team.flags74[0])<<' '<<int(team.flags74[15])<<' '<<observerCount<<' ';
 for(auto& r:regs){std::cout<<r.count<<' ';for(auto p:r.slots)std::cout<<id(p)<<' ';}std::cout<<'\n';
}
void guards(){
 int count=0;std::span<TeamDestructionObserver*> slots;MissionExpirationVector<TeamDestructionObserver*> observers{count,slots,nullptr};std::uint8_t active=1;TeamConstructionRecord team;TeamDestructionServices s{observers,active,1};
 bool refused=false;try{deleteTeam(team,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 // A missing child refuses after earlier effects; never pretend rollback.
 std::vector<int> trace;s.projectDerivedInterfaces=[&](auto&){trace.push_back(1);};s.expire=[&](auto&,auto){trace.push_back(2);};
 refused=false;try{deleteTeam(team,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&trace==std::vector<int>({1,2}));
 // Bound a non-progressing removal child before it can hang the app.
 std::uint8_t ee=0;int tc=0;const void* ptr=nullptr;int typeIdentity=0;
 TeamConstructionType type{&typeIdentity,ee,tc,ptr,ptr};team.type24=&type;team.value54=&typeIdentity;s.removeMember=[](auto&,auto,auto,auto){};refused=false;
 try{destroyTeam(team,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&tc==0);
 std::cout<<"team destruction guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
