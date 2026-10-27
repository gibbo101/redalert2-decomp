// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryUpdatePositionE1.hpp"
#include "sim/CellResidentKind6.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Infantry E1 update-position fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
    require(take<char>(in)=='U');Coord p{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};
    Coord target{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};
    std::int32_t range=take<std::int32_t>(in),queued=take<std::int32_t>(in),bridge=take<int>(in),onMap=take<int>(in);
    std::string extra;require(!(in>>extra)&&bridge>=0&&bridge<=1&&onMap>=0&&onMap<=1);
    const void* targetId=&target;const void* alternate=nullptr;const void* locomotor=&range;
    std::uint8_t bridgeByte=std::uint8_t(bridge),onMapByte=std::uint8_t(onMap),special=0,typeSpecial=0;
    int missionCalls=0,cellCalls=0,currentCellCalls=0;
    InfantryUpdatePositionE1Services s;
    s.mission=[&]{++missionCalls;std::cout<<"m 2 ";return 2;};
    s.cell=[&](const Coord& q){++cellCalls;std::cout<<"C "<<q.x<<' '<<q.y<<' '<<q.z<<' ';return std::uintptr_t(q.x==target.x&&q.y==target.y&&q.z==target.z?2:1);};
    s.currentCell=[&]{++currentCellCalls;return std::uintptr_t(1);};
    s.cellValue=[](std::uintptr_t c){std::cout<<"V "<<c<<" 7 ";return 7;};
    CellResidentKind6State residentState;initializeCellResidentKind6(residentState);const void* residentHead=nullptr;
    s.findKind6=[&](std::uintptr_t c){std::cout<<"6 "<<c<<' ';return findCellResidentKind6(residentState,{residentHead},{});};
    s.findKind2=[](std::uintptr_t c,bool high){std::cout<<"2 "<<c<<' '<<high<<' ';return nullptr;};
    s.findKind1=[](std::uintptr_t c,bool high){std::cout<<"1 "<<c<<' '<<high<<' ';return nullptr;};
    s.targetKind=[](const void*){std::cout<<"K 11 ";return 11;};
    s.targetCoordinates=[&](const void*){std::cout<<"T "<<target.x<<' '<<target.y<<' '<<target.z<<' ';return target;};
    s.locomotorPredicate=[](const void*){std::cout<<"L 1 ";return true;};
    s.sight.missionTransition=[] {std::cout<<"M ";};
    s.sight.removeSight=[](auto a,auto b,auto c,auto d){std::cout<<"R "<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
    s.sight.addSight=[](auto a,auto b,auto c,auto d){std::cout<<"A "<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
    s.sight.postSight=[](Coord q,auto a,std::int32_t r,auto b){std::cout<<"P "<<q.x<<' '<<q.y<<' '<<q.z<<' '<<a<<' '<<r<<' '<<b<<' ';};
    s.postUpdate=[](int k){std::cout<<"U "<<k<<' ';};
    updateInfantryPositionE1({p,queued,targetId,alternate,locomotor,range,bridgeByte,onMapByte,special,typeSpecial},2,s);
    require(missionCalls==7&&cellCalls==3&&currentCellCalls==3);std::cout<<'\n';
}
void guards(){
    Coord p{};std::int32_t q=-1,r=0;const void* n=nullptr;std::uint8_t z=0;
    bool refused=false;try{updateInfantryPositionE1({p,q,n,n,n,r,z,z,z,z},2,{});}catch(const std::invalid_argument&){refused=true;}
    require(refused);std::cout<<"Infantry E1 update-position guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
