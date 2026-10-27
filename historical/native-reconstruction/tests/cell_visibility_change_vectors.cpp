// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityChange.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Cell visibility change fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 require(take<char>(in)=='C');const int x=take<int>(in),y=take<int>(in),present=take<int>(in),primary=take<int>(in),secondary=take<int>(in);const auto flags12c=take<std::uint32_t>(in);const auto counter=take<std::int32_t>(in),maximum=take<std::int32_t>(in);const auto flags140=take<std::uint32_t>(in);const int primaryValue=take<int>(in),secondaryValue=take<int>(in),house=take<int>(in);const auto refreshRules=take<std::uint32_t>(in),finalArgument=take<std::uint32_t>(in);std::string extra;require(!(in>>extra));
 require(x>=-32768&&x<=32767&&y>=-32768&&y<=32767&&(present==0||present==1)&&primary>=0&&primary<256&&secondary>=0&&secondary<256&&primaryValue>=0&&primaryValue<256&&secondaryValue>=0&&secondaryValue<256);
 std::array<CellVisibilityChangeCell,2> cells{};cells[0]={{std::int16_t(x),std::int16_t(y)},std::uint8_t(primary),std::uint8_t(secondary),flags12c,counter,maximum,0,flags140,0};cells[1]={{std::int16_t(0xa5a5),std::int16_t(0xa5a5)},std::uint8_t(primary),std::uint8_t(secondary),flags12c,counter,maximum,0,flags140,1};
 std::vector<CellVisibilityChangeCell*> table(262144);const auto index=y*512+x;if(present&&index>=0&&index<262144)table[std::size_t(index)]=&cells[0];
 CellVisibilityChangeWorld world{table,&cells[1]};world.fallbackStore=[](TerrainCellPoint p){std::cout<<"B "<<p.x<<' '<<p.y<<' ';};world.query=[](TerrainCellPoint p,int id){std::cout<<"L "<<p.x<<' '<<p.y<<' '<<id<<' ';};
 CellVisibilityChangeServices services;services.visibilityValue=[&](TerrainCellPoint p,bool mode){require(p==TerrainCellPoint{std::int16_t(x),std::int16_t(y)});return std::uint8_t(mode?secondaryValue:primaryValue);};services.trace=[](char k,std::int32_t a,std::int32_t b,std::int32_t c){std::cout<<k<<' '<<a;if(k=='G'||k=='F'||k=='C'||k=='P'||k=='S'||k=='V')std::cout<<' '<<b;if(k=='W')std::cout<<' '<<b<<' '<<c;std::cout<<' ';};services.redraw=[](int id){std::cout<<"D "<<id<<' ';};services.discover=[](int id,int h,bool notify){std::cout<<"R "<<id<<' '<<h<<' '<<int(notify)<<' ';};services.refresh=[](int id){std::cout<<"X "<<id<<' ';};
 const bool changed=changeCellVisibility({std::int16_t(x),std::int16_t(y)},house,finalArgument,world,refreshRules,services);const auto& cell=present?cells[0]:cells[1];std::cout<<"Z "<<int(changed)<<' '<<unsigned(cell.primary120)<<' '<<unsigned(cell.secondary121)<<' '<<std::int32_t(cell.flags12c)<<' '<<cell.counter130<<' '<<std::int32_t(cell.flags140)<<' '<<cells[1].point.x<<' '<<cells[1].point.y<<'\n';
}
void guards(){std::array<CellVisibilityChangeCell*,262144> slots{};CellVisibilityChangeCell fallback{};CellVisibilityChangeWorld world{slots,&fallback};CellVisibilityChangeServices services;services.visibilityValue=[](auto,bool){return std::uint8_t(0);};services.redraw=[](int){};services.discover=[](int,int,bool){};bool refused=false;try{revealCellForOrdinarySight({0,0},0,1,world,0,services);}catch(const std::invalid_argument&){refused=true;}require(refused);fallback.counter130=0;fallback.maximum134=3;changeCellVisibility({0,0},0,0x100,world,0,services);require(fallback.counter130==-1);std::cout<<"Cell visibility change guards PASS\n";}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
