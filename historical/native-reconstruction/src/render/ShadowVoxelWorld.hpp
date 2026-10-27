// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/ShadowCache.hpp"
#include "render/FootVoxelStaging.hpp"
#include "render/CachedVoxelShadow.hpp"
#include "render/VoxelShadow.hpp"
namespace ra2 {
struct ShadowVoxelWorldInputs {
    ShadowRequest cache;
    Matrix pose=voxelIdentity();
    PixelPoint point{};
    PixelRect clip{};
    ShadowStencil stencil;
};
enum class ShadowVoxelDrawKind {Skipped,Fresh,Cached,Bypass};
struct ShadowVoxelDrawResult {
    ShadowVoxelDrawKind kind=ShadowVoxelDrawKind::Skipped;
    std::optional<RasterFrame> raster;
};
// Complete successful ordinary shadow cache/render/snapshot/cached-world join.
// One loaded section, required fresh HVA, identity global transform, no half
// scale, healthy Unit/world/gradient 2/zero Z-shape. Pool/planes/actor/converter
// ownership remain supplied; allocation/pool failure and eviction are refused.
// This helper is not yet used by the runtime.
ShadowVoxelDrawResult drawOrdinaryShadowVoxelToWorld(const RasterData&,const RenderData&,
    const VoxelModel*,const Animation*,const ShadowVoxelWorldInputs&,
    VoxelSnapshotIndex*,VoxelSnapshotPool&,const CachedVoxelPartServices&,
    int width,int height,std::vector<std::uint16_t>& colors,
    const std::vector<std::uint16_t>& depth,PixelRect& dirty);
}
