// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryMissionResume.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::invalid_argument("Resume fixture differs");}
void run(std::istream& in){
 std::array<int,23> f;for(auto& v:f)need(bool(in>>v));std::string tail;need(!(in>>tail));
 int raw=f[1],queued=f[2],special=f[3],pending=f[5],status=f[6],animation=f[7],token;
 std::uint8_t entered=f[4],flag=0;const void* alternate=f[9]?&token:nullptr;const void* target=f[10]?&token:nullptr;const void* team=f[11]?&token:nullptr;const void* retained=nullptr;
 const auto event=[&](int k,int x=0,int y=0){std::cout<<k<<' '<<std::uint32_t(x)<<' '<<std::uint32_t(y)<<' ';};
 int queries=0,chosen=-999;
 TechnoMissionResumeServices ts;
 ts.special45c=[&]{event(4,special);need(special!=29);return 0u;};
 ts.predicate3c8=[&]{event(5,1);return 1u;};ts.controller615360=[&]{event(6);return 0u;};
 FootMissionResumeServices fs;
 fs.store=[&](int off,int,int v){event(1,off,v);};
 fs.techno6d48f0=[&](const void* p,std::uint32_t arg){need(!p&&arg==std::uint32_t(f[8]));event(3);resumeTechnoMission(ts);};
 fs.queryPiggyback454c70=[&]()->const void*{event(7);return nullptr;};
 fs.predicate14=[](const void*)->std::uint32_t{need(false);return 0;};
 fs.release8=[](const void*){need(false);};
 fs.percentage4c8=[&](int x,int y){need(!x&&!y);event(8);};
 InfantryMissionResumeServices s;
 s.foot4c6f10=[&](const void* p,std::uint32_t arg)->std::uint32_t{
  event(2,0,arg);if(f[0]==3)return 0x123480ff;
  return resumeOrdinaryFootMission({entered,flag,pending,raw,status,animation,retained},p,arg,fs);
 };
 s.special438=[&]{event(9,special!=-1);return std::uint32_t(special!=-1);};
 s.mission16c=[&]{const int result=raw==-1?queued:raw;event(10,result);++queries;if(f[22]==1&&queries==2)raw=8;return std::uint32_t(result);};
 s.refill4c8b00=[&]{event(11);if(f[22]==2)target=&token;};
 s.missionControl=[&](int off){event(12,raw,off);if(f[22]==3&&off==5)raw=11;return std::uint8_t(off==5?f[20]:f[21]);};
 s.controlled4f52f0=[&]{event(13,f[12]);return std::uint32_t(f[12]);};
 s.house194=[&]{event(14,f[13]);return f[13];};s.rules10a8=[&]{event(15,f[14]);return f[14];};
 s.predicate28c=[&]{event(16,f[15]);return std::uint32_t(f[15]);};
 s.typeByte=[&](int off){const auto v=std::uint8_t(off==0xc11?f[16]:off==0xc14?f[17]:f[19]);event(17,off,v);return v;};
 s.ability6d7910=[&](int i){event(18,i,f[18]);if(f[22]==4)team=nullptr;return std::uint32_t(f[18]);};
 s.queue1d0=[&](int m,int arg){event(19,m,arg);chosen=m;};
 std::uint8_t result;
 if(f[0]==2)result=resumeTechnoMission(ts);
 else if(f[0]==1)result=std::uint8_t(s.foot4c6f10(nullptr,std::uint32_t(f[8])));
 else result=resumeInfantryMission({raw,alternate,target,team},nullptr,std::uint32_t(f[8]),s);
 std::cout<<"F "<<unsigned(result)<<' '<<unsigned(entered)<<' '<<std::uint32_t(raw)<<' '<<std::uint32_t(chosen)<<' '<<bool(target)<<' '<<bool(team)<<'\n';
}
void guards(){
 int raw=0,n=0,animation=-1;std::uint8_t entered=0,flag=0;const void* p=nullptr;
 FootMissionResumeServices s;bool refused=false;
 try{resumeOrdinaryFootMission({entered,flag,n,raw,n,animation,p},nullptr,1,s);}catch(const std::invalid_argument&){refused=true;}need(refused&&entered==1);
 // Reentry must not invoke any missing children or clear the actual latch.
 need(resumeOrdinaryFootMission({entered,flag,n,raw,n,animation,p},nullptr,1,s)==0&&entered==1);
 InfantryMissionResumeServices parent;refused=false;try{resumeInfantryMission({raw,p,p,p},nullptr,1,parent);}catch(const std::invalid_argument&){refused=true;}need(refused);
 std::cout<<"Infantry mission resume guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
