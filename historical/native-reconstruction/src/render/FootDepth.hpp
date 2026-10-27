// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitLighting.hpp"
#include <functional>
namespace ra2 {
struct FootDepthType {int b60=0,b64=0,b5c=0,b68=0;};
UnitLightCell footDepthCoordinates(int worldX,int worldY);
struct FootDepthServices {
    std::function<int()> locomotorDepth,locomotorGradient,predicate0,predicate1,predicate2,baseDepth;
    std::function<std::uint8_t()> predicate3;
    std::function<FootDepthType()> type;
};
int footDepthAdjustment(bool hasLocomotor,const FootDepthServices&);
int footDepthGradient(bool hasLocomotor,const FootDepthServices&);
struct FootDepthCell {
    UnitLightCell position{};
    std::uint32_t flags=0;
    int tile=0,fieldEC=0;
    std::int16_t field116=-1;
    std::int8_t level=0;
};
bool footDepthCellPredicate(const FootDepthCell&,int count);
struct FootDepthWorld {
    std::uint8_t bridge=0;
    int tileBase=0;
    UnitLightCell invalid{}; // Supplied global; initialization is separate.
    std::function<UnitLightCell()> coordinates;
    std::function<const FootDepthCell*(UnitLightCell)> cell;
    std::function<bool(const FootDepthCell&)> cellPredicate;
    std::function<void(int)> trace;
};
// Cell membership/storage and flag/tile construction remain supplied. Stable,
// immutable records and callbacks are required. Two children require a current
// cell on their non-bridge path; invalid fixture pointers are refused safely.
bool footDepthFlag(const FootDepthWorld&,bool mask400=false);
int footDepthPredicate0(const FootDepthWorld&);
int footDepthPredicate1(const FootDepthWorld&);
int footDepthPredicate2(const FootDepthWorld&);
}
