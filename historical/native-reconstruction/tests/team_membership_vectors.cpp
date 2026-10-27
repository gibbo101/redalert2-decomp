// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamMembership.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team membership fixture/domain differs");}
struct Foot{const void* team=nullptr;const void* next=nullptr;MissionTagState* tag=nullptr;int group=123;
    std::uint8_t leader=0,recruit=1,onmap=1,limbo=0,active=1;int health=125;Coord position{};};
void run(std::istream& in){
 std::array<std::int32_t,33> f{};for(auto& x:f)require(bool(in>>x));std::string extra;require(!(in>>extra));
 TeamConstructionRecord team;int old=0,cell=0,script=0,typeId=0,houseId=0;
 TeamConstructionType* typePointer=nullptr;std::uint8_t houseFlag=0;int typeCount=0;const void* null=nullptr;
 TeamConstructionType construction{&typeId,houseFlag,typeCount,null,null};typePointer=&construction;
 std::uint32_t houseCount=0;TeamConstructionHouse house{&houseId,houseCount};
 int persistence=0,instances=0,oldInstances=10;std::uint8_t executing=0;MissionTagType tagType{persistence};MissionTagType* tagTypePointer=&tagType;MissionTagTrigger* first=nullptr;
 MissionTagState tag{tagTypePointer,first,instances,executing},oldTag{tagTypePointer,first,oldInstances,executing};
 std::array<Foot,3> feet;int group=f[8],tfGroup=f[9];std::uint8_t b3=f[11],ed=f[13],weight=f[19];
 TeamMembershipType type{group,f[10]?&tfGroup:nullptr,b3,ed,weight};
 for(int i=0;i<3;++i){auto& a=feet[i];a.team=i==0&&f[4]?&old:nullptr;a.next=i<2?&feet[i+1]:nullptr;a.tag=&oldTag;
  a.leader=i==0?f[25]:i==1;a.onmap=f[22];a.health=f[23];a.limbo=f[24];a.active=f[26];
  a.position=f[32]?Coord{i?INT32_MIN+17:INT32_MAX-11,i?INT32_MAX-7:INT32_MIN+13,104}:Coord{-257+i*770,511-i*640,104+i*104};}
 team.flags74[9]=1;team.type24=typePointer;team.house2C=&house;team.script28=&script;team.value54=f[5]?&feet[std::size_t(f[5]-1)]:nullptr;
 team.cell34=f[6]==1?static_cast<const void*>(&cell):f[6]==2?&feet[0]:nullptr;team.value38=f[6]==2?&feet[0]:nullptr;team.tag70=f[7]?&tag:nullptr;
 team.value48=std::uint32_t(f[15]);team.value4C=std::uint32_t(f[16]);team.values84.fill(std::uint32_t(f[17]));
 const auto pid=[&](const void* p)->int{if(!p)return 0;if(p==&team)return 1;if(p==&old)return 2;
  for(int i=0;i<3;++i)if(p==&feet[i])return 10+i;if(p==&tag)return 30;if(p==&oldTag)return 31;if(p==&cell)return 40;if(p==&typeId)return 50;if(p==&houseId)return 60;if(p==&script)return 70;throw std::invalid_argument("Unknown membership pointer");};
 std::vector<std::int64_t> trace;const auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace.insert(trace.end(),{k,a,b,c,d,e});};
 const auto store=[&](const void* p,std::int64_t off,std::uint32_t v,const void* pointer){
  const auto owner=pid(p);const bool ptr=owner==1?(off==0x24||off==0x28||off==0x2c||off==0x34||off==0x38||off==0x54||off==0x70):owner>=10&&owner<=12&&(off==0x34||off==0x4c4||off==0x4c8);
  const int width=owner==1?(off==0x7d||off==0x7e?1:4):owner>=10&&owner<=12?(off==0x579||off==0x37a?1:4):4;
  event(1,owner,off,width,ptr?pid(pointer):v);};
 int mutated=0;const auto mutate=[&](int where){if(mutated||f[29]!=where)return;mutated=1;event(3,where);
  if(where==1)team.values84[std::size_t(f[3])]=0xfffffffeu;
  if(where==2)team.tag70=&oldTag;
  if(where==3){team.cell34=&cell;ed=128;}
  if(where==4)team.value54=&feet[2];};
 const auto index=[&](const void* p){const auto id=pid(p);require(id>=10&&id<=12);return id-10;};
 const auto typeCount52C=[&](const void* p){event(2,3,pid(p));mutate(2);return f[12];};
 const auto currentScript=[&](const void* p){require(p==&script);event(2,6,0,f[18]);return f[18];};
 int loading=0;TeamAnchorServices anchor{loading,3};anchor.type24=[&]()->auto&{return type;};anchor.script668870=currentScript;
 anchor.foot=[&](const void* p){auto& a=feet[std::size_t(index(p))];return TeamAnchorFoot{p,a.next,a.onmap,a.health,a.limbo,a.leader,a.active,a.position};};
 anchor.kind2C=[&](const void* p){event(2,5,pid(p),f[21]);return f[21];};
 anchor.weighted46C=[&](const void* p){event(2,7,pid(p),f[20]);return std::uint32_t(f[20]);};
 anchor.type80Count52C=typeCount52C;anchor.type80FlagADA=[&](const void* p){(void)typeCount52C(p);return std::uint8_t(f[27]);};
 anchor.distance5D4DA0=[](const void*,const void* target){require(target==0);return 0;};
 anchor.map548000=[&](Coord p)->const void*{event(2,8,p.x,p.y,p.z);mutate(4);return &cell;};
 anchor.permission194=[&](const void* p,const void* c,int d,int l,int prev,int consult){require(c==&cell);event(2,9,pid(p),pid(c),d,l);event(2,10,prev,consult,f[28]);return f[28];};anchor.store=store;
 TeamMembershipServices services;services.type24=[&]()->auto&{return type;};services.store=store;
 services.admission6B8DC0=[&](TeamMemberFoot& foot,int& slot){event(2,1,pid(foot.identity),f[2],f[3]);slot=f[3];mutate(1);return std::uint32_t(f[2]);};
 services.remove6B8FB0=[&](const void* previous,TeamMemberFoot& foot,int slot,std::uint32_t flag){require(previous==&old);event(2,2,pid(foot.identity),slot,flag);foot.team4C4=nullptr;foot.next4C8=nullptr;};
 services.type80Count52C=[&](TeamMemberFoot& a){return typeCount52C(a.identity);};
 services.setTag5D4430=[&](TeamMemberFoot& a,const void* p){auto* incoming=p==&tag?&tag:p==&oldTag?&oldTag:nullptr;require(incoming);setMissionObjectTag({a.tag34,a.identity},incoming,store);};
 services.threat2A0=[&](TeamMemberFoot& a){event(2,4,pid(a.identity),f[14]);mutate(3);return f[14];};
 services.anchor6B9610=[&]{selectTeamMemberAnchor(team,anchor);};
 const auto add=[&](int i){auto& a=feet[std::size_t(i)];TeamMemberFoot foot{&a,a.team,a.next,a.leader,a.group,a.recruit,a.tag};return addTeamMember(team,f[1]?&foot:nullptr,services);};
 std::array<int,3> result{-1,-1,-1};
 if(f[0]==0)result[0]=add(0);
 if(f[0]==1)selectTeamMemberAnchor(team,anchor);
 if(f[0]==2){const void* subjects[]{&tag,team.value54,&cell,&script,&houseId,&typeId,&feet[0],&oldTag};
  expireMemberTeamTag(team,subjects[std::size_t(f[31])],std::uint32_t(f[30]),[&](const void* p){return feet[std::size_t(index(p))].next;},store);}
 if(f[0]==3)for(int i=0;i<3;++i)result[std::size_t(i)]=add(i);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F ";for(auto v:result)std::cout<<v<<' ';
 std::cout<<mutated<<' '<<team.value48<<' '<<team.value4C<<' '<<pid(team.value54)<<' '<<pid(team.cell34)<<' '<<pid(team.value38)<<' '<<pid(team.tag70)<<' '<<pid(team.script28)<<' '<<pid(team.house2C?team.house2C->identity:nullptr)<<' '<<pid(team.type24?team.type24->identity:nullptr)<<' '<<int(team.flags74[9])<<' '<<int(team.flags74[10])<<' ';
 for(auto v:team.values84)std::cout<<v<<' ';std::cout<<instances<<' '<<oldInstances<<' ';
 for(const auto& a:feet)std::cout<<pid(a.team)<<' '<<pid(a.next)<<' '<<pid(a.tag)<<' '<<std::uint32_t(a.group)<<' '<<int(a.leader)<<' '<<int(a.recruit)<<' ';
 std::cout<<int(ed)<<' '<<int(b3)<<'\n';
}
void guards(){
 TeamConstructionRecord t;TeamMembershipServices s;require(!addTeamMember(t,nullptr,s));
 const int zero=0;TeamAnchorServices anchor{zero,1};selectTeamMemberAnchor(t,anchor);require(!t.cell34&&!t.value38);
 int group=-1,tf=7;const std::uint8_t flag=0;TeamMembershipType type{group,&tf,flag,flag,flag};require(teamMembershipGroup(type)==7);group=-2;require(teamMembershipGroup(type)==-2);
 bool refused=false;try{(void)teamAnchorDivide(0x80000000u,0xffffffffu);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"team membership guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
