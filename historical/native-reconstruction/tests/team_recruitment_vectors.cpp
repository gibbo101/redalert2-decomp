// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamRecruitment.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Recruitment fixture/domain differs");}
struct Foot {Coord position;int group=-1,route=17;std::uint8_t flag404=128,flag57e=255;};
void run(std::istream& in){
 std::array<int,28> f;for(auto& n:f)require(bool(in>>n));std::string extra;require(!(in>>extra));
 // slot,count,required,current,group,typeA8,group0..2,admit0..2,outputSlot,
 // profile,anchor,waypoint1,waypoint2,addResult,mutation,kind,tfGroup,hasTF,
 // typeC0C,typeC12,health,state5AC,clearOnly,emptyProfile.
 std::array<Foot,3> feet;for(int i=0;i<3;++i){feet[i].group=f[6+i];feet[i].position={256*(i+1),128*(i+1),208+i*104};}
 if(f[13]==1)for(auto& a:feet)a.position={512,256,0};
 if(f[13]==2){feet[0].position={46341,0,0};feet[1].position={1,1,0};feet[2].position={65536,65535,0};}
 if(f[13]==3){feet[0].position={INT32_MAX,INT32_MIN,0};feet[1].position={INT32_MIN,INT32_MAX,0};feet[2].position={0,0,0};}
 int anchorId=0;const void* anchor=f[14]?&anchorId:nullptr;const Coord empty=f[27]?Coord{INT32_MIN,INT32_MAX,99}:Coord{};const std::uint32_t emptyCell=0x7fff7fff;
 int count=f[1],group=f[4],tfGroup=f[20],current=f[3],selected=-1,admissionCalls=0,waypoints=0,mutated=0,addCalls=0;std::uint8_t typeA8=f[5],zero=0;
 TeamMembershipType type{group,f[21]?&tfGroup:nullptr,zero,zero,zero};
 std::vector<std::int64_t> trace;auto event=[&](int kind,int a=0,int b=0,int c=0,int d=0,int e=0){trace.insert(trace.end(),{kind,a,b,c,d,e});};
 auto index=[&](const void* p){for(int i=0;i<3;++i)if(p==&feet[i])return i;throw std::invalid_argument("Foreign recruiting Foot");};
 auto mutate=[&](int where){if(mutated||f[18]!=where)return;mutated=where;event(7,where);
  if(where==1)count=1;
  if(where==2){feet[1].group=group;typeA8=128;}
  if(where==3)count=3;
 };
 TeamRecruitmentServices s{anchor,empty,emptyCell};
 s.coordinates48=[&](const void* p){if(p==anchor){event(1,99);return Coord{1024,-512,307};}const auto i=index(p);event(1,i);return feet[i].position;};
 s.waypoint6BFA90=[&]{event(2,waypoints);const auto p=std::uint32_t(waypoints++?f[16]:f[15]);return p;};
 s.currentCount84=[&](int slot){require(slot==f[0]);return current;};s.requiredCountA4=[&](int slot){require(slot==f[0]);return f[2];};
 s.group6BFA60=[&]{event(3);return teamMembershipGroup(type);};s.requiredKind2C=[&]{event(4,f[19]);return f[19];};
 s.infantryCount=[&]{return count;};s.infantrySlot=[&](int n)->const void*{require(n>=0&&n<3);return &feet[n];};
 s.footGroup1AC=[&](const void* p){return feet[index(p)].group;};s.typeA8=[&]{return typeA8;};
 s.admission6B8DC0=[&](const void* p,int& slot){const int i=index(p);event(5,i,slot,f[9+i],f[12]);slot=f[12];++admissionCalls;mutate(admissionCalls==1?1:3);return std::uint32_t(f[9+i]);};
 s.clearTarget370=[&](const void* p){const auto i=index(p);event(6,i);auto& a=feet[i];clearInfantryRecruitTarget(nullptr,f[25],a.route,a.flag404,a.flag57e,[&](auto off,auto v){event(8,i,int(off),int(v));});};
 s.addMember6B8CC0=[&](const void* p){selected=index(p);++addCalls;event(9,selected,f[17]);mutate(2);return bool(f[17]);};
 bool result=false;if(f[26]){s.clearTarget370(&feet[0]);}else result=recruitInfantryTeamSlot(f[0],s);
 for(auto x:trace)std::cout<<x<<' ';std::cout<<"F "<<result<<' '<<selected<<' '<<count<<' '<<unsigned(typeA8)<<' '<<mutated<<' '<<admissionCalls<<' '<<waypoints<<' '<<addCalls<<' ';
 for(const auto& a:feet)std::cout<<a.group<<' '<<a.route<<' '<<unsigned(a.flag404)<<' '<<unsigned(a.flag57e)<<' ';
 std::cout<<'\n';
}
void guards(){
 int route=9;std::uint8_t a=128,b=255;int target;
 for(int state:{27,28,29,30}){bool refused=false;try{clearInfantryRecruitTarget(nullptr,state,route,a,b);}catch(const std::invalid_argument&){refused=true;}require(refused&&route==9&&a==128&&b==255);}
 bool refused=false;try{clearInfantryRecruitTarget(&target,0,route,a,b);}catch(const std::invalid_argument&){refused=true;}require(refused&&route==9&&a==128&&b==255);
 require(teamRecruitmentDistance({46341,0,12},{0,0,99})<0);std::cout<<"team recruitment guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
