// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitSurfaceDraw.hpp"
namespace ra2 {
struct UnitSurfaceBridgeServices {
    std::function<std::uint8_t()> flag100;
    std::function<int()> predicate0;
    std::function<bool()> firstContact;
    std::function<int()> contactKind;
    std::function<std::uint8_t()> contactType1357;
};
// Immutable contact/input records. Contact storage/construction is supplied.
void drawBridgeUnitSurface(const UnitSurfaceInputs&,std::uint32_t actor494,
                           const UnitSurfaceBridgeServices&,const UnitSurfaceServices&);
// Original descriptor 0, used by the upper portion of this wrapper. Palette,
// alpha and depth planes have the same bounded domain as blitUnit; depth is read.
BlitStats blitUnitTopGradient(const Bytes& source,int sourceWidth,int sourceHeight,
    PixelRect sourceRect,PixelPoint destination,PixelRect clip,int zAdjust,int brightness,
    const std::vector<Palette16>& palettes,int width,int height,
    std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,
    const std::vector<std::uint16_t>& alpha);
}
