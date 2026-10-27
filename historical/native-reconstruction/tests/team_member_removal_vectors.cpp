// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamMemberRemoval.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team removal fixture differs");}
void run(std::istream& in){
 std::array<int,21> f{};for(auto& v:f)require(bool(in>>v));std::string extra;require(!(in>>extra));
 struct Foot{const void* team=nullptr;const void* next=nullptr;const void* tag=nullptr;std::uint8_t flag=128,leader=0,onMap=1,busy=0,limbo=0;int field=123;const void* link=nullptr;const void* target=nullptr;};
 TeamConstructionRecord team;std::array<Foot,4> feet;int old=0,tag=0,otherTag=0,house=0,type=0,footType=0,cell=0;
 const auto id=[&](const void* p){if(!p)return 0;if(p==&team)return 1;if(p==&old)return 2;for(int i=0;i<4;++i)if(p==&feet[i])return 10+i;if(p==&tag)return 30;if(p==&otherTag)return 31;if(p==&house)return 40;if(p==&type)return 50;if(p==&footType)return 70;if(p==&cell)return 80;throw std::invalid_argument("Foreign removal fixture pointer");};
 std::array<std::array<const void*,6>,2> types{};int count=f[5],count2=2;int currentTask=f[7]==2?1:0;
 for(int t=0;t<2;++t)for(int i=0;i<6;++i)types[t][i]=i==(t?1:f[6])?&footType:&type;
 std::vector<std::uint64_t> trace;const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 const auto at=[&](int i){return f[2]?f[0]-1-i:i;};
 for(int i=0;i<4;++i){auto& a=feet[i];a.team=f[12]?static_cast<const void*>(&team):&old;a.tag=f[13]==0?nullptr:f[13]==1?&tag:&otherTag;a.leader=(f[4]>>i)&1;a.onMap=f[16];a.busy=f[17];a.limbo=f[18];a.link=&cell;a.target=&cell;}
 for(int i=0;i<f[0]-1;++i)feet[at(i)].next=&feet[at(i+1)];
 team.value54=&feet[at(0)];team.tag70=&tag;team.cell34=&cell;team.value48=std::uint32_t(f[8]);team.value4C=std::uint32_t(f[9]);team.values84.fill(std::uint32_t(f[11]));
 const auto store=[&](const void* p,std::int64_t off,std::uint32_t v,const void* pointer){const bool ptr=p==&team?(off==0x54||off==0x34):(off==0x4c4||off==0x4c8||off==0x498||off==0x22c);const int width=p==&team?(off==0x7d||off==0x7e?1:4):(off==0x5a2||off==0x579?1:4);event(1,id(p),std::uint32_t(off),width,ptr?id(pointer):v);};
 int mutated=0;const auto mutate=[&](int where){if(mutated||f[20]!=where)return;mutated=1;event(9,where);if(where==1)count=0;if(where==2)currentTask=2;if(where==3)team.value4C=0xfffffff0u;if(where==4)team.value54=&feet[3];if(where==5)feet[f[1]].tag=&otherTag;};
 TeamRemovalServices s{f[15],4};s.store=store;
 s.foot=[&](const void* p){const auto i=id(p)-10;require(i>=0&&i<4);auto& a=feet[i];return TeamRemovalFoot{p,a.team,a.next,a.flag,a.field,a.link,a.target,a.leader,a.onMap,a.busy,a.limbo};};
 s.tag34=[&](const void* p){return feet[id(p)-10].tag;};s.house1B4=[&](const void*)->const void*{return &house;};
 s.controlled4F52F0=[&](const void* p){require(p==&house);event(2,40,std::uint32_t(f[14]));mutate(5);return std::uint32_t(f[14]);};
 s.clearTag5D4430=[&](const void* p){event(3,id(p));feet[id(p)-10].tag=nullptr;};
 s.task=[&]()->std::optional<TeamRemovalTask>{if(!f[7]||!currentTask)return {};return TeamRemovalTask{currentTask==1?count:count2,types[currentTask-1]};};
 s.type84=[&](const void* p)->const void*{event(4,id(p));mutate(1);mutate(2);return &footType;};
 s.threat2A0=[&](const void* p){event(5,id(p));mutate(3);return std::uint32_t(f[10]);};
 s.resume414=[&](const void* p,const void* target,std::uint32_t flag){require(!target&&flag==1);event(6,id(p),0,flag);mutate(4);};
 const auto result=removeTeamMember(team,&feet[f[1]],f[3],std::uint32_t(f[19]),s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<result<<' '<<mutated<<' '<<id(team.value54)<<' '<<team.value48<<' '<<team.value4C<<' '<<id(team.cell34)<<' '<<int(team.flags74[9])<<' '<<int(team.flags74[10])<<' ';for(auto v:team.values84)std::cout<<v<<' ';std::cout<<(currentTask?59+currentTask:0)<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(count2)<<' ';
 for(const auto& a:feet)std::cout<<id(a.team)<<' '<<id(a.next)<<' '<<id(a.tag)<<' '<<int(a.flag)<<' '<<std::uint32_t(a.field)<<' '<<id(a.link)<<' '<<id(a.target)<<' '<<int(a.leader)<<' ';std::cout<<'\n';
}
void guards(){TeamConstructionRecord t;const int zero=0;TeamRemovalServices s{zero,0};bool refused=false;try{removeTeamMember(t,nullptr,-1,0,s);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"team removal guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
