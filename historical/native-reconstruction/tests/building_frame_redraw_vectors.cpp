// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingFrameRedraw.hpp"
#include "sim/BuildingCoordinates.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building frame vector guard");}
int main(int argc,char**){try{
 if(argc>1){
  const auto previous=std::fegetround();need(std::fesetround(FE_UPWARD)==0);
  need(!buildingRedrawInFrame({}, {},.125,{[]{return 0;},{}})&&std::fegetround()==FE_UPWARD);
  bool refused=false;try{(void)buildingRedrawInFrame({}, {},.125,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  refused=false;try{(void)buildingRedrawInFrame({}, {},.125,{[]{return 1;},{}});}catch(const std::invalid_argument&){refused=true;}need(refused&&std::fegetround()==FE_UPWARD);
  need(std::fesetround(previous)==0);std::cout<<"Building frame guards PASS\n";return 0;
 }
 struct Actor {std::uint8_t onMap,redraw,marked;Coord position;};
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,30> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  int count=int(f[7]),backing=0;const int mode=int(f[8]);bool mutated=false;
  std::array<int,3> order{int(f[9]),int(f[10]),int(f[11])};std::array<Actor,3> actors;
  for(int i=0;i<3;++i){const int j=12+i*6;actors[i]={std::uint8_t(f[j]),std::uint8_t(f[j+1]),std::uint8_t(f[j+2]),{int(f[j+3]),int(f[j+4]),int(f[j+5])}};}
  BuildingFrameRegistry registry{[&]{std::cout<<"N "<<count<<' ';return count;},[&](int i){
   need(i>=0&&i<3);std::cout<<"B "<<backing<<' ';const int id=backing?2-i:order.at(std::size_t(i));need(id>=0&&id<3);auto& a=actors[id];
   return BuildingFrameFields{a.onMap,a.redraw,a.marked,[&,id]{
    std::cout<<"C "<<id<<' ';const auto p=buildingRenderCoordinates(actors[id].position);
    if(!mutated&&mode){mutated=true;std::cout<<"M "<<mode<<' ';
     if(mode==1)count=0;if(mode==2){count=3;backing=1;}if(mode==3)actors[1].onMap=0;
     // Mode4 changes the guest origin after the parent's saved bound reads.
     if(mode==5){auto& b=actors[1].position;b.x=std::bit_cast<std::int32_t>(std::uint32_t(b.x)+257u);b.y=std::bit_cast<std::int32_t>(std::uint32_t(b.y)-129u);b.z=728;}
     if(mode==6)count=-1;
    }return p;
   },[id](int offset,std::uint8_t value){std::cout<<"G "<<id<<' '<<offset<<' '<<unsigned(value)<<' ';}};
  }};
  const bool result=buildingRedrawInFrame({int(f[0]),int(f[1])},{int(f[2]),int(f[3]),int(f[4]),int(f[5])},std::bit_cast<double>(std::uint64_t(f[6])),registry);
  std::cout<<"R "<<result<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
