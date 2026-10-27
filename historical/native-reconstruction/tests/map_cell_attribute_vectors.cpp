// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellAttributes.hpp"
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
MapInputPosition position(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        if(op=='I'){
            unsigned p=0;int a=0,b=0,n=0;in>>p>>a>>b>>n;std::cout<<mapAttributeBufferIndex(position(p),a,b,n);
        }else if(op=='A'){
            MapCellAttributes c;MapAttributeServices s;unsigned p=0,flags=0,sub=0,slope=0,extra=0,overlayData=0,ice=0,cliff=0;
            int tile=0,land=0,tube=0,level=0,overrideLevel=0,fallback=0,latTile=0,pass=0;
            in>>p>>tile>>land>>tube>>sub>>level>>slope>>flags>>extra>>overlayData>>ice>>overrideLevel>>fallback>>cliff>>s.tubeCount>>latTile>>pass;
            c.input.position=position(p);c.input.tile=tile;c.input.land=land;c.input.tube=std::bit_cast<std::int16_t>(std::uint16_t(tube));
            c.input.subTile=std::uint8_t(sub);c.input.level=std::bit_cast<std::int8_t>(std::uint8_t(level));c.input.slope=std::uint8_t(slope);
            c.input.flags=flags;c.input.ice=std::uint8_t(ice);c.extraHeight=std::uint8_t(extra);c.overlayData=std::uint8_t(overlayData);c.passability=std::bit_cast<std::int32_t>(std::uint32_t(pass)^0x13572468u);
            s.fallback=fallback!=0;s.cliffMode=std::uint8_t(cliff);
            int present=0,valid=0,ramp=0,tmpLand=0,height=0,y=0,ey=0,hasExtra=0;
            in>>present>>valid>>ramp>>tmpLand>>height>>y>>ey>>hasExtra;
            MapTileImageInput image;image.columns=1;image.rows=1;image.width=60;image.height=height;
            image.subTiles={valid?std::optional{MapSubTileInput{std::uint8_t(tmpLand),std::uint8_t(ramp),hasExtra!=0,y,ey}}:std::nullopt};
            std::array<MapTileAttributes,3> tiles{};for(auto& t:tiles)t.image=present?&image:nullptr;s.tiles=tiles;
            std::array<int,16> landMap{};for(auto& n:landMap)in>>n;s.landMap=landMap;
            std::array<int,6> neighbors{};for(auto& n:neighbors)in>>n;
            std::array<std::uint8_t,4>b4{0xa5,0xa5,0xa5,0xa5};std::array<std::uint8_t,10>b10{};b10.fill(0xa5);
            std::vector<std::uint8_t> events;
            s.store=[&](MapAttributeField f,unsigned v){word(events,unsigned(f));word(events,v);};
            unsigned query=0;
            s.neighborLevel=[&](MapInputPosition q){if(query>=6)throw std::runtime_error("Unexpected neighbor query");word(events,100);word(events,packed(q));return std::bit_cast<std::int8_t>(std::uint8_t(neighbors[query++]));};
            const auto service=[&](unsigned tag,const MapCellAttributes& a){word(events,tag);for(auto v:{a.input.tile,a.input.land,int(a.input.slope),int(std::uint8_t(a.input.level)),int(a.extraHeight),a.passability})word(events,unsigned(v));};
            s.setupLAT=[&](const MapCellAttributes& a){service(101,a);return latTile;};
            s.updatePassability=[&](const MapCellAttributes& a){service(102,a);return pass;};
            recalculateMapCellAttributes(c,overrideLevel,b4,b10,s);
            std::vector<std::uint8_t> state;for(auto n:{std::uint32_t(c.input.tile),std::uint32_t(c.input.land),std::uint32_t(std::uint16_t(c.input.tube)),
                unsigned(c.input.subTile),unsigned(std::uint8_t(c.input.level)),unsigned(c.input.slope),c.input.flags,unsigned(c.extraHeight),
                unsigned(c.overlayData),unsigned(c.input.ice),unsigned(c.passability)})word(state,n);
            state.insert(state.end(),b4.begin(),b4.end());state.insert(state.end(),b10.begin(),b10.end());
            std::cout<<digest(state)<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown Cell attribute command");
        if(!in)throw std::invalid_argument("Incomplete Cell attribute command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Cell attribute command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
