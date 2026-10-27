// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
namespace ra2 {
// Five scoped constructor defaults and INI field associations, verified on the
// supplied base engine. This is not a complete UnitType or model loader.
struct UnitTypeMetadata {
    std::uint8_t harvester=0,voxel=0,turret=0,hunterSeeker=0,balloonHover=0;
};
UnitTypeMetadata readUnitTypeMetadata(const Ini& rules,const Ini& art,
                                     const std::string& name,UnitTypeMetadata defaults={});
void requireOrdinaryRhinoMetadata(const UnitTypeMetadata&);
}
