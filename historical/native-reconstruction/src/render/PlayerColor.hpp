// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/RasterData.hpp"
namespace ra2 {
Color originalHsvToRgb(HsvColor);
// ColorScheme's palette-copy/remap prefix: replace only indices 16..31.
Palette playerPalette(const RasterData&,const Palette&,HsvColor);
}
