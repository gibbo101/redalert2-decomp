// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/WalkMovement.hpp"
#include "sim/InfantrySubcell.hpp"
#include "sim/UnitDiscovery.hpp"

namespace ra2 {
struct WalkRouteContext;
struct WalkHeadActor {
    const Coord& position;
    const UnitDiscoveryActor& mission;
    const void* const& target494;
};
struct WalkHeadCell {
    InfantryOccupationCell occupation;
    const std::int32_t& overlay44;
};
struct WalkHeadInputs {
    const InfantrySubcellData& subcells;
    OriginalRandomState& random;
    const std::int32_t& houseIndex;
    const std::int32_t& occupationHeight;
    const std::int32_t& bridgeHeight;
    const std::int32_t& levelHeight;
    Coord empty{};
};
struct WalkHeadServices {
    // All occupation, selection and caller lookups share these borrowed Cells.
    std::function<WalkHeadCell(const Coord&)> cell;
    std::function<std::int32_t(const Coord&)> floor;
    std::function<double(double)> squareRoot;
    // Read-only diagnostic observers, never replacement query results.
    std::function<void()> houseQuery;
    std::function<void(int)> missionQuery;
    InfantryOccupationStore cellStore;
    GroundStateStore headStore;
    OriginalRandomRangeObserver randomDraw;
    std::function<void(WalkHeadCell)> cellEffect;
};
// Ordinary complete71F590 paths: empty point, or a nonempty request without an
// entered target child and with overlay-free476CC0. Uses actual Infantry
// release/select/claim; no pathfinder, Walk Process/startup or runtime binding.
// Unsupported children retain preceding writes; no rollback is promised.
std::uint8_t prepareWalkHead(WalkMovementState&,WalkHeadActor,const Coord& request,
    const WalkHeadInputs&,const WalkHeadServices&);

// Ordinary queued preparation borrows the same actor, route and Cell owners as
// selected-head movement. Infantry503190 admission remains a named service;
// only result0 is joined. No replacement passability/pathfinding is inferred.
struct WalkQueuedContext {
    WalkHeadActor actor;
    const WalkHeadInputs& inputs;
    const WalkHeadServices& head;
    std::uint8_t& transition57b;
    std::function<WalkMovementCellView(const Coord&)> coordinateCell;
    std::function<int(WalkMovementCellView,int direction,int level,int,int)> admission;
    // Opt-in original retry/refill caller. Legacy queued facades keep refusing
    // an empty route. The pathfinder itself remains a named supplied service.
    WalkRouteContext* route=nullptr;
};
std::uint8_t processQueuedWalk(WalkMovementState&,WalkMovementActor,
    const WalkMovementNumerics&,const WalkMovementServices&,WalkArrivalContext&,
    WalkQueuedContext&,std::int32_t tick);
}
