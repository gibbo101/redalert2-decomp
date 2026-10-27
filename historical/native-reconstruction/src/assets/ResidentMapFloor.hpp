// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/ResidentMapFinalization.hpp"
#include "assets/MapFloorHeight.hpp"
namespace ra2 {
struct MapWallBuildingPosition {Coord position;int width=0,height=0;};
struct MapFinalizationFloor {
    MapFloorHeightState& state;
    int levelHeight;
    std::span<const MapWallBuildingPosition> buildings;
    std::function<double(double)> tableSquareRoot;
    // Optional read-only observers. The floor query observes the current Cell
    // after recalculation, before its lazy height calculation runs.
    std::function<void(int,std::size_t)> beforeDistance;
    std::function<void(int,Coord)> beforeFloor;
    std::function<void(int)> afterDistance;
};
// Binds actual Cell-center height and Cell-target distance to the later parent.
// Building positions/foundation dimensions, house-index getter, initial globals/
// template and all earlier parent service boundaries remain supplied. Registry
// order must match input.buildings; services.buildingDistance must be empty.
MapFinalizationResult finalizeResidentMapWithFloor(const MapFinalizationInputs&,
    std::span<MapFinalizationCell>,MapCellAttributes& fallback,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const MapFinalizationServices&,const MapFinalizationFloor&);
}
