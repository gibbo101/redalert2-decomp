// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MapVisibility.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void need(bool b){if(!b)throw std::invalid_argument("Radar discovery fixture domain");}
void run(std::istream& in){
 char op;int divisor,x,y,z,order;need(bool(in>>op>>divisor>>x>>y>>z>>order)&&op=='V'&&order>=0&&order<=2);
 std::array<MapVisibilityCell,4> cells;std::vector<MapVisibilityCell*> slots(262144,nullptr);
 for(auto& c:cells){int slot,cx,cy;need(bool(in>>slot>>cx>>cy>>c.flags12c>>c.flags140>>c.count13c));need(slot>=-1&&slot<262144&&cx>=-32768&&cx<=32767&&cy>=-32768&&cy<=32767);c.point={std::int16_t(cx),std::int16_t(cy)};if(slot!=-1){need(!slots[slot]);slots[slot]=&c;}}
 std::string tail;need(!(in>>tail));auto id=[&](const MapVisibilityCell& c){return &c-cells.data();};
 MapVisibilityWorld world{slots,&cells[3],{1,1}};
 world.query=[](char k,TerrainCellPoint p){std::cout<<k<<' '<<p.x<<' '<<p.y<<' ';};world.fallbackStore=[](TerrainCellPoint p){std::cout<<"f "<<p.x<<' '<<p.y<<' ';};world.neighbor=[&](const auto& c,int d){std::cout<<"n "<<id(c)<<' '<<d<<' ';};world.countRead=[&](const auto& c){std::cout<<"c "<<id(c)<<' '<<c.count13c<<' ';};
 MapVisibilityState state{divisor,7,9,1};
 auto call=[&](bool primary){const bool b=primary?mapPrimaryVisibility({x,y,z},state,world):mapCountVisibility({x,y,z},state,world);std::cout<<"R "<<b<<' '<<cells[3].point.x<<' '<<cells[3].point.y<<' ';};
 if(order==0)call(false);else{call(order==1);call(order!=1);}std::cout<<'\n';
}
void guards(){
 std::vector<MapVisibilityCell*> slots(262144,nullptr);MapVisibilityCell fb{{0,0},0,0,1};MapVisibilityWorld w{slots,&fb,{1,1}};MapVisibilityState s{104,1,1,1};
 need(mapCountVisibility({0,0,104},s,w));fb.count13c=-1;need(!mapCountVisibility({},s,w));s.heightDivisor=0;bool bad=false;try{mapCountVisibility({},s,w);}catch(const std::invalid_argument&){bad=true;}need(bad);s.heightDivisor=-1;bad=false;try{mapCountVisibility({0,0,INT32_MIN},s,w);}catch(const std::invalid_argument&){bad=true;}need(bad);
 s.heightDivisor=104;w.borrowedCell=[](auto p){return MapVisibilityCell{p,0,0,2};};need(mapCountVisibility({-257,511,-104},s,w));std::cout<<"radar discovery guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
