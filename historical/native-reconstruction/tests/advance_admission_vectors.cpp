// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveAdvanceAdmission.hpp"
#include "assets/MovementData.hpp"
#include "assets/RenderData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/MapCellChildren.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
#include "GroundDriveGateVectors.hpp"
#include "GroundDriveAdmissionVectors.hpp"
#include "GroundDriveMovingResidentVectors.hpp"
namespace {
void checkAdmissionGuards(){
    // Authored jump-point fixture checks the adapter's boundary and refusal
    // timing. Differential tests supply original tracks and actual admission.
    DriveData data;data.transitions[0]={1,0,0,0};data.transitions[2]={2,0,0,0};
    data.tracks[0].points={{0,0,0},{1,1,0},{2,2,0},{0,0,0}};
    data.tracks[0].jumpIndex=1;data.tracks[1].entryIndex=1;
    for(int code:{0,2,7,-1,1,3,4,5,6,8}){
        GroundDriveAdvanceState s;s.actor.position={-256,-256,0};s.actor.marked74=1;
        s.head={-257,-257,0};s.driving=true;s.track=0;s.index=1;s.accumulator=8;
        int queries=0,actorWrites=0,indexWrites=0;bool reached=false,refused=false;
        GroundDriveAdvanceServices svc;int identity=0;
        svc.ground.floor=[](Coord){return 0;};svc.ground.mark=[](int){};
        svc.coordinateCell=[&](Coord)->const void*{return &identity;};
        svc.wordCell=[](std::int16_t,std::int16_t){};svc.unmarkOccupation=[](Coord){};
        svc.notify=[](int){};svc.postCell=[]{};
        svc.rejectedSwitchAdmission=[](Coord,int){throw std::runtime_error("Stale admission callback used");};
        svc.driveStore=[&](int off,int){if(off==0x5c)++indexWrites;};
        GroundDriveAdvanceAdmissionServices admission;
        admission.cell=[&](Coord p){
            if(p!=s.actor.position||queries>1)throw std::runtime_error("Advance current-Cell query order");
            GroundDriveCell c;c.level=++queries==1?11:-5;return c;
        };
        admission.wordCell=[&](std::int16_t x,std::int16_t y){
            if(queries++!=2||x!=0||y!=-1)throw std::runtime_error("Advance signed word query order");
            GroundDriveCell c;c.identity=&identity;return c;
        };
        admission.check=[&](const GroundDriveCell& c,int d,int level){
            if(queries!=3||c.identity!=&identity||d!=2||level!=-5||s.index!=1||!actorWrites)
                throw std::runtime_error("Advance admission identity/level/placement order");
            reached=true;return code;
        };
        try{advanceWithOrdinaryAdmission(s,data,0,1.,100,false,svc,2,admission,
            [&](int,int){++actorWrites;});}
        catch(const UnsupportedGroundAdmission& e){refused=true;if(e.result!=code)throw;}
        const bool supported=code==0||code==2||code==7;
        if(!reached||refused==supported||s.index!=(supported?2:1)||indexWrites!=(supported?1:0))
            throw std::runtime_error("Advance result/refusal continuation differs");
    }
}
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    std::vector<unsigned char> bytes{s.flags};
    auto word=[&](std::uint64_t n,int size){for(int i=0;i<size;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
    auto scalar=[&](double n){word(std::bit_cast<std::uint64_t>(n),8);};
    scalar(s.height);scalar(s.scale);for(const auto& v:s.planes)for(double n:{v.x,v.y,v.offset,v.limit,v.add})scalar(n);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char out[32];unsigned n=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),out,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Advance digest failed");
    std::ostringstream result;for(auto v:out)result<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return result.str();
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string_view(argv[1])=="--guards"){
        GroundDriveAdvanceState s;s.actor.position={1,2,3};s.accumulator=7;bool refused=false;
        try{advanceWithOrdinaryAdmission(s,{},15,0.,0,false,{},-1,{});}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.actor.position!=Coord{1,2,3}||s.accumulator!=7)
            throw std::runtime_error("Missing Advance admission services changed state");
        checkAdmissionGuards();
        std::cout<<"Advance admission services, 0/2/7 continuation and seven typed refusals: PASS\n";return 0;
    }
    if(argc!=4)throw std::invalid_argument("Advance vectors require owned executable and prepared render/direction data");
    const auto data=readDriveData(readFile(argv[1]),readFile(argv[3]));
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<int,21> v{};in>>cmd;for(auto& n:v)in>>n;
        const auto [track,index,acc,driving,speed,tick,steps,suppress,marked,markEffect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode]=v;
        int heading=0,rot=0,initialRamp=0,dest=0;in>>heading>>rot>>initialRamp>>dest;
        std::array<int,24> route{};for(auto& n:route)in>>n;
        std::array<double,4> numeric{};for(auto& n:numeric){std::uint64_t bits=0;in>>bits;n=std::bit_cast<double>(bits);if(!std::isfinite(n))throw std::invalid_argument("Nonfinite Advance input");}
        const auto [percentage,landSpeed,uphill,downhill]=numeric;
        for(int d:route)if(d<-1||d>7)throw std::invalid_argument("Advance route outside domain");
        if(route.back()!=-1||heading<0||heading>65535||rot<1||rot>127||initialRamp<0||initialRamp>20||dest<0||dest>1)throw std::invalid_argument("Advance state outside domain");
        if(!in||cmd!='V'||track<-1||track>=64||index<0||index>127||driving<0||driving>1||speed<0||speed>255||
           steps<1||steps>256||(suppress!=0&&suppress!=1)||marked<0||marked>255||markEffect<0||markEffect>1||level<-126||level>125||
           ramp<0||ramp>20||pattern<0||pattern>1||resident<0||resident>1||mode<0||mode>3||!std::isfinite(percentage))
            throw std::invalid_argument("Unsupported ground Advance command");
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* n:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*n=std::bit_cast<double>(bits);
            if(!std::isfinite(*n))throw std::invalid_argument("Nonfinite Advance plane");
        }
        if(!in)throw std::invalid_argument("Malformed Advance planes");
        GroundDriveMovingResidentVectors moving(in);
        for(const auto& r:moving.gates.updates)if(r[0]>=steps)
            throw std::invalid_argument("Admission transition beyond Advance sequence");
        if(!in)throw std::invalid_argument("Malformed gate Advance input");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Advance input");
        GroundDriveProcessState state;auto& s=state.movement;s.actor={{x,y,z},std::uint8_t(marked),0};s.head={hx,hy,hz};s.track=track;s.index=index;
        s.accumulator=acc;s.driving=driving!=0;s.reached5a0=7;s.reached5a1=9;s.body.rate=std::uint16_t(rot*256);s.body.desired=s.body.start=std::uint16_t(heading);
        if(track==-1)s.head={};state.destination=dest?Coord{hx,hy,hz}:Coord{};state.route=route;state.percentage=percentage;
        state.ramps={initialRamp,initialRamp,99,7,2,2};state.retryPadding=7;
        std::array<MapCellInput,81> cells;MapCellInput fallback;fallback.position={-7,5};fallback.level=std::int8_t(level);fallback.slope=std::uint8_t(ramp);fallback.land=3;
        std::vector<MapCellInput*> slots(262144);
        for(int dy=-4;dy<=4;++dy)for(int dx=-4;dx<=4;++dx){
            const int cx=hx/256+dx,cy=hy/256+dy;const auto slot=std::int64_t(cy)*512+cx;
            if(resident&&slot>=0&&slot<262144){
                auto& c=cells[std::size_t((dy+4)*9+dx+4)];c.position={std::bit_cast<std::int16_t>(std::uint16_t(cx)),std::bit_cast<std::int16_t>(std::uint16_t(cy))};
                c.level=std::bit_cast<std::int8_t>(std::uint8_t(level+3*int(pattern&&dx>=0)));c.land=pattern?(std::abs(dx)+std::abs(dy))%12:0;c.slope=std::uint8_t((ramp+(pattern?std::abs(dx)+std::abs(dy):0))%21);slots[std::size_t(slot)]=&c;
            }
        }
        MapFloorHeightWorld world{slots,&fallback,{}};MapAttributeLookup words{slots,&fallback,{},{}};
        moving.bind(slots,cells,fallback,landSpeed);moving.processState=&state;
        moving.motion.data=data.get();moving.motion.squareRoot=[&](double n){return tableSqrt(render,n);};
        s.reached5a1=std::uint8_t(moving.initial5a1);s.body.timerStart=-1;
        state.retryStart=moving.retryStart;state.retryPadding=moving.retryPadding;state.retryRemaining=moving.retryRemaining;
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        const auto store=[&](int off,int n){event('A',off,std::uint32_t(n));};
        GroundDriveAdvanceServices adv;
        adv.ground.mark=[&](int kind){event('M',kind,s.actor.position.x,s.actor.position.y,s.actor.position.z,unsigned(s.actor.bridge79),unsigned(s.actor.marked74));
            if(markEffect)s.actor.marked74=std::uint8_t(kind);};
        adv.ground.floor=[&](Coord p){event('F',p.x,p.y,p.z);return mapFloorHeight(floor,104,p,world);};
        adv.coordinateCell=[&](Coord p)->const void*{event('C',p.x,p.y,p.z);return &mapCoordinateCell(p,world,262144);};
        adv.wordCell=[&](std::int16_t xx,std::int16_t yy){event('W',xx,yy);(void)mapAttributeCell({xx,yy},words);};
        adv.unmarkOccupation=[&](Coord p){event('U',p.x,p.y,p.z);};adv.notify=[&](int kind){event('N',kind);};adv.postCell=[&]{event('P');};
        adv.driveStore=[&](int off,int n){event('L',off,std::uint32_t(n));};
        const auto record=[](const MapCellInput& c){return GroundDriveCell{c.position.x,c.position.y,c.level,c.slope,c.land,&c};};
        GroundDriveAdvanceAdmissionServices admission;
        admission.cell=[&](Coord p){event('C',p.x,p.y,p.z);return record(mapCoordinateCell(p,world,262144));};
        admission.wordCell=[&](std::int16_t xx,std::int16_t yy){event('W',xx,yy);return record(mapAttributeCell({xx,yy},words));};
        admission.check=[&](const GroundDriveCell& c,int d,int level){return moving.admit(c,d,level);};
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        for(int j=0;j<steps;++j){
            const int current=signed32(std::uint32_t(tick)+std::uint32_t(j));
            moving.beforeTick(j,current);
            if(s.driving&&s.track!=-1)state.instancePercentage=std::clamp(state.percentage,0.,1.);
            advanceWithOrdinaryAdmission(s,*data,speed,state.percentage,current,suppress!=0,adv,state.route[0],admission,store);
            const bool result=false; // Original complete Advance returns byte zero.
            if(std::fegetround()!=modes[mode])throw std::runtime_error("Advance leaked FP mode");
            event('S',result,s.actor.position.x,s.actor.position.y,s.actor.position.z,s.head.x,s.head.y,s.head.z,s.track,s.index,s.accumulator,s.driving,
                unsigned(s.actor.marked74),unsigned(s.reached5a0),unsigned(s.reached5a1),s.body.desired,s.body.start,s.body.timerStart,s.body.duration,s.body.rate,
                state.wasRotating,std::uint16_t(state.nextX)|(std::uint32_t(std::uint16_t(state.nextY))<<16),unsigned(state.crossing57b),
                std::bit_cast<std::uint64_t>(state.percentage),std::bit_cast<std::uint64_t>(state.instancePercentage),
                state.ramps.current,state.ramps.previous,state.ramps.start,state.ramps.padding,state.ramps.remaining,state.ramps.duration,
                state.retryStart,state.retryPadding,state.retryRemaining);
            for(int d:state.route)event(d);
            event('a','s',unsigned(state.preparation57a));moving.state();
        }
        std::fesetround(old);event('H',digest(floor,fallback.position));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
