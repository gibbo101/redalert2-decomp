// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
namespace ra2 {
struct RadarMapNotificationView {
    const std::int32_t& mode14AC;
    const std::int32_t& mode14A8;
    std::uint8_t& dirty14D5;
    std::uint8_t& full14D6;
};
inline bool radarMapNotificationMode(const RadarMapNotificationView& m){
    // Complete6331A0. Both fields are signed words; equality is exact.
    return m.mode14AC==2&&m.mode14A8==1;
}
inline void requestRadarMapNotification(RadarMapNotificationView m,std::uint32_t argument,
        const std::function<void(std::int64_t,std::uint32_t)>& store={}){
    // Complete6331E0. Read the old full byte before writing dirty. No saturation
    // or preservation of the old nonzero byte: the new full byte is0 or1.
    const auto old=m.full14D6;
    m.dirty14D5=1;if(store)store(0x14d5,1);
    m.full14D6=std::uint8_t(old||std::uint8_t(argument));
    if(store)store(0x14d6,m.full14D6);
}
}
