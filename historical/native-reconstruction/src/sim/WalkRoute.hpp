// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/FootDestination.hpp"
namespace ra2 {
// The same Foot timers/target and Infantry state consumed by commands. The
// caller owns no route copy; the named4C3000 service writes the borrowed queue.
struct WalkRouteContext {
    FootDestinationTimerView retry530;
    std::int32_t& counter53c;
    std::int32_t& state5ac;
    const void* const& target494;
    const std::uint8_t& jumpJetB44;
    const double& interval13c8;
    std::int32_t temporaryPadding=0; // original uninitialized caller local
    std::function<std::int32_t()> clock;
    std::function<std::uint8_t(TerrainCellPoint,int,int)> findRoute;
};
}
