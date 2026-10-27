// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundMovementPlacement.hpp"
#include "assets/MapFloorHeight.hpp"
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
    if(!EVP_Digest(bytes.data(),bytes.size(),out,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Placement digest failed");
    std::ostringstream result;for(auto v:out)result<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return result.str();
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string_view(argv[1])=="--guards"){
        ActorGroundState actor{{1,2,3},1,0};bool refused=false;
        try{setFootLocation(actor,{4,5,6},{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||actor.position!=Coord{1,2,3})throw std::runtime_error("Location guard changed actor");
        refused=false;try{placeDriveResidualGround(actor,{4,5,6},0,{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||actor.marked74!=1)throw std::runtime_error("Placement guard changed marked byte");
        std::cout<<"Movement placement service guards: PASS\n";return 0;
    }
    if(argc!=1)throw std::invalid_argument("Placement vectors take stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<int,18> v{};in>>cmd;for(auto& n:v)in>>n;
        const auto [op,onMap,marked,bridge,bh,x,y,z,nx,ny,nz,resident,level,ramp,fl,fr,mutation,mode]=v;
        if(!in||cmd!='P'||op<0||op>2||onMap<0||onMap>255||marked<0||marked>255||bridge<0||bridge>255||resident<0||resident>1||
           level<-128||level>127||fl<-128||fl>127||ramp<0||ramp>20||fr<0||fr>20||mutation<0||mutation>15||mode<0||mode>3)
            throw std::invalid_argument("Unsupported movement placement command");
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* n:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*n=std::bit_cast<double>(bits);
            if(!std::isfinite(*n))throw std::invalid_argument("Nonfinite placement plane");
        }
        if(!in)throw std::invalid_argument("Malformed placement planes");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing placement input");
        ActorGroundState actor{{x,y,z},std::uint8_t(marked),std::uint8_t(bridge)};
        Coord next{nx,ny,nz};std::uint8_t onmap=std::uint8_t(onMap);
        MapCellInput cell,fallback;cell.level=std::int8_t(level);cell.slope=std::uint8_t(ramp);
        fallback.level=std::int8_t(fl);fallback.slope=std::uint8_t(fr);fallback.position={-7,5};
        std::vector<MapCellInput*> slots(262144);const auto index=(std::uint32_t(ny/256)<<9)+std::uint32_t(nx/256);
        if(resident&&index<slots.size())slots[index]=&cell;
        MapFloorHeightWorld world{slots,&fallback,{}};
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        const auto store=[&](int off,int n){event('A',off,std::uint32_t(n));};
        ActorGroundServices services;
        services.mark=[&](int kind){
            event('M',kind,actor.position.x,actor.position.y,actor.position.z,unsigned(actor.bridge79),unsigned(actor.marked74));
            if(mutation&1)actor.marked74=std::uint8_t(kind);
            if(!kind&&(mutation&2)){
                actor.position={add(actor.position.x,17),add(actor.position.y,-19),add(actor.position.z,23)};
                actor.bridge79^=255;onmap^=255;
            }
            if(!kind&&(mutation&4))next={add(next.x,256),add(next.y,-256),add(next.z,31)};
            if(kind&&(mutation&8))actor.position.z=add(actor.position.z,1);
        };
        services.floor=[&](Coord p){event('F',p.x,p.y,p.z);return mapFloorHeight(floor,104,p,world);};
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        if(op==0)setFootLocation(actor,next,services,store);
        else if(op==1)placeDriveResidualGround(actor,next,bh,services,store);
        else placeDriveCommittedSameCell(actor,next,onmap,bh,services,store);
        if(std::fegetround()!=modes[mode])throw std::runtime_error("Placement leaked FP mode");std::fesetround(old);
        event('S',actor.position.x,actor.position.y,actor.position.z,unsigned(actor.marked74),unsigned(actor.bridge79),unsigned(onmap),
            next.x,next.y,next.z,digest(floor,fallback.position));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
