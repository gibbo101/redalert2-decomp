// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellChildren.hpp"
namespace ra2 {
struct MapGeometryRect {int x=0,y=0,width=0,height=0;bool operator==(const MapGeometryRect&) const=default;};
struct InitialMapGeometry {
    MapGeometryRect full;
    int minimumX=1,minimumY=1,maximumX=0,maximumY=0;
    int diamondMinimum=0,diamondMaximum=0;
    std::vector<MapInputPosition> positions;
};
// Selected CreateEmptyMap projection: initial empty pointer table, reuse=1.
// Existing actors, map copying, cell ownership and broader preparation are separate.
// Positive dimensions with width+height<=256 are the native supported domain.
InitialMapGeometry initialMapGeometry(MapGeometryRect requested);
void initializeMapGeometryCells(const InitialMapGeometry&,std::span<MapCellInput> storage,
    std::span<MapCellInput*> table,MapCellInput& fallback,MapInputPosition invalid,
    std::uint8_t level,const MapInputStore& store={});
// Complete rectangle arithmetic from SetVisibleRect, with an empty actor list.
// Preserve wrapped signed arithmetic and possible negative final dimensions.
MapGeometryRect mapVisibleRect(MapGeometryRect full,MapGeometryRect requested);
MapPermissionShape mapPermissionShape(MapGeometryRect full,MapGeometryRect visible);
struct MapGeometryAllocation {
    std::uint32_t capacity=0,attributeBytes=0,secondaryBytes=0;
    std::array<int,3> subzoneCapacities{};
};
// Numeric projection of the buffer initializer; no allocation/zone/light services.
MapGeometryAllocation mapGeometryAllocation(int width,int height);
// Four-byte attribute records: only passability and level are initialized here.
// Trailing two bytes retain caller-provided allocation contents.
void initializeMapGeometryBuffer(std::span<std::uint8_t> records);
}
