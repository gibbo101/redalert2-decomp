// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingTypeBounds.hpp"
#include <array>
#include <vector>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Type bounds vector domain");}
void event(int k,int id,int f,int v){std::cout<<k<<' '<<id<<' '<<f<<' '<<v<<' ';}
int main(int argc,char**){try{
 if(argc>1){
  BuildingTypeBoundsState s;s.bounds11ec={1,2,3,4};need(buildingTypeBounds(s,{},{}).x==1);
  s.bounds11ec={};bool refused=false;try{(void)buildingTypeBounds(s,{},{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  releaseBuildingSecondary(s,{});int id;s.secondaryB98=&id;s.release13e2=128;refused=false;
  try{releaseBuildingSecondary(s,{});}catch(const std::invalid_argument&){refused=true;}need(refused&&s.secondaryB98==&id);
  std::cout<<"Type bounds guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::vector<int> f;int value;while(in>>value)f.push_back(value);need(in.eof()&&f.size()>=62&&(f.size()-26)%12==0);
  const auto capacity=int((f.size()-26)/12);const int stride=3+capacity*4;
  std::array<int,3> identities{};auto pointer=[&](int id)->const void*{need(id>=-1&&id<3);return id<0?nullptr:&identities[id];};
  auto identify=[&](const void* p){if(!p)return -1;for(int i=0;i<3;++i)if(p==&identities[i])return i;throw std::invalid_argument("Foreign Type image identity");};
  BuildingTypeBoundsState a{{f[2],f[3],f[4],f[5]},pointer(f[10]),pointer(f[11]),std::uint8_t(f[12]),std::uint8_t(f[13])};PixelRect empty{f[6],f[7],f[8],f[9]};bool mutated=false;
  auto mutate=[&]{if(mutated||!f[1])return;mutated=true;event(8,-1,-1,f[1]);
    if(f[1]==1)a.secondaryB98=pointer(f[15]);if(f[1]==2)a.auxiliary11cc=pointer(2);if(f[1]==3)a.release13e2=0;
    if(f[1]==4){f[17]=32767;f[18]=-32768;}if(f[1]==5)a.auxiliary11cc=nullptr;if(f[1]==6)a.secondaryB98=pointer(2);
  };
  const auto image=[&](int id)->ShpBoundsView{
   if(id<0)return {};const int j=17+id*stride;
   return {pointer(id),[&,id,j]{event(4,id,-1,f[j+2]);return std::int16_t(f[j+2]);},
    [&,id,j]{event(5,id,0,f[j]);event(5,id,1,f[j+1]);return PixelPoint{f[j],f[j+1]};},
    [&,id,j](std::uint32_t index,int field){need(index<std::uint32_t(capacity));const auto v=f[j+3+index*4+field];event(6,id,int(index*4)+field,v);return std::int16_t(v);}};
  };
  BuildingTypeBoundsServices s{[&]{event(1,-1,-1,f[14]);return image(f[14]);},
   [&]{event(2,-1,-1,f[15]);if(f[1]!=2)mutate();return image(f[15]);},
   [&](const void* p){return image(identify(p));},
   [&](const void* p){event(7,-1,-1,identify(p));if(f[1]==2)mutate();},
   [&](int off,int value){event(9,-1,off,value);}};
  if(f[0]==2)releaseBuildingSecondary(a,s);
  else {const auto r=f[0]==1?shpFrameBounds(image(f[14]),f[16],empty):buildingTypeBounds(a,empty,s);
   for(int j=0;j<4;++j)event(10,-1,j,j==0?r.x:j==1?r.y:j==2?r.width:r.height);}
  std::cout<<"F "<<a.bounds11ec.x<<' '<<a.bounds11ec.y<<' '<<a.bounds11ec.width<<' '<<a.bounds11ec.height<<' '<<identify(a.secondaryB98)<<' '<<identify(a.auxiliary11cc)<<' '<<unsigned(a.release13e2)<<' '<<unsigned(a.flagB9c)<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
