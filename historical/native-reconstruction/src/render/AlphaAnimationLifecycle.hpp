// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/AlphaAnimation.hpp"
#include "sim/MissionTagExpiration.hpp"
namespace ra2 {
template<class T> struct AlphaAnimationRegistryView {
    MissionExpirationVector<T> entries;
    std::int32_t& capacity;
    std::uint8_t& allocated;
    std::int32_t& increment;
    // Complete vector heap growth is not recovered here. Child may replace
    // backing/capacity/count; its result is tested by low byte only.
    std::function<std::uint32_t(std::int32_t,std::uint32_t)> resize;
};
struct AlphaAnimationLifecycleServices {
    AlphaAnimationRegistryView<AlphaAnimationRecord*>& primary;
    AlphaAnimationRegistryView<const void*>& secondary;
    std::function<std::span<const std::uint8_t>(const void*)> typeImage84;
    // Typed C++ replaces original vtables. Projection trace: 0=derived four,
    // 1=base four, 2=base's two initial auxiliary interfaces. Not a heap effect.
    std::function<void(AlphaAnimationRecord&,unsigned)> projectInterfaces;
    std::function<void(const void*)> beforeFind;
    std::function<void(AlphaAnimationRecord&)> freeRecord;
    MissionTagStore store;
};
inline void alphaStore(const AlphaAnimationLifecycleServices& s,const void* owner,
        std::int64_t offset,std::uint32_t value=0,const void* pointer=nullptr){
    if(s.store)s.store(owner,offset,value,pointer);
}
inline void projectAlphaInterfaces(AlphaAnimationRecord& r,unsigned kind,const AlphaAnimationLifecycleServices& s){
    if(kind!=2)r.derivedInterfaces=kind==0;
    if(s.projectInterfaces)s.projectInterfaces(r,kind);
}
// Complete40FF10 numerical/base-field effects. Interface projections are typed
// host adapters; retain their ordering relative to ordinary field stores.
inline void constructAlphaBase(AlphaAnimationRecord& r,const AlphaAnimationLifecycleServices& s){
    projectAlphaInterfaces(r,2,s);
    r.value18=0;alphaStore(s,&r,0x18);
    r.value1c=0;alphaStore(s,&r,0x1c);
    r.byte20=0;alphaStore(s,&r,0x20);
    const auto flags=std::uint8_t(r.flags14&0xf8);
    r.index10=-1;alphaStore(s,&r,0x10,0xffffffffu);
    projectAlphaInterfaces(r,1,s);
    r.flags14=flags;alphaStore(s,&r,0x14,flags);
}
template<class T> inline void registerAlphaRecord(AlphaAnimationRegistryView<T>& v,T pointer,
        const AlphaAnimationLifecycleServices& s){
    if(v.entries.count>=v.capacity){
        if(!v.allocated&&v.capacity!=0)return;
        if(v.increment<=0)return;
        if(!v.resize)throw std::invalid_argument("Alpha registry heap growth unbound");
        if(!std::uint8_t(v.resize(fillAdd(v.capacity,v.increment),0)))return;
    }
    const auto index=v.entries.count;
    v.entries.count=fillAdd(index,1);alphaStore(s,v.entries.identity,0x10,std::uint32_t(v.entries.count));
    if(index<0||std::size_t(index)>=v.entries.slots.size())throw std::invalid_argument("Alpha registry append outside backing");
    v.entries.slots[std::size_t(index)]=pointer;
    alphaStore(s,v.entries.identity,0x100+std::int64_t(index)*4,0,pointer);
}
inline void registerAlphaRecord(AlphaAnimationRecord& r,AlphaCombinationTable& table,const AlphaAnimationLifecycleServices& s){
    registerAlphaRecord(s.primary,&r,s);
    registerAlphaRecord(s.secondary,static_cast<const void*>(&r),s);
    if(!table.initialized)initializeAlphaCombination(table,[&](auto i,auto value){
        alphaStore(s,&table,i==65536?-1:std::int64_t(i),value);
    });
}
// Complete41EBE0 (associated) /41ED70 (default). Object Type query, file/heap
// ownership and vector resize allocation remain named services. No factory or
// scenario producer is silently inferred from these constructors.
inline AlphaAnimationRecord* constructAlphaAnimation(AlphaAnimationRecord& r,AlphaCombinationTable& table,
        const void* associated,std::int32_t x,std::int32_t y,bool defaultConstructor,
        const AlphaAnimationLifecycleServices& s){
    constructAlphaBase(r,s);
    if(defaultConstructor){
        r.associated24=nullptr;alphaStore(s,&r,0x24);
        r.bounds28.x=0;alphaStore(s,&r,0x28);
        r.bounds28.y=0;alphaStore(s,&r,0x2c);
        r.bounds28.width=0;alphaStore(s,&r,0x30);
        r.bounds28.height=0;alphaStore(s,&r,0x34);
        r.image38={};alphaStore(s,&r,0x38);
        r.expired3c=0;alphaStore(s,&r,0x3c);
        projectAlphaInterfaces(r,0,s);
    }else{
        r.image38={};alphaStore(s,&r,0x38);
        r.associated24=associated;alphaStore(s,&r,0x24,0,associated);
        r.expired3c=0;alphaStore(s,&r,0x3c);
        projectAlphaInterfaces(r,0,s);
        if(!s.typeImage84||!associated)throw std::invalid_argument("Alpha constructor Type query unbound");
        const auto image=s.typeImage84(associated);r.image38=image;alphaStore(s,&r,0x38,0,image.data());
        if(image.size()<6)throw std::invalid_argument("Alpha constructor SHP canvas header missing");
        const auto dimension=[&](unsigned at){const auto value=std::uint16_t(image[at]|(unsigned(image[at+1])<<8));return std::int32_t(std::bit_cast<std::int16_t>(value));};
        const auto width=dimension(2),height=dimension(4);
        r.bounds28.x=x;alphaStore(s,&r,0x28,std::uint32_t(x));
        r.bounds28.y=y;alphaStore(s,&r,0x2c,std::uint32_t(y));
        r.bounds28.width=width;alphaStore(s,&r,0x30,std::uint32_t(width));
        r.bounds28.height=height;alphaStore(s,&r,0x34,std::uint32_t(height));
    }
    registerAlphaRecord(r,table,s);return &r;
}
// Complete41F0F0. The removed argument is ignored; null equals null too.
inline void expireAlphaAnimation(AlphaAnimationRecord& r,const void* expired,std::uint32_t,
        const MissionTagStore& store={}){
    if(r.associated24==expired){r.expired3c=1;if(store)store(&r,0x3c,1,nullptr);}
}
// Complete41F9C0 after typed interface projection, with actual base40FF90's
// interface-only effect. Reuse the existing first-only count-before-shift kernel.
inline AlphaAnimationRecord* destroyAlphaAnimation(AlphaAnimationRecord& r,std::uint32_t deleting,
        const AlphaAnimationLifecycleServices& s){
    projectAlphaInterfaces(r,0,s);
    if(s.beforeFind)s.beforeFind(s.primary.entries.identity);
    eraseMissionExpiration(s.primary.entries,findMissionExpiration(s.primary.entries,&r),s.store);
    if(s.beforeFind)s.beforeFind(s.secondary.entries.identity);
    eraseMissionExpiration(s.secondary.entries,findMissionExpiration(s.secondary.entries,static_cast<const void*>(&r)),s.store);
    projectAlphaInterfaces(r,1,s);
    if(std::uint8_t(deleting)&1){
        if(!s.freeRecord)throw std::invalid_argument("Alpha free service unbound");
        s.freeRecord(r);
    }
    return &r;
}
// Complete410340 deleting base after its interface projection. The record's
// memory may be retained by a research free adapter; do not dispatch it again
// through the derived destructor merely because a stale physical slot remains.
inline AlphaAnimationRecord* destroyAlphaBase(AlphaAnimationRecord& r,std::uint32_t deleting,
        const AlphaAnimationLifecycleServices& s){
    projectAlphaInterfaces(r,1,s);
    if(std::uint8_t(deleting)&1){
        if(!s.freeRecord)throw std::invalid_argument("Alpha base free service unbound");
        s.freeRecord(r);
    }
    return &r;
}
inline AlphaAnimationRecord* deleteAlphaAnimation(AlphaAnimationRecord& r,std::uint32_t deleting,
        const AlphaAnimationLifecycleServices& s){
    return r.derivedInterfaces?destroyAlphaAnimation(r,deleting,s):destroyAlphaBase(r,deleting,s);
}
// Complete41F110. Save reverse extent once, retain backing between deletions,
// reload it only after the virtual deleting child, never use new live count as
// a loop bound. Retained tails can therefore be visited after a child shrinks.
inline void cleanupAlphaAnimations(AlphaCombinationTable& table,
        MissionExpirationVector<AlphaAnimationRecord*>& registry,
        const std::function<void(AlphaAnimationRecord&,std::uint32_t)>& deleting20,
        const MissionTagStore& store={}){
    if(!table.initialized)initializeAlphaCombination(table,[&](auto i,auto value){if(store)store(&table,i==65536?-1:std::int64_t(i),value,nullptr);});
    auto index=fillAdd(registry.count,-1);
    if(index<0)return;
    if(index>=1048576)throw std::invalid_argument("Alpha cleanup exceeds execution bound");
    auto slots=registry.slots;
    for(;index>=0;--index){
        if(std::size_t(index)>=slots.size()||!slots[index])throw std::invalid_argument("Alpha cleanup slot invalid before expired read");
        auto* r=slots[index];
        if(r->expired3c){
            if(!deleting20)throw std::invalid_argument("Alpha cleanup deleting child unbound");
            deleting20(*r,1);slots=registry.slots;
        }
    }
}
}
