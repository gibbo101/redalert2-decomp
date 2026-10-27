// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <span>
namespace ra2 {
struct UnitDrawingInputs {
    std::uint8_t flags=7,specialState=0;
    std::int8_t secondaryIndex=-1;
};
// Only these inspected constructor fields, not a recovered Unit constructor.
UnitDrawingInputs initialUnitDrawingInputs(std::uint8_t allocationFlags);
Coord driveSecondaryCoordinates(Coord current,Coord destination);
struct FootCoordinateServices {
    std::function<Coord()> locomotor,coordinates;
};
// The original second argument is unused. Indexed pool entries are signed words.
// Null locomotors and absent indexed entries are native safety refusals.
Coord footSecondaryCoordinates(std::int8_t index,std::span<const TerrainCellPoint>,
                               const FootCoordinateServices&);
}
