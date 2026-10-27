// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct TechnoNullNotificationActor {
    const void* identity;
    const std::uint8_t& onMap7D;
    std::function<const void*()> tag34,owner1B4;
};
struct TechnoNullNotificationServices {
    const std::uint32_t& emptyCell;
    std::function<const void*()> type80;
    std::function<std::uint32_t(const void*,const void*)> cost84;
    std::function<std::int32_t()> kind2C;
    std::function<void(const void*,std::int32_t,const void*,std::uint32_t)> raiseTag;
    std::function<std::uint32_t&(const void*)> house5360;
    std::function<std::uint32_t()> map6331A0;
    std::function<void(std::uint32_t)> map6331E0;
    std::function<void(const void*,std::int64_t,std::uint32_t)> store;
};
template<class F> inline const F& requireNullNotification(const F& fn){
    if(!fn)throw std::invalid_argument("Null-attacker notification entered child unbound");
    return fn;
}
// Complete-to-return6CED90 E1 with null attacker. The cost query still occurs;
// its unused result does not license omitting the call. Other kinds/attackers
// are outside this recovered domain, not treated as generic destruction.
inline void notifyTechnoNullAttacker(TechnoNullNotificationActor a,const TechnoNullNotificationServices& s){
    const auto type=requireNullNotification(s.type80)();
    (void)requireNullNotification(s.cost84)(type,requireNullNotification(a.owner1B4)());
    if(a.onMap7D){
        const auto kind=requireNullNotification(s.kind2C)();
        if(kind!=1&&a.onMap7D){
            // Re-read the actual on-map and Tag fields after each synchronous
            // Tag call. That call may detach the Tag or mutate the actor.
            if(a.onMap7D){
                if(const auto tag=requireNullNotification(a.tag34)())
                    requireNullNotification(s.raiseTag)(tag,48,a.identity,s.emptyCell);
            }
            if(a.onMap7D){
                if(const auto tag=requireNullNotification(a.tag34)())
                    requireNullNotification(s.raiseTag)(tag,29,a.identity,s.emptyCell);
            }
        }
    }
    if(requireNullNotification(s.kind2C)()!=15)
        throw std::invalid_argument("Null-attacker notification requires ordinary E1 kind15");
    const auto house=a.owner1B4();
    auto& count=requireNullNotification(s.house5360)(house);
    ++count;if(s.store)s.store(house,0x5360,count);
    if(std::uint8_t(requireNullNotification(s.map6331A0)()))
        requireNullNotification(s.map6331E0)(0);
}
}
