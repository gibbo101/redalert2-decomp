// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveProcess.hpp"
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
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    std::vector<unsigned char> bytes{s.flags};
    auto word=[&](std::uint64_t n,int size){for(int i=0;i<size;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
    auto scalar=[&](double n){word(std::bit_cast<std::uint64_t>(n),8);};
    scalar(s.height);scalar(s.scale);for(const auto& v:s.planes)for(double n:{v.x,v.y,v.offset,v.limit,v.add})scalar(n);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char out[32];unsigned n=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),out,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Process digest failed");
    std::ostringstream result;for(auto v:out)result<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return result.str();
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string_view(argv[1])=="--guards"){
        GroundDriveProcessState s;s.movement.actor.position={1,2,3};s.movement.accumulator=7;bool refused=false;
        try{processOrdinaryGroundDrive(s,{},15,0,7,{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.movement.actor.position!=Coord{1,2,3}||s.movement.accumulator!=7)throw std::runtime_error("Process missing-service guard changed state");
        refused=false;try{processGatedOrdinaryGroundDrive(s,{},15,0,7,{},{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.movement.actor.position!=Coord{1,2,3}||s.movement.accumulator!=7)throw std::runtime_error("Process missing-gate guard changed state");
        refused=false;try{processAdmittedOrdinaryGroundDrive(s,{},15,0,7,{},{},{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.movement.actor.position!=Coord{1,2,3}||s.movement.accumulator!=7)throw std::runtime_error("Process missing-admission guard changed state");
        GroundDriveMovingWaitState wait;GroundDriveMovingWaitServices services;
        refused=false;try{processMovingResidentOrdinaryGroundDrive(s,{},15,0,7,{},{},{},{},wait,services);}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.movement.actor.position!=Coord{1,2,3}||s.movement.accumulator!=7||wait.start!=-1)
            throw std::runtime_error("Process missing moving-resident service guard changed state");
        refused=false;try{processAdvanceAdmittedOrdinaryGroundDrive(s,{},15,0,7,{},{},{},{},wait,services);}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.movement.actor.position!=Coord{1,2,3}||s.movement.accumulator!=7||wait.start!=-1)
            throw std::runtime_error("Process missing Advance admission services changed state");
        std::cout<<"Ground Process service guard: PASS\n";return 0;
    }
    if(argc!=3&&argc!=4)throw std::invalid_argument("Process vectors require owned executable and prepared render data");
    const auto data=argc==4?readDriveData(readFile(argv[1]),readFile(argv[3])):readDriveData(readFile(argv[1]));
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<int,21> v{};in>>cmd;for(auto& n:v)in>>n;
        const auto [track,index,acc,driving,speed,tick,steps,suppress,marked,markEffect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode]=v;
        int heading=0,rot=0,initialRamp=0,dest=0;in>>heading>>rot>>initialRamp>>dest;
        std::array<int,24> route{};for(auto& n:route)in>>n;
        std::array<double,4> numeric{};for(auto& n:numeric){std::uint64_t bits=0;in>>bits;n=std::bit_cast<double>(bits);if(!std::isfinite(n))throw std::invalid_argument("Nonfinite Process input");}
        const auto [percentage,landSpeed,uphill,downhill]=numeric;
        bool end=false;for(int d:route){if(d==-1)end=true;else if((end&&cmd!='A'&&cmd!='R'&&cmd!='M'&&cmd!='N')||d<0||d>7)throw std::invalid_argument("Process route outside domain");}
        if(route.back()!=-1||heading<0||heading>65535||rot<1||rot>127||initialRamp<0||initialRamp>20||dest<0||dest>1)throw std::invalid_argument("Process state outside domain");
        if(!in||(cmd!='P'&&cmd!='G'&&cmd!='A'&&cmd!='R'&&cmd!='M'&&cmd!='N')||track<-1||track>=64||index<0||index>127||driving<0||driving>1||speed<0||speed>255||
           steps<1||steps>256||suppress!=0||marked<0||marked>255||markEffect<0||markEffect>1||level<-126||level>125||
           ramp<0||ramp>20||pattern<0||pattern>1||resident<0||resident>1||mode<0||mode>3||!std::isfinite(percentage))
            throw std::invalid_argument("Unsupported ground Process command");
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* n:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*n=std::bit_cast<double>(bits);
            if(!std::isfinite(*n))throw std::invalid_argument("Nonfinite Process plane");
        }
        if(!in)throw std::invalid_argument("Malformed Process planes");
        std::unique_ptr<GroundDriveGateVectors> gates;
        std::unique_ptr<GroundDriveAdmissionVectors> admissionOwner;
        std::unique_ptr<GroundDriveMovingResidentVectors> moving;
        GroundDriveAdmissionVectors* admissions=nullptr;
        if(cmd=='G')gates=std::make_unique<GroundDriveGateVectors>(in);
        if(cmd=='A')admissionOwner=std::make_unique<GroundDriveAdmissionVectors>(in);
        if(cmd=='R')admissionOwner=std::make_unique<GroundDriveAdmissionVectors>(in,true);
        admissions=admissionOwner.get();
        if(cmd=='M'||cmd=='N'){
            if(argc!=4)throw std::invalid_argument("Moving-resident vectors require owned direction data");
            moving=std::make_unique<GroundDriveMovingResidentVectors>(in);admissions=moving.get();
        }
        if(gates)for(const auto& r:gates->updates)if(r[0]>=steps)throw std::invalid_argument("Gate transition beyond Process sequence");
        if(admissions)for(const auto& r:admissions->gates.updates)if(r[0]>=steps)throw std::invalid_argument("Admission transition beyond Process sequence");
        if(!in)throw std::invalid_argument("Malformed gate Process input");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Process input");
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
        if(gates)gates->bind(slots,cells,fallback);
        if(moving){
            moving->bind(slots,cells,fallback,landSpeed);moving->processState=&state;
            moving->motion.data=data.get();moving->motion.squareRoot=[&](double n){return tableSqrt(render,n);};
            s.reached5a1=std::uint8_t(moving->initial5a1);s.body.timerStart=-1;
            state.retryStart=moving->retryStart;state.retryPadding=moving->retryPadding;state.retryRemaining=moving->retryRemaining;
        }else if(admissions)admissions->bind(slots,cells,fallback,landSpeed);
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        const auto store=[&](int off,int n){event('A',off,std::uint32_t(n));};
        GroundDriveProcessServices svc;auto& adv=svc.advance;
        adv.ground.mark=[&](int kind){event('M',kind,s.actor.position.x,s.actor.position.y,s.actor.position.z,unsigned(s.actor.bridge79),unsigned(s.actor.marked74));
            if(markEffect)s.actor.marked74=std::uint8_t(kind);};
        adv.ground.floor=[&](Coord p){event('F',p.x,p.y,p.z);return mapFloorHeight(floor,104,p,world);};
        adv.coordinateCell=[&](Coord p)->const void*{event('C',p.x,p.y,p.z);return &mapCoordinateCell(p,world,262144);};
        adv.wordCell=[&](std::int16_t xx,std::int16_t yy){event('W',xx,yy);(void)mapAttributeCell({xx,yy},words);};
        adv.unmarkOccupation=[&](Coord p){event('U',p.x,p.y,p.z);};adv.notify=[&](int kind){event('N',kind);};adv.postCell=[&]{event('P');};
        const auto record=[](const MapCellInput& c){return GroundDriveCell{c.position.x,c.position.y,c.level,c.slope,c.land,&c};};
        svc.liveCell=[&](const void* c){return record(*static_cast<const MapCellInput*>(c));};
        svc.cell=[&](Coord p){event('C',p.x,p.y,p.z);return record(mapCoordinateCell(p,world,262144));};
        svc.wordCell=[&](std::int16_t xx,std::int16_t yy){event('W',xx,yy);return record(mapAttributeCell({xx,yy},words));};
        svc.center=[&](const GroundDriveCell& c){event('T',c.x,c.y);return Coord{int(c.x)*256+128,int(c.y)*256+128,cellFloorHeight(floor,104,c.level,c.ramp,128,128)};};
        svc.reserve=[&](std::int16_t xx,std::int16_t yy){event('R',xx,yy);};svc.markNext=[&](std::int16_t xx,std::int16_t yy){event('K',xx,yy);};
        if(gates)svc.reserve={}; // The result-bearing entry must not use the old service.
        svc.admit=[&](const GroundDriveCell& c,int d,int level){event('D',c.x,c.y,d,level);};
        svc.noRoute=[&]{event('B');event('J');event('V',0,1);};
        if(moving)moving->waitServices.failedRoute=[&](int option){event('b',option);svc.noRoute();};svc.markOccupation=[&](Coord p){event('E',p.x,p.y,p.z);};
        svc.squareRoot=[&](double n){return tableSqrt(render,n);};
        if(cmd=='N')adv.driveStore=[&](int off,int n){event('d',off,std::uint32_t(n));};
        GroundDriveAdmissionServices admissionServices;
        if(admissions){
            svc.reserve={};svc.admit={};
            svc.markNext=[&](std::int16_t xx,std::int16_t yy){admissions->next(s.actor.position,xx,yy);};
            admissionServices.check=[&](const GroundDriveCell& c,int d,int level){return moving?moving->admit(c,d,level):admissions->admit(c,d,level);};
            admissionServices.driveStore=[&](int off,int n){event('a','L',off,std::uint32_t(n));};
        }
        for(int land=0;land<12;++land)svc.trackSpeed[std::size_t(land)]=float(landSpeed*(1.-land/16.));svc.uphill=uphill;svc.downhill=downhill;
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        for(int j=0;j<steps;++j){
            const int current=signed32(std::uint32_t(tick)+std::uint32_t(j));
            const auto rampStore=[&](int off,int n){event('L',off+4,std::uint32_t(n));};
            if(gates)gates->beforeTick(j,current);
            if(admissions)admissions->beforeTick(j,current);
            const auto movingProcess=cmd=='N'?processAdvanceAdmittedOrdinaryGroundDrive:processMovingResidentOrdinaryGroundDrive;
            const bool result=moving?movingProcess(state,*data,speed,current,7,svc,
                [&](std::int16_t xx,std::int16_t yy){return moving->check(xx,yy);},admissionServices,moving->retry,
                moving->wait,moving->waitServices,store,rampStore):
                cmd=='R'?processResidentOrdinaryGroundDrive(state,*data,speed,current,7,svc,
                [&](std::int16_t xx,std::int16_t yy){return admissions->check(xx,yy);},admissionServices,admissions->retry,store,rampStore):
                admissions?processAdmittedOrdinaryGroundDrive(state,*data,speed,current,7,svc,
                [&](std::int16_t xx,std::int16_t yy){return admissions->check(xx,yy);},admissionServices,store,rampStore):
                gates?processGatedOrdinaryGroundDrive(state,*data,speed,current,7,svc,
                [&](std::int16_t xx,std::int16_t yy){return gates->check(xx,yy);},store,rampStore):
                processOrdinaryGroundDrive(state,*data,speed,current,7,svc,store,rampStore);
            if(std::fegetround()!=modes[mode])throw std::runtime_error("Process leaked FP mode");
            event('S',result,s.actor.position.x,s.actor.position.y,s.actor.position.z,s.head.x,s.head.y,s.head.z,s.track,s.index,s.accumulator,s.driving,
                unsigned(s.actor.marked74),unsigned(s.reached5a0),unsigned(s.reached5a1),s.body.desired,s.body.start,s.body.timerStart,s.body.duration,s.body.rate,
                state.wasRotating,std::uint16_t(state.nextX)|(std::uint32_t(std::uint16_t(state.nextY))<<16),unsigned(state.crossing57b),
                std::bit_cast<std::uint64_t>(state.percentage),std::bit_cast<std::uint64_t>(state.instancePercentage),
                state.ramps.current,state.ramps.previous,state.ramps.start,state.ramps.padding,state.ramps.remaining,state.ramps.duration,
                state.retryStart,state.retryPadding,state.retryRemaining);
            for(int d:state.route)event(d);
            if(gates)gates->state();
            if(admissions){event('a','s',unsigned(state.preparation57a));if(moving)moving->state();else admissions->state();}
        }
        std::fesetround(old);event('H',digest(floor,fallback.position));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
