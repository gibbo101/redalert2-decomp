// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionWaypointReveal.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Waypoint reveal fixture differs");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 require(take<char>(in)=='W');auto disabled=take<unsigned>(in);auto waypoint=take<std::int32_t>(in);
 auto x=take<int>(in),y=take<int>(in);std::array<std::uint32_t,3> flags;for(auto& v:flags)v=take<std::uint32_t>(in);
 std::array<std::int8_t,3> levels;for(auto& v:levels){auto n=take<int>(in);require(n>=-128&&n<=127);v=std::int8_t(n);}
 auto scale=take<std::int32_t>(in);const auto range=take<std::int32_t>(in);const auto mutation=take<int>(in);
 std::string extra;require(!(in>>extra)&&disabled<256&&x>=-32768&&x<=32767&&y>=-32768&&y<=32767&&mutation>=0&&mutation<=2);
 MissionWaypointRevealHouse first{std::uint8_t(disabled)},second{255};auto* house=&first;
 MissionWaypointRevealRules r0{range},r1{signed32(std::uint32_t(range)+0x80000001u)};auto* rules=&r0;
 MissionWaypointRevealWorld world{house,rules,scale};MissionWaypointRevealServices s;int lookups=0,reveals=0;
 s.waypoint=[&](auto n){require(n==waypoint);std::cout<<" W "<<n;return TerrainCellPoint{std::int16_t(x),std::int16_t(y)};};
 s.cell=[&](auto p){require(p==TerrainCellPoint{std::int16_t(x),std::int16_t(y)}&&lookups<3);std::cout<<" L "<<p.x<<' '<<p.y;const auto i=lookups++;return MissionWaypointRevealCell{flags[i],levels[i]};};
 s.reveal=[&](Coord p,int distance,auto* owner,auto a,auto b,auto c,auto d,auto e){
  std::cout<<" A "<<p.x<<' '<<p.y<<' '<<p.z<<' '<<distance<<' '<<(owner==&first?0:owner==&second?1:-1)<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e;
  if(++reveals==1&&mutation){scale=signed32(std::uint32_t(scale)^0x80000001u);if(mutation==1){house=&second;rules=&r1;}else r0.range54c=r1.range54c;}
 };
 const auto result=revealMissionWaypoint(waypoint,world,s);std::cout<<" R "<<unsigned(result)<<'\n';
 require(disabled?(!lookups&&!reveals):(reveals==2&&lookups==(flags[0]&0x100u?2:3)));
}
void guards(){
 MissionWaypointRevealHouse h{1};auto* hp=&h;MissionWaypointRevealRules r;auto* rp=&r;std::int32_t scale=104;
 MissionWaypointRevealWorld w{hp,rp,scale};MissionWaypointRevealServices s;require(revealMissionWaypoint(0,w,s)==1);h.disabled188=0;
 bool refused=false;try{revealMissionWaypoint(0,w,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"mission waypoint reveal guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
