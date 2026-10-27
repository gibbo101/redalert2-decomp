// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapOverlay.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include <optional>

namespace ra2 {
// Selected resource fields. Base type state and debris/vector/heap services are
// explicit; this is native storage, not the original object's ABI or ownership.
struct ResourceDebrisInputs {
    std::uint32_t buffer=0,capacity=0,count=0,growth=0,extra=0;
    std::uint8_t owns=0;
    std::vector<std::uint32_t> items;
};
struct ResourceTypeInputs {
    std::string id;
    int index=-1,spread=0,growth=0,value=0,power=0,color=0;
    double spreadPercentage=0,growthPercentage=0;
    ResourceDebrisInputs debris;
    const OverlayTypeInputs* image=nullptr;
    int numFrames=0,numImages=0,numSlopes=0;
    // +0xF0..+0x124. Constructor leaves +0x104 and +0x120 unchanged.
    std::array<std::uint32_t,14> logic{};
};
struct ResourceTypeRegistry {
    std::vector<ResourceTypeInputs*> slots;
    int count=0,growth=1;
    std::uint8_t owns=1;
};
using ResourceTypeStore=std::function<void(ResourceTypeInputs&,unsigned,unsigned,std::uint64_t)>;
struct ResourceConstructionServices {
    std::function<void(ResourceTypeInputs&,std::string_view)> base;
    std::function<void(ResourceDebrisInputs&)> constructDebris,clearDebris;
    std::function<int(unsigned,int)> grow;
    ResourceTypeStore store;
    std::function<void(unsigned,unsigned,std::uint32_t)> registryStore;
    std::uint32_t currentFrame=0;
};
void constructResourceType(ResourceTypeInputs&,std::string_view,
    ResourceTypeRegistry&,ResourceTypeRegistry&,const ResourceConstructionServices&);
struct ResourceIniServices {
    std::function<bool(ResourceTypeInputs&)> base;
    std::function<int(std::string_view,std::string_view,int)> integer;
    // Supplies a binary64 result for the consumer's store. Original parsing and
    // exceptional x87 conversion behavior (including signaling NaNs) are outside
    // this service contract; do not infer hardware NaN semantics from the oracle.
    std::function<double(std::string_view,std::string_view,double)> real;
    std::function<int(std::string_view,int)> color;
    std::function<std::pair<int,std::string>(std::string_view)> debrisText;
    std::function<ResourceDebrisInputs()> beginDebris;
    std::function<std::optional<std::string>(bool,std::string_view)> nextDebris;
    std::function<std::uint32_t(std::string_view)> resolveDebris;
    std::function<void(ResourceDebrisInputs&,std::uint32_t)> appendDebris;
    std::function<ResourceDebrisInputs(const ResourceDebrisInputs&)> copyDebris;
    std::function<void(ResourceDebrisInputs&,const ResourceDebrisInputs&)> assignDebris;
    std::function<void(ResourceDebrisInputs&)> destroyDebris,releaseDebris;
    ResourceTypeStore store;
    std::span<const OverlayTypeInputs> overlays;
};
bool readResourceTypeIni(ResourceTypeInputs&,const ResourceIniServices&);
struct ResourceListEntry {std::string key,value;int length=0;};
struct ResourceListServices {
    std::function<ResourceListEntry(int)> entry;
    std::function<int(std::string_view)> numericKey;
    std::function<ResourceTypeInputs*()> allocate;
    std::function<bool(ResourceTypeInputs&)> readIni;
    ResourceConstructionServices construction;
};
// Numeric key selects an existing slot when below count; otherwise construct
// the supplied value. Positive string-read result only; returns true even when
// count is nonpositive. Negative indices/null allocation are native refusals.
bool readResourceTypeList(int,ResourceTypeRegistry&,ResourceTypeRegistry&,
    const ResourceListServices&);
MapResourceType mapResourceInputs(const ResourceTypeInputs&);
}
