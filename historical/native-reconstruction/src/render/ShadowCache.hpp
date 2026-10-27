// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
#include <functional>
#include <optional>
namespace ra2 {
struct ShadowRequest {
    std::int32_t key=-1;
    bool actorSuppressed=false,noShadow=false,modelUnavailable=false;
    bool cacheAvailable=true,disableCache=false,allowBuild=true;
};
struct ShadowResult {const RasterFrame* frame=nullptr;bool built=false,bypass=false;};
// Successful-allocation wrapper/index decisions only. Vector storage is a host
// representation; original compressed pool, eviction and failure recovery excluded.
class ShadowCache {
    struct Entry {std::int32_t key;RasterFrame bitmap;};
    std::vector<Entry> entries_;
    std::optional<std::size_t> hot_;
    bool sorted_=false;
    std::size_t capacity_=0;
    RasterFrame direct_;
    const RasterFrame* find(std::int32_t key);
public:
    ShadowResult draw(ShadowRequest,const std::function<RasterFrame()>& build);
    std::size_t size() const{return entries_.size();}
    std::size_t capacity() const{return capacity_;}
    bool sorted() const{return sorted_;}
    std::optional<std::int32_t> hotKey() const{return hot_?std::optional(entries_[*hot_].key):std::nullopt;}
    std::vector<std::int32_t> keys() const;
};
}
