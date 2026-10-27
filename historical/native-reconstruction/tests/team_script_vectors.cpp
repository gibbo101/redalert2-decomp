// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamScript.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team Script fixture differs");}
void run(std::istream& in){
 std::array<int,9> f{};for(auto& n:f)require(bool(in>>n));std::string extra;require(!(in>>extra));
 struct Foot {const void* next=nullptr;const void* field1b0=nullptr;std::uint32_t valueD8=0;};std::array<Foot,4> feet{};int token=0;
 const auto id=[&](const void* p){for(int i=0;i<4;++i)if(p==&feet[i])return i;throw std::invalid_argument("Foreign Script member");};
 const auto at=[&](int i){return f[6]?f[0]-1-i:i;};for(int i=0;i<f[0];++i){auto& a=feet[at(i)];a.next=i+1<f[0]?&feet[at(i+1)]:nullptr;}
 for(auto& a:feet){a.field1b0=f[5]?&token:nullptr;a.valueD8=std::uint32_t(f[4]);}
 TeamConstructionRecord team;team.value54=&feet[at(0)];team.value48=f[0];team.flags74[4]=1;team.flags74[5]=1;team.flags74[11]=1;team.flags74[12]=f[2];team.flags74[9]=f[1];
 MissionScriptConstructionRecord script;int scriptType=0;script.type24=&scriptType;script.cursor2C=f[8];const int count=2;const std::array<MissionScriptAction,2> actions{{{50,f[3]},{50,f[3]}}};
 const MissionScriptTypeResolver type=[&](const void* p){require(p==&scriptType);return MissionScriptTypeState{count,actions};};
 std::vector<std::uint64_t> trace;const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 const MissionTagStore store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* pointer){require(!pointer);event(1,p==&team?99:p==&script?98:id(p),std::uint32_t(off),value);};
 const int taskCount=1,required=f[0];const std::array<TeamAdmissionEntry,1> entries{{{required,nullptr}}};TeamAdmissionTaskForce task{taskCount,entries};const std::uint8_t zero=0;const auto ab=std::uint8_t(f[7]);TeamReadinessType readyType{ab,zero,task};const std::uint32_t empty=0x7fff7fff;TeamReadinessServices ready{{},{},{},{},{},empty,store};ready.type24=[&]()->auto&{return readyType;};
 TeamScriptServices s{4,ab,zero};s.store=store;s.readiness6B8BB0=[&]{event(2);return refreshTeamReadiness(team,ready);};s.anchor6B9610=[&]{event(3);};s.member1C0=[&](const void* p){event(4,id(p));return 0;};s.next4C8=[&](const void* p){return feet[id(p)].next;};
 s.advance668920=[&]{event(5);advanceMissionScript(script,type,store);};s.hasCurrent668940=[&]{event(6);return missionScriptHasCurrent(script,type);};s.current668870=[&]{event(7);return currentMissionScriptAction(script,type);};
 s.clear6D6E50=[&](const void* p){event(8,id(p));setTechnoField1B0(p,feet[id(p)].field1b0,nullptr,store);};
 s.valueD8=[&](const void* p,std::uint32_t value){feet[id(p)].valueD8=value;store(p,0xd8,value,nullptr);};
 tickTeamScript50(team,s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<script.cursor2C<<' ';for(auto v:team.flags74)std::cout<<unsigned(v)<<' ';std::cout<<std::uintptr_t(team.value3C)<<' '<<std::uintptr_t(team.value40)<<' ';for(auto& a:feet)std::cout<<a.valueD8<<' '<<bool(a.field1b0)<<' ';std::cout<<'\n';
}
void guards(){TeamConstructionRecord t;const std::uint8_t zero=0;TeamScriptServices s{4,zero,zero};bool refused=false;try{tickTeamScript50(t,s);}catch(const std::invalid_argument&){refused=true;}require(refused);t.value3C=reinterpret_cast<const void*>(std::uintptr_t(1));refused=false;try{clearInitialTeamTarget(t);}catch(const std::invalid_argument&){refused=true;}require(refused&&t.value3C==reinterpret_cast<const void*>(std::uintptr_t(1)));int token=0;const void* field=&token;setTechnoField1B0(&token,field,nullptr);require(!field);std::cout<<"team Script guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
