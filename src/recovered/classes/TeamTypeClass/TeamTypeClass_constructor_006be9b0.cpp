// TeamTypeClass::TeamTypeClass(char const *ini_name) (0x006BE9B0)
// Default team type, registered in TeamTypes and the abstract list
// 0x00AC0CB0; ArrayIndex is its index in TeamTypes.
#include "shared/team_type.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_7TeamTypeClass@@6BIPersistStream@@@=007ac9f0
// @ref ??_7TeamTypeClass@@6BIRTTITypeInfo@@@=007ac9d4
// @ref ??_7TeamTypeClass@@6BINoticeSink@@@=007ac9cc
// @ref ??_7TeamTypeClass@@6BINoticeSource@@@=007ac9c4
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0cb0

TeamTypeClass::TeamTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    ArrayIndex(-1),
    Group(-1),
    VeteranLevel(1),
    Loadable(false),
    Full(false),
    Annoyance(false),
    GuardSlower(false),
    Recruiter(false),
    Autocreate(false),
    Prebuild(false),
    Reinforce(false),
    Whiner(false),
    Aggressive(false),
    LooseRecruit(false),
    Suicide(false),
    Droppod(false),
    UseTransportOrigin(false),
    unknown_b2(false),
    OnTransOnly(false),
    Priority(7),
    Max(-1),
    unknown_bc(0),
    Owner(0),
    TechLevel(0),
    Tag(0),
    Waypoint(-1),
    TransportWaypoint(-1),
    unknown_d4(0),
    Script(0),
    TaskForce(0),
    IsGlobal(0),
    unknown_e4(9),
    unknown_e8(true),
    unknown_e9(false),
    AvoidThreats(false),
    IonImmune(false),
    TransportsReturnOnUnload(false),
    AreTeamMembersRecruitable(true),
    IsBaseDefense(false),
    OnlyTargetHouseEnemy(false)
{
    TeamTypes.Add(this);
    ArrayIndex = TeamTypes.ID(this);
    unknown_objects_ac0cb0.Add(this);
}
