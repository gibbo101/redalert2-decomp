// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitTypeMetadata.hpp"
#include <stdexcept>
namespace ra2 {
UnitTypeMetadata readUnitTypeMetadata(const Ini& rules,const Ini& art,
                                     const std::string& name,UnitTypeMetadata type) {
    type.harvester=rules.boolean(name,"Harvester",type.harvester);
    type.voxel=art.boolean(name,"Voxel",type.voxel);
    type.turret=rules.boolean(name,"Turret",type.turret);
    type.hunterSeeker=rules.boolean(name,"HunterSeeker",type.hunterSeeker);
    type.balloonHover=rules.boolean(name,"BalloonHover",type.balloonHover);
    return type;
}
void requireOrdinaryRhinoMetadata(const UnitTypeMetadata& type) {
    if(type.harvester||!type.voxel||!type.turret||type.hunterSeeker||type.balloonHover)
        throw std::runtime_error("Only ordinary nonharvester voxel HTNK with a turret is supported");
}
}
