// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionWaypointRevealArea.hpp"
#include <array>
#include <bit>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Reveal-area fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 require(take<char>(in)=='J');const auto disabled=take<unsigned>(in);const auto waypoint=take<std::int32_t>(in);const auto heightScale=take<std::int32_t>(in);const auto bridge=take<std::uint32_t>(in);require(disabled<256&&(bridge==0||bridge==0x100||bridge==0x400));Coord p{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};const auto range=take<std::int32_t>(in);const int houseValue=take<int>(in);
 const auto trim=take<std::uint32_t>(in),unused=take<std::uint32_t>(in),fog=take<std::uint32_t>(in),heightCheck=take<std::uint32_t>(in),child=take<std::uint32_t>(in);const auto divisor=take<std::int32_t>(in);const auto scaleBits=take<std::uint64_t>(in);const int rule1432=take<int>(in),rule142b=take<int>(in),origin=take<int>(in),extent=take<int>(in),primaryMode=take<int>(in),secondaryMode=take<int>(in),predicate=take<int>(in),allied=take<int>(in),flagsSeed=take<int>(in),levelSeed=take<int>(in);const auto size=take<std::size_t>(in);
 require(houseValue>=0&&houseValue<3&&trim<2&&fog<2&&heightCheck<2&&rule1432>=0&&rule1432<2&&rule142b>=0&&rule142b<2&&primaryMode>=0&&primaryMode<3&&secondaryMode>=0&&secondaryMode<3&&predicate>=0&&predicate<2&&allied>=0&&allied<2&&size<=4096);
 std::array<std::int32_t,11> counts{};for(auto& n:counts)n=take<std::int32_t>(in);std::vector<TerrainCellPoint> offsets(size),heightOffsets(size);for(std::size_t i=0;i<size;++i){offsets[i]={take<std::int16_t>(in),take<std::int16_t>(in)};heightOffsets[i]={take<std::int16_t>(in),take<std::int16_t>(in)};}std::string extra;require(!(in>>extra));
 RevealAreaHouse current{1,2,0},other{2,0,allied?4u:0u};auto* house=houseValue==0?nullptr:houseValue==1?&current:&other;
 std::array<RevealAreaCell,17> cells{};for(int i=0;i<17;++i){cells[std::size_t(i)].identity=i;cells[std::size_t(i)].level11b=std::int8_t(((levelSeed+i*3)%15)-7);cells[std::size_t(i)].flags12c=((flagsSeed+i)&1)?8u:0u;cells[std::size_t(i)].flags140=(std::uint32_t(flagsSeed+i*17)&255u)|bridge;}cells[16].point={std::int16_t(0xa5a5),std::int16_t(0xa5a5)};
 std::vector<RevealAreaCell*> primary(262144),secondary(262144);const int rawx=p.x/256,rawy=p.y/256;
 const auto fill=[&](auto& table,int mode){if(mode==2)return;for(int y=rawy-24;y<=rawy+24;++y)for(int x=rawx-24;x<=rawx+24;++x){const int index=y*512+x;if(index<0||index>=262144||(mode==1&&((x+y)&1)))continue;table[std::size_t(index)]=&cells[std::size_t((x&3)|((y&3)<<2))];}};fill(primary,primaryMode);fill(secondary,secondaryMode);
 RevealAreaWorld world{origin,extent,secondary,secondary,&cells[16]};
 world.fallbackStore=[](char k,TerrainCellPoint q){std::cout<<"L "<<k<<' '<<q.x<<' '<<q.y<<' ';};world.query=[](char k,TerrainCellPoint q,int id){std::cout<<k<<' '<<q.x<<' '<<q.y<<' '<<id<<' ';};
 RevealAreaTables tables{counts,offsets,heightOffsets};const double scale=std::bit_cast<double>(scaleBits);RevealAreaState state{divisor,scale,std::uint8_t(rule1432),std::uint8_t(rule142b),&current};RevealAreaServices services;
 services.housePredicate=[&](const auto& a,const auto& b){require(a.identity==2&&b.identity==1);return predicate!=0;};services.squareRoot=[](double n){return std::sqrt(n);};
 services.trace=[](char k,int a,int b,int c){std::cout<<k<<' '<<a<<' ';if(k=='A')std::cout<<b<<' ';else if(k=='W')std::cout<<b<<' '<<c<<' ';};
 services.fogCell=[](TerrainCellPoint q,const auto& h){std::cout<<"F "<<q.x<<' '<<q.y<<' '<<h.identity<<' ';};services.revealCell=[](TerrainCellPoint q,const auto& h,std::uint32_t arg){std::cout<<"R "<<q.x<<' '<<q.y<<' '<<h.identity<<' '<<arg<<' ';};
 std::vector<std::uint8_t> scenario(0x1000,0xa5);const auto address=std::uint32_t(0x632u+std::uint32_t(waypoint)*4u);require(std::uint64_t(address)+4<=scenario.size());
 const auto packed=std::uint32_t(std::uint16_t(p.x/256))|(std::uint32_t(std::uint16_t(p.y/256))<<16);
 for(unsigned i=0;i<4;++i)scenario[address+i]=std::uint8_t(packed>>(8*i));
 MissionWaypointRevealHouse h{std::uint8_t(disabled)};auto* hp=&h;MissionWaypointRevealRules r{range};auto* rp=&r;
 MissionWaypointRevealWorld globals{hp,rp,heightScale};std::array<MissionWaypointRevealHouseBinding,1> bindings{{{hp,&current}}};
 const auto result=revealMissionWaypointArea(waypoint,scenario,globals,world,tables,state,services,bindings);std::cout<<'S';for(const auto& c:cells)std::cout<<' '<<std::int32_t(c.flags140);std::cout<<' '<<cells[16].point.x<<' '<<cells[16].point.y<<" END "<<unsigned(result)<<'\n';
}
void guards(){
 std::array<RevealAreaCell*,262144> slots{};RevealAreaCell fallback{};std::array<std::int32_t,11> counts{};counts.fill(1);std::array<TerrainCellPoint,1> offsets{{{0,0}}};RevealAreaHouse house{1,0,0};RevealAreaWorld world{10,80,slots,slots,&fallback};RevealAreaTables tables{counts,offsets,offsets};RevealAreaState state{104,0.,0,0,&house};RevealAreaServices services;services.squareRoot=[](double n){return std::sqrt(n);};
 revealArea({5120,5120,0},0,&house,0,0,0,0,0,world,tables,state,services);
 bool refused=false;state.heightDivisor=0;try{revealArea({5120,5120,0},1,&house,0,0,0,0,0,world,tables,state,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 MissionWaypointRevealHouse blocked{255};auto* hp=&blocked;MissionWaypointRevealRules r;auto* rp=&r;std::int32_t scale=104;
 MissionWaypointRevealWorld globals{hp,rp,scale};RevealAreaWorld empty;RevealAreaTables noTables;RevealAreaState noState;RevealAreaServices noServices;
 require(revealMissionWaypointArea(0,{},globals,empty,noTables,noState,noServices,{})==1);
 std::cout<<"mission waypoint area guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
