// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowKeys.hpp"
#include "render/VoxelRaster.hpp"
#include <bit>
namespace ra2 {
std::int32_t flatUnitShadowKey(std::int32_t bodyKey,std::uint16_t heading,int y,int speedType,bool balloon) {
    const auto seed=(std::uint32_t(bodyKey)>>5)&1023u;
    const auto pointBits=(std::uint32_t(y)-16u)&31u;
    const auto input=balloon||speedType==1||speedType==2?seed:(seed<<5)|pointBits;
    return std::bit_cast<std::int32_t>((input<<11)|unsigned(voxelHeading(heading)));
}
std::optional<PixelPoint> footShadowPlacement(PixelPoint at,PixelPoint offset,bool has,std::uint8_t predicate) {
    if(!has||predicate!=1)return std::nullopt;
    return PixelPoint{std::bit_cast<std::int32_t>(std::uint32_t(at.x)+std::uint32_t(offset.x)),
                      std::bit_cast<std::int32_t>(std::uint32_t(at.y)+std::uint32_t(offset.y))};
}
}
