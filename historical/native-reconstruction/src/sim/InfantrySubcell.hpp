// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include "sim/OriginalRandomRange.hpp"
#include <functional>

namespace ra2 {
// Borrow the actual Cell occupation words and House-index slots. These are
// shared with other occupants, never counts or a separate infantry map.
struct InfantryOccupationCell {
    std::uint32_t& ground;
    std::uint32_t& elevated;
    const std::uint32_t& flags;
    std::int32_t& groundHouse54;
    std::int32_t& elevatedHouse58;
};
struct InfantrySubcellData {
    // Original immutable order data, supplied privately; not compiled in.
    std::array<std::array<std::uint8_t,4>,9> orders{};
};
struct InfantrySubcellServices {
    std::function<double(double)> squareRoot;
    std::function<InfantryOccupationCell(const Coord&)> cell;
    std::function<std::int32_t(const Coord&)> floor;
    // Read-only observer immediately before the actual borrowed House read.
    std::function<void()> houseQuery;
};
using InfantryOccupationStore=std::function<void(InfantryOccupationCell,int,int,std::uint32_t)>;
// Recovered initializer483390, not a compiled copy of extracted table bytes.
std::array<Coord,5> initialInfantrySubcellOffsets();
int infantrySubcell(const Coord&,const std::function<double(double)>& squareRoot);
void occupyInfantrySubcell(const Coord&,const std::int32_t& houseIndex,
    const std::int32_t& heightThreshold,const InfantrySubcellServices&,
    const InfantryOccupationStore& = {});
void releaseInfantrySubcell(const Coord&,const std::int32_t& heightThreshold,
    const InfantrySubcellServices&,const InfantryOccupationStore& = {});
// Complete ordinary selector4764B0. Entered building-bit64 policy is explicitly
// refused until its actual building/lifecycle children are bound. Forced/raw
// elevated arguments, masks, RNG and floor ordering retain original behavior.
Coord chooseInfantrySubcell(InfantryOccupationCell,const Coord&,
    std::uint8_t force,std::uint8_t elevated,const InfantrySubcellData&,
    OriginalRandomState&,const std::int32_t& bridgeHeight,
    const InfantrySubcellServices&,const OriginalRandomRangeObserver& = {},Coord empty={});
}
