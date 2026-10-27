// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionWaypointDiscovery.hpp"
#include "sim/WaypointResidentDiscovery.hpp"
#include "sim/BuildingCoordinates.hpp"
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
 require(flagsSeed>=0&&flagsSeed<=4096&&levelSeed>=0&&levelSeed<=4096&&p.x>=-1048576&&p.x<=1048576&&p.y>=-1048576&&p.y<=1048576);
 require(houseValue>=0&&houseValue<3&&trim<2&&fog<2&&heightCheck<2&&rule1432>=0&&rule1432<2&&rule142b>=0&&rule142b<2&&primaryMode>=0&&primaryMode<3&&secondaryMode>=0&&secondaryMode<3&&predicate>=0&&predicate<2&&allied>=0&&allied<2&&size<=4096);
 std::array<std::int32_t,11> counts{};for(auto& n:counts)n=take<std::int32_t>(in);std::vector<TerrainCellPoint> offsets(size),heightOffsets(size);for(std::size_t i=0;i<size;++i){offsets[i]={take<std::int16_t>(in),take<std::int16_t>(in)};heightOffsets[i]={take<std::int16_t>(in),take<std::int16_t>(in)};}std::array<std::int32_t,22> widths{},heights{};for(auto& n:widths)n=take<std::int32_t>(in);for(auto& n:heights)n=take<std::int32_t>(in);std::string extra;require(!(in>>extra));
 RevealAreaHouse current{1,2,0},other{2,0,allied?4u:0u};auto* house=houseValue==0?nullptr:houseValue==1?&current:&other;
 std::array<RevealAreaCell,17> cells{};for(int i=0;i<17;++i){cells[std::size_t(i)].identity=i;cells[std::size_t(i)].level11b=std::int8_t(((levelSeed+i*3)%15)-7);cells[std::size_t(i)].flags12c=((flagsSeed+i)&1)?8u:0u;cells[std::size_t(i)].flags140=(std::uint32_t(flagsSeed+i*17)&255u)|bridge;}for(int i=0;i<17;++i){cells[std::size_t(i)].point={std::int16_t(16+(i&3)),std::int16_t(16+(i>>2))};auto& cell=cells[std::size_t(i)];
  cell.primary120=std::uint8_t(flagsSeed+i*5);cell.secondary121=std::uint8_t(flagsSeed+i*7+3);
  cell.flags12c|=0xa5000000u|(((flagsSeed+i)&2)?0x10u:0u);
  constexpr std::array<int,6> counters{-2147483647-1,-1,0,1,2,2147483647};
  constexpr std::array<int,5> maxima{-2,0,1,3,2147483647};
  cell.counter130=counters[std::size_t((flagsSeed+i)%6)];cell.maximum134=maxima[std::size_t((flagsSeed+i)%5)];
 }
 cells[16].point={std::int16_t(0xa5a5),std::int16_t(0xa5a5)};
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
 std::array<std::int8_t,256> results;for(unsigned i=0;i<results.size();++i)results[i]=std::bit_cast<std::int8_t>(std::uint8_t(i*37+unsigned(flagsSeed)*13));
 const auto refreshRules=(flagsSeed&1)?0x1000u:0u;
 CellVisibilityChangeServices leaves;
 leaves.trace=[](char k,int a,int b,int){std::cout<<k<<' '<<a<<' '<<b<<' ';};
 leaves.redraw=[](int id){std::cout<<"DRAW "<<id<<' ';};
 leaves.discover=[](int id,int h,bool notify){std::cout<<"DISC "<<id<<' '<<h<<' '<<int(notify)<<' ';};
 leaves.refresh=[](int id){std::cout<<"REF "<<id<<' ';};
 std::array<CellVisibilityState*,16> registry{};for(unsigned i=0;i<16;++i)registry[i]=&cells[i];
 struct Actor {int next=-1;std::uint8_t flags=0;Coord point{};};std::array<Actor,34> actors{};std::array<int,17> heads;heads.fill(-1);
 for(int i=0;i<17;++i){const auto members=(flagsSeed+i)%4;const auto active=(flagsSeed/4+i)%4;
  for(int m=1;m>=0;--m){const int id=i*2+m;auto& a=actors[std::size_t(id)];a.flags=std::uint8_t(0x80|((active>>m)&1));
   a.point={flagsSeed+i*17+(m&&flagsSeed%3?37:0),flagsSeed+i*23+(m&&flagsSeed%3?-19:0),0};
   if(members&(1<<m)){a.next=heads[std::size_t(i)];heads[std::size_t(i)]=id;}}
 }
 UnitDiscoveryWorld discoveryWorld;discoveryWorld.currentHouse=1;discoveryWorld.mode=flagsSeed%3-1;
 discoveryWorld.loading=flagsSeed%2;discoveryWorld.tagContext=flagsSeed-17;
 for(int id=1;id<=2;++id){auto& h=discoveryWorld.houses[id];h.human134=std::uint8_t((flagsSeed+id)&1?255:0);h.control135=std::uint8_t((flagsSeed+id)&2?128:0);h.discovered13c=17;h.field5668=33;h.field5669=65;h.building18d=127;h.building144=255;}
 std::array<UnitDiscoveryActor,34> discovered{};std::array<BuildingDiscoveryServices,34> building{};
 std::array<WaypointResidentDiscoveryBinding,34> objects{};int activeObject=-1;
 for(int id=0;id<34;++id){auto& a=discovered[std::size_t(id)];a.owner=2;a.field372=std::uint8_t((flagsSeed+id)%3?0:255);
  a.current373=std::uint8_t(flagsSeed%7==0&&id%4==0?255:0);a.other374=129;a.queuedA4=193;
  constexpr std::array<int,4> missions{14,18,-1,19};constexpr std::array<int,3> queued{18,-1,5};
  a.mission98=missions[std::size_t(id%4)];a.queuedA0=queued[std::size_t(id%3)];a.hasTag=id%3==0;
  building[std::size_t(id)]={ [&]{return flagsSeed-2048;},[id]{std::cout<<"RADIO "<<id<<' ';const std::array<std::uintptr_t,2> links{std::uintptr_t(id%5?0:1),1};return buildingHasRadioLinks(id%3==0?2:id%3==1?0:-1,links);},[id](std::uint8_t n){std::cout<<"ACT "<<id<<' '<<unsigned(n)<<' ';} };
  objects[std::size_t(id)]={id,&a,id&1?&building[std::size_t(id)]:nullptr};
 }
 discoveryWorld.trace=[](char k,int n){std::cout<<"D "<<k<<' '<<n<<' ';};
 discoveryWorld.store=[](int subject,int offset,std::uint32_t n){std::cout<<"DW "<<subject<<' '<<offset<<' '<<n<<' ';};
 discoveryWorld.tagEvent=[&](int context){std::cout<<"TAG "<<activeObject<<' '<<context<<' ';if(flagsSeed%5==0){auto& a=discovered.at(std::size_t(activeObject));a.owner=3-a.owner;std::cout<<"OWNER "<<activeObject<<' '<<a.owner<<' ';}};
 const auto residents=[&](int cell){require(cell>=0&&cell<17);CellClosestResidentServices r;r.memberLimit=2;
  r.head=[&,cell](bool elevated){require(!elevated);return heads[std::size_t(cell)];};
  r.flags=[&](int id){return actors.at(std::size_t(id)).flags;};r.next=[&](int id){return actors.at(std::size_t(id)).next;};
  r.coordinates=[&](int id){std::cout<<"COORD "<<id<<' ';const auto raw=actors.at(std::size_t(id)).point;if(!(id&1))return raw;
   return buildingCoordinates({[&](std::uint8_t n){std::cout<<"BH "<<unsigned(n)<<' ';return buildingFoundationHeight(flagsSeed%22,255,n,heights);},[&]{std::cout<<"BW ";return buildingFoundationWidth(flagsSeed%22,widths);},[&]{return raw;}});};r.squareRoot=[](double n){return std::sqrt(n);};return r;};
 const auto result=revealMissionWaypointDiscovery(waypoint,scenario,globals,world,tables,state,services,bindings,results,refreshRules,leaves,registry,residents,
  [](auto point){std::cout<<"NOTIFY "<<point.x<<' '<<point.y<<' ';},[&](int actor,int h){std::cout<<"BY "<<actor<<' '<<h<<' ';activeObject=actor;(void)discoverWaypointResident(actor,h,discoveryWorld,objects);});
 std::cout<<'Z';for(const auto& c:cells)std::cout<<' '<<std::int32_t(c.flags140)<<' '<<std::int32_t(c.flags12c)<<' '<<c.counter130<<' '<<unsigned(c.primary120)<<' '<<unsigned(c.secondary121);
 std::cout<<' '<<cells[16].point.x<<' '<<cells[16].point.y;std::cout<<" U";for(const auto& a:discovered)std::cout<<' '<<a.owner<<' '<<unsigned(a.current373)<<' '<<unsigned(a.other374)<<' '<<a.queuedA0<<' '<<unsigned(a.queuedA4);
 std::cout<<" HOUSES";for(int id=1;id<=2;++id){const auto& h=discoveryWorld.houses.at(id);std::cout<<' '<<unsigned(h.discovered13c)<<' '<<unsigned(h.field5668)<<' '<<unsigned(h.field5669)<<' '<<h.buildingType1b4<<' '<<unsigned(h.building18d)<<' '<<unsigned(h.building144);}
 std::cout<<" END "<<unsigned(result)<<'\n';
}
void guards(){
 UnitDiscoveryWorld objectsWorld;UnitDiscoveryActor actor;std::array<WaypointResidentDiscoveryBinding,2> ambiguous{{{7,&actor},{7,&actor}}};
 bool rejected=false;try{discoverWaypointResident(7,1,objectsWorld,ambiguous);}catch(const std::invalid_argument&){rejected=true;}require(rejected);
 rejected=false;try{discoverWaypointResident(8,1,objectsWorld,ambiguous);}catch(const std::invalid_argument&){rejected=true;}require(rejected);
 actor.current373=1;objectsWorld.currentHouse=1;require(!discoverWaypointResident(7,1,objectsWorld,std::span(ambiguous).first(1)));

 std::array<RevealAreaCell*,262144> slots{};RevealAreaCell fallback{};std::array<std::int32_t,11> counts{};counts.fill(1);std::array<TerrainCellPoint,1> offsets{{{0,0}}};RevealAreaHouse house{1,0,0};RevealAreaWorld world{10,80,slots,slots,&fallback};RevealAreaTables tables{counts,offsets,offsets};RevealAreaState state{104,0.,0,0,&house};RevealAreaServices services;services.squareRoot=[](double n){return std::sqrt(n);};
 revealArea({5120,5120,0},0,&house,0,0,0,0,0,world,tables,state,services);
 bool refused=false;state.heightDivisor=0;try{revealArea({5120,5120,0},1,&house,0,0,0,0,0,world,tables,state,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 MissionWaypointRevealHouse blocked{255};auto* hp=&blocked;MissionWaypointRevealRules r;auto* rp=&r;std::int32_t scale=104;
 MissionWaypointRevealWorld globals{hp,rp,scale};RevealAreaWorld empty;RevealAreaTables noTables;RevealAreaState noState;RevealAreaServices noServices;
 require(revealMissionWaypointArea(0,{},globals,empty,noTables,noState,noServices,{})==1);
 std::cout<<"mission waypoint objects guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
