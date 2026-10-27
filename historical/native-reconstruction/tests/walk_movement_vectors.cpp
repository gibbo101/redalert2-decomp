// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkMovement.hpp"
#include "assets/MovementData.hpp"
#include "assets/WalkCellView.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
template<class... T>void event(T... args){((std::cout<<args<<' '),...);}
void guards() {
    DirectionData data;WalkMovementNumerics n{data};WalkMovementState state;
    ActorGroundState ground;Facing body;int immobilized=0;double percentage=0;
    std::uint8_t a=1,b=1;WalkMovementActor actor{ground,body,immobilized,percentage,a,b};
    bool refused=false;try{processCommittedWalk(state,actor,n,{},0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||state.inProcessing35!=1)throw std::logic_error("Missing head refusal");
    state.head={1,0,0};n.squareRoot=[](double){return 1.;};refused=false;
    const auto previous=std::fegetround();std::fesetround(FE_UPWARD);
    try{processCommittedWalk(state,actor,n,{},0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||state.reallyMoving36!=1||std::fegetround()!=FE_UPWARD)throw std::logic_error("Arrival refusal/FP restoration");
    n.squareRoot=[](double){return 17.;};refused=false;
    try{processCommittedWalk(state,actor,n,{},0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||percentage!=1||a!=1)throw std::logic_error("Missing speed loses preceding writes");
    immobilized=1;state.moving34=255;
    if(processCommittedWalk(state,actor,n,{},0,0)!=255||state.reallyMoving36||state.inProcessing35||b)
        throw std::logic_error("Immobilized skip/raw moving result");
    std::fesetround(previous);std::cout<<"4 Walk movement guards PASS\n";
}
int main(int argc,char** argv){try {
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=4)throw std::invalid_argument("Walk vectors require render/raster/direction data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[2]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[3]),PatchedEngineSha);
    // Supplied immutable scalar matches original79B620, checked by evidence.
    const auto saved=std::fegetround();std::fesetround(FE_TONEAREST);
    const double radians=direction.pi/-32767.;std::fesetround(saved);
    const WalkMovementNumerics numeric{direction,radians,[&](double v){return tableSqrt(render,v);},
        [&](double v){return tableSine(raster,v);},[&](double v){return tableCosine(raster,v);}};
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char command=0;in>>command;std::array<int,25> v{};
        for(auto& value:v)if(!(in>>value))throw std::invalid_argument("Missing Walk input");
        std::string extra;if(command!='W'||in>>extra)throw std::invalid_argument("Invalid Walk input");
        // xyz,headXYZ,speed,immobilized,marked,bridge,5a1,57a,moving,
        // floor,bridgeHeight,oldLevel,newLevel,oldFlags,newFlags,markPolicy,
        // desired,start,timer,duration,tick. Raw bytes are retained.
        for(auto i:{8,9,10,11,12})if(v[i]<0||v[i]>255)throw std::invalid_argument("Walk raw byte");
        if(v[15]<-128||v[15]>127||v[16]<-128||v[16]>127||v[19]<0||v[19]>7||v[20]<0||v[20]>65535||v[21]<0||v[21]>65535)
            throw std::invalid_argument("Walk fixture domain");
        ActorGroundState ground{{v[0],v[1],v[2]},std::uint8_t(v[8]),std::uint8_t(v[9])};
        Facing body{std::uint16_t(v[20]),std::uint16_t(v[21]),v[22],v[23],256};
        auto a1=std::uint8_t(v[10]),a2=std::uint8_t(v[11]);double percentage=.375;
        WalkMovementState state{{17,23,31},{v[3],v[4],v[5]},std::uint8_t(v[12]),173,197};
        MapCellInput old,next;old.level=std::int8_t(v[15]);old.flags=std::uint32_t(v[17]);
        next.level=std::int8_t(v[16]);next.flags=std::uint32_t(v[18]);
        int queries=0;
        WalkMovementServices services;
        services.trace=[](auto c,auto x,auto y,auto z){event(c,x,y,z);};
        services.speed=[&]{return v[6];};
        services.placement.mark=[&](int kind){
            event('M',kind,ground.position.x,ground.position.y,ground.position.z,int(ground.bridge79),int(ground.marked74));
            if(v[19]&1)ground.marked74=std::uint8_t(kind);
            if(!kind&&(v[19]&2)){ground.position.x=signed32(std::uint32_t(ground.position.x)+3);ground.position.y=signed32(std::uint32_t(ground.position.y)-5);ground.position.z=signed32(std::uint32_t(ground.position.z)+7);ground.bridge79^=128;}
            if(kind&&(v[19]&4))ground.position.z=signed32(std::uint32_t(ground.position.z)+11);
        };
        services.placement.floor=[&](Coord p){event('F',p.x,p.y,p.z);return v[13];};
        services.lookup=[&](TerrainCellPoint p)->WalkMovementCellView{event('B',p.x,p.y);return borrowWalkCell(queries++==0?old:next);};
        services.currentCell=[&](Coord p)->WalkMovementCellView{event('N',p.x,p.y,p.z);return borrowWalkCell(next);};
        services.dirty=[&](WalkMovementCellView c){if(c.identity!=&next)throw std::logic_error("Wrong dirty Cell");event('D');};
        for(const auto mode:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}) {
            // Each command is run only once; incoming modes vary by tick bits.
            if(mode!=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::uint32_t(v[24])&3])continue;
            std::fesetround(mode);
            const auto result=processCommittedWalk(state,{ground,body,v[7],percentage,a1,a2},numeric,services,v[24],v[14]);
            if(std::fegetround()!=mode)throw std::logic_error("Walk leaked rounding mode");
            event('R',int(result),'Z',ground.position.x,ground.position.y,ground.position.z,int(ground.marked74),int(ground.bridge79),int(a1),int(a2),std::bit_cast<std::uint64_t>(percentage),
                body.desired,body.start,body.timerStart,body.duration,body.rate,int(state.moving34),int(state.inProcessing35),int(state.reallyMoving36),
                state.destination.x,state.destination.y,state.destination.z,state.head.x,state.head.y,state.head.z);
            std::cout<<'\n';std::fesetround(FE_TONEAREST);
        }
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
