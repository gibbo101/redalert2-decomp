// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTypedTagExpiration.hpp"
namespace ra2 {
// A real authored map Tag identity retained by passive Foot references. This
// host owns its supplied metadata/count, but has not constructed its Trigger
// chain. Team expiration never dereferences that chain or changes Tag counts.
// It must not be used to execute Tag pulses/destruction until those owners join.
struct BootCampFootTagOwner {
    std::int32_t persistence=0,instances=0;std::uint8_t executing=0;
    MissionTagType type{persistence};MissionTagType* typePointer=&type;
    MissionTagTrigger* first=nullptr;
    MissionTagState view{typePointer,first,instances,executing};
    BootCampFootTagOwner()=default;
    BootCampFootTagOwner(const BootCampFootTagOwner&)=delete;
    BootCampFootTagOwner& operator=(const BootCampFootTagOwner&)=delete;
};
// Supplied bounded startup for fields not previously consumed by this host.
// Existing movement/mission/House/Tag/target/radio fields are borrowed elsewhere.
// Values only: no callbacks/spans survive cloning. Each vector keeps its tail.
struct BootCampFootExpirationState {
    const void* headFC=nullptr;const void* link108=nullptr;const void* link20C=nullptr;
    const void* control230=nullptr;const void* service238=nullptr;const void* link23C=nullptr;
    std::array<const void*,7> links260{};
    const void* link27C=nullptr;const void* link384=nullptr;const void* link3F8=nullptr;
    std::int32_t timer148=-1,timer14C=0,timer150=0;
    std::uint8_t byte5BA=0;
    const void* slave580=nullptr;const void* destination4BC=nullptr;const void* cell4B8=nullptr;
    // Derived passive Type/5AC fields are distinct from Infantry's numeric5AC.
    const void* passiveType5A8=nullptr;const void* derivedType=nullptr;const void* derived5AC=nullptr;
    std::array<std::int32_t,3> counts{}; //390,3A8,3C0 only; Foot counts are borrowed.
    std::array<std::array<const void*,8>,5> backing{}; //390,3A8,3C0,4A0,47C.
    template<class F>void remapPointers(F&& map){
        for(auto* p:std::array{&headFC,&link108,&link20C,&control230,&service238,&link23C,&link27C,&link384,&link3F8,&slave580,&destination4BC,&cell4B8,&passiveType5A8,&derivedType,&derived5AC})*p=map(*p);
        for(auto& p:links260)p=map(p);for(auto& b:backing)for(auto& p:b)p=map(p);
    }
    bool operator==(const BootCampFootExpirationState&)const=default;
};
}
