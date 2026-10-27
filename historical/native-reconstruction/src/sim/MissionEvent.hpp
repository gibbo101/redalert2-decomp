// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <bit>

namespace ra2 {
struct MissionEventTimer {std::int32_t start=-1,remaining=0;};
struct MissionEventServices {
    // Actual late House lookup is retained for pulse events, even though these
    // two kinds do not inspect its result. Initial registry setup is supplied.
    std::function<void(std::int32_t countryIndex)> resolveHouse;
};
// Bounded complete base6E6050 paths: event4 discovery,33 selection,13 timer,
// 47 scenario seconds. Callers, pulse production, timers and scheduling remain
// separate dependencies. Unsupported kinds throw rather than simulate success.
inline bool missionEventOccurred(std::int32_t kind,std::int32_t value,
        std::int32_t pulse,std::uint8_t suppressPulse,std::int32_t frame,
        const MissionEventTimer* timer,const MissionEventServices& services) {
    if(kind==47)return value<=frame/15; // Signed truncation, not floor division.
    if(kind==13) {
        if(!timer)throw std::invalid_argument("Mission timer required");
        auto remaining=timer->remaining;
        if(timer->start!=-1) {
            const auto elapsed=std::bit_cast<std::int32_t>(std::uint32_t(frame)-std::uint32_t(timer->start));
            if(elapsed>=remaining)return true;
            remaining=std::bit_cast<std::int32_t>(std::uint32_t(remaining)-std::uint32_t(elapsed));
        }
        return remaining==0;
    }
    // Complete6E6050 event7 pulse-mismatch return. Matching7 effects remain
    // unjoined; Tag48/29 must still traverse the actual registry/event path.
    if(kind==7&&pulse!=7)return false;
    if(kind!=4&&kind!=33)throw std::invalid_argument("Mission event kind requires recovery");
    if(pulse!=kind||suppressPulse)return false;
    if(!services.resolveHouse)throw std::invalid_argument("Mission event House registry required");
    services.resolveHouse(value);
    return true;
}
}
