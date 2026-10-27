// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Facing.hpp"
#include <bit>
#include <functional>
#include <stdexcept>

namespace ra2 {
struct TechnoCoverageActor {
    std::uint8_t& active1FD;
    std::int32_t& range200;
    const std::int32_t& x88;const std::int32_t& y8C;const std::int32_t& z90;
};
struct TechnoCoverageHouse {const std::uint8_t& flag13D;const std::uint8_t& flag566A;std::uint8_t& flag188;};
struct TechnoCoverageCell {std::uint32_t& flags12C;std::int32_t& count130;std::int32_t& count134;std::int32_t& count13C;};
struct TechnoCoverageServices {
    const void* const& currentHouse;
    std::function<std::uint8_t()> allowed30C;
    std::function<std::int8_t()> typeRangeADE;
    std::function<const void*()> owner3C,owner1B4;
    std::function<std::uint8_t(const void*)> localHouse;
    std::function<std::uint8_t(const void*,const void*)> allied;
    std::function<TechnoCoverageHouse(const void*)> house;
    std::function<std::int32_t(std::int32_t)> projectedHeight;
    std::function<TechnoCoverageCell(std::int16_t,std::int16_t)> cell;
    std::function<void()> refresh634030;
    std::function<void(std::int32_t)> redraw4E09A0;
    // Optional observer of actual completed stores, without queries/mutation.
    std::function<void(char,std::int32_t,std::int32_t)> store;
};
// Complete stock6C83F0/6C86F0 around named virtual/House/height/map/refresh
// services. Initial associations and entered service implementations are supplied.
inline void changeTechnoCoverage(bool addition,TechnoCoverageActor a,const TechnoCoverageServices& s){
    const auto need=[](bool ok){if(!ok)throw std::invalid_argument("Missing Techno coverage service");};
    if(!s.currentHouse)return;
    if(addition?bool(a.active1FD):!a.active1FD)return;
    if(addition){need(bool(s.allowed30C));if(!s.allowed30C())return;}
    const auto stored=[&](char owner,int offset,int value){if(s.store)s.store(owner,offset,value);};
    if(!a.range200){need(bool(s.typeRangeADE));a.range200=s.typeRangeADE();stored('A',0x200,a.range200);}
    auto x=a.x88;a.active1FD=addition?1:0;stored('A',0x1fd,a.active1FD);
    auto y=a.y8C;const auto z=a.z90;
    need(bool(s.projectedHeight));
    x=signed32(std::uint32_t(x)+std::uint32_t(s.projectedHeight(z)/-30)*256u);
    y=signed32(std::uint32_t(y)+std::uint32_t(s.projectedHeight(z)/-30)*256u);
    const auto word=[](std::int32_t n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
    const auto centerX=word(x/256),centerY=word(y/256);
    const auto radius=a.range200,start=signed32(0xfffffffeu-std::uint32_t(radius)),end=signed32(std::uint32_t(radius)+2u);
    // Native host bound, not an original clamp or replacement arithmetic model.
    if(start<end&&std::int64_t(end)-start>128)throw std::invalid_argument("Techno coverage traversal exceeds bounded host profile");
    const auto square=[](std::int32_t n){return std::uint32_t(n)*std::uint32_t(n);};
    const auto limit=signed32(square(signed32(std::uint32_t(radius)+1u)));
    const auto privileged=[&]{
        need(bool(s.owner3C)&&bool(s.localHouse));const auto owner=s.owner3C();
        if(s.localHouse(owner))return true;
        need(bool(s.owner1B4)&&bool(s.allied));const auto current=s.currentHouse;const auto direct=s.owner1B4();
        if(s.allied(direct,current))return true;
        need(bool(s.house));return bool(s.house(s.currentHouse).flag13D);
    };
    const auto lookup=[&](std::int16_t cx,std::int16_t cy){need(bool(s.cell));return s.cell(cx,cy);};
    const auto write=[&](TechnoCoverageCell c,int offset,std::int32_t value){
        if(offset==0x12c)c.flags12C=std::uint32_t(value);
        else {auto& dest=offset==0x130?c.count130:offset==0x134?c.count134:c.count13C;dest=value;}stored('C',offset,value);
    };
    for(auto dx=start;dx<end;++dx)for(auto dy=start;dy<end;++dy){
        if(signed32(square(dx)+square(dy))>=limit)continue;
        const auto cx=word(std::int32_t(centerX)+dx),cy=word(std::int32_t(centerY)+dy);
        if(!privileged()){
            if(addition){
                if(lookup(cx,cy).count130!=1&&lookup(cx,cy).count130>=0){auto c=lookup(cx,cy);write(c,0x130,signed32(std::uint32_t(c.count130)+1u));}
                {auto c=lookup(cx,cy);write(c,0x134,signed32(std::uint32_t(c.count134)+1u));}
                if(lookup(cx,cy).count130>=1){
                    auto c=lookup(cx,cy);write(c,0x12c,signed32(std::uint32_t(c.flags12C)&~16u));
                    auto next=lookup(cx,cy);write(next,0x12c,signed32(std::uint32_t(next.flags12C)&~8u));
                }
            }else{
                {auto c=lookup(cx,cy);write(c,0x134,signed32(std::uint32_t(c.count134)-1u));}
                need(bool(s.house));if(s.house(s.currentHouse).flag566A&&lookup(cx,cy).count134<=0){
                    {auto c=lookup(cx,cy);write(c,0x130,signed32(std::uint32_t(c.count130)-1u));}
                    if(lookup(cx,cy).count130<=0){
                        auto c=lookup(cx,cy);write(c,0x12c,signed32(std::uint32_t(c.flags12C)|8u));
                        auto next=lookup(cx,cy);write(next,0x12c,signed32(std::uint32_t(next.flags12C)|16u));
                    }
                }
            }
        }
        if(privileged()){auto c=lookup(cx,cy);write(c,0x13c,signed32(std::uint32_t(c.count13C)+(addition?1u:0xffffffffu)));}
    }
    if(s.currentHouse){need(bool(s.house));s.house(s.currentHouse).flag188=0;stored('H',0x188,0);}
    need(bool(s.refresh634030));s.refresh634030();need(bool(s.redraw4E09A0));s.redraw4E09A0(2);
}
}
