// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResourceTypeInputs.hpp"
#include <bit>
#include <climits>
#include <stdexcept>

namespace ra2 {
namespace {
void check(const ResourceTypeRegistry& r) {
    if(r.count<0||r.slots.size()>INT_MAX||std::size_t(r.count)>r.slots.size())
        throw std::invalid_argument("Invalid resource registry storage");
    for(int i=0;i<r.count;++i)if(!r.slots[std::size_t(i)])throw std::invalid_argument("Null resource registry member");
}
void append(ResourceTypeInputs& t,ResourceTypeRegistry& r,unsigned role,const ResourceConstructionServices& s) {
    bool accepted=r.count<int(r.slots.size());
    if(!accepted&&(r.owns||r.slots.empty())&&r.growth>0) {
        const int capacity=std::bit_cast<std::int32_t>(std::uint32_t(r.slots.size())+std::uint32_t(r.growth));
        if(capacity<0)throw std::invalid_argument("Unsupported resource registry capacity wrap");
        accepted=s.grow&&std::uint8_t(s.grow(role,capacity));check(r);
    }
    if(accepted) {
        if(std::size_t(r.count)>=r.slots.size())throw std::invalid_argument("Resource growth supplied no capacity");
        const unsigned slot=unsigned(r.count++);
        if(s.registryStore)s.registryStore(role,0,unsigned(r.count));
        r.slots[slot]=&t;if(s.registryStore)s.registryStore(role,slot+1,0);
    }
}
}
void constructResourceType(ResourceTypeInputs& t,std::string_view id,ResourceTypeRegistry& types,
    ResourceTypeRegistry& secondary,const ResourceConstructionServices& s) {
    check(types);check(secondary);
    if(!s.base||!s.constructDebris||!s.clearDebris)throw std::invalid_argument("Missing resource construction services");
    s.base(t,id);
    const auto put=[&](auto& field,auto value,unsigned off){field=value;if(s.store)s.store(t,off,sizeof(field),std::uint32_t(field));};
    const auto word=[&](double& field,bool high,unsigned off) {
        const auto fraction=std::bit_cast<std::uint64_t>(0.1);
        const unsigned shift=high?32:0;const auto value=std::uint32_t(fraction>>shift);
        auto bits=std::bit_cast<std::uint64_t>(field);bits=(bits&~(0xffffffffull<<shift))|(std::uint64_t(value)<<shift);
        field=std::bit_cast<double>(bits);if(s.store)s.store(t,off,4,value);
    };
    word(t.spreadPercentage,false,0xa0);word(t.growthPercentage,false,0xb0);
    put(t.index,-1,0x98);put(t.spread,0,0x9c);word(t.spreadPercentage,true,0xa4);
    put(t.growth,0,0xa8);word(t.growthPercentage,true,0xb4);
    put(t.value,0,0xb8);put(t.power,0,0xbc);put(t.color,0,0xc0);
    s.constructDebris(t.debris);put(t.debris.growth,10u,0xd8);put(t.debris.count,0u,0xd4);
    t.image=nullptr;if(s.store)s.store(t,0xe0,4,0);
    put(t.numFrames,0,0xe4);put(t.numImages,0,0xe8);put(t.numSlopes,0,0xec);
    for(unsigned off=0xf0;off<=0xfc;off+=4)put(t.logic[(off-0xf0)/4],0u,off);
    put(t.logic[4],s.currentFrame,0x100);
    for(unsigned off=0x108;off<=0x118;off+=4)put(t.logic[(off-0xf0)/4],0u,off);
    put(t.logic[13],0u,0x124);put(t.logic[11],s.currentFrame,0x11c);
    put(t.index,types.count,0x98);append(t,types,1,s);
    s.clearDebris(t.debris);append(t,secondary,2,s);
}
bool readResourceTypeIni(ResourceTypeInputs& t,const ResourceIniServices& s) {
    if(!s.base)throw std::invalid_argument("Missing resource base INI service");
    if(!s.base(t))return false;
    if(!s.integer||!s.real||!s.color||!s.debrisText||!s.copyDebris||!s.assignDebris||!s.releaseDebris)
        throw std::invalid_argument("Missing resource INI services");
    const auto put=[&](auto& field,auto value,unsigned off){field=value;if(s.store)s.store(t,off,sizeof(field),std::uint32_t(field));};
    const int spread=s.integer(t.id,"Spread",t.spread);
    put(t.spread,spread,0x9c);
    const double spreadPercentage=s.real(t.id,"SpreadPercentage",t.spreadPercentage);
    t.spreadPercentage=spreadPercentage;
    if(s.store)s.store(t,0xa0,8,std::bit_cast<std::uint64_t>(t.spreadPercentage));
    const int growth=s.integer(t.id,"Growth",t.growth);
    put(t.growth,growth,0xa8);
    const double growthPercentage=s.real(t.id,"GrowthPercentage",t.growthPercentage);
    t.growthPercentage=growthPercentage;
    if(s.store)s.store(t,0xb0,8,std::bit_cast<std::uint64_t>(t.growthPercentage));
    const int value=s.integer(t.id,"Value",t.value);put(t.value,value,0xb8);
    const int power=s.integer(t.id,"Power",t.power);
    put(t.power,power,0xbc);put(t.color,s.color(t.id,t.color),0xc0);
    const auto [length,text]=s.debrisText(t.id);ResourceDebrisInputs copy;
    if(length) {
        if(!s.beginDebris||!s.nextDebris||!s.resolveDebris||!s.appendDebris||!s.destroyDebris)
            throw std::invalid_argument("Missing resource debris parsing services");
        auto parsed=s.beginDebris();bool first=true;
        for(;;) {
            auto token=s.nextDebris(first,text);first=false;
            if(!token||token->empty())break;
            if(auto item=s.resolveDebris(*token))s.appendDebris(parsed,item);
        }
        copy=s.copyDebris(parsed);s.destroyDebris(parsed);
    }else copy=s.copyDebris(t.debris);
    s.assignDebris(t.debris,copy);
    put(t.debris.count,copy.count,0xd4);put(t.debris.growth,copy.growth,0xd8);put(t.debris.extra,copy.extra,0xdc);
    if(copy.buffer&&copy.owns)s.releaseDebris(copy);
    const int image=s.integer(t.id,"Image",-1);
    const auto selector=std::uint32_t(image)+1u;
    if(!selector)return true;
    const unsigned slot=selector==3?27:selector==4?127:selector==5?147:102;
    if(slot>=s.overlays.size())throw std::invalid_argument("Missing resource image overlay slot");
    t.image=&s.overlays[slot];if(s.store)s.store(t,0xe0,4,slot+1);
    if(selector!=3)put(t.numSlopes,8,0xec);
    put(t.numFrames,12,0xe4);put(t.numImages,12,0xe8);
    return true;
}
bool readResourceTypeList(int count,ResourceTypeRegistry& types,ResourceTypeRegistry& secondary,
    const ResourceListServices& s) {
    check(types);check(secondary);
    if(count>0&&(!s.entry||!s.numericKey||!s.allocate||!s.readIni))throw std::invalid_argument("Missing resource list services");
    for(int i=0;i<count;++i) {
        const auto row=s.entry(i);if(row.length<=0)continue;
        const int index=s.numericKey(row.key);ResourceTypeInputs* type=nullptr;
        if(index<types.count) {
            if(index<0)throw std::invalid_argument("Negative resource list index");
            type=types.slots[std::size_t(index)];
        }else {
            type=s.allocate();if(!type)throw std::invalid_argument("Resource list allocation returned null");
            constructResourceType(*type,row.value,types,secondary,s.construction);
        }
        s.readIni(*type);
    }
    return true;
}
MapResourceType mapResourceInputs(const ResourceTypeInputs& t) {
    if(!t.image)throw std::invalid_argument("Missing resource image association");
    return {t.index,t.image->index,t.numImages,t.numSlopes,t.numFrames,t.value};
}
}
