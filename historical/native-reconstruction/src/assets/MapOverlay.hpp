// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellChildren.hpp"

namespace ra2 {
struct OverlayTypeInputs;
// Selected base-engine fields, not a copy of the original object layout.
// Default/INI/registry construction is deliberately outside this boundary.
struct MapOverlayType {
    int land=0;
    std::uint8_t flag1FD=0,wall=0,tiberium=0,noUseTileLandType=0,rubble=0,rock=0;
};
struct MapResourceType {
    int index=0,imageIndex=0,numImages=0,numSlopes=0,numFrames=1,value=0;
};
// Complete classifier: signed wrapped range endpoints and first matching record.
// An unmatched resource-marked overlay logs and returns zero, not -1.
int classifyMapOverlay(int overlay,const MapOverlayType*,std::span<const MapResourceType>,
    const std::function<void(int)>& missing={});
// Same recovered classifier, borrowing field279 from the canonical image/type
// owner rather than a separately initialized map-type projection.
int classifyOverlayResource(int overlay,const OverlayTypeInputs*,std::span<const MapResourceType>,
    const std::function<void(int)>& missing={});
// Complete passability root restricted to no occupants. Permission runs first;
// supplied Wheel speeds are used for both overlay and ordinary Cell land.
int overlayCellPassability(const MapCellInput&,bool permitted,const MapOverlayType*,
    std::span<const float> wheelSpeeds);
struct MapResourceServices {
    std::array<MapInputPosition,8> directions{};
    std::span<const MapResourceType> types;
    std::span<const std::uint8_t> frameTable;
    // Lookup/classification services may nest actual native recovered children.
    std::function<int(int)> classify;
    std::function<int(MapInputPosition)> neighborOverlay;
    std::function<void(std::uint8_t)> store;
};
// Complete Cell resource amount/update for argument zero: no random replacement.
// Resource inputs, neighbor storage, direction and frame tables remain supplied.
int updateMapResource(MapInputPosition,int overlay,std::uint8_t& overlayData,
    const MapResourceServices&);
}
