// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string_view>

namespace ra2 {
struct MissionTextRequest {
    std::int32_t leading0=0,leading1=0;
    std::string_view text;
    std::int32_t color=0,style=0x4046;
    std::uint32_t duration=0;
    std::int32_t trailing=0;
};
struct MissionTextServices {
    // Base6715D0 color-table lookup, base6F9EC0 CSF lookup and base5B4DA0
    // message-list insertion remain distinct named children.
    std::function<std::int32_t(std::int32_t)> color;
    std::function<std::string_view(std::string_view)> localize;
    std::function<void(const MissionTextRequest&)> display;
};
inline std::uint32_t missionTextDuration(double delay) {
    OriginalRounding rounding;
    volatile double scaled=delay*900.0;
    constexpr double limit=9223372036854775808.0;
    if(!std::isfinite(scaled)||scaled<-limit||scaled>=limit)
        throw std::invalid_argument("Mission text duration outside bounded x87 conversion");
    return std::uint32_t(std::uint64_t(std::int64_t(scaled)));
}
// Complete base action11 branch6AE2FF..6AE381 around its three named children.
// The color child is called even for an empty inline key. Rules delay and the
// localization/display children are read only after a nonempty key is observed.
inline bool executeMissionTextAction(std::string_view key,std::uint8_t alternateColor,
        double messageDelay,const MissionTextServices& services) {
    if(!services.color)throw std::invalid_argument("Mission text color service required");
    const auto color=services.color(alternateColor?2:1);
    if(key.empty())return true;
    if(!services.localize||!services.display)
        throw std::invalid_argument("Mission text localization/display services required");
    const auto duration=missionTextDuration(messageDelay);
    const auto text=services.localize(key);
    services.display({0,0,text,color,0x4046,duration,0});
    return true;
}
}
