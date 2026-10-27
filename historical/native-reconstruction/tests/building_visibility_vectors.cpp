// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingVisibility.hpp"
#include "render/BuildingFrameRedraw.hpp"
#include "sim/BuildingCoordinates.hpp"
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building visibility vector domain");}
void event(int k,int field=-1,int value=0,int id=-1){std::cout<<k<<' '<<id<<' '<<field<<' '<<value<<' ';}
int main(int argc,char**){try{
 if(argc>1){std::uint8_t marked=0,redraw=0,flag=0,hidden=0;PixelRect clip{};
  BuildingVisibilityServices s;s.bypass=[]{return std::uint8_t(0);};s.contextPresent=[]{return true;};
  need(!drawBuildingIfVisible({marked,redraw,flag,hidden},clip,clip,0,0,s));
  bool refused=false;try{(void)drawBuildingIfVisible({marked,redraw,flag,hidden},clip,clip,1,0,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  std::cout<<"Building visibility guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,30> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  const int force=int(f[0]),special=int(f[1]),mode=int(f[2]);const bool alias=f[3];
  std::uint8_t bypass=f[4],marked=f[6],redraw=f[7],flag=f[8],hidden=f[9];bool context=f[5];
  PixelRect viewport{int(f[10]),int(f[11]),int(f[12]),int(f[13])},input{int(f[14]),int(f[15]),int(f[16]),int(f[17])},bounds{int(f[18]),int(f[19]),int(f[20]),int(f[21])};
  auto& clip=alias?viewport:input;Coord raw{int(f[22]),int(f[23]),int(f[24])};PixelPoint origin{int(f[25]),int(f[26])};int width=int(f[27]),height=int(f[28]);const double scale=std::bit_cast<double>(std::uint64_t(f[29]));bool mutated=false;
  const auto mutate=[&](int point){if(mutated||!mode)return;if((mode==1||mode==3)&&point!=1)return;if((mode==2||mode==5)&&point!=2)return;if(mode==4&&point!=3)return;
   mutated=true;event(10,-1,mode);if(mode==1)viewport={17,-23,200,300};if(mode==2){viewport={9,-11,200,300};origin={7,-13};}
   if(mode==3){raw={512,256,728};hidden=255;}if(mode==5){hidden=255;flag=255;}if(mode==4){clip={21,22,23,24};redraw=255;}
  };
  const auto draw=[&](int id,PixelPoint& p,PixelRect& r){event(9,0,p.x,id);event(9,1,p.y,id);event(9,2,r.x,id);event(9,3,r.y,id);event(9,4,r.width,id);event(9,5,r.height,id);mutate(3);if(mode==4)p={71,72};};
  BuildingVisibilityServices s;
  s.bypass=[&]{event(1,-1,bypass);return bypass;};s.contextPresent=[&]{event(2,-1,context);return context;};
  s.bounds124=[&]{event(5);const auto r=bounds;mutate(1);return r;};
  s.coordinatesA8=[&]{event(6);mutate(2);return buildingRenderCoordinates(raw);};
  s.project6a29d0=[&](Coord p){event(7);PixelPoint result;(void)projectTacticalFrame(p,result,scale,width,height,{[&]{return origin;},[&](int off,int v){event(8,off,v);}});return result;};
  s.ordinary10c=[&](PixelPoint& p,PixelRect& r){draw(0,p,r);};s.special470=[&](PixelPoint& p,PixelRect& r){draw(1,p,r);};
  s.read=[](int off,int v){event(3,off,v);};s.store=[](int off,int v){event(4,off,v);};
  const auto result=drawBuildingIfVisible({marked,redraw,flag,hidden},clip,viewport,force,special,s);event(11,-1,result);
  std::cout<<"F "<<unsigned(marked)<<' '<<unsigned(redraw)<<' '<<unsigned(flag)<<' '<<unsigned(hidden)<<' '<<clip.x<<' '<<clip.y<<' '<<clip.width<<' '<<clip.height<<' '<<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<' '<<raw.x<<' '<<raw.y<<' '<<raw.z<<' '<<origin.x<<' '<<origin.y<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
