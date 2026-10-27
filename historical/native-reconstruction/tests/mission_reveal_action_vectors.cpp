// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionRevealAction.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission Reveal fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
const void* token(std::uint32_t value){return reinterpret_cast<const void*>(std::uintptr_t(value));}
void run(std::istream& in){
 require(take<char>(in)=='R');const auto first=take<std::uint32_t>(in);const auto object=take<unsigned>(in);const auto third=take<std::uint32_t>(in);const auto fourth=take<std::uint32_t>(in);const auto result=take<std::uint32_t>(in);std::string extra;require(!(in>>extra)&&object<3);
 int action=0,objectIdentity=0;MissionRevealActionServices services;bool called=false;
 services.revealAroundWaypoint=[&](const void* a,const void* house,const void* filtered,const void* trigger,const void* packed){
  require(a==&action&&house==token(first)&&filtered==(object==2?&objectIdentity:nullptr)&&trigger==token(third)&&packed==token(fourth));called=true;return result;};
 const auto filteredObject=object?&objectIdentity:nullptr;const auto value=executeMissionRevealAroundWaypointAction(&action,token(first),{filteredObject,std::uint8_t(object==2)},token(third),token(fourth),services);
 require(called);std::cout<<"C "<<0x3000100u<<' '<<first<<' '<<(object==2?0x3001000u:0u)<<' '<<third<<' '<<fourth<<" R "<<unsigned(value)<<'\n';
}
void guards(){
 int action=0,object=0;MissionRevealActionServices missing;bool refused=false;try{(void)executeMissionRevealAroundWaypointAction(&action,nullptr,{&object,1},nullptr,nullptr,missing);}catch(const std::invalid_argument&){refused=true;}require(refused);
 MissionRevealActionServices s;int calls=0;s.revealAroundWaypoint=[&](auto,auto,auto filtered,auto,auto){require(filtered==nullptr);++calls;return 0x123456abu;};
 require(executeMissionRevealAroundWaypointAction(&action,nullptr,{&object,0},nullptr,nullptr,s)==0xabu&&calls==1);
 std::cout<<"mission Reveal Around Waypoint action guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
