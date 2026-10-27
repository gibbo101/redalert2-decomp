// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionControl.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::invalid_argument("Mission control fixture differs");}
void run(std::istream& in){
 int root,index,diag;std::uint32_t present;std::array<std::uint32_t,6> flags;std::uint64_t rate,aa,initialRate;
 need(bool(in>>root>>index>>present));for(auto& v:flags)need(bool(in>>v));need(bool(in>>rate>>aa>>initialRate>>diag));std::string tail;need(!(in>>tail));
 need(root>=0&&root<=3&&index>=-1&&index<30&&diag>=0&&diag<=5);
 MissionControlTable table;for(auto& r:table)r.bytes.fill(0xa7);auto& r=table[0];
 storeMissionControl(r,0,4,std::uint32_t(index));storeMissionControl(r,16,8,initialRate);
 const auto event=[](auto... fields){((std::cout<<std::uint64_t(fields)<<' '),...);};
 const auto mutation=[&](int off,int n,std::uint64_t value){storeMissionControl(r,off,n,value);event(5,off,n,std::uint32_t(value),std::uint32_t(value>>32));};
 const auto trace=[&](int off,int n,std::uint64_t value){
  event(4,off,n,std::uint32_t(value),std::uint32_t(value>>32));
  if(root==1&&diag==4&&off==24&&n==4)mutation(20,4,0x40080000);
  if(root==1&&diag==5&&off==16&&n==8)mutation(0,4,29);
 };
 const auto section=[&](std::string_view name){if(name=="<none>")return std::uint32_t(-1);for(int i=0;i<30;++i)if(name==missionControlNames[i])return std::uint32_t(i);throw std::invalid_argument("Foreign name");};
 MissionControlIniServices s;
 s.hasSection=[&](auto name){event(1,section(name),present);return present;};
 s.boolean=[&](auto name,auto key,std::uint8_t def){
  int k=0;while(k<6&&key!=missionControlKeys[k])++k;need(k<6);event(2,section(name),k,def,flags[k]);
  if(diag==1)mutation(0,4,(k*7+3)%30);
  if(diag==2&&k<5)mutation(k+5,1,128+k);
  return flags[k];
 };
 s.number=[&](auto name,auto key,double def){
  const int k=key=="Rate"?6:7;const auto bits=std::bit_cast<std::uint64_t>(def),value=k==6?rate:aa;
  event(3,section(name),k,std::uint32_t(bits),std::uint32_t(bits>>32),std::uint32_t(value),std::uint32_t(value>>32));
  if(diag==1&&k==6)mutation(0,4,17);
  if(diag==3&&k==7)mutation(16,8,0x3ff8000012345678ull);
  return std::bit_cast<double>(value);
 };
 std::uint32_t result=0;
 if(root==0)initializeMissionControl(r,trace);
 else if(root==1)result=readMissionControl(r,s,trace);
 else if(root==2){for(int i=0;i<30;++i){event(6,i);initializeMissionControl(table[i],trace);}}
 else{
  for(int i=0;i<30;++i){storeMissionControl(table[i],0,4,i);table[i].bytes[6]=std::uint8_t(flags[0]+i);}
  const auto raw=diag==1&&index>=0?std::bit_cast<std::int32_t>(std::uint32_t(index)|0x80000000u):index;
  result=missionRecruitable(table,raw);event(7,result);
  if(index!=-1){event(8,std::uint32_t(raw)<<5);need(missionControlName(missionControlRecord(table,raw))==missionControlNames[index]);}
 }
 std::cout<<"F "<<result<<' ';for(int i=0;i<(root>=2?30:1);++i)for(auto v:table[i].bytes)std::cout<<unsigned(v)<<' ';std::cout<<'\n';
}
void guards(){
 MissionControlTable table{};bool refused=false;
 try{missionControlFlag(table,-1,5);}catch(const std::invalid_argument&){refused=true;}need(refused);
 need(&missionControlRecord(table,std::bit_cast<std::int32_t>(0x80000005u))==&table[5]);
 need(missionRecruitable(table,-1)==1);MissionControlRecord r;storeMissionControl(r,0,4,30);refused=false;
 try{missionControlName(r);}catch(const std::invalid_argument&){refused=true;}need(refused);
 storeMissionControl(r,0,4,0xffffffff);need(missionControlName(r)=="<none>");
 MissionControlIniServices s;refused=false;try{readMissionControl(r,s);}catch(const std::invalid_argument&){refused=true;}need(refused);
 s.hasSection=[](auto){return 0u;};need(readMissionControl(r,s)==0);
 refused=false;try{missionControlNumberBits(std::bit_cast<double>(0x7ff0000000000001ull));}catch(const std::invalid_argument&){refused=true;}need(refused);
 need(missionControlNumberBits(std::bit_cast<double>(0x7ff8000012345678ull))==0x7ff8000012345678ull);
 std::cout<<"Mission control guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
