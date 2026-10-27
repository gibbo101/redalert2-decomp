// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryPositionEffectsE1.hpp"
#include "sim/CellResidentKind6.hpp"
#include "sim/InfantryWeaponSelection.hpp"
#include "sim/PositionCloakEffect.hpp"
#include "sim/CellDirtyEffect.hpp"
#include "sim/UnitDiscovery.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Infantry E1 position-effects fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 const auto prefix=take<char>(in);require(prefix=='F'||prefix=='D');Coord p{take<int>(in),take<int>(in),take<int>(in)};int x=take<int>(in),y=take<int>(in),sa=take<int>(in),sc=take<int>(in),on=take<int>(in),permitted=take<int>(in);int revealed=0,discovered=0,mission=2,human=0,field372=0,loading=0;
 if(prefix=='D'){revealed=take<int>(in);discovered=take<int>(in);mission=take<int>(in);human=take<int>(in);field372=take<int>(in);loading=take<int>(in);}
 require(revealed>=0&&revealed<=255&&discovered>=0&&discovered<=255&&human>=0&&human<=255&&field372>=0&&field372<=255);
 std::string extra;require(!(in>>extra)&&on>=0&&on<=1&&permitted>=0&&permitted<=1&&sa>=0&&sa<=255&&sc>=0&&sc<=255);
 const void* alt=nullptr;const void* effect=nullptr;const void* target=nullptr;std::int32_t mode=0,animation=-1,typeFootprint=0,state=0,turret=-1,kind=15;double rank=0.;std::int16_t footprint=0;std::uint8_t bridge=0,onMap=std::uint8_t(on),flag77=0,active=0,stateA=std::uint8_t(sa),stateC=std::uint8_t(sc);int missions=0,cells=0;int weapons[4]{};const std::uintptr_t cellIdentity=(y*512+x>=0&&y*512+x<262144)?7:8;
 UnitDiscoveryActor discoveryActor;discoveryActor.current373=std::uint8_t(discovered);auto& flag373=discoveryActor.current373;discoveryActor.field372=std::uint8_t(field372);discoveryActor.mission98=mission;discoveryActor.owner=0;discoveryActor.queuedA4=255;
 UnitDiscoveryWorld discoveryWorld;discoveryWorld.currentHouse=0;discoveryWorld.loading=loading;discoveryWorld.houses[0].human134=std::uint8_t(human);
 discoveryWorld.trace=[](char k,int v){std::cout<<k<<' '<<v<<' ';};discoveryWorld.store=[](int who,int off,std::uint32_t v){std::cout<<"W "<<who<<' '<<off<<' '<<v<<' ';};
 InfantryWeaponSelectionType selectionType;selectionType.weapons={{{&weapons[0],0,0},{&weapons[1],0,0}}};selectionType.eliteWeapons={{{&weapons[2],0,0},{&weapons[3],0,0}}};
 InfantryPositionEffectsE1Services s;
 s.alternateQuery=[&](const void* q){std::cout<<"Q 0 ";InfantryWeaponSelectionServices ws;ws.type=[&]() -> const auto& {return selectionType;};ws.mission=[&]{return unitDiscoveryMission(discoveryActor);};return selectInfantryWeaponForNullTarget({state,turret,rank,kind},q,ws);};
 s.mission=[&]{++missions;std::cout<<"m "<<mission<<' ';return mission;};
 s.cellPoint=[&]{std::cout<<"P "<<x<<' '<<y<<' ';return TerrainCellPoint{std::int16_t(x),std::int16_t(y)};};
 s.cell=[&](TerrainCellPoint q){++cells;std::cout<<"C "<<q.x<<' '<<q.y<<' ';return InfantryPositionEffectsE1Cell{cellIdentity,q,0,std::uint8_t(revealed),nullptr};};
 CellResidentKind6State residentState;initializeCellResidentKind6(residentState);const void* residentHead=nullptr;
 s.findKind6=[&](std::uintptr_t c){require(c==cellIdentity);std::cout<<"6 7 ";return findCellResidentKind6(residentState,{residentHead},{});};
 s.permission=[=](TerrainCellPoint q,bool high){std::cout<<"B "<<q.x<<' '<<q.y<<' '<<high<<' ';return bool(permitted);};
 s.positionChild3b8=[&] {std::cout<<"E ";PositionCloakEffectServices cloak;cloak.cell=[&](TerrainCellPoint q){++cells;std::cout<<"C "<<q.x<<' '<<q.y<<' ';return PositionCloakEffectCell{cellIdentity,q,0};};cloak.actorPredicate280=[] {return false;};require(applyPositionCloakEffectPrefix({p,0},cloak)==PositionCloakEffectExit::CellMask);};
 s.dirty=[=](std::uintptr_t c){require(c==cellIdentity);std::cout<<"D 7 ";require(applyCellDirtyEffectPrefix({-1,0,0,0,false})==CellDirtyEffectExit::Overlay);};s.scratchStore=[](int v){std::cout<<"G "<<v<<' ';};
 s.discover=[&]{(void)discoverUnit(discoveryActor,discoveryWorld.currentHouse,discoveryWorld);};
 applyInfantryPositionEffectsE1({p,alt,effect,target,mode,animation,footprint,footprint,bridge,onMap,flag77,active,flag373,stateA,stateC,typeFootprint},2,s);
 require(missions==4&&cells==1+(3-int(discovered!=0))*on&&stateA==0&&stateC==0&&active==on*permitted);std::cout<<"X "<<unsigned(active);
 if(prefix=='D')std::cout<<" Y "<<unsigned(flag373)<<' '<<discoveryActor.queuedA0<<' '<<unsigned(discoveryActor.queuedA4)<<' '<<unsigned(discoveryWorld.houses.at(0).discovered13c)<<' '<<unsigned(discoveryWorld.houses.at(0).field5668)<<' '<<unsigned(discoveryWorld.houses.at(0).field5669);
 std::cout<<'\n';
}
void guards(){
 Coord p{};const void* n=nullptr;std::int32_t z=0,m=-1;std::int16_t w=0;std::uint8_t b=0;
 bool refused=false;try{applyInfantryPositionEffectsE1({p,n,n,n,z,m,w,w,b,b,b,b,b,b,b,z},2,{});}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::uint8_t on=1,active=1,seen=0;int cells=0,dirty=0;
 InfantryPositionEffectsE1Services s;
 s.alternateQuery=[](const void*){return 0;};s.mission=[] {return 2;};s.cellPoint=[] {return TerrainCellPoint{};};
 s.cell=[&](TerrainCellPoint q){++cells;return InfantryPositionEffectsE1Cell{7,q,0,16,nullptr};};
 s.findKind6=[](std::uintptr_t)->const void* {return nullptr;};s.permission=[](TerrainCellPoint,bool){return true;};
 s.positionChild3b8=[]{};s.dirty=[&](std::uintptr_t){++dirty;};s.scratchStore=[](int){};
 auto actor=[&]{return InfantryPositionEffectsE1Actor{p,n,n,n,z,m,w,w,b,on,b,active,seen,b,b,z};};
 refused=false;try{applyInfantryPositionEffectsE1(actor(),2,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&cells==2&&dirty==0);
 seen=255;cells=0;applyInfantryPositionEffectsE1(actor(),2,s);require(cells==2&&dirty==1);
 // A missing optional child is refused only if the original dispatch is entered.
 std::cout<<"Infantry E1 position-effects guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
