// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryWeaponSelection.hpp"
#include <stdexcept>

namespace ra2 {
namespace { void require(bool value,const char* message){if(!value)throw std::invalid_argument(message);} }
std::int32_t selectInfantryWeaponForNullTarget(InfantryWeaponSelectionActor actor,
        const void* target,const InfantryWeaponSelectionServices& services) {
    require(services.type&&services.mission,"Infantry weapon selection requires type and mission services");
    require(actor.state5ac<27||actor.state5ac>30,
        "Infantry deploy-state weapon selection is outside the null-target profile");

    const auto& firstType=services.type();
    require(firstType.turretCount704<=0,
        "Infantry multiple-turret weapon selection is outside the E1 profile");

    const auto weapon=[&](std::size_t index) -> const InfantryWeaponSelectionWeapon& {
        const bool elite=actor.veterancy118>=2.;
        if(elite) {
            const auto& promoted=services.type().eliteWeapons.at(index);
            if(promoted.identity)return promoted;
        }
        return services.type().weapons.at(index);
    };
    const auto& secondary=weapon(1);
    if(!secondary.identity)return 0;
    const auto& primary=weapon(0);
    if(!primary.identity)return 0;
    if(secondary.neverUse112)return 0;
    if(secondary.areaFire126&&services.mission()==16)return 1;
    require(actor.kind==15,"Infantry null-target selection supports only actual Infantry kind 15");
    require(target==nullptr,"Infantry target-dependent weapon selection is not recovered");
    return 0;
}
}
