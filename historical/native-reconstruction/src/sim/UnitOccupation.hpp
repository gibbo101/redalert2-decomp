// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
namespace ra2 {
struct UnitOccupationCell {
    std::uint32_t ground=0,elevated=0,flags=0;
};
struct UnitOccupationServices {
    std::function<UnitOccupationCell&(const Coord&)> cell;
    std::function<int(const Coord&)> floor;
    int heightThreshold=0;
};
using UnitOccupationStore=std::function<void(const UnitOccupationCell&,int,std::uint32_t)>;
// Complete Unit occupation virtuals, separate from Object/Techno/Foot Mark and
// Cell membership. Save Cell identity before floor; read Z/threshold/flags after
// floor. Write the whole occupation dword even when its bit is already correct.
// Initial fields/threshold/map association are supplied; these are not counts.
void markUnitOccupation(const Coord&,const UnitOccupationServices&,const UnitOccupationStore& = {});
void unmarkUnitOccupation(const Coord&,const UnitOccupationServices&,const UnitOccupationStore& = {});
}
