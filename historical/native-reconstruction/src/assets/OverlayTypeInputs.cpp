// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayTypeInputs.hpp"
#include <algorithm>
#include <bit>
#include <climits>
#include <stdexcept>

namespace ra2 {
namespace {
void check(const OverlayTypeRegistry& r){
    if(r.count<0||r.slots.size()>INT_MAX||std::size_t(r.count)>r.slots.size())
        throw std::invalid_argument("Invalid overlay registry storage");
    for(int i=0;i<r.count;++i)if(!r.slots[std::size_t(i)])
        throw std::invalid_argument("Null overlay registry member");
}
}
void constructOverlayType(OverlayTypeInputs& t,std::string_view id,OverlayTypeRegistry& r,
    const OverlayConstructionServices& s){
    check(r);
    if(!s.base)throw std::invalid_argument("Missing overlay base constructor");
    s.base(t,id);
    const auto put=[&](auto& field,auto value,unsigned offset){
        field=value;if(s.store)s.store(t,offset,sizeof(field),std::uint32_t(field));
    };
    put(t.damageLevels,1,0x270);put(t.strength,1,0x274);
    put(t.noUseTileLandType,std::uint8_t(1),0x27c);put(t.drawFlat,std::uint8_t(1),0x283);
    put(t.index,-1,0x264);put(t.land,0,0x268);put(t.cellAnim,0u,0x26c);
    for(auto [field,offset]:{std::pair{&t.wall,0x278u},{&t.tiberium,0x279u},
        {&t.crate,0x27au},{&t.crateTrigger,0x27bu},{&t.veinhole,0x27du},
        {&t.veins,0x27eu},{&t.demandLoad,0x27fu},{&t.explodes,0x280u},
        {&t.chainReaction,0x281u},{&t.overrides,0x282u},{&t.rubble,0x284u},{&t.rock,0x285u}})
        put(*field,std::uint8_t(0),offset);
    // Actual identity helper with loading global zero. Identity storage itself
    // is outside the selected native record, but its ordered store is visible.
    if(s.store)s.store(t,0x10,4,0);
    put(t.radarInvisible,std::uint8_t(1),0x1ff);put(t.selectable,std::uint8_t(0),0x200);
    put(t.insignificant,std::uint8_t(1),0x202);put(t.flag205,std::uint8_t(0),0x205);
    bool append=r.count<int(r.slots.size());
    if(!append&&(r.owns||r.slots.empty())&&r.growth>0){
        const int capacity=std::bit_cast<std::int32_t>(std::uint32_t(r.slots.size())+std::uint32_t(r.growth));
        if(capacity<0)throw std::invalid_argument("Unsupported overlay capacity wrap");
        append=s.grow&&s.grow(capacity);
        check(r);
    }
    if(append){
        if(std::size_t(r.count)>=r.slots.size())throw std::invalid_argument("Overlay growth supplied no capacity");
        const int index=r.count++;
        if(s.registryStore)s.registryStore(0,std::uint32_t(r.count));
        r.slots[std::size_t(index)]=&t;
        if(s.registryStore)s.registryStore(1,std::uint32_t(index));
    }
    const auto found=std::find(r.slots.begin(),r.slots.begin()+r.count,&t);
    put(t.index,found==r.slots.begin()+r.count?-1:int(found-r.slots.begin()),0x264);
}
OverlayTypeInputs* resolveOverlayType(std::string_view id,OverlayTypeRegistry& r,
    const OverlayConstructionServices& s){
    check(r);
    if(!s.equal)throw std::invalid_argument("Missing overlay identity comparison");
    if(s.equal("<none>",id)||s.equal("none",id))return nullptr;
    for(int i=0;i<r.count;++i)if(s.equal(r.slots[std::size_t(i)]->id,id))return r.slots[std::size_t(i)];
    if(!s.allocate)throw std::invalid_argument("Missing overlay allocator");
    auto* t=s.allocate();if(t)constructOverlayType(*t,id,r,s);return t;
}
bool readOverlayTypeList(int count,const std::function<std::pair<int,std::string>(int)>& value,
    OverlayTypeRegistry& r,const OverlayConstructionServices& s){
    if(count>0&&!value)throw std::invalid_argument("Missing overlay list reader");
    for(int i=0;i<count;++i){const auto [length,text]=value(i);if(length)resolveOverlayType(text,r,s);}
    return count>0;
}
bool readOverlayTypeIni(OverlayTypeInputs& t,const OverlayIniServices& s){
    if(!s.base)throw std::invalid_argument("Missing overlay base INI loader");
    if(!s.base(t))return false;
    if(!s.integer||!s.boolean||!s.cellAnimation)throw std::invalid_argument("Missing overlay INI service");
    const auto put=[&](auto& field,auto value,unsigned offset){
        field=value;if(s.store)s.store(offset,sizeof(field),std::uint32_t(field));
    };
    const auto flag=[&](std::uint8_t& field,const char* key,unsigned offset,bool art=false){
        const auto result=std::uint8_t(s.boolean(art,art?t.imageName:t.id,key,field));
        put(field,result,offset);
    };
    const int land=s.integer(false,t.id,"Land",t.land);
    put(t.land,land,0x268);
    const int strength=s.integer(false,t.id,"Strength",t.strength);
    put(t.strength,strength,0x274);
    flag(t.wall,"Wall",0x278);flag(t.tiberium,"Tiberium",0x279);
    flag(t.crate,"Crate",0x27a);flag(t.crateTrigger,"CrateTrigger",0x27b);
    flag(t.explodes,"Explodes",0x280);flag(t.overrides,"Overrides",0x282);
    const auto previousAnimation=t.cellAnim;
    const auto [length,animation]=s.cellAnimation(t.id);
    if(length){
        if(!s.resolveAnimation)throw std::invalid_argument("Missing overlay animation resolver");
        put(t.cellAnim,s.resolveAnimation(animation),0x26c);
    }else put(t.cellAnim,previousAnimation,0x26c);
    put(t.damageLevels,s.integer(true,t.imageName,"DamageLevels",t.damageLevels),0x270);
    flag(t.demandLoad,"DemandLoad",0x27f,true);
    if(t.tiberium){put(t.armor,6,0x9c);if(!t.land)put(t.land,5,0x268);}
    if(!t.theater&&!t.demandLoad){
        if(!s.loadImage)throw std::invalid_argument("Missing overlay image loader");
        put(t.image,s.loadImage(t.imageName+".SHP"),0xa4);
    }
    flag(t.noUseTileLandType,"NoUseTileLandType",0x27c);
    flag(t.veinhole,"IsVeinholeMonster",0x27d);flag(t.veins,"IsVeins",0x27e);
    flag(t.chainReaction,"ChainReaction",0x281);flag(t.drawFlat,"DrawFlat",0x283);
    flag(t.rock,"IsARock",0x285);flag(t.rubble,"IsRubble",0x284);
    return true;
}
}
