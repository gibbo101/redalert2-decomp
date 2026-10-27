// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowCache.hpp"
#include <algorithm>
namespace ra2 {
const RasterFrame* ShadowCache::find(std::int32_t key) {
    if(entries_.empty())return nullptr;
    if(hot_&&entries_[*hot_].key==key)return &entries_[*hot_].bitmap;
    if(!sorted_) {
        std::sort(entries_.begin(),entries_.end(),[](const Entry& a,const Entry& b){return a.key<b.key;});
        hot_.reset();sorted_=true;
    }
    const auto it=std::lower_bound(entries_.begin(),entries_.end(),key,[](const Entry& a,std::int32_t k){return a.key<k;});
    if(it==entries_.end()||it->key!=key)return nullptr;
    hot_=std::size_t(it-entries_.begin());return &it->bitmap;
}
ShadowResult ShadowCache::draw(ShadowRequest r,const std::function<RasterFrame()>& build) {
    if(r.actorSuppressed||r.noShadow||r.modelUnavailable)return {};
    if(!r.cacheAvailable||r.disableCache)r.key=-1;
    if(r.key==-1){direct_=build();return {&direct_,true,true};}
    if(const auto* bitmap=find(r.key))return {bitmap,false,false};
    if(!r.allowBuild)return {};
    auto bitmap=build();
    if(entries_.size()==capacity_) {
        capacity_=capacity_?capacity_*2:10;entries_.reserve(capacity_);hot_.reset();
    }
    entries_.push_back({r.key,std::move(bitmap)});sorted_=false;
    return {find(r.key),true,false}; // original miss snapshots, then recurses to hit
}
std::vector<std::int32_t> ShadowCache::keys() const {std::vector<std::int32_t> result;for(const auto& e:entries_)result.push_back(e.key);return result;}
}
