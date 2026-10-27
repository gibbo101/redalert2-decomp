// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MutableUnitMap.hpp"
namespace ra2 {
// Borrow the movement owner's live Cells, lazy floors and membership fallback.
// Both owners must outlive this view. Binding performs no recovered map query.
// A draw may warm the owner's floor planes or write its fallback coordinates.
class OwnedUnitDrawingMap {
    MutableUnitMap& map_;
    PreparedUnitMembership& unit_;
    MapFloorHeightWorld world_;
public:
    OwnedUnitDrawingMap(MutableUnitMap&,PreparedUnitMembership&);
    const GroundDriveProcessState& actorState(int id)const;
    const MapCellInput& coordinate(Coord);
    const MapCellAttributes& cell(MapInputPosition);
    int floor(Coord);
    // Ordinary nonbridge Unit profile only.
    int relative(Coord);
};
}
