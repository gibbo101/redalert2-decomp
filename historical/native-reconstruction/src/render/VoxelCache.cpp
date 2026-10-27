// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelCache.hpp"
#include <algorithm>
#include <bit>
namespace ra2 {
std::int32_t bodyVoxelKey(std::int32_t key,int frame) {
    return key==-1?-1:std::bit_cast<std::int32_t>((std::uint32_t(key)<<5)|(std::uint32_t(frame)&31));
}
std::int32_t turretVoxelKey(std::int32_t body,std::uint16_t heading,int offset) {
    if(body==-1)return -1;
    auto key=(std::uint32_t(body)&0xFFFFFFE0u)|unsigned(voxelHeading(heading));
    if(!offset)key&=0xFFFFFC1Fu;
    return std::bit_cast<std::int32_t>(key);
}
const RasterFrame* VoxelCache::find(std::int32_t key) {
    if(entries_.empty())return nullptr;
    if(hot_&&entries_[*hot_].key==key)return &entries_[*hot_].frame;
    if(!sorted_) {
        std::sort(entries_.begin(),entries_.end(),[](const Entry& a,const Entry& b){return a.key<b.key;});
        hot_.reset();sorted_=true;
    }
    const auto it=std::lower_bound(entries_.begin(),entries_.end(),key,[](const Entry& a,std::int32_t k){return a.key<k;});
    if(it==entries_.end()||it->key!=key)return nullptr;
    hot_=std::size_t(it-entries_.begin());return &it->frame;
}
VoxelResult VoxelCache::draw(VoxelRequest r,const std::function<RasterFrame()>& build) {
    if(!r.cacheAvailable||r.disableCache)r.key=-1;
    if(r.key!=-1)if(const auto* frame=find(r.key))return {frame,false,false};
    // Original validity checks occur after lookup: a warm hit survives missing
    // model pointers, while a miss with invalid VXL/HVA does not render.
    if(!r.modelAvailable)return {};
    auto frame=build();
    if(r.key==-1){direct_=std::move(frame);return {&direct_,true,true};}
    if(entries_.size()==capacity_) {
        capacity_=capacity_?capacity_*2:10;entries_.reserve(capacity_);hot_.reset();
    }
    entries_.push_back({r.key,std::move(frame)});sorted_=false;
    // Lit misses already draw, then snapshot/append. They do not recursively hit.
    return {&entries_.back().frame,true,false};
}
std::vector<std::int32_t> VoxelCache::keys() const {std::vector<std::int32_t> out;for(const auto& e:entries_)out.push_back(e.key);return out;}
}
