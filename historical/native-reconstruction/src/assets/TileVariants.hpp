// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/OriginalRandom.hpp"
#include <functional>
namespace ra2 {
struct TileVariantTables {
    std::array<int,16> small{};
    std::array<std::array<int,2>,8> neighbors{};
};
struct TileVariantCache {
    std::uint8_t initialized=0;
    std::array<int,64> large{};
};
struct TileVariantImage {int columns=0,rows=0;};
// Actual Cell variant selector with resident/null image and supplied tables/RNG.
// Returns the raw pattern value; the parent performs remaining-count reduction.
// Initialization happens even for small-count and missing-image decisions.
int selectTileVariant(TileVariantCache&,const TileVariantTables&,
    std::int16_t x,std::int16_t y,std::uint8_t sub,int variants,
    const TileVariantImage*,const std::function<std::uint32_t()>& next);
}
