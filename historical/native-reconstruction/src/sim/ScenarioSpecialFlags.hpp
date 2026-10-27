// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string_view>

namespace ra2 {
struct ScenarioFlagRegistryServices {
    // Supplied platform boundary: HKLM, SOFTWARE\\Westwood\\Red Alert 2\\,
    // options0/accessF003F; EscapeMovies, null reserved, four-byte data; Close.
    std::function<std::int32_t(std::uint32_t&)> open;
    std::function<std::int32_t(std::uint32_t,std::uint32_t&,std::uint32_t&)> query;
    std::function<void(std::uint32_t)> close;
};
// Complete68B320. No host registry access: all imported services are explicit.
inline void initializeScenarioSpecialFlags(std::uint32_t& flags,
        const ScenarioFlagRegistryServices& services) {
    if(!services.open)throw std::invalid_argument("Missing scenario registry open service");
    flags&=0xfffffff8u;
    std::uint32_t handle=0,escape=0;
    if(services.open(handle)==0) {
        if(!services.query||!services.close)throw std::invalid_argument("Missing entered scenario registry service");
        std::uint32_t type=0,data=0;
        if(services.query(handle,type,data)==0&&type==4)escape=data&1u;
        services.close(handle);
    }
    flags=(flags&0xfff88087u)|0x8080u|(escape<<3);
}
struct ScenarioSpecialFlagKey {std::string_view key;unsigned bit;};
inline constexpr std::array<ScenarioSpecialFlagKey,13> scenarioSpecialFlagKeys{{
    {"TiberiumExplosive",14},{"MCVDeploy",8},{"InitialVeteran",9},
    {"IonStorms",17},{"Meteorites",16},{"Visceroids",18},
    {"TiberiumGrows",6},{"TiberiumSpreads",7},{"DestroyableBridges",15},
    {"FixedAlliance",10},{"FogOfWar",12},{"Inert",5},{"HarvesterImmune",11}}};
using ScenarioSpecialFlagReader=std::function<std::uint32_t(std::string_view,std::uint32_t)>;
// Complete68B5A0. Read raw defaults (AND AL,1), returned low bit, and live flags
// after each child. Session/override are reread after the first six children.
inline std::uint32_t readScenarioSpecialFlags(std::uint32_t& flags,
        const std::int32_t& session,const std::uint8_t& overrideMode,
        const ScenarioSpecialFlagReader& read) {
    if(!read)throw std::invalid_argument("Missing scenario flag INI reader");
    for(std::size_t i=0;i<scenarioSpecialFlagKeys.size();++i) {
        if(i==6&&session!=0&&!overrideMode)break;
        const auto& entry=scenarioSpecialFlagKeys[i];
        const auto fallback=(flags>>entry.bit)&0xffffff01u;
        const auto result=read(entry.key,fallback);
        flags=(flags&~(1u<<entry.bit))|((result&1u)<<entry.bit);
    }
    return flags;
}
}
