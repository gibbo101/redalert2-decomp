// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellAttributes.hpp"

namespace ra2 {
struct ResidentCellInputs {
    MapAttributeLookup world;
    std::span<const MapTileAttributes> tiles;
    std::span<const int> landMap;
    std::span<const MapOverlayType> overlays;
    std::span<const MapResourceType> resources;
    std::span<const float> wheelSpeeds;
    MapLATSettings lat{};
    std::array<MapInputPosition,8> directions{};
    MapPermissionShape permission;
    int tubeCount=0;
    std::uint8_t cliffMode=0;
    bool fallback=false;
};
struct ResidentCellServices {
    std::function<void(const MapCellAttributes&)> beforeLAT,beforePassability;
    std::function<void(int)> classifyQuery,missingResource,passabilityStore;
    std::function<void(MapAttributeField,std::uint32_t)> store;
    // Optional actual-list child. Permission and overlay lookup still execute
    // here before dispatch; the caller must store the result on the same Cell.
    std::function<int(MapCellAttributes&,bool,const MapOverlayType*)> occupiedPassability;
};
// Bind complete recalculation to actual LAT, classifier, empty-occupant
// passability, permission, lookup and resident TMP consumers. The lookup table
// supplies shared mutable input records, with no copied neighbor state. Registry,
// initial/type/geometry/table construction and actor loading remain supplied.
void recalculateResidentCell(MapCellAttributes&,int levelOverride,
    std::span<std::uint8_t,4>,std::span<std::uint8_t,10>,
    const ResidentCellInputs&,const ResidentCellServices& services={});
}
