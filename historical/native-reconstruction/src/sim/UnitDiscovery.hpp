// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseIndexAlliance.hpp"
#include "sim/HouseInfantryAccounting.hpp"
#include "sim/HouseCountryRegistration.hpp"
#include <cstdint>
#include <array>
#include <functional>
#include <map>
namespace ra2 {
struct UnitDiscoveryHouse {
    std::uint8_t human134=0,control135=0,discovered13c=0,field13d=0,field5668=0,field5669=0;
    // Building448FE0 writes these same House owners after common discovery.
    std::int32_t buildingType1b4=-1;
    std::uint8_t building18d=0,building144=0;
    // One production House owns these fields alongside its discovery flags.
    // Standalone discovery fixtures need no index/alliance initialization.
    HouseIndexAlliance indexAlliance;
    std::uint32_t notification5360=0; // Supplied startup; recovered null-attacker increment.
    HouseCountryType* countryType34=nullptr; // Supplied association; shared owned Type.
    std::uint32_t transferValue5418=0;
    std::array<std::uint32_t,32> transfersFrom5310{};
    std::int32_t lastCountry53B8=-1; // Ledger startup supplied, recovered mutations.
    HouseInfantryAccountingState infantryAccounting; // Supplied map startup; recovered mutation kernels.
    // Shared House fields; color/palette startup remains supplied, not recovered.
    std::array<std::uint8_t,3> radarColor55e9{};
    std::int32_t radarScheme15f40=0;
};
struct UnitDiscoveryActor {
    std::uint8_t field372=0,current373=0,other374=0,queuedA4=0;
    int owner=0,mission98=-1,queuedA0=-1;
    bool hasTag=false;
};
// Read-only logical observers: actor subject 0; House subject is id+1.
using UnitDiscoveryStore=std::function<void(int,int,std::uint32_t)>;
using UnitDiscoveryTrace=std::function<void(char,int)>;
struct UnitDiscoveryWorld {
    std::map<int,UnitDiscoveryHouse> houses;
    int currentHouse=-1,mode=0,loading=0,tagContext=0;
    // Optional Tag event effects remain a supplied service; null tags need none.
    std::function<void(int)> tagEvent;
    UnitDiscoveryStore store;
    UnitDiscoveryTrace trace;
};
std::uint8_t discoveryHouseControlled(const UnitDiscoveryHouse&,int mode);
int unitDiscoveryMission(const UnitDiscoveryActor&);
// Actual QueueMission with its second argument zero, as used by discovery.
void queueUnitDiscoveryMission(UnitDiscoveryActor&,int,const UnitDiscoveryStore& = {});
// Complete Unit-kind Techno notification and Object/House/Mission children.
// Logical house ids preserve null (-1) and pointer equality; construction and
// initial globals/house/actor associations remain supplied.
bool discoverUnit(UnitDiscoveryActor&,int discoverer,UnitDiscoveryWorld&);
}
