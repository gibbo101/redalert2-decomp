// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/LandCharacteristics.hpp"
#include <bit>
#include <stdexcept>
#if defined(__clang__)
#pragma STDC FENV_ACCESS ON
#endif

namespace ra2 {
void loadLandCharacteristics(std::array<LandCharacteristic,12>& table,
    const LandCharacteristicServices& services) {
    if(!services.hasSection||!services.readSpeed||!services.readBuildable)
        throw std::invalid_argument("Land characteristics require INI services");
    for(unsigned section=0;section<table.size();++section) {
        if(!services.hasSection(section))continue;
        auto& row=table[section];
        const auto store=[&](LandSpeed key,double value) {
            // The x87 store is observable separately from the double comparison.
            const volatile float stored=static_cast<float>(value);
            const auto field=static_cast<unsigned>(key);
            row.speed[field]=stored;
            if(services.store)services.store(section,field,std::bit_cast<std::uint32_t>(row.speed[field]));
        };
        const auto read=[&](LandSpeed key) {
            const double first=services.readSpeed(section,key,1.0);
            // Unordered takes the same branch as less-than. The second result
            // is stored without a further comparison; do not cache the first.
            const double value=!(first>=1.0)?services.readSpeed(section,key,1.0):1.0;
            store(key,value);
        };
        read(LandSpeed::Hover);
        read(LandSpeed::Foot);
        read(LandSpeed::Track);
        read(LandSpeed::Wheel);
        store(LandSpeed::Winged,1.0);
        read(LandSpeed::Float);
        read(LandSpeed::Amphibious);
        read(LandSpeed::FloatBeach);
        row.buildable=services.readBuildable(section,0);
        if(services.store)services.store(section,8,row.buildable);
    }
}
}
