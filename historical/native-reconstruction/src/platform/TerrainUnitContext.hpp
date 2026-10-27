// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MutableUnitMap.hpp"
#include "assets/PreparedDriveTerrain.hpp"
#include "assets/PreparedUnitAdmission.hpp"
#include "render/Redraw.hpp"
#include "sim/GroundDriveContext.hpp"
#include <optional>
namespace ra2 {
// One native mover and optional parked Unit on shared private prepared Cells.
// Initial actor/House/visibility and command policies are host inputs. No
// original startup or clone claim; the parked extension is not in the demo.
class TerrainUnitContext final:public GroundDriveContext {
    GroundDriveProcessServices supplied_;
    std::unique_ptr<PreparedDriveTerrain> terrain_;
    GroundStateStore admissionDriveStore_;
public:
    struct ParkedUnit {
        GroundDriveProcessState state;
        UnitMarkState marking;
        UnitDiscoveryActor discovery;
        GroundDriveProcessServices services;
        // Explicit supplied association, independent of the body Facing.
        // Movement-only callers may omit it; drawing must require it.
        std::optional<Facing> turret;
        const Facing& drawingTurret()const;
    };
    std::shared_ptr<MutableUnitMap> map;
    std::unique_ptr<PreparedUnitMembership> unit;
    std::unique_ptr<PreparedUnitAdmission> admission;
    std::unique_ptr<ParkedUnit> parked;
    RedrawState redraw{2,255,0,true};
    TerrainUnitContext(std::shared_ptr<MutableUnitMap>,GroundDriveProcessServices,
        const GroundDriveProcessState& initial={},const GroundStateStore& actorStore={},
        const PreparedMembershipStore& store={},const PreparedUnitMembership::Query& query={});
    TerrainUnitContext(const TerrainUnitContext&)=delete;
    TerrainUnitContext& operator=(const TerrainUnitContext&)=delete;
    TerrainUnitContext(TerrainUnitContext&&)=delete;
    TerrainUnitContext& operator=(TerrainUnitContext&&)=delete;
    std::unique_ptr<GroundDriveContext> clone()const override;
    // Explicit supplied records; caller performs verified height/ramp/Mark
    // initialization. This does not enable a second runtime-controlled Unit.
    void bindParked(const GroundDriveProcessState&,const UnitMarkState&,
        const UnitDiscoveryActor&,const GroundStateStore& actorStore={},
        std::optional<Facing> turret=std::nullopt);
    void enableAdmission(PreparedUnitAdmissionInputs={},const PreparedUnitMembership::Query& = {},
        const PreparedUnitAdmission::Decision& = {},const GroundStateStore& driveStore={});
    bool process(const DriveData&,int speed,int tick,int padding,
        const GroundStateStore& actorStore={},const GroundStateStore& rampStore={}) override;
};
}
