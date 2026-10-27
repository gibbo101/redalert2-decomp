// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/BuildingCoordinates.hpp"
#include "sim/CellClosestResident.hpp"
#include "sim/CellVisibilityDiscovery.hpp"
#include <iostream>
#include <sstream>
#include <array>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
void require(bool v){if(!v)throw std::invalid_argument("Invalid Building coordinate fixture");}
void guards(){
    bool refused=false;try{buildingFoundationWidth(-1,{});}catch(const std::invalid_argument&){refused=true;}require(refused);
    refused=false;try{buildingCoordinates({});}catch(const std::invalid_argument&){refused=true;}require(refused);
    const std::array<std::int32_t,1> table{INT32_MAX};require(buildingFoundationHeight(0,255,255,table)==INT32_MIN);
    const auto p=buildingCoordinates({[](auto){return INT32_MIN;},[]{return INT32_MAX;},[]{return Coord{INT32_MIN,INT32_MAX,127};}});
    require(p==Coord{2147483392,2147483519,127});
    std::cout<<"Building coordinate guards PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op;int index,extra,include,elevated,ignore;Coord p,common;std::array<int,2> flags;int x,y;
        in>>op>>index>>extra>>include>>p.x>>p.y>>p.z>>common.x>>common.y>>common.z>>flags[0]>>flags[1]>>x>>y>>elevated>>ignore;
        require(in&&(op=='C'||op=='H'||op=='W'||op=='R'||op=='V')&&index>=0&&index<22&&extra>=0&&extra<=255&&include>=0&&include<=255&&elevated>=0&&elevated<=1&&ignore>=-1&&ignore<=1);
        for(int f:flags)require(f>=0&&f<=255);
        std::array<std::int32_t,22> widths,heights;for(auto& n:widths)in>>n;for(auto& n:heights)in>>n;require(bool(in));
        const auto width=[&]{event('W');return buildingFoundationWidth(index,widths);};
        const auto height=[&](std::uint8_t arg){event('H',unsigned(arg));return buildingFoundationHeight(index,std::uint8_t(extra),arg,heights);};
        const auto coordinates=[&](int id){event('P',id);return id?buildingCoordinates({height,width,[&]{return p;}}):common;};
        if(op=='C'){const auto c=coordinates(1);event('O',0,std::uint32_t(c.x));event('O',4,std::uint32_t(c.y));event('O',8,std::uint32_t(c.z));event('R',c.x,c.y,c.z);}
        else if(op=='H')event('R',height(std::uint8_t(include)));
        else if(op=='W')event('R',width());
        else {CellClosestResidentServices s;
            s.head=[](bool upper){return upper?1:0;};s.flags=[&](int id){return std::uint8_t(flags.at(std::size_t(id)));};s.next=[](int id){return id? -1:1;};
            s.coordinates=coordinates;s.squareRoot=[](double n){return std::sqrt(n);};s.memberLimit=2;
            if(op=='R'){const int chosen=closestCellResident(x,y,elevated,ignore,s);event('R',chosen);}
            else {TerrainCellPoint current;CellVisibilityDiscoveryServices v;
                v.point=[](int){return TerrainCellPoint{9,11};};
                v.cellAt=[&](TerrainCellPoint point){current=point;if(point==TerrainCellPoint{9,11})return 0;event('F',int(point.x),int(point.y));return -1;};
                v.level=[&](int id){const int level=id==-1?127:0;event('C',int(current.x),int(current.y),id,'L',id,level);return level;};
                v.residents=[&](int){return s;};v.discoveredBy=[](int id,int h){event('D',id,h);};
                discoverVisibleCellResidents(0,17,false,v);event('R');
            }
        }
        in>>std::ws;require(in.eof());std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
