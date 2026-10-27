// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
#include <utility>
namespace ra2 {
struct HouseThreatCell {const std::int16_t& x;const std::int16_t& y;};
struct HouseThreatScore {const void* house;std::int32_t value;};
struct HouseThreatHouse {
    const void* identity;
    const std::int32_t& index30;
    const std::uint8_t& field13D;
    const std::uint8_t& flag134;
    const std::uint8_t& flag135;
    const std::uint32_t& allies5674;
    std::int32_t& enemy54F0;
    const std::int32_t& count5504;
    const std::span<HouseThreatScore>& scores54F8;
    std::span<std::int32_t> grid56D0;
};
// Resolve logical Owner handles at the original late read without mirroring a
// pointer. Getters only map existing fields/identities; they make no queries.
struct HouseThreatOwner {
    std::function<const void*()> get;
    HouseThreatOwner(const void* const& p):get([&p]{return p;}){}
    HouseThreatOwner(std::function<const void*()> f):get(std::move(f)){}
    operator const void*()const{if(!get)throw std::invalid_argument("Missing threat Owner binding");return get();}
};
struct HouseThreatActor {
    const std::uint8_t& flag76;
    const std::uint8_t& flag7D;
    HouseThreatOwner owner1B4;
    HouseThreatCell cell454;
};
struct HouseThreatWorld {
    const std::int32_t& mode;
    const std::int32_t& actorCount;
    const std::span<const void*>& actors;
    HouseThreatCell invalidCell;
    std::span<const std::int32_t,9> offsets;
    std::span<const std::int32_t,9> shifts;
    // Pure borrowed field views. Named virtual services below may mutate owners.
    std::function<HouseThreatHouse(const void*)> house;
    std::function<HouseThreatActor(const void*)> actor;
    std::function<std::int32_t(const void*)> threat2A0;
    std::function<std::int32_t(const void*)> kind2C;
    std::function<HouseThreatCell(const void*)> objectCell1A4;
};
inline std::int32_t houseThreatAdd(std::int32_t a,std::int32_t b){
    return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));
}
inline std::int32_t projectHouseThreatCell(HouseThreatCell c){
    // Complete54E370: signed-word coordinates, division toward zero.
    return std::int32_t(c.x)/4+130*(std::int32_t(c.y)/4)+0x83;
}
inline HouseThreatHouse houseThreatHouse(const HouseThreatWorld& w,const void* p){
    if(!p||!w.house)throw std::invalid_argument("House threat needs a nonnull owned House");
    auto h=w.house(p);
    if(h.identity!=p)throw std::invalid_argument("House threat identity differs");
    return h;
}
inline HouseThreatScore& houseThreatScoreAt(std::span<HouseThreatScore> scores,std::int32_t i){
    if(i<0||std::size_t(i)>=scores.size())throw std::invalid_argument("House threat score backing too small");
    return scores[std::size_t(i)];
}
// Complete4EEBA0. Update every matching entry, then choose the first strictly
// greatest positive nonallied score. Duplicate entries and signed wrap matter.
inline void updateHouseThreatScore(const void* current,std::int32_t delta,const void* target,const HouseThreatWorld& w){
    const auto self=houseThreatHouse(w,current);
    for(std::int32_t i=0;i<self.count5504;++i){
        auto& entry=houseThreatScoreAt(self.scores54F8,i);
        if(entry.house==target)entry.value=houseThreatAdd(entry.value,delta);
    }
    const auto count=self.count5504;const auto scores=self.scores54F8;
    std::int32_t best=0;const void* chosen=nullptr;
    for(std::int32_t i=0;i<count;++i){
        const auto& entry=houseThreatScoreAt(scores,i);
        if(entry.value<=best)continue;
        const auto other=houseThreatHouse(w,entry.house);
        if(other.field13D||entry.house==current||other.index30==self.index30)continue;
        if(other.index30!=-1&&(self.allies5674&(std::uint32_t(1)<<(std::uint32_t(other.index30)&31u))))continue;
        best=entry.value;chosen=entry.house;
    }
    self.enemy54F0=chosen?houseThreatHouse(w,chosen).index30:-1;
}
// Complete4F3420 around named virtual children, joined to actual54E370.
inline void rebuildHouseThreatGrid(const void* current,const HouseThreatWorld& w){
    constexpr std::size_t gridSize=0x4204;
    const auto self=houseThreatHouse(w,current);
    if(self.grid56D0.size()<gridSize)throw std::invalid_argument("House threat grid backing too small");
    std::fill_n(self.grid56D0.begin(),gridSize,0);
    auto index=houseThreatAdd(w.actorCount,-1); // DEC wraps before the signed test.
    for(;index>=0;--index){
        if(std::size_t(index)>=w.actors.size()||!w.actors[std::size_t(index)]||!w.actor)
            throw std::invalid_argument("House threat registry outside owned domain");
        const auto p=w.actors[std::size_t(index)];const auto actor=w.actor(p);
        if(actor.flag76||!actor.flag7D)continue;
        if(!w.threat2A0)throw std::invalid_argument("House threat needs virtual2A0");
        const auto threat=w.threat2A0(p);if(threat<=0)continue;
        if(!w.kind2C)throw std::invalid_argument("House threat needs virtual2C");
        std::int32_t cell;
        if(w.kind2C(p)==15||w.kind2C(p)==1||w.kind2C(p)==2){
            if(actor.cell454.x==w.invalidCell.x&&actor.cell454.y==w.invalidCell.y)continue;
            cell=projectHouseThreatCell(actor.cell454);
            const void* owner=actor.owner1B4;
            if(owner==current)continue;
            const auto filter=w.mode?self.flag134:std::uint8_t(bool(self.flag134||self.flag135));
            if(filter&&owner){
                const auto other=houseThreatHouse(w,owner);
                if(other.index30==self.index30||
                   (other.index30!=-1&&(self.allies5674&(std::uint32_t(1)<<(std::uint32_t(other.index30)&31u)))))continue;
            }
        }else{
            if(!w.objectCell1A4)throw std::invalid_argument("House threat needs virtual1A4");
            cell=projectHouseThreatCell(w.objectCell1A4(p));
        }
        for(std::size_t i=0;i<9;++i){
            const auto slot=houseThreatAdd(cell,w.offsets[i]);
            if(slot<0||std::size_t(slot)>=gridSize)throw std::invalid_argument("House threat stencil exceeds owned grid");
            // Positive threat only; x86 masks the SAR count to five bits.
            const auto contribution=threat>>(std::uint32_t(w.shifts[i])&31u);
            auto& value=self.grid56D0[std::size_t(slot)];
            const auto sum=houseThreatAdd(value,contribution);value=sum<0?0:sum;
        }
    }
}
}
