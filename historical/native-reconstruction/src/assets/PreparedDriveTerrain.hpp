// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapFloorHeight.hpp"
#include "sim/GroundDriveProcess.hpp"
namespace ra2 {
// Borrow the finalized Cell pointer table, fallback and lazy floor state. This
// binding does not construct actors, find routes or implement Mark/occupation.
// The owner must keep every record and this object alive throughout Process.
// Traversed Cells must satisfy the ordinary empty/nonbridge/overlay-free profile;
// check is an optional read-only owner validation, outside original query tracing.
class PreparedDriveTerrain {
public:
    using Query=std::function<void(char,Coord)>;
    PreparedDriveTerrain(MapFloorHeightState&,int levelHeight,MapFloorHeightWorld,
        const std::function<void(const MapCellInput&)>& check={},const Query& query={},
        const std::function<std::uint8_t(const MapCellInput&)>& ordinaryNeighborCheck={});
    // Bind only terrain children; retain the caller's named mission/Mark and
    // occupation services, land speeds, slope factors and square-root service.
    GroundDriveProcessServices bind(GroundDriveProcessServices) const;
private:
    MapFloorHeightState& floor_;
    int height_;
    MapFloorHeightWorld world_;
    std::function<void(const MapCellInput&)> check_;
    std::function<std::uint8_t(const MapCellInput&)> ordinaryNeighborCheck_;
    Query query_;
    const MapCellInput& coordinate(Coord) const;
    const MapCellInput& word(std::int16_t,std::int16_t,bool neighbor=false) const;
    GroundDriveCell record(const MapCellInput&) const;
};
}
