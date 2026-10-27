// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamObserverConstruction.hpp"
#include <iostream>
#include <cfenv>

#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Observer construction fixture differs");}
void run(std::istream& in){
 std::array<int,10> f;for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<=7&&f[1]>=0&&f[1]<6&&f[2]>=0&&f[2]<6&&f[4]>=0&&f[4]<=4&&f[5]>=0&&f[5]<=255&&f[6]>=0&&f[6]<=2&&f[7]>=0&&f[7]<=2&&(f[8]==0||f[8]==1)&&(f[9]==0||f[9]==1));
 TeamObserverType r;r.flags14=std::uint8_t(f[5]);r.identifier24.fill(0x5a);r.name64.fill(0x5a);r.weightB8=r.minimumC0=r.maximumC8=std::bit_cast<double>(0x5a5a5a5a5a5a5a5aull);
 int empty=0,other=0,type[2]{},registryIds[2]{};r.text60=r.objectD8=r.teamDC=r.teamE0=&other;
 std::array<std::uint8_t,64> name;name.fill(0x5a);const int lengths[]{0,0,1,23,24,49,0,0};
 for(int i=0;i<lengths[f[0]];++i)name[i]=std::uint8_t('a'+i%26);name[lengths[f[0]]]=0;
 const auto id=[&](const void* p)->int{if(!p)return 0;if(p==&r)return 1;if(p==&other)return 2;if(p==&empty)return 20;for(int i=0;i<2;++i){if(p==&type[i])return 31+i;if(p==&registryIds[i])return 91+i;}throw std::invalid_argument("Unknown observer fixture pointer");};
 std::vector<std::uint64_t> trace;const auto event=[&](int k,int owner=0,std::uint32_t off=0,std::uint32_t n=0,std::uint64_t value=0){trace.insert(trace.end(),{std::uint64_t(k),std::uint64_t(owner),off,n,value});};
 std::array<int,2> count{},capacity{},growth{};std::array<std::uint8_t,2> allocated{},valid{90,90};
 std::array<std::array<const void*,8>,2> slots{},alt{};std::array<std::span<const void*>,2> backing{};
 std::array<TeamConstructionRegistry,2> regs{{{{count[0],backing[0],&registryIds[0]},capacity[0],allocated[0],growth[0],{},{}},{{count[1],backing[1],&registryIds[1]},capacity[1],allocated[1],growth[1],{},{}}}};
 const int profiles[6][4]{{2,6,1,3},{2,2,0,3},{2,2,128,0},{0,0,0,3},{2,2,128,3},{2,2,1,INT32_MAX}};
 for(int i=0;i<2;++i){const auto* p=profiles[f[1+i]];count[i]=p[0];capacity[i]=p[1];allocated[i]=std::uint8_t(p[2]);growth[i]=p[3];slots[i].fill(&other);alt[i].fill(nullptr);backing[i]=slots[i];}
 int mutated=0;
 const auto mutate=[&](int where){if(mutated||f[4]!=where)return;mutated=1;
  if(where==1){name.fill(0);const std::string text="changed";std::copy(text.begin(),text.end(),name.begin());}
  if(where==2)backing[0]=alt[0];
  if(where==4)r.identifier24[0]='Z';};
 TeamObserverConstructionStore store=[&](const void* p,auto off,auto n,auto v,const void* pointer){
  bool isPointer=p==&r&&(off==0x60||off==0xd8||off==0xdc||off==0xe0);if(p==&registryIds[0]||p==&registryIds[1])isPointer=off>=0x100||off==4;
  event(1,id(p),std::uint32_t(off),n,isPointer?std::uint64_t(id(pointer)):v);
  if(p==&r&&off==0x10)mutate(1);
  if(p==&registryIds[0]&&off==16)mutate(2);
  if(p==&r&&off==0x3c)mutate(4);
 };
 for(int i=0;i<2;++i)regs[i].resize=[&,i](int cap,std::uint32_t zero){require(!zero);event(4,91+i,std::uint32_t(cap),0,std::uint32_t(f[3]));
  if(std::uint8_t(f[3])){if(backing[i].empty())alt[i].fill(nullptr);else std::copy(backing[i].begin(),backing[i].end(),alt[i].begin());backing[i]=alt[i];capacity[i]=cap;allocated[i]=1;}
  if(!mutated&&f[4]==3){mutated=1;count[i]=1;}
  return std::uint32_t(f[3]);};
 if(f[8])initializeTeamObserverRegistry(regs[1],valid[1],[&](){event(1,92,0,4,14);},[&](){event(5);},store);
 TeamObserverConstructionServices s{regs[0],regs[1],&empty};s.store=store;
 s.formatNullName=[&](const void* p){require(p==&r);event(2,1);std::array<std::uint8_t,24> out{};const std::string text="supplied-null-name";std::copy(text.begin(),text.end(),out.begin());return out;};
 s.projectInterfaces=[&](const void* p,unsigned phase){require(p==&r);if(phase==2){event(1,1,8,4,0);event(1,1,12,4,1);}else{int first=phase==1?2:phase==3?6:10;for(int i=0;i<4;++i)event(1,1,i*4,4,first+i);}};
 std::optional<std::span<const std::uint8_t>> input;
 if(f[0])input=f[0]==6?std::span<const std::uint8_t>(r.identifier24):f[0]==7?std::span<const std::uint8_t>(r.name64):std::span<const std::uint8_t>(name);
 // The oracle separately checks the supplied CRT copy service ABI.
 constructTeamObserverType(r,input,s);
 setTeamObserverPrimaryType(r,f[6]?&type[f[6]-1]:nullptr,store);
 if(f[7]){double positive=1,negative=-1,coefficient=.5;TeamObserverWeightServices w;
  w.rules=[&](){return TeamObserverRules{positive,negative,coefficient};};w.store=[&](auto off,auto n,auto v){store(&r,off,n,v,nullptr);};
  const int previous=std::fegetround();require(std::fesetround(f[9]?FE_TOWARDZERO:FE_TONEAREST)==0);updateTeamObserverWeight(r.weight(),f[7]==1,w);require(std::fesetround(previous)==0);}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<mutated<<' '<<std::uint32_t(r.index10)<<' '<<int(r.flags14)<<' '<<r.value18<<' '<<r.value1C<<' '<<int(r.byte20)<<' '<<int(r.byte3D)<<' '<<id(r.text60)<<' ';
 for(auto v:r.identifier24)std::cout<<int(v)<<' ';for(auto v:r.name64)std::cout<<int(v)<<' ';
 for(auto v:{std::uint32_t(r.condition98),r.value9C,r.valueA0,std::uint32_t(r.byteA4),std::uint32_t(r.valueA8),r.valueAC,r.valueB0})std::cout<<v<<' ';
 for(auto v:{r.weightB8,r.minimumC0,r.maximumC8})std::cout<<std::bit_cast<std::uint64_t>(v)<<' ';for(auto v:r.flagsD0)std::cout<<int(v)<<' ';
 for(auto p:{r.objectD8,r.teamDC,r.teamE0})std::cout<<id(p)<<' ';for(auto v:r.conditionsE4)std::cout<<v<<' ';std::cout<<std::uint32_t(r.successes104)<<' '<<std::uint32_t(r.trials108)<<' ';
 for(int i=0;i<2;++i){std::cout<<std::uint32_t(count[i])<<' '<<std::uint32_t(capacity[i])<<' '<<int(valid[i])<<' '<<int(allocated[i])<<' '<<std::uint32_t(growth[i])<<' ';if(backing[i].empty()){for(int j=0;j<8;++j)std::cout<<0<<' ';}else for(auto p:backing[i])std::cout<<id(p)<<' ';}
 std::cout<<'\n';
}
void guards(){
 TeamObserverType r;int count=0,cap=0,growth=0;std::uint8_t allocated=0,valid=0;std::span<const void*> slots;int id=0;TeamConstructionRegistry reg{{count,slots,&id},cap,allocated,growth,{},{}};TeamObserverConstructionServices s{reg,reg,nullptr};
 bool refused=false;try{constructTeamObserverType(r,std::nullopt,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&r.index10==-1&&r.identifier24[0]==0&&r.condition98==0);
 const std::array<std::uint8_t,1> shortInput{'a'};refused=false;try{constructTeamObserverType(r,std::span<const std::uint8_t>(shortInput),s);}catch(const std::invalid_argument&){refused=true;}require(refused&&r.condition98==0);
 refused=false;try{initializeTeamObserverRegistry(reg,valid,{},[]{},{});}catch(const std::invalid_argument&){refused=true;}require(refused&&valid==1&&count==0);
 std::cout<<"team observer construction guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
