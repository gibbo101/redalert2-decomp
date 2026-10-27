// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkMovement.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
template<class... T>void event(T... args){((std::cout<<args<<' '),...);}
void guards(){
    DirectionData direction;WalkMovementNumerics n{direction,0,[](double){return 0.;}};
    WalkMovementState w{{128,128,0},{128,128,0},1,173,197};ActorGroundState g{{128,128,0}};
    Facing f;int frozen=0;double percent=.375;std::uint8_t a=1,b=2,on=1,flag76=0,flag7a=0;
    std::array<std::int32_t,24> route;route.fill(-1);TerrainCellPoint cell{-7,9};
    std::int8_t secondary=-1;WalkArrivalContext arrival{{route,cell,on,flag76,flag7a,secondary},{}};
    WalkMovementServices s;s.placement.mark=[](int){};s.placement.floor=[](Coord){return 0;};
    bool refused=false;try{processSelectedWalk(w,{g,f,frozen,percent,a,b},n,s,arrival,0,104,104);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||route[23]!=-1||cell!=TerrainCellPoint{0,0}||a||w.head!=Coord{128,128,0}||w.inProcessing35!=1)
        throw std::logic_error("Arrival missing release must retain prior writes");
    arrival.services.release=[](const Coord&){};arrival.services.occupy=[](const Coord&){};
    arrival.services.notify=[&](int){on=0;};w.head={128,128,0};w.moving34=255;
    if(processSelectedWalk(w,{g,f,frozen,percent,a,b},n,s,arrival,1,104,104)!=255||w.inProcessing35||b!=2||percent!=0)
        throw std::logic_error("Arrival late off-map exit must skip57A clear and Mark1");
    on=1;secondary=0;w.head={128,128,0};w.destination={128,128,0};arrival.services.notify=[](int){};
    refused=false;try{processSelectedWalk(w,{g,f,frozen,percent,a,b},n,s,arrival,2,104,104);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||w.inProcessing35!=1||b!=2)throw std::logic_error("Entered indexed Foot query must refuse");
    secondary=-1;w.head={128,128,0};g.position={128,128,0};bool claimed=false;
    arrival.services.occupy=[&](const Coord& p){
        if(&p==&g.position)throw std::logic_error("Arrival claim must snapshot Object coordinates");
        const auto old=p;g.position.z+=77;claimed=true;
        if(p!=old)throw std::logic_error("Object mutation changed the claimed snapshot");
    };
    arrival.services.notify=[&](int){on=0;};
    processSelectedWalk(w,{g,f,frozen,percent,a,b},n,s,arrival,3,104,104);
    if(!claimed||g.position.z!=77)throw std::logic_error("Arrival claim snapshot guard did not execute");
    std::cout<<"4 Walk arrival guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=4)throw std::invalid_argument("Walk arrival vectors require render/raster/direction data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[2]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[3]),PatchedEngineSha);
    const auto saved=std::fegetround();std::fesetround(FE_TONEAREST);
    const double radians=direction.pi/-32767.;std::fesetround(saved);
    const WalkMovementNumerics numeric{direction,radians,[&](double v){return tableSqrt(render,v);},
        [&](double v){return tableSine(raster,v);},[&](double v){return tableCosine(raster,v);}};
    std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char command=0;in>>command;std::array<int,59> v{};
        for(auto& x:v)if(!(in>>x))throw std::invalid_argument("Missing Walk arrival input");
        std::string extra;if(command!='A'||in>>extra)throw std::invalid_argument("Invalid Walk arrival input");
        for(auto i:{8,9,10,11,12,54,55,56})if(v[i]<0||v[i]>255)throw std::invalid_argument("Walk raw byte");
        if(v[19]<0||v[19]>7||v[58]<0||v[58]>511||v[52]<-32768||v[52]>32767||v[53]<-32768||v[53]>32767)
            throw std::invalid_argument("Walk arrival fixture domain");
        ActorGroundState ground{{v[0],v[1],v[2]},std::uint8_t(v[8]),std::uint8_t(v[9])};
        Facing body{std::uint16_t(v[20]),std::uint16_t(v[21]),v[22],v[23],256};
        auto a1=std::uint8_t(v[10]),a2=std::uint8_t(v[11]);double percentage=.375;
        WalkMovementState state{{v[49],v[50],v[51]},{v[3],v[4],v[5]},std::uint8_t(v[12]),173,197};
        std::array<std::int32_t,24> route;std::copy_n(v.begin()+25,24,route.begin());
        TerrainCellPoint cell{std::int16_t(v[52]),std::int16_t(v[53])};
        auto on=std::uint8_t(v[54]),flag76=std::uint8_t(v[55]),flag7a=std::uint8_t(v[56]);
        std::int8_t secondary=-1;WalkArrivalContext arrival{{route,cell,on,flag76,flag7a,secondary},{}};
        const auto policy=v[58];
        arrival.services.release=[&](const Coord& p){event('U',p.x,p.y,p.z);
            if(policy&64)route[0]=-1;
            if(policy&128){ground.position.x=signed32(std::uint32_t(ground.position.x)+5);ground.position.z=signed32(std::uint32_t(ground.position.z)+7);}};
        arrival.services.occupy=[&](const Coord& p){event('O',p.x,p.y,p.z);if(policy&256)ground.marked74^=128;};
        arrival.services.notify=[&](int kind){event('J',kind);
            if(policy&1)on=0;if(policy&2)flag76=255;if(policy&4)flag7a=128;
            if(policy&8){on=1;flag76=flag7a=0;}
            if(policy&16)ground.position.z=signed32(std::uint32_t(ground.position.z)+15);
            if(policy&32)state.destination=ground.position;};
        arrival.services.destination=[](int a,int b){event('G',a,b);};
        arrival.services.resetMovement=[](){event('X');};
        WalkMovementServices services;services.trace=[](auto c,auto x,auto y,auto z){event(c,x,y,z);};
        services.speed=[&]{return v[6];};services.placement.floor=[&](Coord p){event('F',p.x,p.y,p.z);return v[13];};
        services.placement.mark=[&](int kind){
            event('M',kind,ground.position.x,ground.position.y,ground.position.z,int(ground.bridge79),int(ground.marked74));
            if(v[19]&1)ground.marked74=std::uint8_t(kind);
            if(!kind&&(v[19]&2)){ground.position.x=signed32(std::uint32_t(ground.position.x)+3);ground.position.y=signed32(std::uint32_t(ground.position.y)-5);ground.position.z=signed32(std::uint32_t(ground.position.z)+7);ground.bridge79^=128;}
            if(kind&&(v[19]&4))ground.position.z=signed32(std::uint32_t(ground.position.z)+11);
        };
        const auto mode=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::uint32_t(v[24])&3];std::fesetround(mode);
        const auto result=processSelectedWalk(state,{ground,body,v[7],percentage,a1,a2},numeric,services,arrival,v[24],v[14],v[57]);
        if(std::fegetround()!=mode)throw std::logic_error("Arrival leaked FP mode");
        event('R',int(result),'Z',ground.position.x,ground.position.y,ground.position.z,int(ground.marked74),int(ground.bridge79),int(a1),int(a2),std::bit_cast<std::uint64_t>(percentage),
            body.desired,body.start,body.timerStart,body.duration,body.rate,int(state.moving34),int(state.inProcessing35),int(state.reallyMoving36),
            state.destination.x,state.destination.y,state.destination.z,state.head.x,state.head.y,state.head.z,
            cell.x,cell.y,int(on),int(flag76),int(flag7a));
        for(auto x:route)event(x);std::cout<<'\n';std::fesetround(FE_TONEAREST);
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
