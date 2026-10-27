// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TacticalViewport.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Viewport vector guard");}
int main(int argc,char**){try{
 if(argc>1){
  TacticalViewportState s;s.centerX=17;s.centerY=-19;int w=5,h=7;const auto before=std::fegetround();
  bool refused=false;try{updateTacticalViewport(s,w,h,{});}catch(const std::invalid_argument&){refused=true;}
  need(refused&&s.originX==15&&s.originY==-22&&std::fegetround()==before);
  std::cout<<"Tactical viewport guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,9> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  TacticalViewportState s;s.centerX=int(f[0]);s.centerY=int(f[1]);int w=int(f[2]),h=int(f[3]);
  updateTacticalViewport(s,w,h,[&](TacticalViewportVector p){
   std::cout<<"I "<<std::bit_cast<std::uint32_t>(p.x)<<' '<<std::bit_cast<std::uint32_t>(p.y)<<' '<<std::bit_cast<std::uint32_t>(p.z)<<" L "<<f[7]<<' '<<f[8]<<' ';
   w=int(f[7]);h=int(f[8]);return TacticalViewportVector{std::bit_cast<float>(std::uint32_t(f[4])),std::bit_cast<float>(std::uint32_t(f[5])),std::bit_cast<float>(std::uint32_t(f[6]))};
  },[](int offset,int v){std::cout<<"S "<<offset<<' '<<v<<' ';});
  std::cout<<"Z "<<s.originX<<' '<<s.originY<<' '<<s.cellX<<' '<<s.cellY<<' '<<s.columns<<' '<<s.rows<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
