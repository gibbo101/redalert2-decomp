// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RectangularVisibility.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  int x=0,y=0;PixelRect r{};const auto inverse=voxelIdentity();RectangularVisibilityServices s;
  auto refuses=[&]{try{drawRectangularVisibility({x,y,r,inverse},r,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing rectangle guard");};
  refuses();s.coordinateCell548000=[](Coord){return TerrainCellPoint{};};refuses();s.terrainPresent=[]{return false;};refuses();
  bool tail=false;s.animation41f5e0=[&](const PixelRect&){tail=true;};drawRectangularVisibility({x,y,r,inverse},r,s);if(!tail)throw std::runtime_error("Absent terrain must still call animation");
  s.terrainPresent=[]{return true;};r.width=INT32_MAX;r.height=INT32_MAX;refuses();
  std::cout<<"Rectangular visibility guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,27> f;std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid rectangular visibility vector");
  Matrix matrix;for(int i=0;i<12;++i)matrix[i]=std::bit_cast<float>(std::uint32_t(f[15+i]));
  PixelPoint origin{int(f[9]),int(f[10])};PixelRect viewport{int(f[11]),int(f[12]),int(f[13]),int(f[14])},requested{int(f[5]),int(f[6]),int(f[7]),int(f[8])};
  TerrainCellPoint anchor{std::int16_t(f[3]),std::int16_t(f[4])};bool present=f[1],mutated=false;const int mode=int(f[0]);
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
  const std::array<int,8> targets{0,1,2,3,4,5,6,1};
  auto mutate=[&](int where){if(!mode||mutated||where!=targets.at(mode))return;mutated=true;event(9,mode);
   if(mode==1){requested.width=-240;requested.height=-255;}if(mode==2||mode==3||mode==5){origin={17,-23};viewport={9,11,180,140};requested={7,8,95,75};}
   if(mode==2||mode==7)present=false;if(mode==4){requested={1,2,3,4};anchor={-7,13};}if(mode==6)requested={31,32,33,34};};
  RectangularVisibilityServices s;s.coordinateCell548000=[&](Coord p){event(1,p.x,p.y,p.z);mutate(1);return anchor;};
  s.terrainPresent=[&]{event(2,present);return present;};s.permitted54aab0=[&](TerrainCellPoint p){event(3,p.x,p.y,std::uint8_t(f[2]));mutate(2);return std::uint8_t(f[2]);};
  s.cell548070=[&](TerrainCellPoint p){const auto value=p.x*3+p.y*7;const auto id=(value%3+3)%3;event(4,p.x,p.y,id);mutate(3);return id;};
  s.project6a27a0=[&](Coord p){event(5,p.x,p.y,p.z);mutate(5);return worldPixels(.125,p);};
  s.draw475520=[&](int id,const PixelPoint& p,const PixelRect& r){event(6,id,p.x,p.y);event(7,r.x,r.y,r.width,r.height);mutate(4);};
  s.animation41f5e0=[&](const PixelRect& r){if(&r!=&requested)throw std::runtime_error("Tail rectangle identity changed");event(8,r.x,r.y,r.width,r.height);mutate(6);};
  drawRectangularVisibility({origin.x,origin.y,viewport,matrix},requested,s);
  std::cout<<trace.str()<<"F "<<origin.x<<' '<<origin.y<<' '<<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<' '<<requested.x<<' '<<requested.y<<' '<<requested.width<<' '<<requested.height<<' '<<anchor.x<<' '<<anchor.y<<' '<<present<<' '<<mutated<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
