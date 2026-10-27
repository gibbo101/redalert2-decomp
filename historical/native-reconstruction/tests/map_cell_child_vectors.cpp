// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellChildren.hpp"
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
void word(std::vector<std::uint8_t>& b,unsigned n){for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(8*i)));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char out[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),out,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(out[i]);return s.str();}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        MapCellInput cell,fallback;fallback.position=position(0x12345678);fallback.tile=777;fallback.slope=3;fallback.level=-7;
        std::vector<MapCellInput*> table(262144);MapAttributeLookup world{table,&fallback,{},{}};
        std::vector<std::uint8_t> events;const auto event=[&](unsigned tag,unsigned value){word(events,tag);word(events,value);};
        world.query=[&](auto p){event(1,packed(p));};world.fallbackStore=[&](auto p){event(2,packed(p));};
        const auto insert=[&](MapCellInput& c){const int i=int(c.position.y)*512+int(c.position.x);if(i>=0&&i<262144)table[std::size_t(i)]=&c;};
        unsigned p=0;in>>p;cell.position=position(p);
        if(op=='L'){
            int slope=0,image=0;in>>cell.tile>>slope>>image;(void)image;cell.slope=std::uint8_t(slope);
            MapLATSettings settings{};for(auto& b:settings)in>>b;
            std::array<MapInputPosition,8> directions{};for(auto& d:directions){unsigned v=0;in>>v;d=position(v);}
            std::array<MapCellInput,8> neighbors{};for(auto& c:neighbors)in>>c.tile;
            for(auto& c:neighbors){int n=0;in>>n;c.slope=std::uint8_t(n);}
            insert(cell);for(unsigned i=0;i<8;++i){neighbors[i].position=offset(cell.position,directions[i]);insert(neighbors[i]);}
            const bool changed=setupMapLAT(cell,settings,directions,world,1024,[&](int tile){event(3,unsigned(tile));});
            std::cout<<int(changed)<<' '<<std::uint32_t(cell.tile)<<' '<<packed(fallback.position)<<' '<<digest(events);
        }else if(op=='P'||op=='E'){
            int level=0,slope=0,value=0,present=0;MapPermissionShape shape;
            in>>level>>slope>>value>>shape.dimension0>>shape.originX>>shape.originY>>shape.width>>shape.height>>present;
            cell.level=std::bit_cast<std::int8_t>(std::uint8_t(level));cell.slope=std::uint8_t(slope);if(present)insert(cell);
            if(op=='E')std::cout<<int(mapCellPermitted(cell.position,std::uint8_t(value)!=0,shape,world));
            else{
                cell.land=value;std::array<float,11> speeds{};for(auto& speed:speeds){unsigned bits=0;in>>bits;speed=std::bit_cast<float>(std::uint32_t(bits));}
                const int pass=emptyCellPassability(cell,mapCellPermitted(cell.position,true,shape,world),speeds);event(4,unsigned(pass));std::cout<<pass;
            }
            std::cout<<' '<<packed(fallback.position)<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown map child command");
        if(!in)throw std::invalid_argument("Incomplete map child command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing map child command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
