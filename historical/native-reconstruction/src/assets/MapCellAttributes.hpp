// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "assets/MapOverlay.hpp"
#include <array>
namespace ra2 {
struct MapCellAttributes {
    MapCellInput input{};
    int overlay=-1,passability=0;
    std::uint8_t overlayData=0,extraHeight=0;
    // Original Cell +0x78. Startup is zero until a recovered cloak-generator
    // owner changes it; ordinary prepared terrain therefore keeps zero.
    std::uint32_t cloakedByHouses=0;
};
struct MapTileAttributes {
    const MapTileImageInput* image=nullptr;
    int animation=-1,animationSubTile=0;
    // Original +0x2B1, not Morphable (+0x2B0). Theater loader sets this only
    // for ShadowCaster and nonzero ShadowTiles; neighbor writes stay refused.
    bool shadowCaster=false;
};
enum class MapAttributeField {Tile,SubTile,Land,Slope,Level,ExtraHeight,Buffer4,Buffer10,Overlay,OverlayData};
struct MapAttributeServices {
    std::span<const MapTileAttributes> tiles;
    std::span<const int> landMap;
    int tubeCount=0;
    std::uint8_t cliffMode=0;
    bool fallback=false;
    std::function<std::int8_t(MapInputPosition)> neighborLevel;
    // Explicit child boundaries: LAT supplies the resulting tile index;
    // passability supplies +0x4C. Other cell fields stay immutable in services.
    std::function<int(const MapCellAttributes&)> setupLAT,updatePassability;
    std::function<void(MapAttributeField,std::uint32_t)> store;
    std::span<const MapOverlayType> overlays;
    std::function<int(int)> classifyResource;
};
// Original map-buffer index: wrapped signed geometry/product, then clamped.
// Nonpositive capacity is a native safety refusal.
int mapAttributeBufferIndex(MapInputPosition,int dimension0,int dimension1,int capacity);
// Complete root on supplied overlay/type records and resident TMP, no new tube/animation
// allocation and non-shadow-casting type. LAT/passability and neighbor storage supplied.
// Buffers are the already selected original 4-byte/10-byte records.
void recalculateMapCellAttributes(MapCellAttributes&,int levelOverride,
    std::span<std::uint8_t,4> buffer4,std::span<std::uint8_t,10> buffer10,
    const MapAttributeServices&);
}
