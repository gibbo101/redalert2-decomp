// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FrameRegionPreparation.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  int x=0,y=0;PixelRect r{};FrameRegionServices s;
  auto refuses=[&]{try{prepareFrameRegions(x,y,r,0,0,0,r,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing frame region guard");};
  refuses();s.dirtyCount=[]{return 129;};refuses();s.dirtyCount=[]{return INT32_MIN;};refuses();
  s.dirtyCount=[]{return 1;};refuses();s.dirtyBacking=[]{return std::span<DirtyRegion>{};};refuses();
  s.dirtyCount=[]{return 0;};refuses();s.cellCount=[]{return 801;};refuses();s.cellCount=[]{return 0;};prepareFrameRegions(x,y,r,0,0,0,r,s);
  s.cellCount=[]{return 1;};refuses();
  std::array<DirtyRegion,2> rows{{{{1,2,3,4},17},{{5,6,7,8},18}}};
  s.cellCount=[]{return 0;};s.dirtyCount=[]{return 1;};s.dirtyBacking=[&]{return std::span<DirtyRegion>(rows);};
  try{prepareFrameRegions(x,y,PixelRect{0,0,20,20},0,0,0,r,s);throw std::runtime_error("Missing depth guard");}
  catch(const std::invalid_argument&){} // Positive region must bind depth child.
  s.depth7761c0=[](const PixelRect&){};prepareFrameRegions(x,y,PixelRect{0,0,20,20},0,0,0,r,s);
  s.dirtyCount=[]{return 0;};s.cellCount=[]{return 1;};s.cellAt=[](int){return 0;};refuses();
  s.center475d60=[](int){return Coord{128,128,99};};refuses();
  s.project6a27a0=[](Coord p){if(p.z!=0)throw std::runtime_error("Frame projection Z not cleared");return PixelPoint{};};refuses();
  s.terrainPresent=[]{return false;};s.cellCount=[]{return 0;};prepareFrameRegions(x,y,r,1,0,0,r,s);
  int visits=0;s.cellCount=[&]{return visits++?0:1;};s.terrainPresent=[]{return true;};refuses();
  std::cout<<"Frame region guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream input(line);std::array<int,38> f;for(auto& v:f)input>>v;if(!input)throw std::invalid_argument("Invalid frame region vector");
  int mode=f[0],count=f[1],dirty=f[2],backing=0,present=f[37];PixelPoint origin{f[4],f[5]};PixelRect viewport{f[6],f[7],f[8],f[9]},clip{f[12],f[13],f[14],f[15]};
  std::array<int,3> order{f[16],f[17],f[18]};std::array<TerrainCellPoint,3> cells;std::array<std::array<DirtyRegion,3>,2> regions;
  for(int i=0;i<3;++i){cells[i]={std::int16_t(f[19+2*i]),std::int16_t(f[20+2*i])};const int k=25+4*i;regions[0][i]={{f[k],f[k+1],f[k+2],f[k+3]},std::uint8_t(17+i)};}
  for(int i=0;i<3;++i)regions[1][i]=regions[0][2-i];
  std::ostringstream trace;auto event=[&](int k,int a=0,int b=0,int c=0,int d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};bool mutated=false;
  auto mutate=[&](int point){
   if(mutated||!mode)return;
   const int target=(mode<=5||mode==11)?1:(mode<=8?2:(mode==9?3:4));if(point!=target)return;
   mutated=true;event(14,mode);
   if(mode==1||mode==11)dirty=0;if(mode==2)dirty=3;if(mode==3||mode==11)backing=1;
   if(mode==4)regions[backing][0].bounds={51,52,13,14};if(mode==5){viewport={9,11,180,140};origin={17,-23};}
   if(mode==6)origin={17,-23};if(mode==7)count=0;if(mode==8){count=3;order[1]=2;order[2]=1;}
   if(mode==9)order[0]=2;if(mode==10)present=0;
  };
  FrameRegionServices s;
  s.dirtyCount=[&]{event(1,dirty);return dirty;};s.setDirtyCount=[&](int n){dirty=n;event(4,n);};
  s.dirtyBacking=[&]{event(2,backing);return std::span<DirtyRegion>(regions[backing]);};
  s.storeTrace=[&](int i,int field,int v){event(3,i,field,v);};
  s.depth7761c0=[&](const PixelRect& r){event(5,r.x,r.y,r.width,r.height);mutate(1);};
  s.cellCount=[&]{event(6,count);return count;};s.cellAt=[&](int i){int id=order.at(i);event(7,i,id);return id;};
  s.center475d60=[&](int id){auto p=cells.at(id);event(8,id,p.x,p.y);event(9,id);return Coord{int(p.x)*256+128,int(p.y)*256+128,0x123};};
  s.project6a27a0=[&](Coord p){event(10,p.x,p.y,p.z);mutate(2);return worldPixels(.125,p);};
  s.terrainPresent=[&]{event(11,present);mutate(3);return present!=0;};
  s.terrain4754b0=[&](int id,PixelPoint p,const PixelRect& r){event(12,id,p.x,p.y,&r==&clip);event(13,r.x,r.y,r.width,r.height);mutate(4);};
  prepareFrameRegions(origin.x,origin.y,viewport,f[3],f[10],f[11],clip,s);
  std::cout<<trace.str()<<"F "<<count<<' '<<dirty<<' '<<backing<<' '<<origin.x<<' '<<origin.y<<' '<<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<' ';
  for(int v:order)std::cout<<v<<' ';for(auto p:cells)std::cout<<p.x<<' '<<p.y<<' ';std::cout<<present<<' ';
  for(const auto& rows:regions)for(const auto& row:rows){const auto r=row.bounds;std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' '<<int(row.flag)<<' ';}std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
