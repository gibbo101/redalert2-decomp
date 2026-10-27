// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamReadiness.hpp"
#include "sim/MissionScriptState.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team readiness/Script fixture differs");}
void run(std::istream& in){
 std::array<int,25> f{};for(auto& v:f)require(bool(in>>v));std::string extra;require(!(in>>extra));
 TeamConstructionRecord team;int cell=0;team.cell34=f[22]?&cell:nullptr;team.value48=std::uint32_t(f[1]);
 for(auto [off,index]:{std::pair{0x7a,6},{0x78,7},{0x81,8},{0x7b,9},{0x79,10},{0x76,11},{0x7d,12},{0x7e,13}})team.flags74[off-0x74]=f[index];
 std::array<TeamAdmissionEntry,6> entries;for(int i=0;i<6;++i){int value=i?0:4;if(f[3]==1)value=std::array<int,6>{INT32_MAX,1,INT32_MIN,-1,6,0}[i];if(f[3]==2)value=i-2;if(f[3]==3)value=f[24];entries[i]={value,nullptr};}
 const int count=f[2];TeamAdmissionTaskForce task{count,entries};std::uint8_t ab=f[4],a7=f[5];TeamReadinessType type{ab,a7,task};const std::uint32_t empty=0x7fff7fff;
 int tagCount=f[14],destroyed=0,raises=0;bool switched=false;std::array<int,3> tags{};std::vector<std::int64_t> trace;
 auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace.insert(trace.end(),{k,a,b,c,d,e});};
 TeamReadinessServices s{{}, {}, {}, {}, {},empty,{}};s.type24=[&]()->auto&{return type;};
 s.store=[&](const void* owner,auto off,auto value,const void*){require(owner==&team);event(1,off,off==0x34?4:1,value);};
 s.tagCount=[&]{return tagCount;};s.tagSlot=[&](int i)->const void*{require(i>=0&&i<3);return &tags[switched?2-i:i];};
 s.raise6B3DF0=[&](const void* p,int ev,int zero,std::uint32_t point,int z1,int z2){int id=-1;for(int i=0;i<3;++i)if(p==&tags[i])id=i;require(id>=0&&ev==23&&!zero&&point==empty&&!z1&&!z2);event(2,id,ev,zero,point);++raises;
  if(raises==1&&f[16]){event(3,f[16]);if(f[16]==1)tagCount=0;if(f[16]==2)tagCount=1;if(f[16]==3)switched=true;}
  return std::uint32_t(f[15]);};
 s.destroy20=[&](std::uint32_t flags){require(flags==1);++destroyed;event(4,flags);};
 MissionScriptConstructionRecord script;int scriptIdentity=0;script.type24=f[20]?nullptr:&scriptIdentity;script.cursor2C=f[18];int scriptCount=f[19];
 const std::array<MissionScriptAction,6> actions{{{50,70},{20,13},{8,-1},{INT32_MIN,INT32_MAX},{0,0},{10,7}}};
 MissionScriptTypeResolver resolve=[&](const void* p){require(p==&scriptIdentity);return MissionScriptTypeState{scriptCount,actions};};
 const auto store=[&](const void* owner,auto off,auto value,const void*){require(owner==&script&&off==0x2c);event(5,off,value);};
 int result=-1;MissionScriptAction answer{-99,-99};
 const auto operation=[&](int op){
  if(op==0){answer=currentMissionScriptAction(script,resolve);result=-1;}
  if(op==1){answer=nextMissionScriptAction(script,resolve);result=-1;}
  if(op==2)result=resetMissionScript(script,store);
  if(op==3)result=advanceMissionScript(script,resolve,store);
  if(op==4)result=missionScriptHasCurrent(script,resolve);
  event(6,op,result,answer.action,answer.argument);
 };
 if(f[0]==0)result=refreshTeamReadiness(team,s);
 else if(f[17]!=5)operation(f[17]);
 else{operation(2);for(int i=0;i<f[23];++i){operation(3);operation(4);if(result)operation(0);}}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<result<<' '<<bool(team.cell34)<<' '<<destroyed<<' '<<raises<<' '<<tagCount<<' '<<script.cursor2C<<' '<<scriptCount<<' '<<answer.action<<' '<<answer.argument<<' '<<teamRequiredQuantity(task)<<' '<<team.value48<<' ';
 for(auto v:team.flags74)std::cout<<int(v)<<' ';std::cout<<'\n';
}
void guards(){
 const int one=1;std::array<TeamAdmissionEntry,1> entries{};TeamAdmissionTaskForce task{one,entries};require(teamRequiredQuantity(task)==0);
 MissionScriptConstructionRecord script;require(currentMissionScriptAction(script,{}).action==-1);require(resetMissionScript(script));
 bool refused=false;script.cursor2C=0;try{(void)currentMissionScriptAction(script,{});}catch(const std::invalid_argument&){refused=true;}require(refused);
 refused=false;const int count=2;TeamAdmissionTaskForce bad{count,entries};try{(void)teamRequiredQuantity(bad);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"team readiness guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
