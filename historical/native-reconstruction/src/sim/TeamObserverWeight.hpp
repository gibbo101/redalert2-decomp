// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
namespace ra2 {
// Borrowed AI-trigger observer fields; construction/registry association is separate.
struct TeamObserverWeight {
    double& weightB8;
    const double& minimumC0;
    const double& maximumC8;
    std::int32_t& successes104;
    std::int32_t& trials108;
};
struct TeamObserverRules {
    const double& successB8;
    const double& failureC0;
    const double& failureCoefficientC8;
};
struct TeamObserverWeightServices {
    std::function<TeamObserverRules()> rules;
    // Optional post-store observation; offset, byte width, raw bits.
    std::function<void(std::uint32_t,std::uint32_t,std::uint64_t)> store;
};
// Complete41DFB0/41E070 arithmetic in the bounded finite, binary64-precision
// domain. Inherits the caller's rounding direction. Extended exponent, NaN and
// original caller FP initialization remain unjoined; unsupported inputs refuse.
void updateTeamObserverWeight(TeamObserverWeight observer,bool success,
                              const TeamObserverWeightServices& services);
}
