// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ActorGroundState.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    std::vector<unsigned char> bytes{s.flags};
    auto word=[&](std::uint64_t n,int size){for(int i=0;i<size;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
    auto scalar=[&](double n){word(std::bit_cast<std::uint64_t>(n),8);};
    scalar(s.height);scalar(s.scale);
    for(const auto& v:s.planes)for(double n:{v.x,v.y,v.offset,v.limit,v.add})scalar(n);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char out[32];unsigned n=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),out,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Ground digest failed");
    std::ostringstream result;for(auto v:out)result<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return result.str();
}
void guards(){
    ActorGroundState a{{0,0,0},1,0};bool refused=false;
    try{setActorRelativeHeight(a,0,0,{});}catch(const std::invalid_argument&){refused=true;}
    if(!refused||a.position.z)throw std::runtime_error("Missing height service was accepted");
    DriveRampState r;refused=false;
    try{observeDriveRamp(r,{},0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||r.current||r.start!=-1)throw std::runtime_error("Missing Cell service was accepted");
    std::cout<<"Ground service guards: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Ground vectors take stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<int,23> v{};in>>cmd;for(auto& n:v)in>>n;
        const auto [op,tick,height,bridge,marked,bridgeHeight,x,y,z,resident,level,ramp,flevel,framp,
            current,previous,start,padding,remaining,duration,temporary,mutation,mode]=v;
        if(!in||cmd!='G'||op<0||op>5||bridge<0||bridge>255||marked<0||marked>255||resident<0||resident>1||
           level<-128||level>127||flevel<-128||flevel>127||ramp<0||ramp>255||framp<0||framp>255||
           ((op==0||op>=4)&&(ramp>20||framp>20))||mutation<0||mutation>7||mode<0||mode>3)
            throw std::invalid_argument("Unsupported ground state command");
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* n:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*n=std::bit_cast<double>(bits);
            if(!std::isfinite(*n))throw std::invalid_argument("Nonfinite ground plane template");
        }
        if(!in)throw std::invalid_argument("Malformed ground plane template");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing ground plane template");
        ActorGroundState actor{{x,y,z},std::uint8_t(marked),std::uint8_t(bridge)};
        DriveRampState state{current,previous,start,padding,remaining,duration};
        MapCellInput cell,fallback;cell.level=std::int8_t(level);cell.slope=std::uint8_t(ramp);
        fallback.level=std::int8_t(flevel);fallback.slope=std::uint8_t(framp);fallback.position={-7,5};
        std::vector<MapCellInput*> slots(262144);const auto index=(std::uint32_t(y/256)<<9)+std::uint32_t(x/256);
        if(resident&&index<slots.size())slots[index]=&cell;
        MapFloorHeightWorld world{slots,&fallback,{}};
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        const auto aw=[&](int offset,int value){event('A',offset,std::uint32_t(value));};
        const auto dw=[&](int offset,int value){event('D',offset,std::uint32_t(value));};
        auto move=[&]{actor.position={add(actor.position.x,256),add(actor.position.y,-256),add(actor.position.z,17)};};
        ActorGroundServices services;
        services.mark=[&](int kind){
            event('M',kind,actor.position.x,actor.position.y,actor.position.z,unsigned(actor.bridge79),unsigned(actor.marked74));
            if(!kind&&(mutation&1)){move();actor.bridge79^=255;actor.marked74=0;}
            if(kind&&(mutation&2))actor.position.z=add(actor.position.z,1);
        };
        services.floor=[&](Coord p){event('F',p.x,p.y,p.z);return mapFloorHeight(floor,104,p,world);};
        const auto getRamp=[&]{
            // Complete 0x5D51E0 intentionally performs two map lookups, taking a
            // fresh coordinate copy each time; the first result is discarded.
            event('C',actor.position.x,actor.position.y,actor.position.z);
            (void)mapCoordinateCell(actor.position,world,262144);
            if(mutation&4)move();
            event('C',actor.position.x,actor.position.y,actor.position.z);
            const auto& c=mapCoordinateCell(actor.position,world,262144);event('R',unsigned(c.slope));return c.slope;
        };
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
        std::fesetround(modes[mode]);
        if(op==0||op>=4)setActorRelativeHeight(actor,height,bridgeHeight,services,aw);
        if(op==1)initializeDriveRamp(state,height,tick,temporary,dw);
        else if(op==2||op==4)unlimboDriveRamp(state,getRamp,tick,temporary,dw);
        else if(op==3||op==5)observeDriveRamp(state,getRamp,tick,temporary,dw);
        if(std::fegetround()!=modes[mode])throw std::runtime_error("Ground FP mode leaked");std::fesetround(old);
        event('S',actor.position.x,actor.position.y,actor.position.z,unsigned(actor.bridge79),unsigned(actor.marked74),
            state.current,state.previous,state.start,state.padding,state.remaining,state.duration,digest(floor,fallback.position));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
