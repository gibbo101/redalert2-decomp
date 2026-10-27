// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OwnedUnitDrawingMap.hpp"
#include "sim/GroundDriveProcess.hpp"
namespace ra2 {
// Explicit borrowed boundary; the renderer does not know the platform owner.
// This bounded scene supplies one common HTNK type and House for both actors.
// Initial type/House association and traversal/selection remain host policies.
struct OwnedUnitDrawActor {
    int id;
    const GroundDriveProcessState& state;
    const Facing& turret;
    // Optional borrowed actor+494 storage, read at drawing. Legacy scenes keep
    // their supplied null target; no host pointer is narrowed to a guest dword.
    const void* const* target494=nullptr;
    std::uint32_t surfaceTarget494()const{return target494&&*target494?1u:0u;}
};
struct OwnedUnitDrawScene {
    OwnedUnitDrawingMap& map;
    std::span<const OwnedUnitDrawActor> actors;
    int selected=-1;
};
}
