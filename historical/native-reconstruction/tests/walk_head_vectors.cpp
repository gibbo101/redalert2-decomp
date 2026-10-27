// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkHead.hpp"
#include "sim/OriginalMath.hpp"
#include "assets/InfantrySubcellData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include <cfenv>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace ra2;
template<class... T>void event(T... args){((std::cout<<args<<' '),...);}
struct Cell {
    std::uint32_t ground,elevated,flags;int groundHouse,elevatedHouse,overlay=-1;
    WalkHeadCell view(){return {{ground,elevated,flags,groundHouse,elevatedHouse},overlay};}
};
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
int identity(Coord p){return int((std::uint32_t(p.x)>>8 ^ std::uint32_t(p.y)>>8)&1u);}
void guards(){
    WalkMovementState walk{{17,23,31},{192,192,0},173,197,255};Coord position{128,128,0},request{384,128,0};
    UnitDiscoveryActor mission;mission.mission98=8;const void* target=&mission;
    int house=3,threshold=104,bridgeHeight=104,levelHeight=104;Cell cell{0x12340010,0x56780000,0,7,9};
    InfantrySubcellData data;OriginalRandomState rng;WalkHeadInputs inputs{data,rng,house,threshold,bridgeHeight,levelHeight};
    WalkHeadServices s;s.squareRoot=[](double v){return std::sqrt(v);};s.cell=[&](const Coord&){return cell.view();};s.floor=[](const Coord&){return 0;};
    bool refused=false;try{prepareWalkHead(walk,{position,mission,target},request,inputs,s);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||cell.ground!=0x12340000||cell.groundHouse!=-1||walk.head!=Coord{192,192,0})
        throw std::logic_error("Target child refusal must retain actual release and old head");
    target=nullptr;mission.mission98=2;cell.overlay=7;request={448,192,0};
    refused=false;try{prepareWalkHead(walk,{position,mission,target},request,inputs,s);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||walk.head!=request||cell.groundHouse!=-1)throw std::logic_error("Overlay refusal must retain selected head before claim");
    cell.overlay=-1;s.floor={};
    const auto mode=std::fegetround();std::fesetround(FE_UPWARD);
    refused=false;try{prepareWalkHead(walk,{position,mission,target},request,inputs,s);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||std::fegetround()!=FE_UPWARD)throw std::logic_error("Missing floor must restore host FP mode");
    std::fesetround(mode);s.floor=[](const Coord&){return 0;};request={};
    if(prepareWalkHead(walk,{position,mission,target},request,inputs,s)||walk.head!=Coord{}||cell.ground!=0x12340001||cell.groundHouse!=3||walk.destination!=Coord{17,23,31}||walk.moving34!=173||walk.inProcessing35!=197||walk.reallyMoving36!=255)
        throw std::logic_error("Empty request must claim current position without changing other Walk fields");
    std::cout<<"4 Walk head guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=3)throw std::invalid_argument("Walk head requires render/subcell data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);const auto data=readInfantrySubcellData(readFile(argv[2]),PatchedEngineSha);
    std::string line;std::size_t sequence=0;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char command;int disabled,first,second,targetValue,count;std::uint32_t seed;Coord position;WalkMovementState walk{{17,23,31},{},173,197,255};
        if(!(in>>command>>disabled>>first>>second>>seed>>position.x>>position.y>>position.z>>walk.head.x>>walk.head.y>>walk.head.z)||command!='H'||disabled<0||disabled>255||first<0||first>=250||second<0||second>=250)throw std::invalid_argument("Walk head initial fixture");
        std::array<Cell,2> cells{};for(auto& c:cells)if(!(in>>c.ground>>c.elevated>>c.flags>>c.groundHouse>>c.elevatedHouse))throw std::invalid_argument("Walk head Cells");
        if(!(in>>targetValue>>count)||targetValue<0||targetValue>1||count<1||count>512)throw std::invalid_argument("Walk head steps");
        const void* target=targetValue?&cells:nullptr;OriginalRandomState rng{std::uint8_t(disabled),first,second,{}};
        for(auto& word:rng.table){seed=seed*1664525u+1013904223u;word=seed;}
        const auto savedMode=std::fegetround();const int modes[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};const int mode=modes[sequence++%4];std::fesetround(mode);
        UnitDiscoveryActor mission;
        for(int i=0;i<count;++i){
            Coord request;int requestKind,trigger,mutation,floor,threshold,house,height,level;
            if(!(in>>request.x>>request.y>>request.z>>requestKind>>trigger>>mutation>>floor>>threshold>>house>>height>>level>>mission.mission98>>mission.queuedA0)||requestKind<0||requestKind>2||trigger<0||trigger>8||mutation<0||mutation>1023)throw std::invalid_argument("Walk head step domain");
            int floors=0;WalkHeadServices s;
            const auto tag=[&](const Coord& p){return &p==&walk.head?'h':&p==&position?'a':&p==&request?'r':'s';};
            s.squareRoot=[&](double v){event('Q',int(v));return tableSqrt(render,v);};
            s.cell=[&](const Coord& p){const int id=identity(p);event('N',id,tag(p),p.x,p.y,p.z);return cells[std::size_t(id)].view();};
            s.floor=[&](const Coord& p){
                event('F',tag(p),p.x,p.y,p.z);++floors;
                if(floors==trigger){
                    if(mutation&1){position.x=add(position.x,5);position.y=add(position.y,-7);position.z=add(position.z,77);}
                    if(mutation&2){request.x=add(request.x,257);request.y=add(request.y,-513);request.z=add(request.z,11);}
                    if(mutation&4)for(auto& c:cells)c.flags^=0x100;
                    if(mutation&8)threshold=add(threshold,37);
                    if(mutation&16)house=add(house,5);
                    if(mutation&32)height=add(height,11);
                    if(mutation&64)level=add(level,1);
                    if(mutation&128)for(auto& c:cells){c.ground^=0x1234001c;c.elevated^=0x9876001c;}
                    if(mutation&256){mission.mission98=-1;mission.queuedA0=8;}
                    if(mutation&512){walk.head.x=add(walk.head.x,257);walk.head.y=add(walk.head.y,-513);walk.head.z=add(walk.head.z,11);}
                }
                return floor;
            };
            s.houseQuery=[&]{event('H',house);};s.missionQuery=[&](int m){event('M',m);};
            s.cellStore=[&](InfantryOccupationCell c,int off,int width,std::uint32_t value){event('C',&c.ground==&cells[0].ground?0:1,off,width,value);};
            s.headStore=[&](int off,int value){event('L',off,std::uint32_t(value));};
            s.randomDraw=[&](std::uint32_t value,const OriginalRandomState& state){event('D',value,state.next1,state.next2);};
            s.cellEffect=[&](WalkHeadCell c){event('E',&c.occupation.ground==&cells[0].ground?0:1);};
            const Coord& borrowed=requestKind==1?walk.head:requestKind==2?position:request;
            const auto result=prepareWalkHead(walk,{position,mission,target},borrowed,{data,rng,house,threshold,height,level},s);
            if(std::fegetround()!=mode)throw std::logic_error("Walk head changed host FP mode");
            event('R',int(result),'P',position.x,position.y,position.z,request.x,request.y,request.z,walk.head.x,walk.head.y,walk.head.z,threshold,house,height,level,mission.mission98,mission.queuedA0);
        }
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra Walk head input");std::fesetround(savedMode);
        event('Z');for(const auto& c:cells)event(c.ground,c.elevated,c.flags,c.groundHouse,c.elevatedHouse);
        event("rng",int(rng.disabled),rng.next1,rng.next2);for(auto word:rng.table)event(word);std::cout<<'\n';
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
