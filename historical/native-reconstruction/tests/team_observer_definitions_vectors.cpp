// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TeamObserverDefinitions.hpp"
#include "assets/TeamObserverInputs.hpp"
#include "sim/StringLookup.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Observer definition fixture differs");}
std::uint32_t hash(std::string_view s){std::uint32_t v=2166136261u;for(auto c:s){if(!c)break;v=(v^std::uint8_t(c))*16777619u;}return v;}
const std::array<std::vector<std::string>,9> keys{{{}, {"alpha"},{"alpha","beta","alpha"},{"<none>","none","gamma"},{"1234567890123456789012345"},{"ALPHA","Beta"},{},{"gamma","delta"},{}}};
const std::array<std::vector<std::string>,9> enable{{{}, {"alpha"},{"alpha","beta","unknown"},{"none","gamma"},{"1234567890123456789012345"},{"ALPHA","beta"},{"alpha","beta","none"},{"delta","gamma"},{}}};
void run(std::istream& in){
 std::array<std::int64_t,9> f;for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<=0xffffffffll&&f[1]>=0&&f[1]<9&&f[2]>=0&&f[2]<4&&f[3]>=0&&f[3]<3&&f[4]>=0&&f[4]<=0xffffffffll&&f[5]>=0&&f[5]<=0xffffffffll&&f[6]>=INT32_MIN&&f[6]<=INT32_MAX&&f[7]>=0&&f[7]<7&&f[8]>=1&&f[8]<=2);
 std::array<TeamObserverType,8> records;std::array<TeamObserverType*,8> slots{},alt{};
 const auto id=[&](const void* p){if(!p)return 0u;for(unsigned i=0;i<records.size();++i)if(p==&records[i])return i+1;throw std::invalid_argument("Foreign observer identity");};
 const auto setName=[&](unsigned i,std::string_view key){auto& r=records[i];r.identifier24.fill(0);std::copy_n(key.begin(),std::min<std::size_t>(24,key.size()),r.identifier24.begin());};
 for(unsigned i=0;i<8;++i){slots[i]=&records[i];alt[i]=&records[i];records[i].value9C=0x11220000+i;records[i].byteA4=128+i;records[i].valueB0=20+i;setName(i,i==0?"alpha":i==1?"beta":"unused");}
 std::swap(alt[0],alt[1]);std::span<TeamObserverType*> backing=f[2]==2?std::span<TeamObserverType*>(alt):std::span<TeamObserverType*>(slots);
 int count=f[2]==0?0:f[2]==3?-1:2,session=int(f[6]);unsigned next=2,allocations=0,mutated=0;std::vector<std::uint64_t> trace;
 const auto event=[&](std::uint64_t k,std::uint64_t a=0,std::uint64_t b=0,std::uint64_t c=0){trace.insert(trace.end(),{std::uint64_t(k),std::uint64_t(a),std::uint64_t(b),std::uint64_t(c)});};
 const auto mutate=[&](int where){if(mutated||f[7]!=where)return;mutated=1;event(9,where);
  if(where==1)backing=alt;
  if(where==2){session=1;count=1;backing=alt;}
  if(where==3)session=1;
  if(where==5)count=0;
  if(where==6)backing[0]=nullptr;};
 TeamObserverDefinitionServices s{{},{},{},{},{},{},{},session,{}};
 s.entryCount=[&](auto section){unsigned n=section=="AITriggerTypes"?0:1;int result=f[1]==8?-1:int((n?enable:keys)[f[1]].size());event(1,n,std::uint32_t(result));return result;};
 s.entryKey=[&](auto section,int i)->std::string_view{unsigned n=section=="AITriggerTypes"?0:1;const auto& key=(n?enable:keys)[f[1]].at(i);event(2,n,i,hash(key));return key;};
 s.compare=[&](auto a,auto b){event(3,hash(a),hash(b));const int result=compareStringLookupKeys(a,b);if(a=="alpha"&&b=="alpha"){mutate(1);mutate(6);}if(a=="alpha"&&result)mutate(5);return result;};
 s.allocate=[&](unsigned size)->void*{++allocations;auto* p=(f[3]==1||(f[3]==2&&allocations==2))?nullptr:&records.at(next++);event(4,size,id(p));return p;};
 s.construct=[&](void* memory,auto key){auto* r=static_cast<TeamObserverType*>(memory);event(5,id(r),hash(key));setName(id(r)-1,key);r->value9C=0;r->byteA4=0;r->valueB0=0;require(count>=-1&&count<8);if(count<0)throw std::invalid_argument("Negative supplied construction count");backing[count++]=r;return r;};
 s.load=[&](auto& r){event(6,id(&r),std::uint32_t(f[4]));++r.valueB0;mutate(2);return bool(std::uint8_t(f[4]));};
 s.boolean=[&](auto section,auto key,bool fallback){require(section=="AITriggerTypesEnable"&&!fallback);event(7,hash(key),std::uint32_t(f[5]));mutate(3);return std::uint32_t(f[5]);};
 s.store=[&](const void* p,auto off,auto n,auto v,const void*){require(n==(off==0xa4?1:4));event(8,id(p),off,v);if(off==0x9c&&f[7]==4&&!mutated){mutated=1;event(9,4);static_cast<TeamObserverType*>(const_cast<void*>(p))->byteA4=77;}};
 for(int i=0;i<f[8];++i)loadTeamObserverDefinitions(std::uint32_t(f[0]),{count,backing},s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<mutated<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(session)<<' '<<next<<' '<<allocations<<' ';for(auto p:backing)std::cout<<id(p)<<' ';
 for(auto& r:records){std::cout<<r.value9C<<' '<<unsigned(r.byteA4)<<' '<<r.valueB0<<' '<<hash(std::string_view(reinterpret_cast<const char*>(r.identifier24.data())))<<' ';}std::cout<<'\n';
}
void guards(){
 int count=0,session=0;std::span<TeamObserverType*> backing;TeamObserverDefinitionServices s{{},{},{},{},{},{},{},session,{}};
 bool refused=false;try{loadTeamObserverDefinitions(0,{count,backing},s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 s.entryCount=[](auto){return 1;};s.entryKey=[](auto,int){return std::string_view("none");};s.compare=compareStringLookupKeys;
 refused=false;try{loadTeamObserverDefinitions(1,{count,backing},s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"team observer definitions guards PASS\n";
}
void composition(){
 // Actual native constructor/loader composition. This is separate from the
 // original parent proof's supplied construction and record-loading services.
 std::array<TeamObserverType,4> records;std::array<TeamObserverType*,4> typed{};
 std::array<const void*,4> abstractSlots{},observerSlots{};
 std::span<TeamObserverType*> backing(typed);int count=0,abstractCount=0;
 int capacity=4,abstractCapacity=4,increment=4,session=0;std::uint8_t allocated=1;
 std::span<const void*> abstractBacking(abstractSlots),observerBacking(observerSlots);
 TeamConstructionRegistry abstractRegistry{{abstractCount,abstractBacking,&abstractSlots},abstractCapacity,allocated,increment,{},{}};
 TeamConstructionRegistry observerRegistry{{count,observerBacking,&observerSlots},capacity,allocated,increment,{},{}};
 observerRegistry.appendSlot=[&](int i,const void* p){require(i>=0&&i<4);observerSlots[i]=p;typed[i]=static_cast<TeamObserverType*>(const_cast<void*>(p));};
 TeamObserverConstructionServices construction{abstractRegistry,observerRegistry,nullptr,{},{},{}};
 int teamIdentity=0,teamCount=1;std::array<const void*,1> teamSlots{&teamIdentity};std::span<const void*> teamBacking(teamSlots);
 TeamObserverTypeLookup teamLookup{teamCount,teamBacking,[](auto){return TeamObserverTypeNames{"alpha","First team"};},compareStringLookupKeys};
 TeamObserverInputServices input;input.value=[](auto)->std::optional<std::string>{return "Observer,alpha,<none>,ignored,7,Target,0123,10.9,-1.2,100,1,unused,2,1,<none>,1,1,0";};
 input.compare=compareStringLookupKeys;input.teamType=[&](auto name){return findTeamObserverTeamType(name,teamLookup);};
 input.countryIndex=[](auto){return -1;};for(auto& f:input.objectIndex)f=[](auto){return -1;};
 input.integer=[](auto t){return std::atoi(std::string(t).c_str());};input.number=[](auto t){return std::strtod(std::string(t).c_str(),nullptr);};
 input.space=[](int c){return c==32||(c>=9&&c<=13);};input.hexPair=[](auto t){return std::uint32_t(std::strtoul(std::string(t).c_str(),nullptr,16));};input.taskForceTech=[](auto){return 7;};
 TeamObserverDefinitionServices services{{},{},compareStringLookupKeys,{},{},{},{},session,{}};
 services.entryCount=[](auto section){return section=="AITriggerTypes"?2:1;};services.entryKey=[](auto,int){return std::string_view("observer");};
 unsigned next=0;services.allocate=[&](auto size)->void*{require(size==0x110&&next<4);return &records[next++];};
 services.construct=[&](void* p,auto key){std::string name(key);name.push_back(0);auto* r=static_cast<TeamObserverType*>(p);constructTeamObserverType(*r,std::span<const std::uint8_t>(reinterpret_cast<const std::uint8_t*>(name.data()),name.size()),construction);return r;};
 services.load=[&](auto& r){return loadTeamObserverInputs(r,input);};services.boolean=[](auto,auto,bool){return 256u;};
 loadTeamObserverDefinitions(0,{count,backing},services);
 require(count==1&&abstractCount==1&&next==1&&typed[0]==&records[0]&&abstractSlots[0]==&records[0]);
 const auto& r=records[0];require(r.teamDC==&teamIdentity&&r.teamE0==nullptr&&r.value9C==0&&r.byteA4==0&&r.valueB0==7&&r.weightB8==10&&r.minimumC0==4294967295.&&r.conditionsE4[0]==0x2301&&r.trials108==0);
 loadTeamObserverDefinitions(1,{count,backing},services);require(count==1&&abstractCount==1&&next==1&&r.value9C==1&&r.byteA4==1);
 std::cout<<"team observer definitions composition PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}if(argc==2&&std::string(argv[1])=="--composition"){composition();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
