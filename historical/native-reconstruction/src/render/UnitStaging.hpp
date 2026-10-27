// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
namespace ra2 {
using IndexRemap = std::array<std::uint8_t,256>;
// Single-shade original Convert: weighted Manhattan distance, first tie wins.
IndexRemap stagingRemap(const Palette& source,const Palette& destination);
PixelRect stagingUnion(PixelRect current,PixelRect next);
// Transparent source zero; a nonzero source may remap to opaque zero.
void blitIndexed(const Bytes&,int sourceWidth,int sourceHeight,PixelRect,PixelPoint,PixelRect,
                 const IndexRemap&,int width,int height,Bytes& destination);
struct UnitStaging {
    Bytes pixels=Bytes(256*256);
    PixelRect dirty{};
    void clear();
    void add(const RasterFrame&,const IndexRemap&);
};
}
