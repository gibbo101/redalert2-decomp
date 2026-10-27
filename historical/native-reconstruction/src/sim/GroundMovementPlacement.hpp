// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/ActorGroundState.hpp"
namespace ra2 {
// Complete Foot SetLocation and its Object coordinate setter. Source coordinates
// are read after Mark(0); the Mark implementation remains a supplied service.
void setFootLocation(ActorGroundState&,const Coord&,const ActorGroundServices&,
    const GroundStateStore& store={});
// Scoped Drive Advance residual placement, 0x4A2054..0x4A2112. The candidate is
// already computed. This does not recover the complete advance/route/clearance.
void placeDriveResidualGround(ActorGroundState&,const Coord&,int bridgeHeight,
    const ActorGroundServices&,const GroundStateStore& store={});
// Scoped committed same-Cell path, 0x4A1AB0..0x4A1AFB. onMap is read after
// SetLocation; false exits to the original parent's cleanup without height work.
void placeDriveCommittedSameCell(ActorGroundState&,const Coord&,const std::uint8_t& onMap,
    int bridgeHeight,const ActorGroundServices&,const GroundStateStore& store={});
}
