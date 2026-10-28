// TeamClass::TeamClass(TeamTypeClass *type, HouseClass *owner, int arg3) (0x006B7430)
// Creates a team of a type for a house: joins the team list and the abstract
// lists, counts itself in its type (and the owner's team count), makes the
// script and tag, and heads for the type's waypoint.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/tag.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?Waypoint_Location@TeamTypeClass@@QBE?AVCell@@XZ=006bfa90
// @ref ?unknown_cell_ac0050@@3VCell@@A=00ac0050
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??0TagClass@@QAE@PAVTagTypeClass@@@Z=006b3870
// @ref ??0ScriptClass@@QAE@PAVScriptTypeClass@@@Z=00668730
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_objects_ac0d30@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d30

extern Cell unknown_cell_ac0050;
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0;
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0d30;

TeamClass::TeamClass(TeamTypeClass *type, HouseClass *owner, int arg3) :
    Class(type),
    Script(0),
    Owner(owner),
    unknown_30(0),
    unknown_34(0),
    unknown_38(0),
    unknown_3c(0),
    unknown_40(0),
    unknown_44((AbstractClass *)arg3),
    unknown_48(0),
    unknown_4c(0),
    unknown_50(Frame),
    Member(0),
    unknown_58(),
    unknown_64(0L),
    Tag(0),
    IsTransient(false),
    NeedsReGrouping(false),
    GuardSlowerIsNotUnderStrength(false),
    IsForcedActive(false),
    IsHasBeen(false),
    IsFullStrength(false),
    IsUnderStrength(true),
    IsReforming(false),
    IsLagging(false),
    NeedsToDisappear(true),
    JustDisappeared(false),
    IsMoving(false),
    StepCompleted(true),
    TargetNotAssigned(false),
    IsLeavingMap(false),
    IsSuspended(false)
{
    Teams.Add(this);
    unknown_objects_ac0cb0.Add(this);
    unknown_objects_ac0c58.Add(this);
    unknown_AbstractClass_list_00ac0d60.Add(this);
    unknown_objects_ac0d30.Add(this);
    memset(unknown_84, 0, sizeof(unknown_84));
    if (Class != 0) {
        if (Owner != 0 && Class->IsBaseDefense) {
            Owner->unknown_555c++;
        }
        if (Class->Waypoint_Location() != unknown_cell_ac0050) {
            unknown_34 = (AbstractClass *)&Map[Class->Waypoint_Location()];
        }
        Class->unknown_d4++;
        if (Class->Tag != 0) {
            Tag = new TagClass(Class->Tag);
        }
        Script = new ScriptClass(Class->Script);
    }
}
