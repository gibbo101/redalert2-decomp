// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/ResidentCellPreparation.hpp"
#include "assets/MapFloorHeight.hpp"
#include "sim/GroundDriveProcess.hpp"
#include "sim/UnitMembership.hpp"
#include "sim/UnitMark.hpp"
#include "sim/UnitOccupation.hpp"
#include "sim/MapVisibility.hpp"
#include "sim/UnitDiscovery.hpp"
namespace ra2 {
// Borrowed mutable map records and original-sized attribute buffers. Initial
// actor/House/visibility/occupation associations remain explicit caller inputs.
struct PreparedMembershipMap {
    std::span<MapCellAttributes* const> cells;
    std::span<const int> slots;
    MapCellAttributes& fallback;
    MapFloorHeightState& floor;
    ResidentCellInputs resident;
    std::span<std::uint8_t> buffer4,buffer10;
    int width=0,height=0,levelHeight=104;
};
using PreparedMembershipStore=std::function<void(char,int,int,std::uint32_t)>;
// Ordinary nonbridge mover and an optional explicitly bound parked Unit. No
// original allocation, Tag execution, actor lifecycle or route finding.
// The borrowed map, bound actor records and this binding must outlive callbacks.
class PreparedUnitMembership {
public:
    using Query=std::function<void(char,Coord)>;
    PreparedUnitMembership(PreparedMembershipMap,const PreparedMembershipStore& = {},
        const Query& = {});
    PreparedUnitMembership(const PreparedUnitMembership&)=delete;
    PreparedUnitMembership& operator=(const PreparedUnitMembership&)=delete;
    UnitMembershipWorld membership;
    std::vector<UnitOccupationCell> occupation;
    std::vector<MapVisibilityCell> visibilityCells;
    UnitMarkState marking;
    UnitDiscoveryActor discovery;
    UnitDiscoveryWorld houses;
    MapVisibilityState visibility;
    std::function<void()> redrawMap;
    int occupationThreshold=128;
    // Bind only Mark and occupation. Retain supplied admission/mission/route and
    // terrain services; the latter must use world() to forward shared fallback.
    GroundDriveProcessServices bind(GroundDriveProcessServices,GroundDriveProcessState&,
        const GroundStateStore& actorStore={});
    // The extra actor is logical id 1. Its records and stable addresses belong
    // to the enclosing owner; it shares Cells/House/foundation/visibility here.
    GroundDriveProcessServices bindParked(GroundDriveProcessServices,GroundDriveProcessState&,
        UnitMarkState&,UnitDiscoveryActor&,const GroundStateStore& actorStore={});
    const GroundDriveProcessState& actorState(int) const;
    const UnitDiscoveryActor& actorDiscovery(int) const;
    UnitDiscoveryActor& actorDiscovery(int);
    UnitMarkState& actorMark(int);
    MapFloorHeightWorld world();
    // Coordinate/map roots already stored the physical fallback point before
    // calling their observer. Forward the remaining associations once.
    void forwardAssignedFallback(MapInputPosition);
    const UnitMembershipCell& cellMembership(std::size_t index) const;
    // Host preview snapshot. Copy only logical values; callbacks and pointer
    // tables remain bound to the destination's independently owned map.
    void copyStateFrom(const PreparedUnitMembership&);
private:
    static constexpr int CellBase=1000; // Disjoint from legacy global subject200.
    PreparedMembershipMap map_;
    PreparedMembershipStore store_;
    Query query_;
    std::vector<MapVisibilityCell*> visibilityTable_;
    struct ActorBinding {
        GroundDriveProcessState* state;
        UnitMarkState* marking;
        UnitDiscoveryActor* discovery;
    };
    std::map<int,ActorBinding> actors_;
    GroundDriveProcessServices bindActor(int,GroundDriveProcessServices,
        GroundDriveProcessState&,UnitMarkState&,UnitDiscoveryActor&,const GroundStateStore&);
    void notify(int,int);
    MapCellAttributes& attributes(int);
    int index(const MapCellInput&) const;
    void fallback(MapInputPosition);
    void occupationChange(Coord,bool);
    void recalculate(int,int);
    void write(char,int,int,std::uint32_t) const;
};
}
