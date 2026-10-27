// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTagExpiration.hpp"
#include <array>
namespace ra2 {
// Borrowed fields: callbacks can change the live Type/House association.
struct TeamConstructionType {
    const void* identity;
    std::uint8_t& houseFlagEE;
    std::int32_t& countD4;
    const void*& tagC8;
    const void*& scriptD8;
};
struct TeamConstructionHouse { const void* identity; std::uint32_t& teamCount555C; };
struct TeamConstructionRecord {
    std::int32_t index10=-1;
    std::uint8_t flags14=0,byte20=0;
    std::uint32_t value18=0,value1C=0;
    TeamConstructionType* type24=nullptr;
    const void* script28=nullptr;
    TeamConstructionHouse* house2C=nullptr;
    std::uint32_t value30=0;
    const void* cell34=nullptr;
    const void* value38=nullptr;
    const void* value3C=nullptr;const void* value40=nullptr;
    std::uint32_t argument44=0,value48=0,value4C=0;
    const void* value54=nullptr;
    std::uint32_t timer50=0,timer58=0,value60=0,timer64=0,value6C=0;
    const void* tag70=nullptr;
    std::array<std::uint8_t,16> flags74{};
    std::array<std::uint32_t,6> values84{};
};
struct TeamConstructionRegistry {
    MissionExpirationVector<const void*> entries;
    std::int32_t& capacity;
    std::uint8_t& allocated;
    std::int32_t& increment;
    std::function<std::uint32_t(std::int32_t,std::uint32_t)> resize;
    // Optional typed projection onto an existing physical registry (e.g. the
    // mission recipient views). It writes that owner's slot, never a copy.
    std::function<void(std::int32_t,const void*)> appendSlot;
};
struct TeamConstructionServices {
    const std::int32_t& frame;
    const std::uint32_t& emptyCell;
    // Team866178, sharedAC0CB0, AC0C58, genericAC0D60, AC0D30, in order.
    std::array<TeamConstructionRegistry*,5> registries;
    std::function<std::uint32_t(TeamConstructionType&)> waypoint6BFA90;
    std::function<const void*(std::uint32_t)> map548070;
    std::function<void*(std::uint32_t)> allocate;
    std::function<const void*(void*,const void*)> constructTag6B3870;
    std::function<const void*(void*,const void*)> constructScript668730;
    // Typed interface projection:2 auxiliary,1 base four,0 derived four.
    std::function<void(TeamConstructionRecord&,unsigned)> projectInterfaces;
    MissionTagStore store;
};
template<class Services> inline void teamConstructionStore(const Services& s,const void* owner,
        std::int64_t offset,std::uint32_t value=0,const void* pointer=nullptr){
    if(s.store)s.store(owner,offset,value,pointer);
}
// Complete40FF10 fields and projection order, also recovered for AlphaImage.
// This simulation representation does not depend on render records or SDL.
template<class Record,class Services> inline void constructTeamAbstractBase(Record& r,const Services& s){
    if(s.projectInterfaces)s.projectInterfaces(r,2);
    r.value18=0;teamConstructionStore(s,&r,0x18);
    r.value1C=0;teamConstructionStore(s,&r,0x1c);
    r.byte20=0;teamConstructionStore(s,&r,0x20);
    const auto flags=std::uint8_t(r.flags14&0xf8);
    r.index10=-1;teamConstructionStore(s,&r,0x10,0xffffffffu);
    if(s.projectInterfaces)s.projectInterfaces(r,1);
    r.flags14=flags;teamConstructionStore(s,&r,0x14,flags);
}
template<class Services> inline void registerConstructedTeam(TeamConstructionRegistry& v,const void* p,const Services& s){
    if(v.entries.count>=v.capacity){
        if(!v.allocated&&v.capacity)return;
        if(v.increment<=0)return;
        if(!v.resize)throw std::invalid_argument("Team registry growth unbound");
        if(!std::uint8_t(v.resize(std::bit_cast<std::int32_t>(std::uint32_t(v.capacity)+std::uint32_t(v.increment)),0)))return;
    }
    const auto index=v.entries.count;
    v.entries.count=std::bit_cast<std::int32_t>(std::uint32_t(index)+1);
    teamConstructionStore(s,v.entries.identity,16,std::uint32_t(v.entries.count));
    if(v.appendSlot)v.appendSlot(index,p);
    else{
    if(index<0||std::size_t(index)>=v.entries.slots.size())throw std::invalid_argument("Team registry append outside backing");
    v.entries.slots[std::size_t(index)]=p;
    }
    teamConstructionStore(s,v.entries.identity,0x100+std::int64_t(index)*4,0,p);
}
// Complete6B7430. No members are created here. Tag/Script constructors, heap,
// waypoint resolution and map lookup remain explicit children.
inline TeamConstructionRecord* constructTeam(TeamConstructionRecord& r,TeamConstructionType* type,
        TeamConstructionHouse* house,std::uint32_t argument,const TeamConstructionServices& s){
    constructTeamAbstractBase(r,s);
    r.type24=type;teamConstructionStore(s,&r,0x24,0,type?type->identity:nullptr);
    r.script28=nullptr;teamConstructionStore(s,&r,0x28);
    r.house2C=house;teamConstructionStore(s,&r,0x2c,0,house?house->identity:nullptr);
    r.value30=0;teamConstructionStore(s,&r,0x30);
    r.cell34=nullptr;teamConstructionStore(s,&r,0x34);
    r.value38=0;teamConstructionStore(s,&r,0x38);
    r.value3C=0;teamConstructionStore(s,&r,0x3c);
    r.value40=0;teamConstructionStore(s,&r,0x40);
    r.argument44=argument;teamConstructionStore(s,&r,0x44,argument);
    r.value48=0;teamConstructionStore(s,&r,0x48);
    r.value4C=0;teamConstructionStore(s,&r,0x4c);
    r.timer50=std::uint32_t(s.frame);teamConstructionStore(s,&r,0x50,r.timer50);
    r.value54=0;teamConstructionStore(s,&r,0x54);
    const auto frame58=std::uint32_t(s.frame);
    r.value60=0;teamConstructionStore(s,&r,0x60);
    r.timer58=frame58;teamConstructionStore(s,&r,0x58,r.timer58);
    const auto frame64=std::uint32_t(s.frame);
    r.timer64=frame64;teamConstructionStore(s,&r,0x64,r.timer64);
    r.value6C=0;teamConstructionStore(s,&r,0x6c);
    r.tag70=nullptr;teamConstructionStore(s,&r,0x70);
    for(unsigned i=0;i<16;++i){r.flags74[i]=i==6||i==9||i==12;teamConstructionStore(s,&r,0x74+i,r.flags74[i]);}
    if(s.projectInterfaces)s.projectInterfaces(r,0);
    for(auto* registry:s.registries){
        if(!registry)throw std::invalid_argument("Team physical registry unbound");
        registerConstructedTeam(*registry,&r,s);
    }
    for(unsigned i=0;i<6;++i){r.values84[i]=0;teamConstructionStore(s,&r,0x84+4*i);}
    if(!r.type24)return &r;
    if(r.house2C&&r.type24->houseFlagEE){
        ++r.house2C->teamCount555C;
        teamConstructionStore(s,r.house2C->identity,0x555c,r.house2C->teamCount555C);
    }
    if(!s.waypoint6BFA90)throw std::invalid_argument("Team waypoint child unbound");
    const auto point=s.waypoint6BFA90(*r.type24);
    if(std::uint16_t(point)!=std::uint16_t(s.emptyCell)||std::uint16_t(point>>16)!=std::uint16_t(s.emptyCell>>16)){
        const auto second=s.waypoint6BFA90(*r.type24);
        if(!s.map548070)throw std::invalid_argument("Team map lookup child unbound");
        r.cell34=s.map548070(second);teamConstructionStore(s,&r,0x34,0,r.cell34);
    }
    auto& count=r.type24->countD4;count=std::bit_cast<std::int32_t>(std::uint32_t(count)+1);
    teamConstructionStore(s,r.type24->identity,0xd4,std::uint32_t(count));
    if(r.type24->tagC8){
        if(!s.allocate)throw std::invalid_argument("Team Tag allocation unbound");
        auto* storage=s.allocate(56);const void* tag=nullptr;
        if(storage){
            if(!s.constructTag6B3870)throw std::invalid_argument("Team Tag constructor unbound");
            tag=s.constructTag6B3870(storage,r.type24->tagC8);
        }
        r.tag70=tag;teamConstructionStore(s,&r,0x70,0,tag);
    }
    if(!s.allocate)throw std::invalid_argument("Team Script allocation unbound");
    auto* storage=s.allocate(48);const void* script=nullptr;
    if(storage){
        if(!s.constructScript668730)throw std::invalid_argument("Team Script constructor unbound");
        script=s.constructScript668730(storage,r.type24->scriptD8);
    }
    r.script28=script;teamConstructionStore(s,&r,0x28,0,script);
    return &r;
}
// Complete6B9590 for a nonnull expired Tag and a newly constructed memberless
// Team. The member-head splice and other populated reference words refuse until
// their actual producers are joined; an unrelated Tag still executes all tests.
inline void expireConstructedTeamTag(TeamConstructionRecord& r,const void* subject,
        std::uint32_t,const MissionTagStore& store={}){
    if(!subject||r.value54||r.value40||r.value3C||r.value38||r.argument44||r.value30)
        throw std::invalid_argument("Team expiration outside constructed Tag domain");
    const auto clear=[&](std::int64_t off){if(store)store(&r,off,0,nullptr);};
    if(r.tag70==subject){r.tag70=nullptr;clear(0x70);}
    // Fresh member head54 is null, so removed's low-byte splice is not entered.
    if(r.house2C&&r.house2C->identity==subject){r.house2C=nullptr;clear(0x2c);}
    if(r.script28==subject){r.script28=nullptr;clear(0x28);}
    if(r.cell34==subject){r.cell34=nullptr;clear(0x34);}
    if(r.type24&&r.type24->identity==subject){r.type24=nullptr;clear(0x24);}
}

}
