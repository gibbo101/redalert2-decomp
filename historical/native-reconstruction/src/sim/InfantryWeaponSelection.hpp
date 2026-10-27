// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>

namespace ra2 {
struct InfantryWeaponSelectionWeapon {
    const void* identity{};
    std::uint8_t neverUse112{};
    std::uint8_t areaFire126{};
};
struct InfantryWeaponSelectionType {
    std::int32_t turretCount704{};
    std::int32_t deployFireWeapon5c8{};
    std::uint8_t deployFire5cc{};
    std::array<InfantryWeaponSelectionWeapon,2> weapons{};
    std::array<InfantryWeaponSelectionWeapon,2> eliteWeapons{};
};
struct InfantryWeaponSelectionActor {
    const std::int32_t& state5ac;
    const std::int32_t& currentTurret10c;
    const double& veterancy118;
    const std::int32_t& kind;
};
struct InfantryWeaponSelectionServices {
    std::function<const InfantryWeaponSelectionType&()> type;
    std::function<std::int32_t()> mission;
};

// Bounded ordinary-Infantry base508530 -> base6C1380 selection through the
// null-target exit. Deploy states and target-dependent branches remain outside
// this interface.
std::int32_t selectInfantryWeaponForNullTarget(
    InfantryWeaponSelectionActor,const void* target,
    const InfantryWeaponSelectionServices&);
}
