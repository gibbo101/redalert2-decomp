// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
namespace ra2 {
// Scoped UnitType+B94 constructor default and missing-key association only.
// A present MovementRestrictedTo value needs the original enum reader profile;
// MovementZone is a separate field. Native text/index construction is supplied.
int readUnitMovementRestriction(const Ini&,const std::string& typeId);
}
