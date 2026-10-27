// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/OriginalRandom.hpp"
#include <bit>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace ra2 {
// Read-only observation after each raw draw, before masking/rejection. A disabled
// generator still has a draw attempt, but its state does not advance.
using OriginalRandomRangeObserver =
    std::function<void(std::uint32_t,const OriginalRandomState&)>;

// Complete terminating signed-range policy on supplied generator state. Seeding
// and scenario/global ownership are separate. This entry is not runtime wiring.
inline std::int32_t rangedOriginalRandom(OriginalRandomState& state,
    std::int32_t first,std::int32_t second,
    const OriginalRandomRangeObserver& observe={},std::size_t maxDraws=4000000) {
    if(first==second)return first;
    if(first>second)std::swap(first,second);
    const auto low=std::bit_cast<std::uint32_t>(first);
    const auto width=std::bit_cast<std::uint32_t>(second)-low;
    // Wider spans enter the original signed rejection loop with a zero mask.
    // Refuse that unsupported nonterminating profile, rather than repair it.
    if(width>=0x80000000u)
        throw std::invalid_argument("Random range exceeds terminating original span");
    // Preserve the original signed (width+1)<=width branch, including its
    // surprising out-of-range result and absence of generator reads/draws.
    if(width==0x7fffffffu)
        return std::bit_cast<std::int32_t>(low+0x80000000u);
    const auto mask=(std::uint32_t(1)<<std::bit_width(width))-1;
    for(std::size_t draw=0;draw<maxDraws;++draw){
        const auto raw=nextOriginalRandom(state);
        if(observe)observe(raw,state);
        const auto candidate=raw&mask;
        if(candidate<=width)return std::bit_cast<std::int32_t>(low+candidate);
    }
    // Research/host liveness guard, not an original return or rollback. Any
    // already consumed draws remain consumed; use a clone when atomicity matters.
    throw std::runtime_error("Original random range exhausted host draw bound");
}
}
