// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ObjectGroundQueries.hpp"
#include "sim/TechnoHouseTransfer.hpp"
#include "sim/TerrainOccupation.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool v){if(!v)throw std::invalid_argument("Transfer wrapper vector domain");}
std::uint32_t packed(Coord c){const auto p=terrainCellPoint(c);return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
void run(std::istream& in){
 std::array<std::int64_t,11> f{};for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<=3&&f[1]>=0&&f[1]<=255&&f[2]>=0&&f[2]<=255&&f[10]>=0&&f[10]<=8);
 for(int i=3;i<=9;++i)require(f[i]>=INT32_MIN&&f[i]<=INT32_MAX);
 ActorGroundState a{{int(f[3]),int(f[4]),int(f[5])},std::uint8_t(f[1]),std::uint8_t(f[2])};
 std::int32_t level=int(f[7]),bridgeHeight=int(f[8]);std::uint32_t point=0x0059003f;
 const auto mutate=[&](int mode){
  if(!mode)return;std::cout<<"D "<<mode<<' ';
  if(mode==1||mode==7)a.position.z=-123456789;
  if(mode==2||mode==7)a.bridge79=f[2]?0:255;
  if(mode==3||mode==7)bridgeHeight=INT32_MIN;
  if(mode==4||mode==7)level=INT32_MIN;
  if(mode==5||mode==7||mode==8){a.position.x=-257;a.position.y=INT32_MAX;}
  if(mode==6||mode==7||mode==8)a.marked74=0;
 };
 const auto height=[&]{std::cout<<"H ";return relativeObjectGroundHeight(a,bridgeHeight,[&](Coord p){
  require(p==Coord{int(f[3]),int(f[4]),int(f[5])});std::cout<<"P "<<p.x<<' '<<p.y<<' '<<p.z<<' ';
  if(f[10]!=8)mutate(int(f[10]));return int(f[6]);});};
 const auto query=[&]{return std::uint32_t(objectAboveGround(a.marked74,level,height));};
 const auto cell=[&]{std::cout<<"C ";return packed(a.position);};
 std::uint32_t result=0;int token=0;
 if(f[0]==0)result=query();
 else if(f[0]==1)result=std::uint32_t(height());
 else if(f[0]==3)result=cell();
 else result=transferInfantryHouse(&token,~0u,{[&](const void* p,auto arg){require(p==&token&&arg==1);std::cout<<"B "<<arg<<' ';if(f[10]==8)mutate(8);return std::uint32_t(f[9]);},query,cell,[&](auto p){point=p;std::cout<<"W "<<p<<' ';}});
 std::cout<<"F "<<result<<' '<<point<<' '<<std::uint32_t(a.position.x)<<' '<<std::uint32_t(a.position.y)<<' '<<std::uint32_t(a.position.z)<<' '<<unsigned(a.marked74)<<' '<<unsigned(a.bridge79)<<' '<<std::uint32_t(level)<<' '<<std::uint32_t(bridgeHeight)<<'\n';
}
void guards(){
 ActorGroundState a;const std::int32_t level=104;require(!objectAboveGround(a.marked74,level,{}));
 const auto refused=[](auto fn){bool caught=false;try{fn();}catch(const std::invalid_argument&){caught=true;}require(caught);};
 a.marked74=255;refused([&]{objectAboveGround(a.marked74,level,{});});refused([&]{relativeObjectGroundHeight(a,level,{});});
 std::cout<<"Infantry transfer wrapper guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
