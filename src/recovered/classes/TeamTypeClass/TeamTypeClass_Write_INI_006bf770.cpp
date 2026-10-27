// bool TeamTypeClass::Write_INI(CCINIClass &ini) const (0x006BF770, slot 26)
// The abstract type's keys, then every team key under the team's ID; the
// house is written by its type's index (-1 for none), waypoints by name,
// and the tag, script and task force by ID when set.
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/tag_type.hpp"
#include "shared/script.hpp"
#include "shared/task_force.hpp"
#include "shared/ccini_class.hpp"
// @ref ??_C@_05GGEJ@Group?$AA@=007f6dac
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
// @ref ?Put_Bool@INIClass@@QAE_NPBD0_N@Z=0050f380
// @ref ?Put_HousesType@CCINIClass@@QAE_NPBD0H@Z=0046aab0
// @ref ?Put_String@INIClass@@QAE_NPBD00@Z=0050e5f0
// @ref ?Waypoint_Name_7249f0@@YIPADH@Z=007249f0
// @ref ??_C@_03CHAC@Tag?$AA@=007cdce4
// @ref ??_C@_03GMOG@Max?$AA@=007f7034
// @ref ??_C@_04OOPN@Full?$AA@=007f70e0
// @ref ??_C@_05DIE@House?$AA@=007cde40
// @ref ??_C@_06GELG@Script?$AA@=007cdda0
// @ref ??_C@_06KEIO@Whiner?$AA@=007f7074
// @ref ??_C@_07GFCG@Droppod?$AA@=007f709c
// @ref ??_C@_07JAAJ@Suicide?$AA@=007f706c
// @ref ??_C@_08LLBB@Loadable?$AA@=007f70e8
// @ref ??_C@_08MJHG@Priority?$AA@=007f7038
// @ref ??_C@_08MLCN@Prebuild?$AA@=007f70b0
// @ref ??_C@_08PLKM@Waypoint?$AA@=007cdc9c
// @ref ??_C@_09FKED@TechLevel?$AA@=007da8bc
// @ref ??_C@_09GHMB@Reinforce?$AA@=007f70a4
// @ref ??_C@_09KPKI@Annoyance?$AA@=007f70d4
// @ref ??_C@_09LFAP@Recruiter?$AA@=007f707c
// @ref ??_C@_09LPKL@IonImmune?$AA@=007f7018
// @ref ??_C@_09MNJN@TaskForce?$AA@=007cdd54
// @ref ??_C@_0BC@DBEL@TransportWaypoint?$AA@=007f6fb4
// @ref ??_C@_0BD@CJAD@UseTransportOrigin?$AA@=007f7088
// @ref ??_C@_0BF@FMMK@OnlyTargetHouseEnemy?$AA@=007f7000
// @ref ??_C@_0BJ@BOLL@TransportsReturnOnUnload?$AA@=007f6fe4
// @ref ??_C@_0BK@ICCI@AreTeamMembersRecruitable?$AA@=007f6fc8
// @ref ??_C@_0L@GDKO@Autocreate?$AA@=007f70bc
// @ref ??_C@_0L@HKNK@Aggressive?$AA@=007f7050
// @ref ??_C@_0M@CCCO@OnTransOnly?$AA@=007f7044
// @ref ??_C@_0M@PENK@GuardSlower?$AA@=007f70c8
// @ref ??_C@_0N@BOHN@VeteranLevel?$AA@=007f70f4
// @ref ??_C@_0N@DDPB@AvoidThreats?$AA@=007f7024
// @ref ??_C@_0N@EBAO@LooseRecruit?$AA@=007f705c
// @ref ??_C@_0O@OBEE@IsBaseDefense?$AA@=007d0c34

// The name of a waypoint index ("A".."ZZ"; 0x007249F0, __fastcall; name
// hypothesis).
char *__fastcall Waypoint_Name_7249f0(int waypoint);

bool TeamTypeClass::Write_INI(CCINIClass &ini) const
{
    if (AbstractTypeClass::Write_INI(ini)) {
        int house = -1;
        if (Owner != 0) {
            house = Owner->Type->House;
        }
        ini.Put_Int(ID, "VeteranLevel", VeteranLevel);
        ini.Put_Bool(ID, "Loadable", Loadable);
        ini.Put_Bool(ID, "Full", Full);
        ini.Put_Bool(ID, "Annoyance", Annoyance);
        ini.Put_Bool(ID, "GuardSlower", GuardSlower);
        ini.Put_HousesType(ID, "House", house);
        ini.Put_Bool(ID, "Recruiter", Recruiter);
        ini.Put_Bool(ID, "Autocreate", Autocreate);
        ini.Put_Bool(ID, "Prebuild", Prebuild);
        ini.Put_Bool(ID, "Reinforce", Reinforce);
        ini.Put_Bool(ID, "Droppod", Droppod);
        ini.Put_Bool(ID, "UseTransportOrigin", UseTransportOrigin);
        ini.Put_Bool(ID, "Whiner", Whiner);
        ini.Put_Bool(ID, "LooseRecruit", LooseRecruit);
        ini.Put_Bool(ID, "Aggressive", Aggressive);
        ini.Put_Bool(ID, "Suicide", Suicide);
        ini.Put_Int(ID, "Priority", Priority);
        ini.Put_Int(ID, "Max", Max);
        ini.Put_Int(ID, "TechLevel", TechLevel);
        ini.Put_Int(ID, "Group", Group);
        ini.Put_Bool(ID, "OnTransOnly", OnTransOnly);
        ini.Put_Bool(ID, "AvoidThreats", AvoidThreats);
        ini.Put_Bool(ID, "IonImmune", IonImmune);
        ini.Put_Bool(ID, "TransportsReturnOnUnload", TransportsReturnOnUnload);
        ini.Put_Bool(ID, "AreTeamMembersRecruitable", AreTeamMembersRecruitable);
        ini.Put_Bool(ID, "IsBaseDefense", IsBaseDefense);
        ini.Put_Bool(ID, "OnlyTargetHouseEnemy", OnlyTargetHouseEnemy);
        if (Tag != 0) {
            ini.Put_String(ID, "Tag", Tag->ID);
        }
        ini.Put_String(ID, "Waypoint", Waypoint_Name_7249f0(Waypoint));
        ini.Put_String(ID, "TransportWaypoint", Waypoint_Name_7249f0(TransportWaypoint));
        if (Script != 0) {
            ini.Put_String(ID, "Script", Script->ID);
        }
        if (TaskForce != 0) {
            ini.Put_String(ID, "TaskForce", TaskForce->ID);
        }
        return true;
    }
    return false;
}
