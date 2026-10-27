// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityMask.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Cell visibility mask fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 require(take<char>(in)=='M');const int x=take<int>(in),y=take<int>(in),mode=take<int>(in);std::array<int,9> slots{};for(auto& v:slots)v=take<int>(in);std::array<std::uint32_t,10> flags12c{},flags140{};for(auto& v:flags12c)v=take<std::uint32_t>(in);for(auto& v:flags140)v=take<std::uint32_t>(in);const int seed=take<int>(in);std::string extra;require(!(in>>extra));require(x>=-32768&&x<=32767&&y>=-32768&&y<=32767&&(mode==0||mode==1)&&seed>=0&&seed<256);for(auto v:slots)require(v>=-1&&v<9);
 std::array<CellVisibilityMaskCell,10> cells{};for(int i=0;i<10;++i){cells[std::size_t(i)].identity=i;cells[std::size_t(i)].flags12c=flags12c[std::size_t(i)];cells[std::size_t(i)].flags140=flags140[std::size_t(i)];}cells[9].point={std::int16_t(0xa5a5),std::int16_t(0xa5a5)};
 std::vector<CellVisibilityMaskCell*> table(262144);constexpr std::array<std::array<int,2>,9> offsets{{{{0,0}},{{-1,-1}},{{0,-1}},{{1,-1}},{{-1,0}},{{1,0}},{{-1,1}},{{0,1}},{{1,1}}}};
 for(std::size_t i=0;i<offsets.size();++i){const auto px=std::int16_t(std::uint16_t(x+offsets[i][0])),py=std::int16_t(std::uint16_t(y+offsets[i][1]));const int index=int(py)*512+int(px);if(slots[i]>=0&&index>=0&&index<262144)table[std::size_t(index)]=&cells[std::size_t(slots[i])];}
 std::array<std::int8_t,256> results{};for(int i=0;i<256;++i)results[std::size_t(i)]=std::int8_t(std::uint8_t(i*37+seed*13));CellVisibilityMaskWorld world{table,&cells[9]};world.fallbackStore=[](TerrainCellPoint p){std::cout<<"B "<<p.x<<' '<<p.y<<' ';};world.query=[](TerrainCellPoint p,int id){std::cout<<"L "<<p.x<<' '<<p.y<<' '<<id<<' ';};const auto result=cellVisibilityMask({std::int16_t(x),std::int16_t(y)},mode!=0,results,world);std::cout<<"R "<<result<<' '<<cells[9].point.x<<' '<<cells[9].point.y<<'\n';
}
void guards(){std::array<CellVisibilityMaskCell*,262144> slots{};CellVisibilityMaskCell fallback{};CellVisibilityMaskWorld world{slots,&fallback};std::array<std::int8_t,255> shortTable{};bool refused=false;try{cellVisibilityMask({0,0},false,shortTable,world);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"Cell visibility mask guards PASS\n";}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
