// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/ActorGroundState.hpp"
#include "sim/TerrainOccupation.hpp"
#include <functional>

namespace ra2 {
// Walk has its own destination/head and three raw bytes. It is not a Drive.
struct WalkMovementState {
    Coord destination,head;
    std::uint8_t moving34=0,inProcessing35=0,reallyMoving36=0;
    // Supplied ordinary startup; borrowed by the recovered IPiggyback predicate.
    // Nonnull retained locomotor ownership/unstacking remains guarded.
    const void* piggyback38=nullptr;
};
// Borrow the same Foot/Object fields used by placement, never mirror a Drive.
struct WalkMovementActor {
    ActorGroundState& ground;
    Facing& body;
    std::int32_t& immobilized3fc;
    double& percentage468;
    std::uint8_t& field5a1;
    std::uint8_t& field57a;
};
// A lookup borrows the actual Cell fields. Copying a view retains those
// associations across later lookups/services; it never snapshots level/flags.
// Identity is opaque to the movement kernel and belongs to the binding.
struct WalkMovementCellView {
    const std::int8_t& level;
    const std::uint32_t& flags;
    const void* identity;
};
struct WalkMovementNumerics {
    const DirectionData& direction;
    double radiansPerFacing=0;
    std::function<double(double)> squareRoot;
    std::function<float(double)> sine,cosine;
};
struct WalkMovementServices {
    std::function<std::int32_t()> speed;
    ActorGroundServices placement; // named Mark and map-floor effects
    std::function<WalkMovementCellView(TerrainCellPoint)> lookup;
    std::function<WalkMovementCellView(Coord)> currentCell;
    std::function<void(WalkMovementCellView)> dirty;
    // Read-only diagnostic observer; A/L stores and named C/V/S/T/Q/D queries.
    std::function<void(char,std::int64_t,std::int64_t,std::int64_t)> trace;
};
struct WalkArrivalActor {
    std::array<std::int32_t,24>& route4d0;
    TerrainCellPoint& cell450;
    std::uint8_t& onMap7d;
    std::uint8_t& flag76;
    std::uint8_t& flag7a;
    const std::int8_t& secondaryIndex574;
};
struct WalkArrivalServices {
    // Infantry EC/E8 occupation and174/410/4D0 effects remain named services.
    // Nonempty head coordinates are borrowed; Object coordinates are snapshots,
    // as in the actual head helper's virtual dispatch.
    std::function<void(const Coord&)> release,occupy;
    std::function<void(int)> notify;
    std::function<void(int,int)> destination;
    std::function<void()> resetMovement;
};
struct WalkArrivalContext {WalkArrivalActor actor;WalkArrivalServices services;};
// Complete Walk Process71DFF0 -> Movement_AI71E220 paths with a nonempty head
// at planar distance >=17. Arrival, selecting the next subcell and initial
// routing remain explicit refusals; this is not yet runtime infantry walking.
// Named speed/Mark/floor/map/dirty effects and initial associations are supplied.
std::uint8_t processCommittedWalk(WalkMovementState&,WalkMovementActor,
    const WalkMovementNumerics&,const WalkMovementServices&,std::int32_t tick,
    std::int32_t bridgeHeight,Coord empty={});
// Same kernel, adding the actual selected-head arrival continuation. Only the
// ordinary negative secondary-index Foot-coordinate profile is joined here.
// Initial routing/choosing a nonempty next subcell remain refused.
std::uint8_t processSelectedWalk(WalkMovementState&,WalkMovementActor,
    const WalkMovementNumerics&,const WalkMovementServices&,WalkArrivalContext&,
    std::int32_t tick,std::int32_t bridgeHeight,std::int32_t levelHeight,Coord empty={});
}
