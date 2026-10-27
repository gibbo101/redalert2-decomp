// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <span>
namespace ra2 {
struct ShadowStencil {
    std::span<const std::uint8_t> pixels;
    int width=0,height=0;
    PixelPoint origin{}; // original plotter's supplied stencil X/Y
};
Vec3 voxelShadowOffset(const RasterData&,float lightAngle);
// Bounded single-section shadow: original lower-corner projection, occupied
// columns, two-pixel writes and optional zero/nonzero surface stencil.
RasterFrame rasterVoxelShadow(const VoxelSection&,const Matrix& model,const Matrix& camera,Vec3 offset,ShadowStencil stencil={});
// Original 0x2001 shadow Z-read blit, flat gradient; leaves depth unchanged.
BlitStats blitShadow(const Bytes&,int sourceWidth,int sourceHeight,PixelRect,PixelPoint,PixelRect,int zAdjust,
                    int width,int height,std::vector<std::uint16_t>& colors,const std::vector<std::uint16_t>& depth);
}
