// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkMissionResume.hpp"
#include "sim/TechnoAbility.hpp"
#include "sim/UnitDiscovery.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::invalid_argument("Resume fixture differs");}
void run(std::istream& in){
 std::array<int,29> f;for(auto& v:f)need(bool(in>>v));int abilityIndex,mutation,atQuery;std::uint64_t vetBits;unsigned vByte,eByte;
 need(bool(in>>abilityIndex>>vetBits>>vByte>>eByte>>mutation>>atQuery));std::string tail;need(!(in>>tail));
 need((f[0]==0||f[0]==5)&&abilityIndex>=0&&abilityIndex<18&&vByte<256&&eByte<256&&mutation>=0&&mutation<=3&&atQuery>=0&&atQuery<=8);
 need(f[0]==5||abilityIndex==16);
 int raw=f[1],queued=f[2],special=f[3],pending=f[5],status=f[6],animation=f[7],token;
 std::uint8_t entered=f[4],flag=0;const void* alternate=f[9]?&token:nullptr;const void* target=f[10]?&token:nullptr;const void* team=f[11]?&token:nullptr;const void* retained=nullptr;
 const auto event=[&](int k,int x=0,int y=0){std::cout<<k<<' '<<std::uint32_t(x)<<' '<<std::uint32_t(y)<<' ';};
 int queries=0,chosen=-999;double veterancy=std::bit_cast<double>(vetBits);
 std::array<std::array<std::uint8_t,2>,2> abilityFlags{{{std::uint8_t(vByte),std::uint8_t(eByte)},{std::uint8_t(vByte^255),std::uint8_t(eByte^255)}}};
 const void* currentType=&abilityFlags[0];int abilityQueries=0;
 const auto abilityTrace=[&](char k,const void* type,std::uint32_t off){
  const int kind=k=='V'?27:k=='E'?28:k=='T'?29:k=='B'?30:31;
  event(kind,type==&abilityFlags[1]?1:0,int(off));
  if(++abilityQueries==atQuery&&mutation){
   if(mutation==1)veterancy=1.5;
   if(mutation==2)currentType=&abilityFlags[1];
   if(mutation==3){abilityFlags[0][0]^=255;abilityFlags[0][1]^=255;}
   event(32,mutation,atQuery);
  }
 };
 const auto ability=[&](int index)->std::uint32_t{
  event(26,index);TechnoAbilityServices child;
  child.type80=[&]{return currentType;};
  child.typeByte=[&](const void* type,std::uint32_t off){
   need(type==&abilityFlags[0]||type==&abilityFlags[1]);const auto& row=abilityFlags[type==&abilityFlags[1]?1:0];
   need(off==0x26c + unsigned(index)||off==0x27e + unsigned(index));return row[off==0x26c + unsigned(index)?0:1];
  };child.trace=abilityTrace;return technoHasAbility(veterancy,index,child);
 };
 WalkMovementState walk;walk.moving34=std::uint8_t(f[23]);walk.piggyback38=f[24]?&token:nullptr;walk.inProcessing35=std::uint8_t(f[25]);
 std::uint32_t refs=f[26],global=f[27];double percentage=std::bit_cast<double>(0x3fe400001234abcdull);
 const auto trace=[&](char k,int x,int y,std::int64_t v){
  const int kind=k=='B'?7:k=='C'?20:k=='I'?21:k=='Q'?22:k=='v'?23:k=='p'?24:25;
  event(kind,k=='a'||k=='p'?x:0,int(v));
  if(k=='Q'&&f[28]==2)walk.moving34=255;
  if(k=='a'&&x==0x468&&f[28]==1){auto bits=std::bit_cast<std::uint64_t>(percentage);percentage=std::bit_cast<double>((bits&0xffffffff00000000ull)|0xabcdef01u);}
 };
 TechnoMissionResumeServices ts;
 ts.special45c=[&]{event(4,special);need(special!=29);return 0u;};
 ts.predicate3c8=[&]{event(5,1);return 1u;};ts.controller615360=[&]{event(6);return 0u;};
 FootMissionResumeServices fs;
 fs.store=[&](int off,int,int v){event(1,off,v);};
 fs.techno6d48f0=[&](const void* p,std::uint32_t arg){need(!p&&arg==std::uint32_t(f[8]));event(3);resumeTechnoMission(ts);};
 fs.queryPiggyback454c70=[&]()->const void*{event(7);return nullptr;};
 fs.predicate14=[](const void*)->std::uint32_t{need(false);return 0;};
 fs.release8=[](const void*){need(false);};
 fs.percentage4c8=[&](int x,int y){need(!x&&!y);event(8);
  if(f[28]==3){global+=11;refs+=7;}zeroFootResumePercentage(percentage,trace);};
 InfantryMissionResumeServices s;
 s.foot4c6f10=[&](const void* p,std::uint32_t arg)->std::uint32_t{
  event(2,0,arg);if(f[0]==3)return 0x123480ff;
  return resumeWalkFootMission({entered,flag,pending,raw,status,animation,retained},walk,{global,refs},p,arg,fs,trace);
 };
 s.special438=[&]{event(9,special!=-1);return std::uint32_t(special!=-1);};
 s.mission16c=[&]{const int result=raw==-1?queued:raw;event(10,result);++queries;if(f[22]==1&&queries==2)raw=8;return std::uint32_t(result);};
 s.refill4c8b00=[&]{event(11);if(f[22]==2)target=&token;const int count=0;refillEmptyFootResumeDestination(target,count);};
 s.missionControl=[&](int off){event(12,raw,off);if(f[22]==3&&off==5)raw=11;return std::uint8_t(off==5?f[20]:f[21]);};
 s.controlled4f52f0=[&]{event(13,f[12]);return std::uint32_t(f[12]);};
 s.house194=[&]{event(14,f[13]);return f[13];};s.rules10a8=[&]{event(15,f[14]);return f[14];};
 s.predicate28c=[&]{event(16,f[15]);return std::uint32_t(f[15]);};
 s.typeByte=[&](int off){const auto v=std::uint8_t(off==0xc11?f[16]:off==0xc14?f[17]:f[19]);event(17,off,v);return v;};
 s.ability6d7910=ability;
 UnitDiscoveryActor mission;mission.mission98=raw;mission.queuedA0=queued;mission.queuedA4=128;
 s.queue1d0=[&](int m,int arg){event(19,m,arg);need(!arg);chosen=m;mission.mission98=raw;
  queueUnitDiscoveryMission(mission,m,[&](int,int off,std::uint32_t v){event(33,off,int(v));});
 };
 std::uint8_t result;
 if(f[0]==5)result=std::uint8_t(ability(abilityIndex));
 else if(f[0]==4)result=canEndWalkPiggyback(walk,trace);
 else if(f[0]==2)result=resumeTechnoMission(ts);
 else if(f[0]==1)result=std::uint8_t(s.foot4c6f10(nullptr,std::uint32_t(f[8])));
 else result=resumeInfantryMission({raw,alternate,target,team},nullptr,std::uint32_t(f[8]),s);
 std::cout<<"F "<<unsigned(result)<<' '<<unsigned(entered)<<' '<<std::uint32_t(raw)<<' '<<std::uint32_t(chosen)<<' '<<bool(target)<<' '<<bool(team)<<' '<<global<<' '<<refs<<' '<<std::uint32_t(std::bit_cast<std::uint64_t>(percentage))<<' '<<std::uint32_t(std::bit_cast<std::uint64_t>(percentage)>>32)<<' '<<unsigned(walk.moving34)<<" A "<<std::uint32_t(std::bit_cast<std::uint64_t>(veterancy))<<' '<<std::uint32_t(std::bit_cast<std::uint64_t>(veterancy)>>32)<<' '<<(currentType==&abilityFlags[1])<<' ';
 for(auto& row:abilityFlags)for(auto v:row)std::cout<<unsigned(v)<<' ';std::cout<<std::uint32_t(mission.queuedA0)<<' '<<unsigned(mission.queuedA4)<<'\n';
}
void guards(){
 double unpromoted=0;need(technoHasAbility(unpromoted,-999,{})==0);
 double promoted=1.5;bool refused=false;try{technoHasAbility(promoted,16,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
 TechnoAbilityServices child;int token;child.type80=[&]()->const void*{return &token;};refused=false;
 try{technoHasAbility(promoted,16,child);}catch(const std::invalid_argument&){refused=true;}need(refused);
 child.typeByte=[&](const void* p,std::uint32_t off){need(p==&token&&off==0x27c);return std::uint8_t(255);};need(technoHasAbility(promoted,16,child)==1);
 std::cout<<"Infantry resume ability guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
