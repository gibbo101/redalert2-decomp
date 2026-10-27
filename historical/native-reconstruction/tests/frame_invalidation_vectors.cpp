// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FrameInvalidation.hpp"
#include "render/BuildingRenderBounds.hpp"
#include "render/BuildingFrameRedraw.hpp"
#include "render/Redraw.hpp"
#include "sim/BuildingCoordinates.hpp"
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Frame invalidation vector domain");}
void event(int k,int id,int f,int v){std::cout<<k<<' '<<id<<' '<<f<<' '<<v<<' ';}
struct Actor {int kind;std::uint8_t redraw;Coord raw;BuildingRenderBoundsState cache;PixelRect type;};
int main(int argc,char**){try{
 if(argc>1){
  invalidateFrameBuildings({}, {},{[]{return 0;},{}},{});
  bool refused=false;try{invalidateFrameBuildings({}, {},{},{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  BuildingRenderBoundsState cache;need(&buildingRenderBounds(cache,{[]{return Coord{};},[]{return PixelPoint{};},{},{},{}})==&cache.bounds50c);
  refused=false;try{(void)buildingRenderBounds(cache,{[]{return Coord{1,0,0};},[]{return PixelPoint{};},{},{},{}});}catch(const std::invalid_argument&){refused=true;}need(refused);
  std::cout<<"Frame invalidation guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,91> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  const int kind=int(f[0]),mode=int(f[1]);PixelPoint origin{int(f[2]),int(f[3])},offset{int(f[4]),int(f[5])};
  int width=int(f[6]),height=int(f[7]),count=int(f[9]),backing=0;const double scale=std::bit_cast<double>(std::uint64_t(f[8]));bool mutated=false;
  PixelRect requested{int(f[15]),int(f[16]),int(f[17]),int(f[18])};std::array<int,3> order{int(f[19]),int(f[20]),int(f[21])};
  std::array<Actor,3> actors;
  for(int i=0;i<3;++i){int j=22+i*18;auto& a=actors[i];a.kind=int(f[j]);a.redraw=std::uint8_t(f[j+1]);a.raw={int(f[j+2]),int(f[j+3]),int(f[j+4])};
   a.cache.coordinates51c={int(f[j+5]),int(f[j+6]),int(f[j+7])};a.cache.origin528={int(f[j+8]),int(f[j+9])};a.cache.bounds50c={int(f[j+10]),int(f[j+11]),int(f[j+12]),int(f[j+13])};a.type={int(f[j+14]),int(f[j+15]),int(f[j+16]),int(f[j+17])};}
  DirtyRegionQueue queue;queue.count=int(f[14]);queue.growth=int(f[11]);queue.ownsAllocation=bool(f[12]);
  for(int i=0;i<int(f[10]);++i){int j=76+i*5;queue.slots.push_back({{int(f[j]),int(f[j+1]),int(f[j+2]),int(f[j+3])},std::uint8_t(f[j+4])});}
  const auto mutate=[&]{if(mutated||!mode)return;mutated=true;event(14,-1,-1,mode);
   if(mode==1)count=0;if(mode==2){count=3;backing=1;}if(mode==3){origin={17,-23};offset={9,-11};}
   if(mode==4)actors[1].redraw=0;if(mode==5){actors[1].raw={512,256,728};width=-360;height=-180;}if(mode==6)count=-1;
  };
  const auto project=[&](Coord p,int id){event(6,id,-1,0);PixelPoint out;
   const bool result=projectTacticalFrame(p,out,scale,width,height,{[&]{event(8,id,0,origin.x);event(8,id,4,origin.y);return origin;},[&](int off,int v){event(7,id,off,v);}});
   return std::pair{out,result};};
  const auto bounds=[&](int id)->const PixelRect& {auto& a=actors.at(std::size_t(id));return buildingRenderBounds(a.cache,{
   [&,id]{event(5,id,-1,0);return buildingRenderCoordinates(actors[id].raw);},
   [&,id]{event(8,id,0,origin.x);event(8,id,4,origin.y);return origin;},
   [&,id](Coord p){return project(p,id).first;},
   [&,id]{event(9,id,-1,0);const auto r=actors[id].type;mutate();return r;},
   [&,id](int off,int v){event(10,id,off,v);}});};
  const auto dirty=[&](PixelRect r,std::uint8_t flag){for(int j=0;j<5;++j)event(11,-1,j,j==0?r.x:j==1?r.y:j==2?r.width:j==3?r.height:flag);
   registerDirtyRegion(queue,{r,flag},[&](DirtyRegionQueue& q,int n){event(22,-1,-1,n);if(!f[13])return false;q.slots.resize(std::size_t(n),{{90,91,92,93},94});event(23,-1,-1,n);return true;},
    [](RedrawEvent e){event(e.kind=='n'?20:21,e.index,e.field,e.value);});};
  if(kind==0){auto [out,ok]=project(actors[0].raw,0);event(15,-1,-1,ok);}
  else if(kind==1){const auto r=bounds(0);for(int j=0;j<4;++j)event(16,-1,j,j==0?r.x:j==1?r.y:j==2?r.width:r.height);}
  else invalidateFrameBuildings(requested,offset,{[&]{event(1,-1,-1,count);return count;},[&](int i){need(i>=0&&i<3);event(2,-1,-1,backing);int id=backing?2-i:order[i];auto& a=actors.at(std::size_t(id));
    return FrameInvalidationObject{[&,id]{event(3,id,-1,actors[id].kind);if(actors[id].kind==6)event(4,id,-1,actors[id].redraw);return actors[id].kind;},a.redraw,[&,id]()->const PixelRect&{return bounds(id);},[&,id]{event(13,id,-1,actors[id].redraw);}};}},dirty);
  std::cout<<"F ";for(const auto& a:actors){const auto& c=a.cache;std::cout<<unsigned(a.redraw)<<' '<<c.coordinates51c.x<<' '<<c.coordinates51c.y<<' '<<c.coordinates51c.z<<' '<<c.origin528.x<<' '<<c.origin528.y<<' '<<c.bounds50c.x<<' '<<c.bounds50c.y<<' '<<c.bounds50c.width<<' '<<c.bounds50c.height<<' ';}
  std::cout<<queue.count<<' '<<queue.slots.size()<<' ';for(const auto& s:queue.slots)std::cout<<s.bounds.x<<' '<<s.bounds.y<<' '<<s.bounds.width<<' '<<s.bounds.height<<' '<<unsigned(s.flag)<<' ';std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
