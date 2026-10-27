// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarCellNotification.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Radar notification guard");}
int main(int argc,char**){
 if(argc>1){int zero=0;float scale=1;RefreshSurface* missing=nullptr;
  notifyRadarCell({0,0},{missing,zero,zero,zero,zero,zero,scale},{});
  std::cout<<"Radar notification guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line))try{
  std::istringstream in(line);std::array<std::int64_t,11> f{};for(auto& n:f)need(bool(in>>n));std::string extra;need(!(in>>extra));
  int mw=int(f[3]),ox=int(f[4]),oy=int(f[5]),rw=int(f[6]),rh=int(f[7]);float scale=std::bit_cast<float>(std::uint32_t(f[8]));
  RefreshSurfaceVirtuals table;RefreshSurface surface{&table,int(f[9]),int(f[10])};RefreshSurface* first=f[0]?&surface:nullptr;
  table.width7C=[](auto& s){std::cout<<"W "<<s.width<<' ';return s.width;};
  table.height80=[](auto& s){std::cout<<"H "<<s.height<<' ';return s.height;};
  RadarCellNotificationServices services;services.queue632620=[](auto p){std::cout<<"Q "<<p.x<<' '<<p.y<<' ';};
  notifyRadarCell({std::int16_t(f[1]),std::int16_t(f[2])},{first,mw,ox,oy,rw,rh,scale},services);std::cout<<"Z\n";
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}
}
