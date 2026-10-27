// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamCreation.hpp"
#include "sim/MissionCreateTeamAction.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  int type,house;const void* owner=&house;std::int32_t maximum=-1,count=0,mode=0;std::uint32_t loading=1;
  TeamCreationServices s{loading,mode};s.logBegin=[]{ };s.logName=[](auto){};s.allocate=[](auto)->void*{return nullptr;};
  if(createTeamFromType({&type,owner,maximum,count,"fixture"},nullptr,s))throw std::runtime_error("Failed allocation fabricated a Team");
  s.allocate=[&](auto)->void*{return &type;};bool refused=false;
  try{createTeamFromType({&type,owner,maximum,count,"fixture"},nullptr,s);}catch(const std::invalid_argument&){refused=true;}
  if(!refused)throw std::runtime_error("Missing Team constructor accepted");
  s.construct6b7430=[](auto,auto,auto,auto)->const void*{throw std::runtime_error("child failure");};
  loading=0;MissionCreateTeamServices a{loading,[&](auto,auto){createTeamFromType({&type,owner,maximum,count,"fixture"},nullptr,s);}};
  refused=false;try{executeMissionCreateTeamAction(&type,a);}catch(const std::runtime_error&){refused=true;}
  if(!refused||loading!=1)throw std::runtime_error("Team child failure incorrectly rolled back action counter");
  std::cout<<"Team creation guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,11> f{};std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid Team factory input");
  int type,house1,house2,record,other;auto house=[&](int id)->const void*{return id==1?&house1:id==2?&house2:nullptr;};
  const void* owner=house(int(f[5]));std::uint32_t depth=f[1];std::int32_t mode=int(f[2]),maximum=int(f[3]),count=int(f[4]);bool mutated=false;
  const auto pid=[&](const void* p){return p==&house1?1:p==&house2?2:p==&record?3:p==&other?4:0;};
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0,std::int64_t e=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
  auto mutate=[&](int at){if(mutated||f[9]!=at)return;mutated=true;event(6,at);if(at==1){depth=0;owner=&house2;maximum=0;}if(at==2)maximum=-2147483647;if(at==3)owner=&house2;if(at==4)depth=0xffffffffu;if(at==5)depth=0;};
  TeamCreationServices s{depth,mode};s.logBegin=[&]{event(1,depth);mutate(1);};s.logName=[&](auto name){if(name!="fixture")throw std::runtime_error("Name identity differs");event(2);mutate(3);};
  s.houseCount4f35f0=[&](const void* h,const void* t){if(t!=&type)throw std::runtime_error("Type identity differs");event(3,pid(h));mutate(2);return int(f[10]);};
  s.allocate=[&](auto size)->void*{event(4,size);mutate(4);return f[7]?&record:nullptr;};
  s.construct6b7430=[&](void* r,const void* t,const void* h,int zero)->const void*{if(r!=&record||t!=&type)throw std::runtime_error("Constructor identities differ");event(5,3,pid(h),zero);mutate(5);return f[8]==1?&record:f[8]==2?&other:nullptr;};
  const auto invoke=[&](const void* h){auto* result=createTeamFromType({&type,owner,maximum,count,"fixture"},h,s);event(7,pid(result));return result;};
  int result=0;if(f[0]){MissionCreateTeamServices action{depth,[&](const void* t,int zero){if(t!=&type||zero)throw std::runtime_error("Action factory arguments differ");invoke(nullptr);}};result=executeMissionCreateTeamAction(&type,action);}else result=pid(invoke(house(int(f[6]))));
  std::cout<<trace.str()<<"F "<<result<<' '<<depth<<' '<<maximum<<' '<<count<<' '<<pid(owner)<<' '<<mutated<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
