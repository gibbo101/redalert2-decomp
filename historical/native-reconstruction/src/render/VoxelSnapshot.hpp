// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitStaging.hpp"
#include <functional>
#include <optional>
#include <span>
namespace ra2 {
// The original encoder reads two bytes beyond the declared row. Callers must
// supply readable padding (including actual following surface pixels).
Bytes encodeVoxelRow(std::span<const std::uint8_t> source,int width);
Bytes decodeVoxelRow(std::span<const std::uint8_t> encoded);

// Bounded original append protocol, with caller-owned native storage. The +8
// header field is a pool-relative offset instead of an original process pointer.
// A failed append retains its header and any earlier completed rows/cursor.
std::optional<std::size_t> appendVoxelSnapshot(Bytes& pool,std::size_t& cursor,
    std::span<const std::uint8_t> source,int width,int height,const std::array<int,6>& crop);

// Complete ordinary cached Unit part wrapper and byte compressed-row copy.
// Unit kind 1/staging/flags zero (or cleared bit 0x10), no depth/alpha surfaces.
// Actor getters, initialized remap and native surface/pool ownership are supplied.
struct CachedVoxelPartServices {
    std::function<void()> kind;
    std::function<void(std::uint32_t)> selectBlitter;
    std::function<int()> value2C4,value2C0;
};
void drawOrdinaryCachedVoxelPart(const Bytes& pool,std::size_t snapshot,PixelPoint,
    PixelRect clip,std::uint32_t flags,int brightness,const CachedVoxelPartServices&,
    const IndexRemap&,Bytes& staging,PixelRect& dirty);
}
