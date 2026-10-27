// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
struct MissionAllyServices {
    // Base4ED760 House lookup and base4E5660 House::MakeAlly remain named
    // children. Null identities are forwarded exactly by the dispatcher.
    std::function<const void*(std::int32_t)> resolveHouse;
    std::function<void(const void*,const void*,std::uint8_t)> makeAlly;
};

// Complete base action37 branch6AE382..6AE3BE around its named House children.
inline bool executeMissionAllyAction(std::int32_t houseTypeIndex,const void* currentHouse,
                                     const MissionAllyServices& services) {
    if(houseTypeIndex==-1)return true;
    if(!services.resolveHouse||!services.makeAlly)
        throw std::invalid_argument("Mission ally House services required");
    const auto* resolved=services.resolveHouse(houseTypeIndex);
    services.makeAlly(currentHouse,resolved,0);
    services.makeAlly(resolved,currentHouse,0);
    return true;
}
}
