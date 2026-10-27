// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FootLitDraw.hpp"
#include "render/VoxelPartStaging.hpp"
#include "render/VoxelSnapshot.hpp"
namespace ra2 {
// Native ownership is supplied. Entries retain the original successful signed
// sort/hot/append protocol, but point into the caller's native snapshot pool.
class VoxelSnapshotIndex {
    struct Entry {std::int32_t key;std::size_t snapshot;};
    std::vector<Entry> entries_;
    std::optional<std::size_t> hot_;
    std::size_t capacity_=0;
    bool sorted_=false;
public:
    std::optional<std::size_t> find(std::int32_t);
    void append(std::int32_t,std::size_t);
    std::size_t size() const{return entries_.size();}
    std::size_t capacity() const{return capacity_;}
    bool sorted() const{return sorted_;}
    std::optional<std::int32_t> hotKey() const{return hot_?std::optional(entries_[*hot_].key):std::nullopt;}
    std::vector<std::int32_t> keys() const;
};
struct VoxelSnapshotPool {Bytes bytes;std::size_t cursor=0;};
enum class FootVoxelDrawKind {Skipped,Fresh,Cached,Bypass};
struct FootVoxelDrawResult {FootVoxelDrawKind kind=FootVoxelDrawKind::Skipped;std::optional<RasterFrame> raster;};
// Complete ordinary Foot/Drive -> Techno cache -> raster/staging/snapshot or
// cached staging join. Healthy Unit-kind-1/staging, inactive status, flags 0x2800,
// zero actor flags and false house predicate only. The model/HVA validity check
// follows cache lookup; a warm hit may have missing current model records.
// A null index or DisableVoxelCache bypasses snapshots. Pool exhaustion/eviction,
// allocation failure and alternate actor/status/blitter branches are refused.
FootVoxelDrawResult drawOrdinaryFootVoxelPart(const RasterData&,const RenderData&,
    const VoxelModel*,const Animation*,const VoxelPalette&,const FootLitRequest&,
    bool hasDrive,bool disableCache,VoxelSnapshotIndex*,VoxelSnapshotPool&,
    const StagedVoxelPartServices&,const IndexRemap&,UnitStaging&);
// Direct Techno boundary for callers that have already executed Foot forwarding.
FootVoxelDrawResult drawOrdinaryTechnoVoxelPart(const RasterData&,const RenderData&,
    const VoxelModel*,const Animation*,const VoxelPalette&,const FootLitRequest&,
    bool disableCache,VoxelSnapshotIndex*,VoxelSnapshotPool&,
    const StagedVoxelPartServices&,const IndexRemap&,UnitStaging&);
}
