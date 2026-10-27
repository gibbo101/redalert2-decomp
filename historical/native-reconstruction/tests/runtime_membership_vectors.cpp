// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TerrainUnitContext.hpp"
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
    std::unique_ptr<prepared_fixture::Map> prepared;std::shared_ptr<MutableUnitMap> map;std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        if(op=='P'){
            prepared=std::make_unique<prepared_fixture::Map>();prepared->prepare(in,render);
            map=std::make_shared<MutableUnitMap>(UnitMapSeed{prepared->cells,prepared->slots,prepared->fallback,prepared->floorState,prepared->membershipResident,prepared->buffer4,prepared->buffer10,prepared->width,prepared->height,prepared->levelHeight});
            if(map->levelHeight!=stock.levelHeight)throw std::invalid_argument("Prepared Drive requires stock height");
        }else if(op=='M'||op=='A'||op=='R'){
            if(!map)throw std::invalid_argument("Prepared Drive requires a prepared map");
            Coord at,destination;int heading=0,rot=0,speed=0,tick=0,steps=0,marked=0,effect=0,mode=0,present=0,key=0;
            in>>at.x>>at.y>>at.z>>destination.x>>destination.y>>destination.z>>heading>>rot>>speed>>tick>>steps>>marked>>effect>>mode>>present>>key;
            std::array<int,24> route;for(auto& d:route)in>>d;
            std::array<std::uint64_t,4> numeric;for(auto& n:numeric)in>>n;
            int crusher=1;if(op=='A'||op=='R')in>>crusher;
            Coord parkedAt;int parkedHeading=0,firstPadding=0,secondPadding=0,parkedOrder=0;
            if(op=='R')in>>parkedAt.x>>parkedAt.y>>parkedAt.z>>parkedHeading>>firstPadding>>secondPadding>>parkedOrder;
            if(!in||heading<0||heading>65535||rot<1||rot>127||speed<0||speed>255||steps<1||steps>256||marked<0||marked>255||
               marked!=0||effect!=1||mode<0||mode>3||present<0||present>1||crusher<0||crusher>255||
               parkedHeading<0||parkedHeading>65535||parkedOrder<0||parkedOrder>1)throw std::invalid_argument("Prepared Drive command outside domain");
            std::array<double,4> numbers;for(unsigned i=0;i<4;++i){numbers[i]=std::bit_cast<double>(numeric[i]);if(!std::isfinite(numbers[i]))throw std::invalid_argument("Nonfinite Drive numeric input");}
            bool end=false;for(int d:route){if(d==-1)end=true;else if((end&&op=='M')||d<0||d>7)throw std::invalid_argument("Invalid route");}if(route.back()!=-1)throw std::invalid_argument("Unterminated route");
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
            const auto query=[](char c,Coord p){out(c,p.x,p.y);if(c=='C'||c=='F')out(p.z);};
            const auto store=[](char kind,int id,int off,std::uint32_t value){out('w',kind,id,off,value);};
            TerrainUnitContext context(map,std::move(supplied),state,actorStore,store,query);
            if(op=='R'){
                GroundDriveProcessState parked;parked.movement.actor={parkedAt,0,0};
                parked.movement.reached5a0=7;parked.movement.reached5a1=9;
                parked.movement.body.desired=parked.movement.body.start=std::uint16_t(parkedHeading);
                parked.movement.body.rate=std::uint16_t(rot*256);
                UnitDiscoveryActor discovery;discovery.owner=0;discovery.mission98=2;discovery.queuedA0=-1;discovery.queuedA4=255;
                context.bindParked(parked,{},discovery,[](int off,int n){out('r','A',off,std::uint32_t(n));});
            }
            if(op=='A'||op=='R')context.enableAdmission({std::uint8_t(crusher),0,0,op=='R',{firstPadding,secondPadding}},query,
                [](char kind,int a,int b,int c){out('a',kind,a,b,c);},
                [](int off,int n){out('a','L',off,std::uint32_t(n));});
            auto& live=context.state;auto& movement=live.movement;
            auto& membership=*context.unit;const auto& services=context.services;
            MapFloorHeightWorld world=membership.world();
            const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
            setActorRelativeHeight(movement.actor,0,416,services.advance.ground,actorStore);
            unlimboDriveRamp(live.ramps,[&]{(void)services.cell(movement.actor.position);return services.cell(movement.actor.position).ramp;},tick,7,rampStore);
            if(op=='R'){
                auto& p=*context.parked;
                setActorRelativeHeight(p.state.movement.actor,0,416,p.services.advance.ground,[](int off,int n){out('r','A',off,std::uint32_t(n));});
                unlimboDriveRamp(p.state.ramps,[&]{(void)p.services.cell(p.state.movement.actor.position);return p.services.cell(p.state.movement.actor.position).ramp;},tick,7,
                    [](int off,int n){out('r','L',off+4,std::uint32_t(n));});
                if(!parkedOrder)p.services.advance.ground.mark(1);
            }
            services.advance.ground.mark(1);
            if(op=='R'&&parkedOrder)context.parked->services.advance.ground.mark(1);
            for(int j=0;j<steps;++j){
                const int now=signed32(std::uint32_t(tick)+std::uint32_t(j));
                const bool result=context.process(*drive,speed,now,7,actorStore,rampStore);
                out('S',result,movement.actor.position.x,movement.actor.position.y,movement.actor.position.z,movement.head.x,movement.head.y,movement.head.z,
                    movement.track,movement.index,movement.accumulator,movement.driving,unsigned(movement.actor.marked74),unsigned(movement.reached5a0),unsigned(movement.reached5a1),
                    movement.body.desired,movement.body.start,movement.body.timerStart,movement.body.duration,movement.body.rate,live.wasRotating,
                    std::uint16_t(live.nextX)|(std::uint32_t(std::uint16_t(live.nextY))<<16),unsigned(live.crossing57b),
                    std::bit_cast<std::uint64_t>(live.percentage),std::bit_cast<std::uint64_t>(live.instancePercentage),
                    live.ramps.current,live.ramps.previous,live.ramps.start,live.ramps.padding,live.ramps.remaining,live.ramps.duration,
                    live.retryStart,live.retryPadding,live.retryRemaining);
                for(int d:live.route)out(d);
                if(op=='A'||op=='R')out('a','s',unsigned(live.preparation57a));
                DriveBodyInputs body;body.ramp=live.ramps;body.tick=now;body.type330=30.5;body.type338=24.25;
                std::int32_t bodyKey=key,shadowKey=key;const auto facing=[&]{out('f');return movement.body.current(now);};
                const auto keyStore=[](int n){out('k',std::uint32_t(n));};
                out("body");const auto bodyMatrix=driveBodyPose(raster,poseData,matrices,quaternions,body,facing,present?&bodyKey:nullptr,[]{out('t');},keyStore);
                out("matrix");for(float n:bodyMatrix)out(std::bit_cast<std::uint32_t>(n));out(std::uint32_t(bodyKey));
                DriveShadowInputs shadow;shadow.position=movement.actor.position;shadow.tick=now;shadow.slopeStart=live.ramps.start;shadow.slopeRemaining=live.ramps.remaining;shadow.slopeDuration=live.ramps.duration;
                DriveShadowServices shadowServices;
                shadowServices.currentRamp=[&](Coord p){out('c');return mapCoordinateCell(p,world,262144).slope;};shadowServices.bodyFacing=facing;
                out("shadow");const auto shadowMatrix=driveShadowPose(raster,matrices,shadow,shadowServices,present?&shadowKey:nullptr,true,keyStore);
                out("matrix");for(float n:shadowMatrix)out(std::bit_cast<std::uint32_t>(n));out(std::uint32_t(shadowKey));
                out("relative",relativeMapHeight(map->floor,stock.levelHeight,movement.actor.position,0,416,world));
                if(std::fegetround()!=modes[mode])throw std::runtime_error("Prepared Drive leaked FP mode");
            }
            std::fesetround(old);
            Bytes bytes{map->floor.flags};const auto append=[&](std::uint64_t n,unsigned count){for(unsigned i=0;i<count;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
            append(std::bit_cast<std::uint64_t>(map->floor.height),8);append(std::bit_cast<std::uint64_t>(map->floor.scale),8);
            for(const auto& p:map->floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})append(std::bit_cast<std::uint64_t>(n),8);
            append(prepared_fixture::packed(map->fallback.input.position),4);out('H',digest(bytes));
            Bytes selected;const auto word=[&](std::uint32_t n){for(int i=0;i<4;++i)selected.push_back(std::uint8_t(n>>(i*8)));};
            for(std::size_t i=0;i<membership.occupation.size();++i){
                const auto& c=i==map->cells.size()?map->fallback:map->cells[i].attributes;const auto& o=membership.occupation[i];const auto& m=membership.membership.cells.at(1000+int(i));
                for(auto n:{std::uint32_t(c.input.tile),std::uint32_t(c.input.land),std::uint32_t(c.input.subTile),std::uint32_t(std::uint8_t(c.input.level)),std::uint32_t(c.input.slope),std::uint32_t(c.extraHeight),std::uint32_t(c.passability),std::uint32_t(m.head),std::uint32_t(m.alternateHead),o.ground,o.elevated})word(n);
            }
            out("map",digest(selected),digest(map->buffer4),digest(map->buffer10),membership.membership.actors.at(0).next,unsigned(membership.marking.needsRedraw),unsigned(membership.discovery.current373),unsigned(membership.discovery.other374),unsigned(membership.houses.houses.at(0).discovered13c),unsigned(membership.houses.houses.at(0).field5668),unsigned(membership.houses.houses.at(0).field5669));
            if(op=='R'){
                const auto& p=*context.parked;const auto& a=p.state.movement.actor;const auto& d=p.discovery;
                out("parked",a.position.x,a.position.y,a.position.z,unsigned(a.marked74),membership.membership.actors.at(1).next,
                    unsigned(p.marking.needsRedraw),unsigned(d.current373),unsigned(d.other374));
            }
        }else throw std::invalid_argument("Unknown prepared Drive command");
        if(!in)throw std::invalid_argument("Incomplete prepared Drive command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing prepared Drive command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
