// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapOverlay.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
MapInputPosition position(unsigned n){return {std::bit_cast<std::int16_t>(std::uint16_t(n)),std::bit_cast<std::int16_t>(std::uint16_t(n>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
MapInputPosition offset(MapInputPosition p,MapInputPosition d){return position(unsigned(std::uint16_t(int(p.x)+d.x))|(unsigned(std::uint16_t(int(p.y)+d.y))<<16));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char out[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),out,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(out[i]);return s.str();}
std::vector<MapResourceType> resources(std::istream& in){
    unsigned n=0;in>>n;if(n>8)throw std::invalid_argument("Resource fixture too large");
    std::vector<MapResourceType> out(n);for(auto& r:out)in>>r.index>>r.imageIndex>>r.numImages>>r.numSlopes>>r.numFrames>>r.value;return out;
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        std::vector<std::uint8_t> events;
        const auto event=[&](unsigned tag,unsigned n){for(auto v:{tag,n})for(int i=0;i<4;++i)events.push_back(std::uint8_t(v>>(i*8)));};
        MapOverlayType type;std::vector<MapResourceType> types;
        const auto classify=[&](int overlay){event(1,unsigned(overlay));return classifyMapOverlay(overlay,&type,types,[&](int n){event(2,unsigned(n));});};
        if(op=='C'){
            int overlay=0,flag=0;in>>overlay>>flag;type.tiberium=std::uint8_t(flag);types=resources(in);
            std::cout<<std::uint32_t(classify(overlay))<<' '<<digest(events);
        }else if(op=='P'){
            MapCellInput cell,fallback;fallback.position=position(0x12345678);fallback.level=-7;fallback.slope=3;
            unsigned p=0;int level=0,slope=0,overlay=0;in>>p>>level>>slope>>cell.land>>overlay>>type.land;
            for(auto* flag:{&type.flag1FD,&type.wall,&type.tiberium,&type.noUseTileLandType,&type.rubble,&type.rock}){int n=0;in>>n;*flag=std::uint8_t(n);}
            MapPermissionShape shape;int present=0;in>>shape.dimension0>>shape.originX>>shape.originY>>shape.width>>shape.height>>present;
            std::array<float,12> speeds{};for(auto& speed:speeds){unsigned bits=0;in>>bits;speed=std::bit_cast<float>(std::uint32_t(bits));}
            cell.position=position(p);cell.level=std::bit_cast<std::int8_t>(std::uint8_t(level));cell.slope=std::uint8_t(slope);
            std::vector<MapCellInput*> table(262144);const int index=int(cell.position.y)*512+int(cell.position.x);
            if(present&&index>=0&&index<262144)table[std::size_t(index)]=&cell;
            MapAttributeLookup world{table,&fallback,[&](auto q){event(3,packed(q));},[&](auto q){event(4,packed(q));}};
            const int result=overlayCellPassability(cell,mapCellPermitted(cell.position,true,shape,world),overlay==-1?nullptr:&type,speeds);
            event(6,unsigned(result));std::cout<<result<<' '<<packed(fallback.position)<<' '<<digest(events);
        }else if(op=='R'){
            unsigned p=0;int overlay=0,flag=0,initial=0;in>>p>>overlay>>flag>>initial;type.tiberium=std::uint8_t(flag);types=resources(in);
            MapResourceServices s;s.types=types;s.classify=classify;
            for(auto& d:s.directions){unsigned n=0;in>>n;d=position(n);}
            std::array<int,8> overlays{};for(auto& n:overlays)in>>n;
            std::array<std::uint8_t,9> frames{};for(auto& f:frames){unsigned n=0;in>>n;f=std::uint8_t(n);}s.frameTable=frames;
            std::vector<int> table(262144,-1);const auto origin=position(p);
            for(unsigned i=0;i<8;++i){const auto q=offset(origin,s.directions[i]);const int index=int(q.y)*512+int(q.x);if(index>=0&&index<262144)table[std::size_t(index)]=int(i);}
            unsigned fallback=0x12345678;
            s.neighborOverlay=[&](auto q){event(3,packed(q));const int index=int(q.y)*512+int(q.x);if(index>=0&&index<262144&&table[std::size_t(index)]!=-1)return overlays[std::size_t(table[std::size_t(index)])];fallback=packed(q);event(4,fallback);return -1;};
            s.store=[&](auto data){event(5,data);};auto data=std::uint8_t(initial);
            const int result=updateMapResource(origin,overlay,data,s);
            std::cout<<std::uint32_t(result)<<' '<<unsigned(data)<<' '<<fallback<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown overlay command");
        if(!in)throw std::invalid_argument("Incomplete overlay command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing overlay command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
