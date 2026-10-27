// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundDriveAdvance.hpp"
#include <stdexcept>
namespace ra2 {
// Domain refusal, not an original return code. Preview may reject the command;
// live stepping must propagate it rather than continue with missing effects.
struct UnsupportedGroundAdmission : std::invalid_argument {
    int result;
    explicit UnsupportedGroundAdmission(int code)
        :std::invalid_argument("Ground Process switch admission requires zero result"),result(code){}
};
// Supplied records at the empty, nonbridge, overlay-free movement boundary.
// Position is the Cell's word coordinate, not the queried world coordinate.
struct GroundDriveCell {
    std::int16_t x=0,y=0;
    std::int8_t level=0;
    std::uint8_t ramp=0;
    int land=0;
    const void* identity=nullptr;
};
struct GroundDriveProcessState {
    GroundDriveAdvanceState movement;
    DriveRampState ramps;
    Coord destination{};
    std::array<int,24> route=[] {std::array<int,24> a{};a.fill(-1);return a;}();
    double percentage=1.;
    double instancePercentage=1.;
    bool wasRotating=false;
    std::uint8_t crossing57b=0;
    std::uint8_t preparation57a=0;
    std::int16_t nextX=0,nextY=0;
    int retryStart=-1,retryPadding=0,retryRemaining=0;
};
struct GroundDriveProcessServices {
    GroundDriveAdvanceServices advance;
    std::function<GroundDriveCell(Coord)> cell;
    std::function<GroundDriveCell(std::int16_t,std::int16_t)> wordCell;
    // Reload a retained record after intervening queries. The shared fallback's
    // word coordinates can have changed without changing its identity.
    std::function<GroundDriveCell(const void*)> liveCell;
    std::function<void(std::int16_t,std::int16_t)> reserve;
    std::function<void(std::int16_t,std::int16_t)> markNext;
    std::function<Coord(const GroundDriveCell&)> center;
    std::function<void(Coord)> markOccupation;
    // These callbacks represent empty admission and pathfinding failure. They
    // must preserve the supported actor/Cell state; no pathfinder is implemented.
    std::function<void(const GroundDriveCell&,int,int)> admit;
    std::function<void()> noRoute;
    std::function<double(double)> squareRoot;
    std::array<float,12> trackSpeed{};
    double uphill=1.,downhill=1.2;
    // Optional ordinary preparation look-ahead (476AC0 -> overlay+1FD).
    // This is a query beyond the next Cell, not traversal/admission. Return the
    // actual overlay+1FD byte, or zero for an absent overlay. Nonzero selects
    // the first direction and stores curve64=1 in the result-bearing join.
    // Absence retains the legacy wordCell validation and overlay-free scope.
    std::function<std::uint8_t(std::int16_t,std::int16_t)> ordinaryNeighbor;
    // Retained candidate overlay after actual first admission and Mark(1).
    // Null retains the earlier overlay-free preparation scope.
    const GroundDrivePreparationOverlayServices* candidateOverlay=nullptr;
};
// Complete Process/preparation in the ordinary healthy, Accelerates=0,
// IsTrain=0, Passive=0, mission=Move, on-map, nonbridge empty-ground profile.
// Supplied route has 0..7 entries then -1; retry delay is zero. Type/actor/map
// construction, admission/occupation/mission effects and route finding are not
// recovered here. The existing flat Drive/runtime adapter is unchanged.
bool processOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
// Result-bearing gate join. A false result waits before Facing, Mark/admission
// or track commitment. Admission, next-Cell, routes and the other services keep
// the earlier supplied-success domain. This entry is not wired to the runtime.
// reserve is unused here; checkGates must be nonnull and may change gate missions
// and the shared fallback, but must preserve mover/route/terrain records.
bool processGatedOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
struct GroundDriveAdmissionServices {
    // Complete admission decisions may return 0/3/7 in this ordinary bounded
    // join. Other codes need additional warning/combat/wait behavior and are
    // refused. Advance's rejected-switch caller requires result zero; its
    // nonzero-result side effects remain outside this entry. Callbacks preserve
    // mover/route/terrain except shared fallback.
    std::function<int(const GroundDriveCell&,int,int)> check;
    GroundStateStore driveStore;
};
// Opaque timer words supplied at the two distinct result-6 load boundaries.
// They are not the ramp timer padding or evidence of original initialization.
struct GroundDriveResidentRetry {
    int firstPadding=0,secondPadding=0;
};
// Result-bearing gate and 0/3/7 admission extension. Retained entries after a
// route sentinel are permitted. IsTrain=0, overlay-free, preparation57a=0,
// zero retry delay and all earlier ordinary type/actor boundaries remain.
// reserve/admit are unused; required next-Cell/Mark effects are separate binds.
// This entry is not wired to the runtime.
bool processAdmittedOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundDriveAdmissionServices&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
// Extends preparation to allied stationary resident result 6. Both complete
// Process callers pass preparation flag 1; the recursive retry passes 0 after
// clearing the queue head. Close-enough/scatter and nonzero Advance admission
// remain refused. Initial resident associations and Mark effects are separate.
// This entry is not enabled in the runtime.
bool processResidentOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundDriveAdmissionServices&,const GroundDriveResidentRetry&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
// Separate opt-in moving-resident caller extension. Initial timer inputs and
// failed-route effects are supplied; this does not enable runtime actor commands.
// Preparation admits2 with actual wait/retry and force-single recursion. Advance
// accepts2 only at the ordinary Unit-kind1/Passive0 rejected-switch boundary.
// Other nonzero Advance results and flag-zero scatter remain explicit refusals.
struct GroundDriveMovingWaitState { int start=-1,padding=0,remaining=0; };
// Joined command/preparation callers borrow the same actual actor timer words.
// Legacy Process records keep their existing owners and entry scopes.
struct GroundDriveTimerView { int& start;int& padding;int& remaining; };
// Optional preparation join. Route finding is supplied; every consumer below
// binds an actual map/resident/House/Cell algorithm on the same borrowed owners.
// Absence retains the earlier failed-pathfinder and flag-zero refusals.
struct GroundDrivePreparationServices {
    const int& closeEnough;
    int heightDivisor;
    std::function<bool()> findRoute;
    std::function<bool(std::int16_t,std::int16_t)> permission;
    std::function<int(const GroundDriveCell&,bool)> resident;
    std::function<bool(int)> allied;
    std::function<bool()> passengers;
    std::function<std::uint32_t(const GroundDriveCell&)> flags;
    std::function<void(const GroundDriveCell&,std::uint8_t)> scatter;
    std::function<void()> setCounter;
    std::function<bool()> closeTarget;
};
struct GroundDriveProcessResultServices {
    std::uint8_t& onMap7d;
    std::uint8_t& flag76;
    std::uint8_t& flag7a;
    std::uint8_t& field5b9;
    std::uint8_t& shortTrack60;
    std::uint8_t& flag61;
    std::uint8_t& curve64;
    GroundDriveTimerView retry;
    GroundDriveTimerView wait;
    // Bind actual child algorithms on the same owners, not supplied success.
    std::function<bool(int,bool)> advance;
    std::function<bool()> idleTarget;
    std::function<int()> mission;
    std::function<bool()> hasTarget;
    std::function<void()> moveToTarget;
    std::function<void()> zeroPercentage;
    std::function<bool()> finishEmptyPreparation;
    std::function<int()> targetKind;
    const GroundDrivePreparationServices* preparation=nullptr;
};
struct GroundDriveMovingWaitServices {
    int duration=0,temporaryPadding=0;
    // Supplied failed pathfinder, false accessibility and mission request,
    // in that order. The original caller selects the measured option1 or2.
    std::function<void(int)> failedRoute;
};
bool processMovingResidentOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundDriveAdmissionServices&,const GroundDriveResidentRetry&,
    GroundDriveMovingWaitState&,const GroundDriveMovingWaitServices&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
// Separate complete Process join for actual Advance0/2/7. Result7 continues
// the committed track through the unsigned default branch; preparation retains
// the moving-resident wait/retry behavior above. Other Advance results/scatter
// remain refused. Shared owned-world/runtime adoption is a separate gate.
bool processAdvanceAdmittedOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundDriveAdmissionServices&,const GroundDriveResidentRetry&,
    GroundDriveMovingWaitState&,const GroundDriveMovingWaitServices&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
// Separate result-bearing caller control through the same Process/preparation
// kernel. The composition checks ordinary flags325/32D/wake-effect exclusions
// and binds actual children. Runtime adoption remains a separate gate.
bool processResultOrdinaryGroundDrive(GroundDriveProcessState&,const DriveData&,int speed,
    int tick,int timerPadding,const GroundDriveProcessServices&,
    const std::function<bool(std::int16_t,std::int16_t)>& checkGates,
    const GroundDriveAdmissionServices&,const GroundDriveResidentRetry&,
    const GroundDriveMovingWaitServices&,const GroundDriveProcessResultServices&,
    const GroundStateStore& actorStore={},const GroundStateStore& rampStore={});
}
