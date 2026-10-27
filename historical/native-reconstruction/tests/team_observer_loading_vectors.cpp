// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TeamObserverInputs.hpp"
#include "sim/StringLookup.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Observer loading fixture differs");}
std::string unhex(const std::string& s){if(s=="-")return {};require(s.size()%2==0);std::string out;for(std::size_t i=0;i<s.size();i+=2)out.push_back(char(std::stoul(s.substr(i,2),nullptr,16)));return out;}
std::uint32_t hash(std::string_view s){std::uint32_t v=2166136261u;for(auto c:s){if(!c)break;v=(v^std::uint8_t(c))*16777619u;}return v;}
void run(std::istream& in){
 std::string raw;std::array<int,7> f;require(bool(in>>raw));for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[1]>=0&&f[1]<9&&f[2]>=-1&&f[2]<=3&&f[4]>=0&&f[4]<=4&&f[5]>=0&&f[5]<=4&&f[6]>=1&&f[6]<=2);
 const auto line=raw=="~"?std::optional<std::string>{}:std::optional<std::string>{unhex(raw)};
 TeamObserverType r;r.identifier24.fill(0);std::string key="observer";std::copy(key.begin(),key.end(),r.identifier24.begin());r.name64.fill('Q');r.name64.back()=0;
 r.condition98=-7;r.valueA0=44;r.valueA8=-3;r.valueAC=55;r.valueB0=66;r.weightB8=23.75;r.minimumC0=-2.5;r.maximumC8=99.25;r.flagsD0={128,129,130,131,132};r.conditionsE4.fill(0xaabbccddu);r.successes104=7;r.trials108=11;
 int team[3]{},objects[4]{},tech[3]{},task[2]{};r.teamDC=&team[0];r.teamE0=&team[1];r.objectD8=&objects[3];
 const auto id=[&](const void* p){if(!p)return 0;for(int i=0;i<3;++i){if(p==&team[i])return i+1;if(p==&tech[i])return i+21;}for(int i=0;i<4;++i)if(p==&objects[i])return i+11;throw std::invalid_argument("Unknown observer loader identity");};
 const std::array<std::string,3> identifiers{"ALPHA","beta","alias"},names{"first team","second team","ALPHA"};
 std::array<const void*,3> slots{&team[0],&team[1],&team[2]},alt{&team[1],&team[0],&team[2]};std::span<const void*> backing=f[5]==1?std::span<const void*>(alt):std::span<const void*>(slots);int count=f[5]==2?0:f[5]==3?-1:f[5]==4?1:3,session=f[0],taskCount[2]{f[1]==6?0:f[1]==7?-1:f[1]==8?1:3,f[1]==6?0:f[1]==7?INT32_MIN:f[1]==8?3:2};
 const int levels[6][3]{{5,-1,20},{20,-1,5},{-1,20,-1},{INT32_MIN,0,INT32_MAX},{1,2,3},{-1,-1,-1}};std::array<int,3> level;std::copy_n(levels[f[1]%6],3,level.begin());
 std::array<TeamAdmissionEntry,3> entries{{{1,&tech[0]},{2,&tech[1]},{3,&tech[2]}}};
 std::vector<std::uint64_t> trace;const auto event=[&](std::uint64_t k,std::uint64_t a=0,std::uint64_t b=0,std::uint64_t c=0){trace.insert(trace.end(),{k,a,b,c});};int mutated=0;
 const auto mutate=[&](int where){if(mutated||f[4]!=where)return;mutated=1;event(13,where);
  if(where==1)backing=alt;
  if(where==2){taskCount[0]=1;taskCount[1]=1;session=0;level[1]=42;}
  if(where==3){r.teamDC=&team[1];r.teamE0=&team[0];r.valueB0=123;}
  if(where==4)r.teamDC=&team[1];};
 const auto compare=[&](std::string_view a,std::string_view b){event(2,hash(a),hash(b));const auto result=compareStringLookupKeys(a,b);return result;};
 TeamObserverTypeLookup lookup{count,backing,[&](const void* p){const int i=id(p)-1;return TeamObserverTypeNames{identifiers[i],names[i]};},{}};
 lookup.compare=[&](auto a,auto b){const auto result=compare(a,b);mutate(1);return result;};
 TeamObserverInputServices s;s.value=[&](auto name){event(3,hash(name));return line;};s.compare=compare;
 s.teamType=[&](auto name){event(12,hash(name));return findTeamObserverTeamType(name,lookup);};
 s.countryIndex=[&](auto name){event(6,hash(name),std::uint32_t(f[3]));return f[3];};
 std::array<std::array<const void*,1>,4> objectSlots{};for(int i=0;i<4;++i){objectSlots[i][0]=&objects[i];s.objectIndex[i]=[&,i](auto name){const int result=f[2]==i?0:-1;event(7,i,hash(name),std::uint32_t(result));return result;};s.objectSlots[i]=[&,i](){return std::span<const void*>(objectSlots[i]);};}
 s.integer=[&](auto token){const auto v=std::uint32_t(std::strtoll(std::string(token).c_str(),nullptr,10));event(4,hash(token),v);return std::bit_cast<std::int32_t>(v);};
 s.number=[&](auto token){const double v=std::strtod(std::string(token).c_str(),nullptr);event(5,hash(token),std::bit_cast<std::uint64_t>(v));return v;};
 s.space=[&](int c){const bool b=c==' '||c=='\t'||c=='\n'||c=='\r'||c=='\f'||c=='\v';event(8,std::uint32_t(c),b);return b;};
 s.hexPair=[&](auto token){const auto value=std::uint32_t(std::strtoull(std::string(token).c_str(),nullptr,16));event(9,hash(token),value);return value;};
 s.taskForceTech=[&](const void* p){const int i=id(p)==2?1:0;event(11,i);return teamObserverTaskForceTech({{taskCount[i],entries},session,[&](const void* q){const auto index=id(q)-21;const auto value=level[index];event(10,id(q),std::uint32_t(value));mutate(2);mutate(4);return value;}});};
 s.store=[&](const void* p,auto off,auto n,auto v,const void* pointer){require(p==&r);const bool ptr=off==0xd8||off==0xdc||off==0xe0;event(1,std::uint64_t(off),n,ptr?std::uint64_t(id(pointer)):v);if(off==0xb8&&n==8)mutate(3);};
 bool result=false;for(int i=0;i<f[6];++i)result=loadTeamObserverInputs(r,s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<result<<' '<<mutated<<' ';for(auto v:r.name64)std::cout<<int(v)<<' ';
 for(auto v:{std::uint32_t(r.condition98),r.valueA0,std::uint32_t(r.valueA8),r.valueAC,r.valueB0})std::cout<<v<<' ';for(auto v:{r.weightB8,r.minimumC0,r.maximumC8})std::cout<<std::bit_cast<std::uint64_t>(v)<<' ';for(auto v:r.flagsD0)std::cout<<int(v)<<' ';
 for(auto p:{r.objectD8,r.teamDC,r.teamE0})std::cout<<id(p)<<' ';for(auto v:r.conditionsE4)std::cout<<v<<' ';std::cout<<std::uint32_t(r.successes104)<<' '<<std::uint32_t(r.trials108)<<' '<<std::uint32_t(taskCount[0])<<' '<<std::uint32_t(taskCount[1])<<' '<<std::uint32_t(session)<<' ';
 for(auto v:level)std::cout<<std::uint32_t(v)<<' ';std::cout<<std::uint32_t(count)<<' ';for(auto p:backing)std::cout<<id(p)<<' ';std::cout<<'\n';
}
void guards(){
 TeamObserverType r;TeamObserverInputServices s;bool refused=false;try{loadTeamObserverInputs(r,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 int count=1,session=1;std::array<TeamAdmissionEntry,1> entries{{{1,nullptr}}};refused=false;try{teamObserverTaskForceTech({{count,entries},session,[](auto){return 0;}});}catch(const std::invalid_argument&){refused=true;}require(refused);
 count=0;require(teamObserverTaskForceTech({{count,{}},session,{}})==0);
 std::span<const void*> slots;TeamObserverTypeLookup w{count,slots,{},{}};require(findTeamObserverTeamType(std::nullopt,w)==nullptr);
 count=1;refused=false;try{findTeamObserverTeamType("a",w);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"team observer loading guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
