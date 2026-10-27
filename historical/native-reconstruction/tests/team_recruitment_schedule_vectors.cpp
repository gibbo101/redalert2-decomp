// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamRecruitmentSchedule.hpp"
#include "sim/UnitDiscovery.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool ok){if(!ok)throw std::invalid_argument("Team AI fixture/guard differs");}
void run(std::istream& in){
 std::array<int,24> f{};for(auto& x:f)require(bool(in>>x));std::string extra;require(!(in>>extra));
 TeamConstructionRecord t;int foot=0,anchor=0;std::uint8_t blocked=f[19];
 t.value48=std::uint32_t(f[0]);t.value54=f[1]?&foot:nullptr;t.cell34=f[2]?&anchor:nullptr;t.value38=f[2]?&foot:nullptr;
 t.flags74[9]=f[3];t.flags74[4]=f[4];t.flags74[6]=f[5];t.flags74[7]=f[6];t.flags74[14]=f[7];
 t.timer64=std::uint32_t(f[8]);t.value6C=std::uint32_t(f[9]);t.timer50=std::uint32_t(f[10]);t.value3C=reinterpret_cast<const void*>(std::uintptr_t(std::uint32_t(f[23])));
 t.values84.fill(std::uint32_t(f[14]));std::array<TeamAdmissionEntry,6> entries{};
 for(int i=0;i<6;++i)entries[i]={f[15],nullptr};int count=f[13];TeamAdmissionTaskForce task{count,entries};
 std::uint8_t zero=0;TeamReadinessType type{zero,zero,task};UnitDiscoveryHouse house;house.human134=f[16];house.control135=f[17];
 int anchorCalls=0,recruitCalls=0,memberCalls=0,destroyed=0;bool mutated=false;std::vector<std::uint64_t> trace;
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){trace.insert(trace.end(),{std::uint64_t(k),a,b,c,d,e});};
 const MissionTagStore store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* ptr){require(p==&t);event(1,std::uint32_t(off),(off==0x34||off==0x38||off==0x54)?std::uint32_t(ptr!=nullptr):value);};
 const auto put=[&](std::uint32_t off,std::uint32_t value){if(off==0x48)t.value48=value;else if(off>=0x84)t.values84[(off-0x84)/4]=value;else t.flags74[off-0x74]=std::uint8_t(value);store(&t,off,value,nullptr);};
 const std::uint32_t empty=0x7fff7fff;TeamReadinessServices ready{{},{},{},{},{},empty,store};ready.type24=[&]()->auto&{return type;};ready.destroy20=[&](std::uint32_t arg){require(arg==1);++destroyed;event(7,arg);};
 const int frame=f[11],mode=f[12],timeout=f[21];TeamRecruitmentScheduleServices s{frame,mode,timeout};s.store=store;
 s.readiness6B8BB0=[&]{event(8);return refreshTeamReadiness(t,ready);};
 s.anchor6B9610=[&]{++anchorCalls;event(2);t.cell34=t.value54?&anchor:nullptr;store(&t,0x34,0,t.cell34);t.value38=t.value54;store(&t,0x38,0,t.value38);};
 s.house4F52F0=[&]{event(4);return discoveryHouseControlled(house,mode);};s.taskForceDC=[&]{return TeamAdmissionTaskForce{count,entries};};
 s.recruit6B91C0=[&](int slot){++recruitCalls;event(3,slot);
  if(f[18]){put(0x84+4*slot,t.values84[slot]+1u);put(0x48,t.value48+1u);t.value54=&foot;store(&t,0x54,0,&foot);put(0x7e,1);put(0x7d,1);}
  if(!mutated&&f[20]){mutated=true;count=f[20]==1?0:f[20]==2?1:6;event(9,count);}
 };
 s.member1C0=[&](const void* p){require(p==&foot);++memberCalls;event(5);return blocked;};
 s.continuation6BA1A0=[&]{event(6);continueUntargetedTeam(t,store);};
 if(f[22]){s.continuation6BA1A0();}else tickRecruitingTeam(t,s);
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<t.value48<<' '<<bool(t.value54)<<' '<<bool(t.cell34)<<' '<<bool(t.value38)<<' '<<std::uintptr_t(t.value40)<<' '<<anchorCalls<<' '<<recruitCalls<<' '<<memberCalls<<' '<<destroyed<<' '<<count<<' ';
 for(auto x:t.flags74)std::cout<<unsigned(x)<<' ';for(auto x:t.values84)std::cout<<x<<' ';std::cout<<'\n';
}
void guards(){
 TeamConstructionRecord t;int foot=0;t.value3C=reinterpret_cast<const void*>(std::uintptr_t(1));continueUntargetedTeam(t);t.value54=&foot;
 bool refused=false;try{continueUntargetedTeam(t);}catch(const std::invalid_argument&){refused=true;}require(refused&&t.value40==0);
 const int zero=0;TeamRecruitmentScheduleServices s{zero,zero,zero};t.flags74[11]=1;refused=false;
 try{tickRecruitingTeam(t,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 t.flags74[14]=1;t.timer64=0xffffffffu;t.value6C=1;tickRecruitingTeam(t,s);require(t.flags74[14]==1);
 std::cout<<"team recruitment schedule guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
