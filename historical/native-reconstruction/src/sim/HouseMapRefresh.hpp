// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
#include <utility>
namespace ra2 {
// Logical Owner handles may be resolved live without mirroring a pointer field.
// The getter is a pure binding: it must not issue gameplay or map queries.
struct HouseMapRefreshOwner {
    std::function<const void*()> get;
    HouseMapRefreshOwner(const void* const& p):get([&p]{return p;}){}
    HouseMapRefreshOwner(std::function<const void*()> f):get(std::move(f)){}
    operator const void*()const {if(!get)throw std::invalid_argument("Missing House Owner binding");return get();}
};
struct HouseMapRefreshActor {
    const std::uint8_t& flag76;
    const std::uint8_t& sight373;
    HouseMapRefreshOwner owner1B4;
    const std::int32_t& range1F4;
    const std::int32_t& x88;const std::int32_t& y8C;const std::int32_t& z90;
};
struct HouseMapRefreshType {const std::uint8_t& flag534;const std::uint8_t& flagADD;};
struct HouseMapRefreshWorld {
    const std::int32_t& count;
    const std::span<const void*>& actors;
    HouseMapRefreshOwner currentHouse;
    const std::uint8_t& alliedVision142B;
    // Pure borrowed views; named virtual callbacks may change their owners.
    std::function<HouseMapRefreshActor(const void*)> actor;
    // Bind existing recovered4F52B0/4E5540 kernels to the same House owners.
    std::function<bool(const void*)> localHouse;
    std::function<bool(const void*,const void*)> allied;
    std::function<std::int32_t(const void*)> kind2C;
    std::function<HouseMapRefreshType(const void*)> type80;
    std::function<void(const void*,std::int32_t,std::int32_t,std::int32_t,std::int32_t,const void*)> sight;
    std::function<void(const void*,std::int32_t)> image;
    std::function<void(std::array<std::int32_t,3>,std::int32_t,std::int32_t,std::uint32_t)> postSight;
};
// Complete49E000 removal and49DE00 addition scans, around named sight/type/image/
// post-sight leaves. Kind and type queries must remain separate and live.
inline void refreshHouseMapSight(bool addition,std::uint8_t skipBuildings,std::int32_t argument,const HouseMapRefreshWorld& w){
    const auto count=w.count;
    for(std::int32_t i=0;i<count;++i){
        if(std::size_t(i)>=w.actors.size())throw std::invalid_argument("House map refresh registry exceeds supplied backing");
        const auto p=w.actors[std::size_t(i)];if(!p)continue;
        if(!w.actor)throw std::invalid_argument("House map refresh needs actor view");
        const auto actor=w.actor(p);if(actor.flag76)continue;
        const auto kind=[&]{if(!w.kind2C)throw std::invalid_argument("House map refresh needs kind2C");return w.kind2C(p);};
        const auto local=[&]{if(!w.localHouse)throw std::invalid_argument("House map refresh needs House4F52B0");return w.localHouse(actor.owner1B4);};
        const auto allied=[&]{if(!w.allied)throw std::invalid_argument("House map refresh needs House4E5540");return w.allied(actor.owner1B4,w.currentHouse);};
        const auto type=[&]{if(!w.type80)throw std::invalid_argument("House map refresh needs type80");return w.type80(p);};
        if(kind()==6&&skipBuildings)continue;
        const auto dispatch=[&](std::int32_t second,std::int32_t third,const void* house){
            if(!w.sight)throw std::invalid_argument("House map refresh needs sight virtual");
            w.sight(p,addition?0x418:0x41c,0,second,third,house);
            if(addition){
                const std::array<std::int32_t,3> point{actor.x88,actor.y8C,actor.z90};
                const auto radius=std::bit_cast<std::int32_t>(std::uint32_t(actor.range1F4)+3u);
                if(!w.postSight)throw std::invalid_argument("House map refresh needs post-sight child");
                w.postSight(point,0,radius,0);
            }
        };
        if(local()){
            if(!actor.sight373)continue;
            dispatch(0,0,nullptr);
        }else{
            if(kind()==6&&w.alliedVision142B&&allied()){
                dispatch(argument,0,nullptr);continue;
            }
            if(addition&&kind()==6&&type().flag534&&!local()){
                dispatch(0,1,w.currentHouse);continue;
            }
        }
        if(type().flagADD){
            if(!w.image)throw std::invalid_argument("House map refresh needs image virtual");
            w.image(p,addition?0x3ac:0x3b0);
        }
    }
}
}
