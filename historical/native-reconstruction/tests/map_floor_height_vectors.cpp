// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapFloorHeight.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
using namespace ra2;
namespace {
std::string stateDigest(const MapFloorHeightState& s,MapInputPosition p) {
    std::vector<unsigned char> bytes{s.flags};
    const auto word=[&](std::uint64_t n,int size){for(int i=0;i<size;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
    const auto scalar=[&](double n){word(std::bit_cast<std::uint64_t>(n),8);};
    scalar(s.height);scalar(s.scale);
    for(const auto& v:s.planes)for(double n:{v.x,v.y,v.offset,v.limit,v.add})scalar(n);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char digest[32];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),digest,&size,EVP_sha256(),nullptr)||size!=32)throw std::runtime_error("Height digest failed");
    std::ostringstream out;for(auto n:digest)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(n);return out.str();
}
void guards() {
    const int old=std::fegetround();std::fesetround(FE_UPWARD);
    MapFloorHeightState s;s.planes[0].x=1;
    if(cellFloorHeight(s,104,-1,0,0,0)!=-103||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Signed level rounding/FP restoration differs");
    if(cellFloorHeight(s,208,1,1,255,0)!=311||s.height!=104||s.scale!=104.0/256)throw std::runtime_error("Warm height cache was invalidated");
    MapCellInput cell,fallback;cell.level=1;fallback.level=2;fallback.position={7,8};
    std::vector<MapCellInput*> table(262144);table[511]=&cell;
    MapFloorHeightWorld world{table,&fallback,{}};
    if(mapFloorHeight(s,104,{-256,256,0},world)!=104||fallback.position!=MapInputPosition{7,8})throw std::runtime_error("Combined signed map alias was rejected");
    bool observed=false;world.fallbackStore=[&](auto p){observed=p==fallback.position;};
    mapFloorHeight(s,104,{-1,-257,0},world);
    if(!observed||fallback.position!=MapInputPosition{0,-1})throw std::runtime_error("Fallback word position/store differs");
    auto invalid=s;invalid.flags=0;bool refused=false;
    try{cellFloorHeight(invalid,104,0,21,0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused||invalid.flags||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Unsupported ramp changed state");
    invalid=s;invalid.scale=std::numeric_limits<double>::max();refused=false;
    try{cellFloorHeight(invalid,104,0,1,255,0);}catch(const std::invalid_argument&){refused=true;}
    // Upper clamping can make a finite result even after a large intermediate.
    if(std::fegetround()!=FE_UPWARD)throw std::runtime_error("Height exception changed rounding");
    std::fesetround(old);std::cout<<"Floor height negative rounding/warm state/map alias/fallback/domain guards: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Height vectors take commands on stdin");
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;unsigned flags=0,count=0;std::uint64_t bits=0;MapFloorHeightState state;
        in>>op>>flags>>bits;state.flags=std::uint8_t(flags);state.height=std::bit_cast<double>(bits);
        in>>bits;state.scale=std::bit_cast<double>(bits);
        for(auto& plane:state.planes)for(auto* v:{&plane.x,&plane.y,&plane.offset,&plane.limit,&plane.add}){in>>bits;*v=std::bit_cast<double>(bits);}
        in>>count;if(flags>255||count<1||count>64||std::string("HCMR").find(op)==std::string::npos)throw std::invalid_argument("Invalid height fixture header");
        MapCellInput cell,fallback;fallback.position={-7,5};std::vector<MapCellInput*> table(262144);int previous=-1;
        MapFloorHeightWorld world{table,&fallback,{}};
        for(unsigned i=0;i<count;++i) {
            int current=0,level=0,ramp=0,x=0,y=0,z=0,bridge=0,bridgeHeight=0,slot=0,present=0,flevel=0,framp=0;
            in>>current>>level>>ramp>>x>>y>>z>>bridge>>bridgeHeight>>slot>>present>>flevel>>framp;
            if(!in||level<-128||level>127||ramp<0||ramp>20||flevel<-128||flevel>127||framp<0||framp>20||slot<0||slot>=262144||present<0||present>1||bridge<0||bridge>255||(op=='C'&&(x<-32768||x>32767||y<-32768||y>32767)))throw std::invalid_argument("Invalid height row");
            cell.level=std::int8_t(level);cell.slope=std::uint8_t(ramp);cell.position={std::int16_t(x),std::int16_t(y)};
            fallback.level=std::int8_t(flevel);fallback.slope=std::uint8_t(framp);
            if(previous>=0)table[std::size_t(previous)]=nullptr;table[std::size_t(slot)]=present?&cell:nullptr;previous=slot;
            int value=0;const Coord point{x,y,z};
            if(op=='H')value=cellFloorHeight(state,current,cell.level,cell.slope,x,y);
            else if(op=='C'){const auto out=mapCellCenterHeight(state,current,cell);std::cout<<std::uint32_t(out.x)<<' '<<std::uint32_t(out.y)<<' ';value=out.z;}
            else if(op=='M')value=mapFloorHeight(state,current,point,world);
            else value=relativeMapHeight(state,current,point,std::uint8_t(bridge),bridgeHeight,world);
            std::cout<<std::uint32_t(value)<<' '<<stateDigest(state,fallback.position)<<' ';
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing height fixture");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
