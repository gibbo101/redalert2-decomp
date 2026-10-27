// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapGeometry.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void word(std::vector<std::uint8_t>& b,std::uint32_t n){for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
MapInputPosition position(std::uint32_t p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
MapCellInput initial(unsigned seed,unsigned i){MapCellInput c;const auto v=(i+1u)*2654435761u+seed*2246822519u;
    c.position=position(v);c.tile=std::bit_cast<std::int32_t>(v^0x12345678u);c.land=std::bit_cast<std::int32_t>(v);
    c.flags=v;c.tube=std::bit_cast<std::int16_t>(std::uint16_t(v));c.subTile=std::uint8_t(v>>8);
    c.ice=std::uint8_t(v>>16);c.level=std::bit_cast<std::int8_t>(std::uint8_t(v>>24));c.slope=std::uint8_t(v);return c;}
void state(std::vector<std::uint8_t>& b,const MapCellInput& c){for(auto n:std::array<std::uint32_t,9>{
    std::uint16_t(c.position.x)|(std::uint32_t(std::uint16_t(c.position.y))<<16),std::uint32_t(c.tile),
    std::uint16_t(c.tube),std::uint32_t(c.land),c.ice,c.subTile,std::uint8_t(c.level),c.slope,c.flags})word(b,n);}
std::string buffers(int w,int h,unsigned seed){const auto a=mapGeometryAllocation(w,h);
    if(a.capacity>66049)throw std::invalid_argument("Fixture buffer capacity outside profile");
    std::vector<std::uint8_t> data(std::size_t(a.capacity)*14,std::uint8_t(seed*37u+0x93));
    initializeMapGeometryBuffer(std::span(data).first(a.attributeBytes));return digest(data);}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        if(op=='V'){
            MapGeometryRect full,r;unsigned seed=0;in>>full.x>>full.y>>full.width>>full.height>>r.x>>r.y>>r.width>>r.height>>seed;
            const auto result=mapVisibleRect(full,r);const auto shape=mapPermissionShape(full,result);
            std::cout<<shape.originX<<' '<<shape.originY<<' '<<shape.width<<' '<<shape.height;
        }else if(op=='B'){
            int w=0,h=0,old=0;unsigned seed=0;in>>w>>h>>old>>seed;
            const auto a=mapGeometryAllocation(w,h);
            std::cout<<a.capacity;for(auto n:a.subzoneCapacities)std::cout<<' '<<n;std::cout<<' '<<buffers(w,h,seed);
        }else if(op=='G'){
            unsigned seed=0,invalid=0,level=0,rebuild=0;MapGeometryRect requested;
            in>>seed>>invalid>>requested.x>>requested.y>>requested.width>>requested.height>>level>>rebuild;
            if(level>255||rebuild>1)throw std::invalid_argument("Invalid initial map profile");
            const auto g=initialMapGeometry(requested);std::vector<MapCellInput> cells;
            for(std::size_t i=0;i<g.positions.size();++i)cells.push_back(initial(seed,unsigned(i)));
            auto fallback=initial(seed,99999);std::vector<MapCellInput*> table(262144);std::vector<std::uint8_t> states,events,geometry;
            auto store=[&](const MapCellInput* c,MapInputField f,std::uint32_t v){
                word(events,c==&fallback?0xffffffffu:unsigned(c-cells.data()));word(events,unsigned(f));word(events,v);};
            initializeMapGeometryCells(g,cells,table,fallback,position(invalid),std::uint8_t(level),store);
            for(const auto& c:cells){state(states,c);if(table[std::size_t(c.position.y)*512+std::size_t(c.position.x)]!=&c)throw std::runtime_error("Incorrect cell pointer");}
            state(states,fallback);
            for(auto n:{g.full.x,g.full.y,g.full.width,g.full.height,g.minimumX,g.minimumY,g.maximumX,g.maximumY,g.diamondMinimum,g.diamondMaximum})word(geometry,std::uint32_t(n));
            word(geometry,g.full.width>63||g.full.height>63?2:seed);
            std::cout<<cells.size()<<' '<<digest(states)<<' '<<digest(events)<<' '<<digest(geometry)<<' '<<(rebuild?buffers(g.full.width,g.full.height,seed):"-");
        }else throw std::invalid_argument("Unknown map geometry command");
        if(!in)throw std::invalid_argument("Incomplete map geometry command");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing map geometry command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
