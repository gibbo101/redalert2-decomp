// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallOwner.hpp"
#include "render/Lighting.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
std::string digest(const std::vector<std::uint8_t>& bytes) {
    unsigned char out[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),out,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<size;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(out[i]);return s.str();
}
struct Candidate {WallOwnerBuilding flags;int owner=0,foundation=0,width=0,height=0,distance=0;Coord point;};
}
int main(int argc,char** argv){try{
    if(argc!=2)throw std::invalid_argument("Supply private render-data.bin");
    const auto render=readRenderData(readFile(argv[1]));
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;int overlay=0,wall=0,owner=0;unsigned count=0,packed=0;int height=0;
        in>>op>>overlay>>wall>>owner;
        if(op=='W')in>>packed>>height;
        else if(op!='S')throw std::invalid_argument("Unknown wall owner command");
        in>>count;if(count>1024)throw std::invalid_argument("Wall owner registry too large");
        std::vector<Candidate> candidates(count);std::vector<WallOwnerBuilding> flags;
        for(auto& c:candidates) {
            int active=0,onMap=0,eligible=0;in>>active>>onMap>>eligible>>c.owner;
            if(op=='W')in>>c.foundation>>c.width>>c.height>>c.point.x>>c.point.y>>c.point.z;
            else in>>c.distance;
            for(int value:{active,onMap,eligible})if(value<0||value>255)throw std::invalid_argument("Invalid wall owner byte");
            c.flags={std::uint8_t(active),std::uint8_t(onMap),std::uint8_t(eligible)};flags.push_back(c.flags);
        }
        if(!in || wall<0 || wall>255)throw std::invalid_argument("Incomplete wall owner command");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing wall owner command");
        std::vector<std::uint8_t> events;
        const auto event=[&](std::initializer_list<std::uint32_t> values){for(auto v:values)for(unsigned k=0;k<4;++k)events.push_back(std::uint8_t(v>>(k*8)));};
        WallOwnerServices s;
        s.distance=[&](std::size_t id) {
            const auto& c=candidates[id];event({1,unsigned(id)});
            int result=c.distance;
            if(op=='W') {
                const MapInputPosition point{std::bit_cast<std::int16_t>(std::uint16_t(packed)),std::bit_cast<std::int16_t>(std::uint16_t(packed>>16))};
                event({2,packed});const auto target=wallOwnerCellCoordinates(point,height);
                event({3,std::uint32_t(target.x),std::uint32_t(target.y)});
                event({4,unsigned(id)});event({5,unsigned(c.foundation)});event({6,unsigned(c.foundation)});
                const auto source=wallOwnerBuildingCoordinates(c.point,c.width,c.height);
                result=wallOwnerCellDistance(source,target,[&](double n){return tableSqrt(render,n);});
            }
            event({10,std::uint32_t(result)});if(op=='W')event({7,11});return result;
        };
        s.owner=[&](std::size_t id){event({8,unsigned(id)});return candidates[id].owner;};
        s.store=[&](int value){event({9,std::uint32_t(value)});};
        assignMapWallOwner(overlay,std::uint8_t(wall),owner,flags,s);
        std::cout<<std::uint32_t(owner)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
