// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitMovementRestriction.hpp"
#include <stdexcept>
namespace ra2 {
int readUnitMovementRestriction(const Ini& rules,const std::string& typeId){
    if(rules.section(typeId).contains("movementrestrictedto"))
        throw std::invalid_argument("Present MovementRestrictedTo requires additional enum input recovery");
    return -1;
}
}
