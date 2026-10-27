// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayPlacement.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& values){
    std::vector<unsigned char> bytes;for(auto n:values)for(unsigned i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(n>>(i*8)));
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned length=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),hash,&length,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<length;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(hash[i]);return out.str();
}
MapInputPosition point(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0,slope=0,wallByte=0,limbo=0,onMap=0,redraw=0,active=0,p=0,effect=0;
        int index=0,mode=0,x=0,y=0,flag=0,owner=0,loading=0;
        in>>op>>seed>>index>>slope>>wallByte>>limbo>>onMap>>redraw>>active>>mode>>x>>y>>p>>flag>>owner>>loading>>effect;
        LoadedWallPlacementServices wall;std::array<unsigned,8> aliases{};
        for(auto& direction:wall.directions){unsigned d=0;in>>d;direction=point(d);}for(auto& id:aliases)in>>id;
        if(!in||op!='W'||!wallByte||wallByte>255||slope>255||limbo>255||onMap>255||redraw>255||active>255||!loading||effect>3)
            throw std::invalid_argument("Wall fixture domain");
        for(auto id:aliases)if(id>8)throw std::invalid_argument("Wall fixture alias");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing wall fixture input");
        OverlayTypeInputs type;type.index=index;type.wall=std::uint8_t(wallByte);
        TransientMapOverlay actor;actor.type=&type;actor.position={x,y,std::bit_cast<int>(seed)};
        actor.limbo=std::uint8_t(limbo);actor.onMap=std::uint8_t(onMap);actor.redraw=std::uint8_t(redraw);actor.active=std::uint8_t(active);
        std::array<OverlayPlacementCell,9> cells;
        for(unsigned i=0;i<cells.size();++i){auto& c=cells[i];c.overlay=std::bit_cast<int>(seed^(i*0x1234567u));c.data=std::uint8_t(seed+i);
            c.slope=std::uint8_t(i?slope^i:slope);c.position=point(p);c.owner=std::bit_cast<int>(seed^(i*0x7654321u));c.neighbors=std::uint8_t(seed+i*31);}
        Words events;unsigned current=0,lookups=0;
        const auto event=[&](std::initializer_list<unsigned> values){events.insert(events.end(),values.begin(),values.end());};
        auto& s=wall.object;
        s.noAttachedAnimation=[&]{event({2});};s.redraw=[&]{event({3});};
        s.cell=[&](MapInputPosition q)->OverlayPlacementCell&{current=lookups?aliases.at(lookups-1):0;++lookups;event({4,packed(q),current});return cells[current];};
        s.store=[&](unsigned role,unsigned offset,unsigned size,unsigned value){if(role)event({21,current,offset,size,value});else event({20,offset,size,value});};
        s.recalculate=[&](auto& c,int level){current=0;if(&c!=&cells[0]||level!=-1)throw std::runtime_error("Wall recalculation arguments");event({6,unsigned(level)});};
        s.retire=[&](auto& a){event({7,20,0x7d,1,0});a.active=0;};
        wall.loading=loading;wall.placementFlag=flag;wall.currentOwner=owner;wall.permissionQuery=[&]{event({5,1,0,0});};
        wall.updateWall=[&](auto& c,std::uint8_t argument){
            if(&c!=&cells[0]||argument!=1)throw std::runtime_error("Wall-update arguments");event({8,argument});current=0;
            if(effect&1){c.data=std::uint8_t(seed>>8);s.store(1,0x11e,1,c.data);}
            if(effect&2){c.overlay=-1;s.store(1,0x44,4,unsigned(c.overlay));c.neighbors=255;s.store(1,0x122,1,c.neighbors);}
        };
        const bool result=markLoadedMapWall(actor,mode,wall);
        Words output{unsigned(result),actor.onMap,actor.redraw,actor.limbo,actor.active,unsigned(actor.position.x),unsigned(actor.position.y),unsigned(actor.position.z)};
        for(const auto& c:cells)output.insert(output.end(),{unsigned(c.overlay),c.data,c.slope,packed(c.position),unsigned(c.owner),c.neighbors});
        output.push_back(lookups);std::cout<<digest(output)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
