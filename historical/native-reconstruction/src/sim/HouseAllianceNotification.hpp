// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
namespace ra2 {
struct HouseAllianceNotificationFields {
    const std::uint8_t& flag13D;
    const std::uint8_t& flag134;
    const std::uint8_t& flag135;
    std::uint8_t& flag191;
};
struct HouseAllianceNotificationWorld {
    const std::uint8_t& rules111D;
    const void* const& session;
    const std::int32_t& mode;
    const std::int32_t& count;
    const std::span<const void*>& houses;
    // Pure field view, not an effect or a cached owner snapshot.
    std::function<HouseAllianceNotificationFields(const void*)> house;
    std::function<std::uint32_t(const void*)> session4;
    std::function<void(const void*,const void*,std::uint8_t)> makeAlly;
    std::function<void(const void*,const void*,std::uint8_t)> makeEnemy;
    std::function<void(const void*,std::uint8_t)> stored191; // Optional store observer.
};
inline bool houseAllianceNotificationLocal(HouseAllianceNotificationFields h,std::int32_t mode){
    return mode?h.flag134!=0:bool(h.flag134||h.flag135);
}
// Complete4EC5E0 around named session/recursive diplomacy services. This parent
// has no current-House argument. Startup/associations and child effects are not
// reconstructed by supplying these callbacks. Exceptions do not roll back.
inline void notifyHouseAlliances(const HouseAllianceNotificationWorld& w){
    const auto enabled=w.rules111D; // Saved before the possibly mutating session call.
    const auto session=w.session;
    bool permitted=false;
    if(session){
        if(!w.session4)throw std::invalid_argument("Alliance notification needs session virtual4");
        permitted=std::uint8_t(w.session4(session))!=0;
    }
    if(!permitted&&!enabled)return;
    const auto at=[&](std::int32_t i){
        if(i<0||std::size_t(i)>=w.houses.size())throw std::invalid_argument("Alliance notification registry outside owned backing");
        return w.houses[std::size_t(i)];
    };
    const auto fields=[&](const void* p){
        if(!w.house)throw std::invalid_argument("Alliance notification needs House fields");
        return w.house(p);
    };
    for(std::int32_t i=0;i<w.count;++i){
        const auto self=at(i);if(!self)continue;
        const auto h=fields(self);if(h.flag13D||houseAllianceNotificationLocal(h,w.mode))continue;
        h.flag191=1;if(w.stored191)w.stored191(self,1);
        for(std::int32_t j=0;j<w.count;++j){
            const auto other=at(j);if(!other)continue;
            const auto target=fields(other);if(target.flag13D)continue;
            const auto& service=houseAllianceNotificationLocal(target,w.mode)?w.makeEnemy:w.makeAlly;
            if(!service)throw std::invalid_argument("Alliance notification needs entered diplomacy service");
            service(self,other,0);
        }
    }
}
}
