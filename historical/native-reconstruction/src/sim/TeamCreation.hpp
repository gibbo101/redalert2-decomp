// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string_view>
namespace ra2 {
struct TeamTypeCreationView {
    const void* identity;
    const void* const& houseC0;
    const std::int32_t& maximumB8;
    const std::int32_t& countD4;
    std::string_view name64;
};
struct TeamCreationServices {
    const std::uint32_t& loading;
    const std::int32_t& sessionMode;
    // Original diagnostic logger4068F0 remains a platform service.
    std::function<void()> logBegin;
    std::function<void(std::string_view)> logName;
    std::function<std::int32_t(const void*,const void*)> houseCount4f35f0;
    std::function<void*(std::uint32_t)> allocate;
    std::function<const void*(void*,const void*,const void*,std::int32_t)> construct6b7430;
};
// Complete6BEC80. Actual Team construction/member placement is a separate child;
// successful allocation alone must never be treated as creating four infantry.
inline const void* createTeamFromType(TeamTypeCreationView type,const void* explicitHouse,
        const TeamCreationServices& s){
    if(!s.logBegin)throw std::invalid_argument("Team creation diagnostic service unbound");
    s.logBegin();
    const auto* house=explicitHouse?explicitHouse:type.houseC0;
    if(!s.loading){
        const auto maximum=type.maximumB8;
        if(maximum>=0){
            if(!s.sessionMode){if(type.countD4>=maximum)return nullptr;}
            else{
                if(!s.houseCount4f35f0)throw std::invalid_argument("Team creation House count unbound");
                const auto count=s.houseCount4f35f0(house,type.identity);
                if(count>=type.maximumB8)return nullptr;
            }
        }
    }
    if(!s.logName||!s.allocate)throw std::invalid_argument("Team creation allocation services unbound");
    s.logName(type.name64);
    auto* record=s.allocate(156);
    if(!record)return nullptr;
    if(!s.construct6b7430)throw std::invalid_argument("Team constructor6B7430 unbound");
    return s.construct6b7430(record,type.identity,house,0);
}
}
