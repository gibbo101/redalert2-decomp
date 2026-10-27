// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamConstruction.hpp"
#include "sim/TeamObserverWeight.hpp"
#include <optional>
namespace ra2 {
// Ordinary AbstractType base. Unwritten padding/other fields have no synthetic
// initialization here. Text storage is owned, not a borrowed temporary buffer.
struct TeamObserverAbstractType {
    std::int32_t index10=-1;
    std::uint8_t flags14=0,byte20=0;
    std::uint32_t value18=0,value1C=0;
    std::array<std::uint8_t,25> identifier24{};
    std::uint8_t byte3D=0;
    const void* text60=nullptr;
    std::array<std::uint8_t,49> name64{};
};
struct TeamObserverType:TeamObserverAbstractType {
    std::int32_t condition98=0,valueA8=0;
    std::uint32_t value9C=0,valueA0=0,valueAC=0,valueB0=0;
    std::uint8_t byteA4=0;
    double weightB8=0,minimumC0=0,maximumC8=0;
    std::array<std::uint8_t,5> flagsD0{};
    const void* objectD8=nullptr;
    const void* teamDC=nullptr;
    const void* teamE0=nullptr;
    std::array<std::uint32_t,8> conditionsE4{};
    std::int32_t successes104=0,trials108=0;
    TeamObserverWeight weight(){return {weightB8,minimumC0,maximumC8,successes104,trials108};}
};
using TeamObserverConstructionStore=std::function<void(const void*,std::int64_t,std::uint32_t,std::uint64_t,const void*)>;
struct TeamObserverConstructionServices {
    TeamConstructionRegistry& abstractTypesA40928;
    TeamConstructionRegistry& observersA3D260;
    const void* emptyText;
    // Original null-name formatting is an explicit CRT service, not a native
    // pointer truncated into a32-bit generated identifier.
    std::function<std::array<std::uint8_t,24>(const void*)> formatNullName;
    // Same base phases2/1 as constructTeamAbstractBase;3=AbstractType,0=observer.
    std::function<void(const void*,unsigned)> projectInterfaces;
    TeamObserverConstructionStore store;
};
void constructTeamObserverType(TeamObserverType& record,
        std::optional<std::span<const std::uint8_t>> identifier,
        const TeamObserverConstructionServices& services);
void setTeamObserverPrimaryType(TeamObserverType& record,const void* type,
        const TeamObserverConstructionStore& store={});
// Complete4D2D90, with typed projection and explicit CRT atexit service.
void initializeTeamObserverRegistry(TeamConstructionRegistry& registry,std::uint8_t& valid12,
        const std::function<void()>& projectInterfaces,
        const std::function<void()>& registerExit,
        const TeamObserverConstructionStore& store={});
}
