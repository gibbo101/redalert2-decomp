// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingStaticScan.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building static scan domain");}
void event(int k,int id=-1,int field=-1,int value=0){std::cout<<k<<' '<<id<<' '<<field<<' '<<value<<' ';}
struct Actor{int kind;std::uint8_t hidden,redraw;PixelRect bounds;};
int main(int argc,char**){try{
 if(argc>1){scanStaticBuildings({}, {},0,{},{},{[]{return 0;},{}});
  bool refused=false;try{scanStaticBuildings({}, {},0,{},{},{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  std::cout<<"Building static scan guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<int,38> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  const int force=f[0],mode=f[1];int count=f[2],bypass=f[3],backing=0;PixelPoint offset{f[4],f[5]};
  PixelRect dirty{f[6],f[7],f[8],f[9]},clip{f[10],f[11],f[12],f[13]};
  std::array<Actor,3> actors;for(int i=0;i<3;++i){int j=17+i*7;actors[i]={f[j],std::uint8_t(f[j+1]),std::uint8_t(f[j+2]),{f[j+3],f[j+4],f[j+5],f[j+6]}};}
  bool mutated=false;const auto mutate=[&](int point){if(mutated||!mode)return;if((mode<=3||mode==6)&&point!=1)return;if((mode==4||mode==7)&&point!=2)return;if(mode==5&&point!=3)return;
   mutated=true;event(10,-1,-1,mode);if(mode==1||mode==4)count=0;if(mode==2){count=3;backing=1;}
   if(mode==3){offset={17,-23};clip={9,-11,200,300};}if(mode==5){actors[0].hidden=128;actors[1].hidden=255;bypass=0;}
   if(mode==6){actors[1].hidden=255;bypass=0;}if(mode==7)actors[0].redraw=255;
  };
  scanStaticBuildings(dirty,clip,force,[&]{event(6,-1,0,offset.x);event(6,-1,4,offset.y);return offset;},[&]{event(5,-1,-1,bypass);return std::uint8_t(bypass);},
   {[&]{event(1,-1,-1,count);return count;},[&](int index){need(index>=0&&index<3);event(2,-1,-1,backing);const int id=backing?2-index:f[14+index];auto& a=actors.at(id);
    return BuildingStaticObject{{[&,id]{event(3,id,-1,actors[id].kind);mutate(3);if(actors[id].kind==6)event(4,id,-1,actors[id].hidden);return actors[id].kind;},a.redraw,[&,id]()->const PixelRect&{event(7,id);mutate(1);return actors[id].bounds;},[&,id]{event(9,id,-1,actors[id].redraw);}},a.hidden,
     [&,id](PixelRect r,int forwarded,int zero){event(8,id,0,r.x);event(8,id,1,r.y);event(8,id,2,r.width);event(8,id,3,r.height);event(8,id,4,forwarded);event(8,id,5,zero);if(mode==7)r={21,22,23,24};mutate(2);}};
   }});
  std::cout<<"F ";for(const auto& a:actors)std::cout<<unsigned(a.hidden)<<' '<<unsigned(a.redraw)<<' ';
  std::cout<<count<<' '<<backing<<' '<<offset.x<<' '<<offset.y<<' '<<clip.x<<' '<<clip.y<<' '<<clip.width<<' '<<clip.height<<' '<<bypass<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
