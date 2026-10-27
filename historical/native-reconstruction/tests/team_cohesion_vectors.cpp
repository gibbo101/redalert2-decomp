// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamCohesion.hpp"
#include "sim/MissionScriptState.hpp"
#include "sim/UnitDiscovery.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team cohesion fixture differs");}
void run(std::istream& in){
 std::array<int,20> f{};for(auto& x:f)require(bool(in>>x));std::string extra;require(!(in>>extra));
 struct Foot {const void* next=nullptr;std::uint8_t onmap=0,flag76=0,leader=0;int health=0;const void* target=nullptr;const void* alternate=nullptr;UnitDiscoveryActor mission;};
 std::array<Foot,4> feet{};int anchor=0,nearby=0;TeamConstructionRecord team;team.value54=f[1]?&feet[0]:nullptr;team.cell34=&anchor;team.value38=f[1]?&feet[0]:nullptr;
 team.flags74[1]=f[17];team.flags74[6]=1;team.flags74[7]=f[19];team.flags74[9]=1;team.value48=f[1];
 for(int i=0;i<4;++i){auto& a=feet[i];a.next=i+1<f[1]?&feet[i+1]:nullptr;a.onmap=f[2];a.health=f[3];a.flag76=f[4];a.leader=(f[5]&(1<<i))?128:0;a.target=f[15]?&nearby:nullptr;a.alternate=f[16]?&nearby:nullptr;a.mission.mission98=f[12];a.mission.queuedA0=f[13];a.mission.queuedA4=f[14];}
 const auto id=[&](const void* p){for(int i=0;i<4;++i)if(p==&feet[i])return i;throw std::invalid_argument("Foreign fixture member");};
 std::vector<std::uint64_t> trace;const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 const MissionTagStore store=[&](const void* p,std::int64_t off,std::uint32_t value,const void*){event(1,p==&team?99:id(p),std::uint32_t(off),value);};
 MissionScriptConstructionRecord script;script.cursor2C=f[9]==-1?-1:0;int typeIdentity=0;script.type24=&typeIdentity;const int scriptCount=1;const std::array<MissionScriptAction,1> actions{{{f[9],70}}};
 const MissionScriptTypeResolver type=[&](const void* p){require(p==&typeIdentity);return MissionScriptTypeState{scriptCount,actions};};
 TeamCohesionServices s{f[10],4};s.store=store;
 s.foot=[&](const void* p){auto& a=feet[id(p)];return TeamCohesionFoot{p,a.next,a.onmap,a.health,a.flag76,a.leader,a.target,a.alternate};};
 s.script668870=[&]{event(2);return currentMissionScriptAction(script,type).action;};
 s.range=[&](bool relaxed){return f[relaxed?8:7];};s.distance5D4C00=[&](const void* p,const void* target){require(target==&anchor);event(3,id(p));return f[6];};
 s.kind2C=[&](const void* p){event(4,id(p));return f[11];};
 s.mission16C=[&](const void* p){event(5,id(p));return unitDiscoveryMission(feet[id(p)].mission);};
 s.queue1D0=[&](const void* p,int mission,int flag){require(!flag);event(6,id(p),mission,flag);queueUnitDiscoveryMission(feet[id(p)].mission,mission,[&](int,int off,std::uint32_t v){store(p,off,v,nullptr);});};
 const auto targetId=[&](const void* p){return !p?0:p==&anchor?100:p==&nearby?101:999;};
 s.target370=[&](const void* p,const void* target){require(!target);event(7,id(p));};
 s.destination410=[&](const void* p,const void* target,int flag){require(flag==1);event(8,id(p),targetId(target),flag);};
 s.coordinates48=[&](const void* p){require(p==&anchor);event(9);return Coord{-513,767,208};};
 s.nearby4C8AF0=[&](const void* p,TerrainCellPoint point){event(10,id(p),std::uint32_t(point.x),std::uint32_t(point.y));return TerrainCellPoint{7,-8};};
 s.map548070=[&](TerrainCellPoint p)->const void*{event(11,std::uint32_t(p.x),std::uint32_t(p.y));return &nearby;};
 const int required=f[1],taskCount=1;const std::array<TeamAdmissionEntry,1> entries{{{required,nullptr}}};TeamAdmissionTaskForce task{taskCount,entries};const std::uint8_t zero=0;TeamReadinessType readyType{zero,zero,task};const std::uint32_t empty=0x7fff7fff;
 TeamReadinessServices ready{{},{},{},{},{},empty,store};ready.type24=[&]()->auto&{return readyType;};
 int result=-1;
 if(f[0])result=regroupTeamMembers(team,s);
 else{
  TeamActivationServices a{4};a.store=store;a.readiness6B8BB0=[&]{event(12);return refreshTeamReadiness(team,ready);};a.next4C8=[&](const void* p){return feet[id(p)].next;};a.leader579=[&](const void* p,std::uint8_t v){feet[id(p)].leader=v;store(p,0x579,v,nullptr);};
  a.reset668900=[&]{event(13);resetMissionScript(script,[&](const void*,std::int64_t off,std::uint32_t v,const void*){event(1,98,off,v);});};
  a.anchor6B9610=[&]{event(14);};a.member1C0=[&](const void* p){event(15,id(p));return std::uint32_t(f[18]);};a.cohesion6B9F40=[&]{event(16);return std::uint32_t(regroupTeamMembers(team,s));};
  activateRecruitedTeam(team,a);
 }
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<result<<' '<<script.cursor2C<<' ';for(auto v:team.flags74)std::cout<<unsigned(v)<<' ';
 for(const auto& a:feet)std::cout<<unsigned(a.leader)<<' '<<std::uint32_t(a.mission.mission98)<<' '<<std::uint32_t(a.mission.queuedA0)<<' '<<unsigned(a.mission.queuedA4)<<' '<<bool(a.target)<<' ';std::cout<<'\n';
}
void guards(){TeamConstructionRecord team;const int zero=0;TeamCohesionServices s{zero,0};require(regroupTeamMembers(team,s));TeamActivationServices a{0};bool refused=false;try{activateRecruitedTeam(team,a);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"team cohesion guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
