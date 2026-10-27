// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/ActorGroundState.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
// Complete5D4810. The floor sees a snapshot; Z and bridge remain live afterward.
inline std::int32_t relativeObjectGroundHeight(const ActorGroundState& actor,
        const std::int32_t& bridgeHeight,const std::function<std::int32_t(Coord)>& floor){
    if(!floor)throw std::invalid_argument("Object relative height floor unbound");
    const auto sampled=floor(actor.position);
    auto height=std::uint32_t(actor.position.z)-std::uint32_t(sampled);
    if(actor.bridge79)height-=std::uint32_t(bridgeHeight);
    return std::bit_cast<std::int32_t>(height);
}
// Complete5D5410, including the stock Infantry4CCE70 tail jump. Only AL is
// meaningful. The global threshold is loaded after the virtual height query.
inline bool objectAboveGround(const std::uint8_t& marked74,const std::int32_t& levelHeight,
        const std::function<std::int32_t()>& height1B0){
    if(!marked74)return false;
    if(!height1B0)throw std::invalid_argument("Object ground query height unbound");
    const auto height=height1B0();
    const auto threshold=std::bit_cast<std::int32_t>(std::uint32_t(levelHeight)*2u);
    return height>=threshold;
}
}
