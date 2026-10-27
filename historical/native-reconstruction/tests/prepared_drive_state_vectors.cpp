// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedDriveTerrain.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MovementData.hpp"
#include "assets/Archive.hpp"
#include "render/DriveBodyPose.hpp"
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
std::string digest(const std::uint8_t* p,std::size_t n){return digest(Bytes(p,p+n));}
std::string digest(const std::vector<std::uint32_t>& v){Bytes b;for(auto n:v)for(unsigned i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));return digest(b);}
}
#include "prepared_map_fixture.hpp"
int main(int argc,char** argv){try{
    if(argc!=7)return 2;
    const auto drive=readDriveData(readFile(argv[1]));
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[3]),PatchedEngineSha);
    const auto directions=readDirectionData(readFile(argv[4]),PatchedEngineSha);
    const auto geometryData=readRampGeometryData(readFile(argv[5]),PatchedEngineSha);
    const auto poseData=readRampPoseData(readFile(argv[6]),PatchedEngineSha);
    const auto stock=stockRampGeometry(render,raster,directions,geometryData);
    const auto matrices=voxelRampShadowMatrices(raster,stock.axisTilt,stock.diagonalTilt);
    const auto quaternions=voxelRampQuaternions(raster,render,stock.axisTilt,stock.diagonalTilt);
    std::unique_ptr<prepared_fixture::Map> map;std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        if(op=='P'){
            map=std::make_unique<prepared_fixture::Map>();map->prepare(in,render);
            if(map->levelHeight!=stock.levelHeight)throw std::invalid_argument("Prepared Drive requires stock height");
        }else if(op=='M'){
            if(!map)throw std::invalid_argument("Prepared Drive requires a prepared map");
            Coord at,destination;int heading=0,rot=0,speed=0,tick=0,steps=0,marked=0,effect=0,mode=0,present=0,key=0;
            in>>at.x>>at.y>>at.z>>destination.x>>destination.y>>destination.z>>heading>>rot>>speed>>tick>>steps>>marked>>effect>>mode>>present>>key;
            std::array<int,24> route;for(auto& d:route)in>>d;
            std::array<std::uint64_t,4> numeric;for(auto& n:numeric)in>>n;
            if(!in||heading<0||heading>65535||rot<1||rot>127||speed<0||speed>255||steps<1||steps>256||marked<0||marked>255||
               effect<0||effect>1||mode<0||mode>3||present<0||present>1)throw std::invalid_argument("Prepared Drive command outside domain");
            std::array<double,4> numbers;for(unsigned i=0;i<4;++i){numbers[i]=std::bit_cast<double>(numeric[i]);if(!std::isfinite(numbers[i]))throw std::invalid_argument("Nonfinite Drive numeric input");}
            bool end=false;for(int d:route){if(d==-1)end=true;else if(end||d<0||d>7)throw std::invalid_argument("Invalid route");}if(route.back()!=-1)throw std::invalid_argument("Unterminated route");
            GroundDriveProcessState state;auto& m=state.movement;
            m.actor={at,std::uint8_t(marked),0};m.reached5a0=7;m.reached5a1=9;
            m.body.desired=m.body.start=std::uint16_t(heading);m.body.rate=std::uint16_t(rot*256);
            state.destination=destination;state.route=route;state.percentage=numbers[0];state.retryPadding=7;
            const auto actorStore=[](int off,int n){out('A',off,std::uint32_t(n));};
            const auto rampStore=[](int off,int n){out('L',off+4,std::uint32_t(n));};
            GroundDriveProcessServices supplied;
            supplied.advance.ground.mark=[&](int kind){out('M',kind,m.actor.position.x,m.actor.position.y,m.actor.position.z,unsigned(m.actor.bridge79),unsigned(m.actor.marked74));if(effect)m.actor.marked74=std::uint8_t(kind);};
            supplied.advance.unmarkOccupation=[](Coord p){out('U',p.x,p.y,p.z);};
            supplied.advance.notify=[](int n){out('N',n);};supplied.advance.postCell=[]{out('P');};
            supplied.reserve=[](auto x,auto y){out('R',x,y);};supplied.markNext=[](auto x,auto y){out('K',x,y);};
            supplied.markOccupation=[](Coord p){out('E',p.x,p.y,p.z);};
            supplied.admit=[](const GroundDriveCell& c,int d,int level){out('D',c.x,c.y,d,level);};
            supplied.noRoute=[]{out('B','J','V',0,1);};supplied.squareRoot=[&](double n){return tableSqrt(render,n);};
            for(int i=0;i<12;++i)supplied.trackSpeed[std::size_t(i)]=float(numbers[1]*(1.-i/16.));
            supplied.uphill=numbers[2];supplied.downhill=numbers[3];
            const auto check=[&](const MapCellInput& c){
                if(&c==&map->fallback.input){if(map->fallback.overlay!=-1)throw std::invalid_argument("Overlay fallback");return;}
                const auto slot=std::size_t(std::uint16_t(c.position.y))*512+std::uint16_t(c.position.x);
                if(slot>=map->slots.size()||map->slots[slot]<0||map->table[slot]!=&c||map->cells[std::size_t(map->slots[slot])].attributes.overlay!=-1)
                    throw std::invalid_argument("Prepared Drive profile refuses overlay/noncanonical Cells");
            };
            const auto query=[](char c,Coord p){out(c,p.x,p.y);if(c=='C'||c=='F')out(p.z);};
            MapFloorHeightWorld world{map->table,&map->fallback.input,{}};
            PreparedDriveTerrain terrain(map->floorState,stock.levelHeight,world,check,query);
            const auto services=terrain.bind(supplied);
            const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
            setActorRelativeHeight(m.actor,0,416,services.advance.ground,actorStore);
            unlimboDriveRamp(state.ramps,[&]{(void)services.cell(m.actor.position);return services.cell(m.actor.position).ramp;},tick,7,rampStore);
            for(int j=0;j<steps;++j){
                const int now=signed32(std::uint32_t(tick)+std::uint32_t(j));
                const bool result=processOrdinaryGroundDrive(state,*drive,speed,now,7,services,actorStore,rampStore);
                out('S',result,m.actor.position.x,m.actor.position.y,m.actor.position.z,m.head.x,m.head.y,m.head.z,
                    m.track,m.index,m.accumulator,m.driving,unsigned(m.actor.marked74),unsigned(m.reached5a0),unsigned(m.reached5a1),
                    m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate,state.wasRotating,
                    std::uint16_t(state.nextX)|(std::uint32_t(std::uint16_t(state.nextY))<<16),unsigned(state.crossing57b),
                    std::bit_cast<std::uint64_t>(state.percentage),std::bit_cast<std::uint64_t>(state.instancePercentage),
                    state.ramps.current,state.ramps.previous,state.ramps.start,state.ramps.padding,state.ramps.remaining,state.ramps.duration,
                    state.retryStart,state.retryPadding,state.retryRemaining);
                for(int d:state.route)out(d);
                DriveBodyInputs body;body.ramp=state.ramps;body.tick=now;body.type330=30.5;body.type338=24.25;
                std::int32_t bodyKey=key,shadowKey=key;const auto facing=[&]{out('f');return m.body.current(now);};
                const auto keyStore=[](int n){out('k',std::uint32_t(n));};
                out("body");const auto bodyMatrix=driveBodyPose(raster,poseData,matrices,quaternions,body,facing,present?&bodyKey:nullptr,[]{out('t');},keyStore);
                out("matrix");for(float n:bodyMatrix)out(std::bit_cast<std::uint32_t>(n));out(std::uint32_t(bodyKey));
                DriveShadowInputs shadow;shadow.position=m.actor.position;shadow.tick=now;shadow.slopeStart=state.ramps.start;shadow.slopeRemaining=state.ramps.remaining;shadow.slopeDuration=state.ramps.duration;
                DriveShadowServices shadowServices;
                shadowServices.currentRamp=[&](Coord p){out('c');return mapCoordinateCell(p,world,262144).slope;};shadowServices.bodyFacing=facing;
                out("shadow");const auto shadowMatrix=driveShadowPose(raster,matrices,shadow,shadowServices,present?&shadowKey:nullptr,true,keyStore);
                out("matrix");for(float n:shadowMatrix)out(std::bit_cast<std::uint32_t>(n));out(std::uint32_t(shadowKey));
                out("relative",relativeMapHeight(map->floorState,stock.levelHeight,m.actor.position,0,416,world));
                if(std::fegetround()!=modes[mode])throw std::runtime_error("Prepared Drive leaked FP mode");
            }
            std::fesetround(old);
            Bytes bytes{map->floorState.flags};const auto append=[&](std::uint64_t n,unsigned count){for(unsigned i=0;i<count;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
            append(std::bit_cast<std::uint64_t>(map->floorState.height),8);append(std::bit_cast<std::uint64_t>(map->floorState.scale),8);
            for(const auto& p:map->floorState.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})append(std::bit_cast<std::uint64_t>(n),8);
            append(prepared_fixture::packed(map->fallback.input.position),4);out('H',digest(bytes));
        }else throw std::invalid_argument("Unknown prepared Drive command");
        if(!in)throw std::invalid_argument("Incomplete prepared Drive command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing prepared Drive command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
