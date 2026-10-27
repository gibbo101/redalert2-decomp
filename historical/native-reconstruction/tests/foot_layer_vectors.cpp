// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/FootLayer.hpp"
#include "sim/FootCoordinates.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace ra2;
template<class T>T take(std::istream& in){T n{};if(!(in>>n))throw std::invalid_argument("Missing layer input");return n;}
int bounded(std::istream& in,int lo,int hi){const auto n=take<int>(in);if(n<lo||n>hi)throw std::invalid_argument("Layer input domain");return n;}
void guards(){
    FootLayerServices s;
    for(int i=0;i<128;++i)if(footCoordinateLayer(std::int8_t(i),-99,s)!=0)throw std::runtime_error("Indexed bypass made queries");
    bool refused=false;try{footCoordinateLayer(-1,0,s);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing layer services accepted");
    std::uint8_t bridge=255;int floors=0,heights=0,lookups=0;
    s.bridge=[&]{return bridge;};s.secondaryCoordinates=[](int flag){if(flag!=77)throw std::runtime_error("Flag lost");return Coord{12,34,56};};
    s.actorCoordinates=[](){return Coord{90,91,92};};
    s.floorHeight=[&](Coord){if(!floors++){bridge=0;return 0;}return 313;};
    s.levelHeight=[&]{return ++heights==1?104:209;};
    s.cellFlags=[&](Coord p){if(p!=Coord{12,34,56})throw std::runtime_error("Saved point lost");++lookups;return 0u;};
    if(footCoordinateLayer(-1,77,s)!=255||floors!=2||heights!=2||lookups!=1)throw std::runtime_error("Live queries/raw saved byte differ");
    bridge=0;floors=heights=lookups=0;s.cellFlags=[&](Coord){++lookups;return 0x100u;};
    if(objectCoordinateLayer(77,s)!=1||floors!=2||heights!=1||lookups!=1)throw std::runtime_error("Bridge lookup early return differs");
    bridge=128;floors=heights=0;s.floorHeight=[&](Coord){return floors++?0:1;};s.levelHeight=[&]{++heights;return 0x40000000;};
    if(objectCoordinateLayer(77,s)!=0||floors!=2||heights!=1)throw std::runtime_error("Wrapped threshold differs");
    std::cout<<"5 native layer guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Layer vectors read stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='L')return 2;
        const auto index=std::int8_t(bounded(in,-128,127));
        const auto px=std::int16_t(bounded(in,-32768,32767)),py=std::int16_t(bounded(in,-32768,32767));
        MapCellInput fallback;fallback.position={-7,5};fallback.level=std::int8_t(bounded(in,-128,127));fallback.slope=std::uint8_t(bounded(in,0,20));fallback.flags=take<std::uint32_t>(in);
        const auto point=[&](){const int x=take<int>(in),y=take<int>(in),z=take<int>(in);return Coord{x,y,z};};
        const Coord position=point(),head=point();
        const int count=bounded(in,0,16);std::vector<MapCellInput> cells(std::size_t(count),MapCellInput{});std::vector<MapCellInput*> slots(262144);
        for(auto& c:cells){const int slot=bounded(in,0,262143);if(slots[slot])throw std::invalid_argument("Duplicate layer Cell slot");slots[slot]=&c;c.level=std::int8_t(bounded(in,-128,127));c.slope=std::uint8_t(bounded(in,0,20));c.flags=take<std::uint32_t>(in);}
        const int actionCount=bounded(in,1,128);std::vector<std::array<int,6>> actions;
        for(int i=0;i<actionCount;++i){const int mode=bounded(in,0,1),flag=take<int>(in),bridge=bounded(in,0,255),height=take<int>(in),threshold=take<int>(in),mutation=bounded(in,-1,255);actions.push_back({mode,flag,bridge,height,threshold,mutation});}
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra layer input");
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};
        MapFloorHeightState floor;floor.planes[0].x=1.;
        MapFloorHeightWorld world{slots,&fallback,[&](auto p){event('W',std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16));}};
        std::array<TerrainCellPoint,128> pool;pool.fill({px,py});
        FootCoordinateServices coordinates;
        // The original Drive getter reads head+40, NOT Move_To destination+34.
        coordinates.locomotor=[&](){event('H');return driveSecondaryCoordinates(position,head);};
        coordinates.coordinates=[&](){event('O');return position;};
        std::uint8_t bridge=0;
        for(const auto& a:actions){
            bridge=std::uint8_t(a[2]);int floors=0;FootLayerServices s;
            s.bridge=[&](){event('B',int(bridge));return bridge;};
            s.secondaryCoordinates=[&](int flag){event('C',flag);auto p=footSecondaryCoordinates(index,pool,coordinates);event('P',p.x,p.y,p.z);return p;};
            s.actorCoordinates=[&](){event('A',position.x,position.y,position.z);return position;};
            s.floorHeight=[&](Coord p){event('F',p.x,p.y,p.z);const int h=mapFloorHeight(floor,a[3],p,world);event('V',h);if(!floors++&&a[5]>=0){bridge=std::uint8_t(a[5]);event('X',int(bridge));}return h;};
            s.levelHeight=[&](){event('T',a[4]);return a[4];};
            s.cellFlags=[&](Coord p){event('M',p.x,p.y,p.z);const auto flags=mapCoordinateCell(p,world,262144).flags;event('m',flags);return flags;};
            const auto result=a[0]?footCoordinateLayer(index,a[1],s):objectCoordinateLayer(a[1],s);event('R',int(result));
        }
        event("state",int(bridge),fallback.position.x,fallback.position.y,int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));
        for(const auto& plane:floor.planes)for(double x:{plane.x,plane.y,plane.offset,plane.limit,plane.add})event(std::bit_cast<std::uint64_t>(x));
        std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
