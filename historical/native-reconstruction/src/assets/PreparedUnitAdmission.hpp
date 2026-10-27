// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedUnitMembership.hpp"
#include "sim/UnitNextCell.hpp"
namespace ra2 {
// Initial type/House/registry associations, not a recovered constructor. The
// bounded owner is House 0, with no registry entries or weapons and only an
// explicitly enabled parked allied Unit in addition to the mover;
// UnitType +B94 (MovementRestrictedTo) is -1, IsTrain/count704 are zero.
struct PreparedUnitAdmissionInputs {
    std::uint8_t crusher=1;
    int houseIndex=0;
    std::uint32_t houseAllies=0;
    // Explicit opt-in: one parked allied Unit, separately bound to membership.
    // Timer padding is supplied, not recovered construction/initialization.
    bool parkedResident=false;
    GroundDriveResidentRetry residentRetry;
};
// Borrow the same mutable map, Unit lists and occupation records as Mark. Views
// refresh before each original read-only decision; inner fallback stores forward
// immediately through the membership binding. No original allocation/startup,
// original stationary construction, gate animation or pathfinding is supplied.
class PreparedUnitAdmission {
public:
    using Decision=std::function<void(char,int,int,int)>;
    PreparedUnitAdmission(PreparedMembershipMap,PreparedUnitMembership&,
        GroundDriveProcessState&,const GroundDriveProcessServices&,
        PreparedUnitAdmissionInputs={},const PreparedUnitMembership::Query& = {},
        const Decision& = {});
    PreparedUnitAdmission(const PreparedUnitAdmission&)=delete;
    PreparedUnitAdmission& operator=(const PreparedUnitAdmission&)=delete;
    PreparedUnitAdmission(PreparedUnitAdmission&&)=delete;
    PreparedUnitAdmission& operator=(PreparedUnitAdmission&&)=delete;
    GroundDriveProcessServices bind(GroundDriveProcessServices);
    bool process(const DriveData&,int speed,int tick,int timerPadding,
        const GroundDriveProcessServices&,const GroundStateStore& actorStore={},
        const GroundStateStore& rampStore={},const GroundStateStore& driveStore={});
    PreparedUnitAdmissionInputs inputs()const{return inputs_;}
private:
    PreparedMembershipMap map_;
    PreparedUnitMembership& member_;
    GroundDriveProcessState& state_;
    PreparedUnitAdmissionInputs inputs_;
    PreparedUnitMembership::Query query_;
    Decision decision_;
    UnitAdmissionWorld world_;
    void refresh(int tick);
    int identity(const MapCellInput&) const;
    bool gates(std::int16_t,std::int16_t,int tick);
    int admit(const GroundDriveCell&,int direction,int level,int tick);
    void next(std::int16_t,std::int16_t);
    void fallback(TerrainCellPoint);
    void event(char,int=0,int=0,int=0) const;
};
}
