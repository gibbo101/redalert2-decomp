// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FrameTerrainRequests.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  int x=0,y=0;PixelRect r{};FrameTerrainServices s;
  auto refuses=[&]{try{requestFrameTerrain(x,y,r,r,r,r,0,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing terrain guard");};
  refuses();s.cellCount=[]{return 801;};refuses();s.cellCount=[]{return 0;};refuses();s.dirtyCount=[]{return 129;};refuses();
  s.dirtyCount=[]{return 0;};requestFrameTerrain(x,y,r,r,r,r,256,s);s.cellCount=[]{return 1;};refuses();
  s.cellCount=[]{return 0;};s.dirtyCount=[]{return 1;};refuses();
  std::cout<<"Frame terrain guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream input(line);std::array<int,47> f;for(auto& v:f)input>>v;if(!input)throw std::invalid_argument("Invalid terrain vector");
  int count=f[1],dirty=f[2],backing=0;bool present=f[46];const int mode=f[0];
  PixelPoint origin{f[4],f[5]};PixelRect viewport{f[6],f[7],f[8],f[9]},first{f[10],f[11],f[12],f[13]},second{f[14],f[15],f[16],f[17]},clip{f[18],f[19],f[20],f[21]};
  std::array<int,3> order{f[22],f[23],f[24]};std::array<TerrainCellPoint,3> cells;std::array<std::array<DirtyRegion,3>,2> regions;
  for(int i=0;i<3;++i){cells[i]={std::int16_t(f[25+2*i]),std::int16_t(f[26+2*i])};const int at=31+5*i;regions[0][i]={{f[at],f[at+1],f[at+2],f[at+3]},std::uint8_t(f[at+4])};}
  for(int i=0;i<3;++i)regions[1][i]=regions[0][2-i];
  std::ostringstream trace;auto event=[&](int k,int a=0,int b=0,int c=0,int d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};bool mutated=false;
  const std::array<int,13> targets{0,1,1,2,3,3,5,6,6,2,5,4,6};
  auto mutate=[&](int point){
   if(!mode||mutated||point!=targets.at(mode))return;mutated=true;event(15,mode);
   if(mode==1||mode==4)count=0;
   if(mode==2){count=3;order[1]=2;order[2]=1;}
   if(mode==3)present=false;
   if(mode==5){origin={17,-23};viewport={9,11,180,140};second={7,8,19,20};}
   if(mode==6)dirty=3;
   if(mode==7){backing=1;dirty=0;}
   if(mode==8)backing=1;
   if(mode==9)order[0]=2;
   if(mode==10)second={21,22,23,24};
   if(mode==11){dirty=3;backing=1;}
   if(mode==12)viewport={11,13,100,90};
  };
  FrameTerrainServices s;
  s.cellCount=[&]{event(1,count);return count;};s.cellAt=[&](int i){const auto id=order.at(i);event(2,i,id);return id;};
  s.center475d60=[&](int id){const auto p=cells.at(id);event(3,id,p.x,p.y);event(4,id);mutate(1);return Coord{int(p.x)*256+128,int(p.y)*256+128,0x123};};
  s.project6a27a0=[&](Coord p){event(5,p.x,p.y,p.z);mutate(2);return worldPixels(.125,p);};
  s.terrainPresent=[&]{event(6,present);return present;};
  s.terrain475520=[&](int id,PixelPoint p,const PixelRect& r){event(7,id,p.x,p.y,&r==&clip);event(8,r.x,r.y,r.width,r.height);mutate(3);};
  s.animation41f1c0=[&](PixelPoint p,const PixelRect& r){event(9,p.x,p.y,&r==&clip);event(8,r.x,r.y,r.width,r.height);mutate(4);};
  s.rectangle6a7820=[&](const PixelRect& r){event(10,&r==&viewport?0:&r==&first?1:&r==&second?2:3);event(8,r.x,r.y,r.width,r.height);mutate(5);};
  s.alpha4110b0=[&](const PixelRect& r){event(14,r.x,r.y,r.width,r.height);mutate(6);};
  s.dirtyCount=[&]{event(11,dirty);return dirty;};s.dirtyBacking=[&]{event(12,backing);return std::span<DirtyRegion>(regions.at(backing));};
  s.dirtyFlagTrace=[&](int i,std::uint8_t flag){event(13,i,flag);};
  requestFrameTerrain(origin.x,origin.y,viewport,first,second,clip,f[3],s);
  std::cout<<trace.str()<<"F "<<count<<' '<<dirty<<' '<<backing<<' '<<origin.x<<' '<<origin.y<<' ';
  for(const auto& r:{viewport,first,second,clip})std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';
  for(auto id:order)std::cout<<id<<' ';for(auto p:cells)std::cout<<p.x<<' '<<p.y<<' ';std::cout<<present<<' ';
  for(const auto& rows:regions)for(const auto& d:rows){auto r=d.bounds;std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' '<<int(d.flag)<<' ';}
  std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
