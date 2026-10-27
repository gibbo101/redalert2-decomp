// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayObjectLifetime.hpp"
#include <algorithm>
#include <bit>
#include <climits>
#include <stdexcept>
namespace ra2 {
namespace {
void emit(const OverlayLifetimeServices& s,unsigned role,unsigned off,unsigned n,std::uint32_t value){if(s.store)s.store(role,off,n,value);}
template<class T> void put(T& field,T value,unsigned off,const OverlayLifetimeServices& s){field=value;emit(s,0,off,sizeof(T),std::uint32_t(value));}
void check(const OverlayTransientRegistry& r){
    if(r.count<0||r.slots.size()>INT_MAX||std::size_t(r.count)>r.slots.size())throw std::invalid_argument("Invalid Overlay object registry");
}
void append(OverlayTransientRegistry& r,unsigned role,std::uint32_t identity,const OverlayLifetimeServices& s){
    check(r);bool accept=r.count<int(r.slots.size());
    if(!accept&&(r.owns||r.slots.empty())&&r.growth>0){
        const int capacity=std::bit_cast<std::int32_t>(std::uint32_t(r.slots.size())+std::uint32_t(r.growth));
        if(capacity<0)throw std::invalid_argument("Unsupported Overlay object capacity wrap");
        accept=s.grow&&std::uint8_t(s.grow(role,capacity));check(r);
    }
    if(accept){
        if(std::size_t(r.count)>=r.slots.size())throw std::invalid_argument("Overlay object growth supplied no capacity");
        const unsigned slot=unsigned(r.count++);emit(s,role,0,4,unsigned(r.count));
        r.slots[slot]=identity;emit(s,role,slot+1,4,identity);
    }
}
bool remove(OverlayTransientRegistry& r,unsigned role,std::uint32_t identity,const OverlayLifetimeServices& s){
    const auto it=std::find(r.slots.begin(),r.slots.begin()+r.count,identity);
    if(it==r.slots.begin()+r.count)return false;
    unsigned index=unsigned(it-r.slots.begin());--r.count;emit(s,role,0,4,unsigned(r.count));
    for(;index<unsigned(r.count);++index){r.slots[index]=r.slots[index+1];emit(s,role,index+1,4,r.slots[index]);}
    return true;
}
}
void constructOverlayObjectBase(TransientMapOverlay& actor,OverlayObjectBase& base,Coord invalid,
    std::uint32_t resourceTag,std::uint32_t identity,const std::array<OverlayTransientRegistry*,4>& registries,
    const OverlayLifetimeServices& s){
    for(auto* r:registries){if(!r)throw std::invalid_argument("Missing Overlay base registry");check(*r);}
    // Complete Abstract constructor selected writes. Preserve high flag bytes.
    put(base.word18,0u,0x18,s);put(base.word1C,0u,0x1c,s);put(base.byte20,std::uint8_t(0),0x20,s);
    put(actor.identityToken,0xffffffffu,0x10,s);
    base.flags14&=0xfffffff8u;emit(s,0,0x14,1,base.flags14&255);
    put(base.coord24.x,0,0x24,s);put(base.coord24.y,0,0x28,s);put(base.coord24.z,0,0x2c,s);
    put(base.word6C,255,0x6c,s);put(base.word70,255,0x70,s);
    put(actor.limbo,std::uint8_t(1),0x76,s);put(actor.active,std::uint8_t(1),0x7d,s);put(base.byte85,std::uint8_t(1),0x85,s);
    for(unsigned i=0;i<3;++i)put(base.links30[i],0u,0x30+i*4,s);
    put(base.word64,-1,0x64,s);put(base.byte68,std::uint8_t(0),0x68,s);
    put(actor.onMap,std::uint8_t(0),0x74,s);put(actor.redraw,std::uint8_t(0),0x75,s);
    for(unsigned i=0;i<6;++i)put(base.bytes77[i],std::uint8_t(0),0x77+i,s);
    put(base.lastLayer,-1,0x80,s);put(base.byte84,std::uint8_t(0),0x84,s);
    put(actor.position.x,invalid.x,0x88,s);put(actor.position.y,invalid.y,0x8c,s);
    put(base.word94,0u,0x94,s);put(actor.position.z,invalid.z,0x90,s);
    // Each embedded resource handle stores its tag before its three zero words.
    for(unsigned i=0;i<2;++i){
        const unsigned offset=i?0x50:0x3c;
        put(base.resourceTags[i],resourceTag,offset+12,s);
        for(unsigned j=0;j<3;++j)put(base.resources[i][j],0u,offset+j*4,s);
    }
    for(unsigned i=0;i<4;++i)append(*registries[i],i+1,identity,s);
    base.flags14|=2;emit(s,0,0x14,1,base.flags14&255);
}
void retireLoadedOverlayObject(TransientMapOverlay& actor,const OverlayObjectBase& base,
    std::uint32_t identity,OverlayTransientRegistry& retired,const OverlayLifetimeServices& s){
    if(!actor.limbo)throw std::invalid_argument("Persistent Overlay removal requires recovery");
    check(retired);
    if(base.links30[2]){if(!s.detachTag)throw std::invalid_argument("Missing Overlay tag service");s.detachTag(base.links30[2]);}
    if(!s.expired)throw std::invalid_argument("Missing Overlay pointer expiration");
    s.expired(identity); // Removed byte exactly one; original Object Limbo rejects.
    put(actor.active,std::uint8_t(0),0x7d,s);append(retired,5,identity,s);
}
void cleanupLoadedOverlayObjects(std::span<TransientMapOverlay* const> actors,
    OverlayTransientRegistry& retired,OverlayTransientRegistry& overlays,const OverlayLifetimeServices& s){
    check(retired);check(overlays);
    if(!s.expired||!s.baseDestroy||!s.free)throw std::invalid_argument("Missing Overlay destruction services");
    const auto get=[&](std::uint32_t id)->TransientMapOverlay&{
        if(!id||id>actors.size()||!actors[id-1]||!actors[id-1]->limbo)throw std::invalid_argument("Invalid or persistent cleanup actor");
        return *actors[id-1];
    };
    // Preflight identities before mutation; no general-object/heap claim.
    for(int i=0;i<retired.count;++i)get(retired.slots[std::size_t(i)]);
    unsigned cursor=0;
    while(cursor<unsigned(retired.count)){
        const auto identity=retired.slots[cursor];auto& actor=get(identity);
        if(actor.active){++cursor;continue;}
        while(remove(retired,5,identity,s)){}
        // Actual Release returns one. The four RTTI comparisons are negative
        // for this Overlay-only domain; external RTTI implementation supplied.
        if(s.rttiQuery)for(unsigned kind=0;kind<4;++kind)s.rttiQuery(identity,kind);
        s.expired(identity);remove(overlays,6,identity,s);
        actor.type=nullptr;emit(s,0,0x98,4,0);
        s.baseDestroy(identity);s.free(identity);
    }
}
}
