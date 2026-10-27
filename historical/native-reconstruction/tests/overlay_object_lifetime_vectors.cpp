// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayObjectLifetime.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& v){
    std::vector<unsigned char> bytes;for(auto n:v)for(unsigned i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(n>>(i*8)));
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(bytes.data(),bytes.size(),hash,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<n;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(hash[i]);return out.str();
}
MapInputPosition point(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
void state(Words& out,const TransientMapOverlay& a,const OverlayObjectBase& b){
    out.insert(out.end(),{a.identityToken,b.flags14,b.word18,b.word1C,b.byte20,unsigned(b.coord24.x),unsigned(b.coord24.y),unsigned(b.coord24.z)});
    out.insert(out.end(),b.links30.begin(),b.links30.end());
    for(unsigned i=0;i<2;++i){out.insert(out.end(),b.resources[i].begin(),b.resources[i].end());out.push_back(b.resourceTags[i]);}
    out.insert(out.end(),{unsigned(b.word64),b.byte68,unsigned(b.word6C),unsigned(b.word70),a.onMap,a.redraw,a.limbo});
    out.insert(out.end(),b.bytes77.begin(),b.bytes77.end());out.insert(out.end(),{a.active,unsigned(b.lastLayer),b.byte84,b.byte85,unsigned(a.position.x),unsigned(a.position.y),unsigned(a.position.z),b.word94,a.type?1u:0u});
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0,p=0,invalid=0,capacity=0,count=0,owns=0,growResult=0,resource=0,n=0,mode=0;int incoming=0,flag=0,growth=0;
        in>>op>>seed>>p>>invalid>>incoming>>flag>>capacity>>count>>growth>>owns>>growResult>>resource>>n>>mode;
        if(!in||capacity>16||count>capacity||growth>16||owns>255||resource>255||n<1||n>8||mode>255)throw std::invalid_argument("Overlay lifetime fixture domain");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing lifetime fixture input");
        OverlayTypeInputs type;type.index=102;type.land=(mode&8)?5:0;type.crate=(mode&16)?255:0;
        std::vector<TransientMapOverlay> actors(n);std::vector<OverlayObjectBase> bases(n);std::vector<TransientMapOverlay*> pointers;
        for(unsigned i=0;i<n;++i){auto& a=actors[i];a.type=&type;a.position={13,17,19};a.limbo=1;a.active=std::uint8_t((seed>>i)&1);a.identityToken=seed+i;bases[i].flags14=seed+i;bases[i].links30[2]=(op=='R'&&(mode&32))?1:0;pointers.push_back(&a);}
        std::array<OverlayTransientRegistry,6> regs;
        for(unsigned role=0;role<6;++role){auto& r=regs[role];r.count=int(count);r.growth=growth;r.owns=std::uint8_t(owns);for(unsigned i=0;i<capacity;++i)r.slots.push_back(i%n+1);}
        // Constructor/retirement start with an empty retirement queue; cleanup
        // fixtures instead supply the configured duplicates/active entries.
        if(op!='K')regs[4].count=0;
        Words events;unsigned current=1,identityCounter=seed^0xfedcba98;std::vector<unsigned> freed(n);
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        OverlayLifetimeServices life;
        life.store=[&](unsigned role,unsigned off,unsigned size,unsigned value){if(!role)event({30,current,off,size,value});else event({30+role,off,size,value});};
        life.grow=[&](unsigned role,int amount){event({50,role,unsigned(amount),growResult});if(std::uint8_t(growResult)){auto& r=regs.at(role-1);r.slots.resize(std::size_t(amount));r.owns=1;}return growResult;};
        life.detachTag=[&](unsigned tag){event({60,tag});};life.expired=[&](unsigned id){current=id;event({61,id});};
        life.baseDestroy=[&](unsigned id){event({62,id});};life.free=[&](unsigned id){event({63,id});++freed.at(id-1);};
        life.rttiQuery=[&](unsigned id,unsigned kind){event({64,id,kind});};
        OverlayPlacementCell cell;cell.overlay=std::bit_cast<std::int32_t>(seed^0x76543210);cell.data=std::uint8_t(seed);cell.slope=std::uint8_t((mode&4)?5:0);
        OverlayPlacementServices placement;
        placement.identityCounter=seed?&identityCounter:nullptr;
        placement.base=[&](auto& a){constructOverlayObjectBase(a,bases[current-1],{std::bit_cast<std::int32_t>(seed),17,-19},1,current,{&regs[0],&regs[1],&regs[2],&regs[3]},life);};
        placement.grow=[&](int amount){return std::uint8_t(life.grow(6,amount))!=0;};
        placement.noAttachedAnimation=[&]{event({2});};placement.redraw=[&]{event({3});};
        placement.cell=[&](auto pos)->OverlayPlacementCell&{event({4,packed(pos)});return cell;};
        placement.resource=[&](auto& c){event({5});c.data=std::uint8_t(resource);event({21,0x11e,1,c.data});};
        placement.recalculate=[&](auto&,int level){event({6,unsigned(level)});};
        placement.retire=[&](auto& a){retireLoadedOverlayObject(a,bases[current-1],current,regs[4],life);};
        placement.store=[&](unsigned role,unsigned off,unsigned size,unsigned value){if(!role)event({20,current,off,size,value});else event({20+role,off,size,value});};
        if(op=='C')for(unsigned i=0;i<n;++i){current=i+1;constructLoadedMapOverlay(actors[i],type,point(p),point(invalid),incoming,flag,current,regs[5],1,placement);}
        else if(op=='R')for(unsigned i=0;i<n;++i){current=i+1;retireLoadedOverlayObject(actors[i],bases[i],current,regs[4],life);if(mode&64)retireLoadedOverlayObject(actors[i],bases[i],current,regs[4],life);}
        else if(op!='K')throw std::invalid_argument("Unknown lifetime fixture operation");
        if(op=='K'||(mode&1))cleanupLoadedOverlayObjects(pointers,regs[4],regs[5],life);
        Words output{identityCounter,unsigned(flag),unsigned(cell.overlay),cell.data,cell.slope};
        for(unsigned i=0;i<n;++i)state(output,actors[i],bases[i]);
        for(auto& r:regs){output.insert(output.end(),{unsigned(r.count),unsigned(r.slots.size()),r.owns});output.insert(output.end(),r.slots.begin(),r.slots.end());}
        output.insert(output.end(),freed.begin(),freed.end());std::cout<<digest(output)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
