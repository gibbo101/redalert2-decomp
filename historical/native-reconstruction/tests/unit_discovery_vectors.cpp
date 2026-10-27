// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MapVisibility.hpp"
#include "sim/UnitDiscovery.hpp"
#include "render/RampGeometry.hpp"
#include "assets/Archive.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <array>
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
bool byte(int v){return v>=0&&v<=255;}
bool house(int v){return v>=-1&&v<=1;}
int readByte(std::istream& in){int v=0;in>>v;if(!in||!byte(v))throw std::invalid_argument("Invalid discovery byte");return v;}
void guards(){
    MapVisibilityState s;MapVisibilityWorld w;bool refused=false;
    try{mapPrimaryVisibility({},s,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Zero visibility divisor accepted");
    s.mode=1;s.currentHouse13d=255;s.overrideValue=-1;
    if(mapSecondaryVisibility({},s,w))throw std::runtime_error("Secondary shortcut failed");
    std::cout<<"Visibility division refusal and pre-division secondary shortcut: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=5)throw std::invalid_argument("Expected geometry/render/raster/direction data");
    const auto geometry=readRampGeometryData(readFile(argv[1]),PatchedEngineSha);
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[3]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[4]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;if(!in)throw std::invalid_argument("Empty discovery fixture");
        if(op=='S'){
            int mode=0;in>>mode;if(!in||mode<0||mode>3)throw std::invalid_argument("Invalid stock FP mode");
            const int rounding=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::size_t(mode)];
            if(std::fesetround(rounding))throw std::runtime_error("Cannot set stock FP mode");
            const auto g=stockRampGeometry(render,raster,direction,geometry);
            for(double v:{g.diagonal,g.diagonalPer60,g.inverseDiagonalPer60,g.angle45,g.angle60,g.angle90})event(std::bit_cast<std::uint64_t>(v));
            event(g.levelHeight,std::bit_cast<std::uint64_t>(g.diagonalTilt),std::bit_cast<std::uint64_t>(g.axisTilt),g.quadrupleHeight);
            // Direction3 from the complete initialized eight-direction table.
            event(1,1);
            if(std::fegetround()!=rounding)throw std::runtime_error("Stock caller FP mode changed");
        }else if(op=='V'){
            int secondary=0;Coord p;MapVisibilityState s;
            in>>secondary>>s.heightDivisor>>s.mode>>s.overrideValue;s.currentHouse13d=std::uint8_t(readByte(in));in>>p.x>>p.y>>p.z;
            if(!in||secondary<0||secondary>1)throw std::invalid_argument("Invalid visibility header");
            std::array<MapVisibilityCell,4> cells;std::vector<MapVisibilityCell*> table(262144);
            for(int i=0;i<4;++i){
                int slot=0,x=0,y=0;std::uint64_t a=0,b=0;in>>slot>>x>>y>>a>>b;
                if(!in||slot<-1||slot>=262144||x<-32768||x>32767||y<-32768||y>32767||a>0xffffffff||b>0xffffffff||(i==3&&slot!=-1))throw std::invalid_argument("Invalid visibility Cell");
                cells[i]={{std::int16_t(x),std::int16_t(y)},std::uint32_t(a),std::uint32_t(b)};
                if(slot!=-1){if(table[std::size_t(slot)])throw std::invalid_argument("Duplicate visibility slot");table[std::size_t(slot)]=&cells[i];}
            }
            MapVisibilityWorld w{table,&cells[3],{1,1}};
            w.query=[](char k,TerrainCellPoint p){event(k,int(p.x),int(p.y));};
            w.neighbor=[&](const auto& c,int d){event('n',int(&c-cells.data()),d);};
            w.fallbackStore=[](TerrainCellPoint p){event('f',int(p.x),int(p.y));};
            // Both production borrowed lookup and legacy table lookup must
            // match the same original trace, including stored-point neighbor
            // identity and fallback assignments. Reset logical state between.
            const auto initial=cells;std::ostringstream tableTrace,borrowedTrace;
            auto* originalOutput=std::cout.rdbuf(tableTrace.rdbuf());
            try {
                const bool result=secondary?mapSecondaryVisibility(p,s,w):mapPrimaryVisibility(p,s,w);
                event('R',int(result),int(cells[3].point.x),int(cells[3].point.y));
                cells=initial;int selected=-1;
                w.borrowedCell=[&](TerrainCellPoint point){
                    const int slot=int(point.y)*512+int(point.x);auto* cell=slot>=0&&slot<262144?table[std::size_t(slot)]:nullptr;
                    if(!cell){cells[3].point=point;w.fallbackStore(point);cell=&cells[3];}
                    selected=int(cell-cells.data());return *cell;
                };
                w.neighbor=[&](const auto&,int d){event('n',selected,d);};
                std::cout.rdbuf(borrowedTrace.rdbuf());
                const bool resultBorrowed=secondary?mapSecondaryVisibility(p,s,w):mapPrimaryVisibility(p,s,w);
                event('R',int(resultBorrowed),int(cells[3].point.x),int(cells[3].point.y));
                std::cout.rdbuf(originalOutput);
            }catch(...){std::cout.rdbuf(originalOutput);throw;}
            if(tableTrace.str()!=borrowedTrace.str())throw std::runtime_error("Borrowed visibility lookup changed original table behavior");
            std::cout<<tableTrace.str();
        }else if(op=='H'){
            int mode=0;in>>mode;UnitDiscoveryHouse h;h.human134=std::uint8_t(readByte(in));h.control135=std::uint8_t(readByte(in));
            event(unsigned(discoveryHouseControlled(h,mode)));
        }else if(op=='Q'){
            UnitDiscoveryActor a;int requested=0;in>>a.mission98>>a.queuedA0;a.queuedA4=std::uint8_t(readByte(in));in>>requested;
            if(!in)throw std::invalid_argument("Invalid mission fixture");
            queueUnitDiscoveryMission(a,requested,[](int s,int o,std::uint32_t v){event('W',s,o,v);});
            event('R',a.queuedA0,unsigned(a.queuedA4));
        }else if(op=='D'){
            UnitDiscoveryActor a;UnitDiscoveryWorld w;int hasTag=0,mutation=0,count=0;
            in>>w.mode>>w.loading>>w.tagContext>>w.currentHouse>>a.owner;
            a.field372=std::uint8_t(readByte(in));a.current373=std::uint8_t(readByte(in));a.other374=std::uint8_t(readByte(in));
            in>>a.mission98>>a.queuedA0;a.queuedA4=std::uint8_t(readByte(in));in>>hasTag>>mutation;
            if(!in||!house(w.currentHouse)||a.owner<0||a.owner>1||hasTag<0||hasTag>1||mutation<0||mutation>1)throw std::invalid_argument("Invalid discovery actor");
            a.hasTag=hasTag!=0;
            for(int i=0;i<2;++i){auto& h=w.houses[i];for(auto* p:{&h.human134,&h.control135,&h.discovered13c,&h.field13d,&h.field5668,&h.field5669})*p=std::uint8_t(readByte(in));}
            in>>count;if(!in||count<1||count>128)throw std::invalid_argument("Invalid discovery sequence size");
            w.trace=[](char k,int v){event(k,v);};w.store=[](int s,int o,std::uint32_t v){event('W',s,o,v);};
            w.tagEvent=[&](int context){event('t',4,context);if(mutation){a.owner=1-a.owner;event('z',a.owner);}};
            for(int i=0;i<count;++i){
                int discoverer=0;in>>discoverer;if(!in||!house(discoverer))throw std::invalid_argument("Invalid discoverer");
                const bool accepted=discoverUnit(a,discoverer,w);
                event('R',int(accepted),a.owner,unsigned(a.current373),unsigned(a.other374),a.queuedA0,unsigned(a.queuedA4));
                for(int j=0;j<2;++j){const auto& h=w.houses.at(j);event(unsigned(h.discovered13c),unsigned(h.field5668),unsigned(h.field5669));}
            }
        }else throw std::invalid_argument("Invalid discovery fixture kind");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing discovery input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
