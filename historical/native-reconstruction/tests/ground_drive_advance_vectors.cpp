// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveAdvance.hpp"
#include "assets/MovementData.hpp"
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
namespace {
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
        try{advanceOrdinaryGroundDrive(s,{},15,1.,0,false,{});}catch(const std::invalid_argument&){refused=true;}
        if(!refused||s.actor.position!=Coord{1,2,3}||s.accumulator!=7)throw std::runtime_error("Advance missing-service guard changed state");
        std::cout<<"Ground Advance service guard: PASS\n";return 0;
    }
    const bool observeDrive=argc==3&&std::string_view(argv[2])=="--drive-stores";
    if(argc!=2&&!observeDrive)throw std::invalid_argument("Advance vectors require an owned executable and optional --drive-stores");
    const auto data=readDriveData(readFile(argv[1]));
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;std::array<int,21> v{};in>>cmd;for(auto& n:v)in>>n;
        const auto [track,index,acc,driving,speed,tick,steps,suppress,marked,markEffect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode]=v;
        std::uint64_t percentBits=0;in>>percentBits;const double percentage=std::bit_cast<double>(percentBits);
        if(!in||cmd!='A'||track<-1||track>=64||index<0||index>127||driving<0||driving>1||speed<0||speed>255||
           steps<1||steps>64||suppress<0||suppress>1||marked<0||marked>255||markEffect<0||markEffect>1||level<-126||level>125||
           ramp<0||ramp>20||pattern<0||pattern>1||resident<0||resident>1||mode<0||mode>3||!std::isfinite(percentage))
            throw std::invalid_argument("Unsupported ground Advance command");
        MapFloorHeightState floor;
        for(auto& p:floor.planes)for(auto* n:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){
            std::uint64_t bits=0;in>>bits;*n=std::bit_cast<double>(bits);
            if(!std::isfinite(*n))throw std::invalid_argument("Nonfinite Advance plane");
        }
        if(!in)throw std::invalid_argument("Malformed Advance planes");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Advance input");
        GroundDriveAdvanceState s;s.actor={{x,y,z},std::uint8_t(marked),0};s.head={hx,hy,hz};s.track=track;s.index=index;
        s.accumulator=acc;s.driving=driving!=0;s.reached5a0=7;s.reached5a1=9;s.body.rate=1280;
        std::array<MapCellInput,81> cells;MapCellInput fallback;fallback.position={-7,5};fallback.level=std::int8_t(level);fallback.slope=std::uint8_t(ramp);
        std::vector<MapCellInput*> slots(262144);
        for(int dy=-4;dy<=4;++dy)for(int dx=-4;dx<=4;++dx){
            const int cx=hx/256+dx,cy=hy/256+dy;const auto slot=std::int64_t(cy)*512+cx;
            if(resident&&slot>=0&&slot<262144){
                auto& c=cells[std::size_t((dy+4)*9+dx+4)];c.position={std::bit_cast<std::int16_t>(std::uint16_t(cx)),std::bit_cast<std::int16_t>(std::uint16_t(cy))};
                c.level=std::int8_t(level+int(pattern&&dx>=0));c.slope=std::uint8_t((ramp+(pattern?std::abs(dx)+std::abs(dy):0))%21);slots[std::size_t(slot)]=&c;
            }
        }
        MapFloorHeightWorld world{slots,&fallback,{}};MapAttributeLookup words{slots,&fallback,{},{}};
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        const auto store=[&](int off,int n){event('A',off,std::uint32_t(n));};
        GroundDriveAdvanceServices svc;
        if(observeDrive)svc.driveStore=[&](int off,int value){event('L',off,std::uint32_t(value));};
        svc.ground.mark=[&](int kind){event('M',kind,s.actor.position.x,s.actor.position.y,s.actor.position.z,unsigned(s.actor.bridge79),unsigned(s.actor.marked74));
            if(markEffect)s.actor.marked74=std::uint8_t(kind);};
        svc.ground.floor=[&](Coord p){event('F',p.x,p.y,p.z);return mapFloorHeight(floor,104,p,world);};
        svc.coordinateCell=[&](Coord p)->const void*{event('C',p.x,p.y,p.z);return &mapCoordinateCell(p,world,262144);};
        svc.wordCell=[&](std::int16_t xx,std::int16_t yy){event('W',xx,yy);(void)mapAttributeCell({xx,yy},words);};
        svc.unmarkOccupation=[&](Coord p){event('U',p.x,p.y,p.z);};svc.notify=[&](int kind){event('N',kind);};svc.postCell=[&]{event('P');};
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        for(int j=0;j<steps;++j){
            const int current=signed32(std::uint32_t(tick)+std::uint32_t(j));advanceOrdinaryGroundDrive(s,*data,speed,percentage,current,suppress!=0,svc,store);
            if(std::fegetround()!=modes[mode])throw std::runtime_error("Advance leaked FP mode");
            event('S',s.actor.position.x,s.actor.position.y,s.actor.position.z,s.head.x,s.head.y,s.head.z,s.track,s.index,s.accumulator,s.driving,
                unsigned(s.actor.marked74),unsigned(s.actor.bridge79),unsigned(s.reached5a0),unsigned(s.reached5a1),s.body.desired,s.body.start,s.body.timerStart,s.body.duration);
        }
        std::fesetround(old);event('H',digest(floor,fallback.position));std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
