// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <optional>
namespace ra2 {
// Ordinary Unit seed followed by flat Drive Shadow_Matrix key packing.
// Ramps, airborne/alternate types, tilt/rocking and timer invalidation excluded.
std::int32_t flatUnitShadowKey(std::int32_t bodyKey,std::uint16_t heading,int shadowPointY=0,int speedType=1,bool balloonHover=false);
// Complete Foot dispatch's locomotor gate and wrapped location adjustment.
std::optional<PixelPoint> footShadowPlacement(PixelPoint location,PixelPoint offset,bool hasLocomotor,std::uint8_t shadowPredicate);
}
