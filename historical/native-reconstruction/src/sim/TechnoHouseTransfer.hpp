// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/WalkMovement.hpp"
#include <functional>
#include <span>
#include <stdexcept>
namespace ra2 {
struct TechnoHouseTransferActor {
    const void* identity;
    const std::uint8_t& flag76;
    const std::uint8_t& flags14;
    const Coord& position88;
    std::uint32_t& threat400;
    std::uint8_t& field372;
    // Pure access/store bindings onto one actual owner field, not a mirror.
    std::function<const void*()> owner1B4;
    std::function<void(const void*)> setOwner1B4;
};
struct TechnoHouseTransferHouse {
    std::uint32_t& value5418;
    std::span<std::uint32_t> values5310;
    std::int32_t& value53B8;
    const std::int32_t& countryB8;
};
struct TechnoHouseTransferServices {
    const void* const& localHouse;
    std::function<TechnoHouseTransferHouse(const void*)> house;
    std::function<void(const void*)> clear370;
    std::function<void(const void*,std::uint32_t)> destination410;
    std::function<void()> detach6155E0;
    std::function<void(const void*,std::uint32_t)> remove4ED440;
    std::function<void(const void*)> notifyDC;
    std::function<const void*()> type80;
    std::function<std::uint32_t(const void*,const void*)> cost84;
    std::function<void(const void*)> remove4EA800,add4EA970;
    std::function<std::int32_t()> kind2C,country38;
    std::function<void(std::int32_t)> draw11C;
    std::function<void()> clearReferences6D7C80;
    std::function<const void*(Coord)> coordinate548000;
    std::function<std::uint32_t()> point454;
    std::function<const void*(std::uint32_t)> cell548070;
    std::function<void(const void*,std::int32_t,std::uint32_t)> threat476B20;
    std::function<std::uint32_t()> threat2A0;
    std::function<void(const void*,std::uint32_t)> add4ED610;
    std::function<const void*(std::int32_t)> radio636E10;
    std::function<void(const void*,std::uint32_t)> sight414;
    std::function<void()> sight424,sight420;
    std::function<void(const void*,std::int64_t,std::uint32_t,const void*)> store;
};
template<class F> inline const F& requireHouseTransfer(const F& f){if(!f)throw std::invalid_argument("House transfer entered child unbound");return f;}
inline void detachNullTechnoController(const void* controller408){
    // Complete-to-return6155E0 -> complete6D1430 null408 path only.
    if(controller408)throw std::invalid_argument("House transfer nonnull408 effects require recovery");
}
inline void checkHouseTransferMapRemoval(std::uint8_t sidebar4EE1){
    // Complete-to-return67C150 disabled-sidebar path only, before actor queries.
    if(sidebar4EE1)throw std::invalid_argument("House transfer enabled sidebar67C150 requires recovery");
}
// Complete636E10: read backing[index], regardless of logical radio count.
// Bounds are a native owned-memory guard, not original invalid-memory parity.
inline const void* houseTransferRadioSlot(std::span<const void* const> backing,std::int32_t index){
    if(index<0||std::size_t(index)>=backing.size())throw std::invalid_argument("House transfer radio slot outside owned backing");
    return backing[std::size_t(index)];
}
// Complete-to-return6CD940 ordinary E1, null-radio paths. All entered services
// are required. Exceptions may follow original stores; preflight or use a
// disposable clone where an integration boundary is not yet recovered.
inline bool transferTechnoHouse(TechnoHouseTransferActor a,const void* next,const TechnoHouseTransferServices& s){
    if(next==requireHouseTransfer(a.owner1B4)())return false;
    if(!next)throw std::invalid_argument("House transfer requires an owned nonnull destination House");
    const auto put=[&](const void* p,std::int64_t off,std::uint32_t v,const void* ptr=nullptr){if(s.store)s.store(p,off,v,ptr);};
    requireHouseTransfer(s.clear370)(nullptr);
    requireHouseTransfer(s.destination410)(nullptr,1);
    requireHouseTransfer(s.detach6155E0)();
    requireHouseTransfer(s.remove4ED440)(a.owner1B4(),0);
    requireHouseTransfer(s.notifyDC)(nullptr);
    const auto type=requireHouseTransfer(s.type80)();
    const auto cost=requireHouseTransfer(s.cost84)(type,a.owner1B4());
    auto house=requireHouseTransfer(s.house)(next);house.value5418+=cost;put(next,0x5418,house.value5418);
    requireHouseTransfer(s.remove4EA800)(a.owner1B4());requireHouseTransfer(s.add4EA970)(next);
    if(requireHouseTransfer(s.kind2C)()!=15)throw std::invalid_argument("House transfer requires original E1 kind15");
    const auto index=requireHouseTransfer(s.country38)();auto indexed=s.house(next);
    if(index<0||std::size_t(index)>=indexed.values5310.size())throw std::invalid_argument("House transfer index outside owned5310 backing");
    auto& count=indexed.values5310[std::size_t(index)];++count;put(next,0x5310+std::int64_t(4)*index,count);
    const auto country=s.house(next).countryB8;const auto old=a.owner1B4();s.house(old).value53B8=country;put(old,0x53b8,std::uint32_t(country));
    if(!a.flag76)requireHouseTransfer(s.draw11C)(0);
    requireHouseTransfer(s.clearReferences6D7C80)();
    if(!a.flag76)requireHouseTransfer(s.draw11C)(3);
    const void* cell=nullptr;
    if(!a.flag76){
        cell=(a.flags14&4u)?requireHouseTransfer(s.cell548070)(requireHouseTransfer(s.point454)()):requireHouseTransfer(s.coordinate548000)(a.position88);
        if(cell){
            const auto delta=0u-a.threat400;const auto owner=requireHouseTransfer(s.country38)();
            requireHouseTransfer(s.threat476B20)(cell,owner,delta);a.threat400=0;put(a.identity,0x400,0);
        }
    }
    requireHouseTransfer(a.setOwner1B4)(next);put(a.identity,0x1b4,0,next);
    a.field372=std::uint8_t(next==s.localHouse&&s.localHouse);put(a.identity,0x372,a.field372);
    if(!a.flag76&&cell){
        a.threat400=requireHouseTransfer(s.threat2A0)();put(a.identity,0x400,a.threat400);
        const auto value=a.threat400;const auto owner=requireHouseTransfer(s.country38)();
        requireHouseTransfer(s.threat476B20)(cell,owner,value);
    }
    requireHouseTransfer(s.add4ED610)(a.owner1B4(),1);
    if(!a.flag76){
        if(requireHouseTransfer(s.kind2C)()!=15)throw std::invalid_argument("House transfer post-owner E1 kind differs");
        if(requireHouseTransfer(s.radio636E10)(0))throw std::invalid_argument("House transfer linked radio continuation unjoined");
        requireHouseTransfer(s.destination410)(nullptr,1);requireHouseTransfer(s.clear370)(nullptr);
        requireHouseTransfer(s.sight414)(nullptr,1);requireHouseTransfer(s.sight424)();requireHouseTransfer(s.sight420)();
    }
    return true;
}
struct InfantryHouseTransferServices {
    std::function<std::uint32_t(const void*,std::uint32_t)> base6CD940;
    std::function<std::uint32_t()> query54,point1A0;
    std::function<void(std::uint32_t)> set454;
};
// Complete4CA7D0. Its own second argument is ignored; literal1 is forwarded.
inline bool transferInfantryHouse(const void* next,std::uint32_t,const InfantryHouseTransferServices& s){
    if(!std::uint8_t(requireHouseTransfer(s.base6CD940)(next,1)))return false;
    if(!std::uint8_t(requireHouseTransfer(s.query54)()))requireHouseTransfer(s.set454)(requireHouseTransfer(s.point1A0)());
    return true;
}
}
