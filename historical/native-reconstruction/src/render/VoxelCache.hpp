// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
#include <functional>
#include <optional>
namespace ra2 {
std::int32_t bodyVoxelKey(std::int32_t locomotorKey,int frame);
std::int32_t turretVoxelKey(std::int32_t bodyKey,std::uint16_t turretHeading,int turretOffset);
struct VoxelRequest {std::int32_t key=-1;bool cacheAvailable=true,disableCache=false,modelAvailable=true;};
struct VoxelResult {const RasterFrame* frame=nullptr;bool built=false,bypass=false;};
// Successful lit wrapper/index decisions. Logical frames replace compressed
// snapshots; actor sharing, pool lifetime/eviction and failures remain open.
class VoxelCache {
    struct Entry {std::int32_t key;RasterFrame frame;};
    std::vector<Entry> entries_;
    std::optional<std::size_t> hot_;
    bool sorted_=false;
    std::size_t capacity_=0;
    RasterFrame direct_;
    const RasterFrame* find(std::int32_t);
public:
    VoxelResult draw(VoxelRequest,const std::function<RasterFrame()>& build);
    std::size_t size() const{return entries_.size();}
    std::size_t capacity() const{return capacity_;}
    bool sorted() const{return sorted_;}
    std::optional<std::int32_t> hotKey() const{return hot_?std::optional(entries_[*hot_].key):std::nullopt;}
    std::vector<std::int32_t> keys() const;
};
}
