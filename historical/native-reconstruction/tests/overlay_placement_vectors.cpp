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
std::string digest(const Words& words){
    std::vector<unsigned char> bytes;for(auto v:words)for(int i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(v>>(8*i)));
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),hash,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(hash[i]);return out.str();
}
MapInputPosition point(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
int signedValue(unsigned v){return std::bit_cast<std::int32_t>(v);}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0,crate=0,slope=0,enabled=0,limbo=0,onMap=0,redraw=0,active=0,p=0,invalid=0,capacity=0,count=0,owns=0,growResult=0,resource=0;
        int index=0,land=0,mode=0,flag=0,incoming=0,growth=0;
        in>>op>>seed>>index>>land>>crate>>slope>>enabled>>limbo>>onMap>>redraw>>active>>mode>>p>>invalid>>flag>>incoming>>capacity>>count>>growth>>owns>>growResult>>resource;
        if(!in||capacity>32||count>capacity||growth>32||crate>255||slope>255||enabled>255||limbo>255||onMap>255||redraw>255||active>255||owns>255||growResult>255||resource>255)throw std::invalid_argument("Overlay placement fixture domain");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing placement input");
        const auto pos=point(p);const Coord center{int(pos.x)*256+128,int(pos.y)*256+128,0};
        OverlayTypeInputs type;type.index=index;type.land=land;type.crate=std::uint8_t(crate);
        TransientMapOverlay actor{&type,op=='M'?center:Coord{signedValue(seed),signedValue(seed^0x12345678),signedValue(seed+17)},std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo),std::uint8_t(active)};
        actor.identityToken=seed^0xaaaaaaaa;
        OverlayPlacementCell cell;cell.overlay=signedValue(seed^0x76543210);cell.data=std::uint8_t(seed);cell.slope=std::uint8_t(slope);
        OverlayTransientRegistry registry;registry.count=int(count);registry.growth=growth;registry.owns=std::uint8_t(owns);
        for(unsigned i=0;i<capacity;++i)registry.slots.push_back(i+2);
        Words events;
        unsigned identityCounter=seed^0xfedcba98;
        const auto event=[&](std::initializer_list<unsigned> words){events.insert(events.end(),words.begin(),words.end());};
        OverlayPlacementServices s;
        if(seed)s.identityCounter=&identityCounter;
        s.base=[&](auto&){event({0});};
        s.grow=[&](int n){event({1,unsigned(n),growResult});if(!growResult)return false;registry.slots.resize(std::size_t(n));registry.owns=1;return true;};
        s.noAttachedAnimation=[&]{event({2});};s.redraw=[&]{event({3});};
        s.cell=[&](auto p)->OverlayPlacementCell&{event({4,packed(p)});return cell;};
        s.resource=[&](auto& c){event({5});c.data=std::uint8_t(resource);event({21,0x11e,1,c.data});};
        s.recalculate=[&](auto&,int level){event({6,unsigned(level)});};
        s.retire=[&](auto& a){event({7});a.active=0;event({20,0x7d,1,0});};
        s.store=[&](unsigned role,unsigned off,unsigned n,unsigned value){event({20+role,off,n,value});};
        unsigned result=0;
        if(op=='C'){constructLoadedMapOverlay(actor,type,pos,point(invalid),incoming,flag,1,registry,std::uint8_t(enabled),s);result=1;}
        else if(op=='M')result=markLoadedMapOverlay(actor,mode,s);
        else if(op=='U')result=unlimboLoadedMapOverlay(actor,center,std::uint8_t(enabled),s);
        else throw std::invalid_argument("Unknown overlay placement input");
        Words state{1,actor.identityToken,identityCounter,unsigned(actor.position.x),unsigned(actor.position.y),unsigned(actor.position.z),actor.onMap,actor.redraw,actor.limbo,actor.active,unsigned(cell.overlay),cell.data,cell.slope,unsigned(flag),unsigned(registry.count),unsigned(registry.slots.size()),registry.owns};
        state.insert(state.end(),registry.slots.begin(),registry.slots.end());
        std::cout<<result<<' '<<digest(state)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
