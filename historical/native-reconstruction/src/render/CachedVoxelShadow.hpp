// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelSnapshot.hpp"
namespace ra2 {
// Healthy Unit, world surface, flags 0x2001, gradient 2 and zero Z-shape.
// Native pool/planes/converter ownership and actor getters are supplied.
// This is a separate, not-yet-integrated compressed shadow child.
void drawOrdinaryCachedVoxelShadow(const Bytes& pool,std::size_t snapshot,
    PixelPoint,PixelRect,const CachedVoxelPartServices&,int width,int height,
    std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth,
    PixelRect& dirty);
}
