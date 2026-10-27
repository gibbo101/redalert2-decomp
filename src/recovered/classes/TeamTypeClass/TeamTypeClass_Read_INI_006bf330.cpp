// bool TeamTypeClass::Read_INI(CCINIClass &ini) (0x006BF330, slot 25)
// The abstract type's keys, then the team keys under the team's ID: the
// owner (by house type index), the flags and limits, the tag, waypoints
// (by name), script and task force (made when missing).
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/tag_type.hpp"
#include "shared/script.hpp"
#include "shared/task_force.hpp"
#include "shared/ccini_class.hpp"
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ?Get_HousesType@CCINIClass@@QBEHPBD0H@Z=0046aa00
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ?Find_Or_Make@TagTypeClass@@SIPAV1@PBD@Z=006b4d20
// @ref ?Find_Or_Make@ScriptTypeClass@@SIPAV1@PBD@Z=00668f70
// @ref ?Find_Or_Make@TaskForceClass@@SIPAV1@PBD@Z=006b6fb0
// @ref ?Waypoint_Name_7249f0@@YIPADH@Z=007249f0
// @ref ?Waypoint_From_Name_724a70@@YIHPAD@Z=00724a70


// The name of a waypoint index ("A".."ZZ") and back (0x007249F0,
// 0x00724A70, __fastcall; names hypotheses).
char *__fastcall Waypoint_Name_7249f0(int waypoint);
int __fastcall Waypoint_From_Name_724a70(char *name);

static inline TagTypeClass *Get_Tag(CCINIClass &ini, char const *section, char const *entry, TagTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return TagTypeClass::Find_Or_Make(name);
    }
    return defvalue;
}

static inline ScriptTypeClass *Get_Script(CCINIClass &ini, char const *section, char const *entry, ScriptTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return ScriptTypeClass::Find_Or_Make(name);
    }
    return defvalue;
}

static inline TaskForceClass *Get_Task_Force(CCINIClass &ini, char const *section, char const *entry, TaskForceClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return TaskForceClass::Find_Or_Make(name);
    }
    return defvalue;
}

bool TeamTypeClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
        int house = -1;
        if (Owner != 0) {
            house = Owner->Type->House;
        }
        house = ini.Get_HousesType(ID, "House", house);
        if (house != -1) {
            Owner = HouseClass::As_Pointer(house);
        }
        VeteranLevel = ini.Get_Int(ID, "VeteranLevel", VeteranLevel);
        Loadable = ini.Get_Bool(ID, "Loadable", Loadable);
        Full = ini.Get_Bool(ID, "Full", Full);
        Annoyance = ini.Get_Bool(ID, "Annoyance", Annoyance);
        GuardSlower = ini.Get_Bool(ID, "GuardSlower", GuardSlower);
        Autocreate = ini.Get_Bool(ID, "Autocreate", Autocreate);
        Prebuild = ini.Get_Bool(ID, "Prebuild", Prebuild);
        Reinforce = ini.Get_Bool(ID, "Reinforce", Reinforce);
        Droppod = ini.Get_Bool(ID, "Droppod", Droppod);
        UseTransportOrigin = ini.Get_Bool(ID, "UseTransportOrigin", UseTransportOrigin);
        Recruiter = ini.Get_Bool(ID, "Recruiter", Recruiter);
        Whiner = ini.Get_Bool(ID, "Whiner", Whiner);
        Suicide = ini.Get_Bool(ID, "Suicide", Suicide);
        LooseRecruit = ini.Get_Bool(ID, "LooseRecruit", LooseRecruit);
        Aggressive = ini.Get_Bool(ID, "Aggressive", Aggressive);
        OnTransOnly = ini.Get_Bool(ID, "OnTransOnly", OnTransOnly);
        Priority = ini.Get_Int(ID, "Priority", Priority);
        Max = ini.Get_Int(ID, "Max", Max);
        TechLevel = ini.Get_Int(ID, "TechLevel", TechLevel);
        Tag = Get_Tag(ini, ID, "Tag", Tag);
        Group = ini.Get_Int(ID, "Group", Group);
        AvoidThreats = ini.Get_Bool(ID, "AvoidThreats", AvoidThreats);
        IonImmune = ini.Get_Bool(ID, "IonImmune", IonImmune);
        IsBaseDefense = ini.Get_Bool(ID, "IsBaseDefense", IsBaseDefense);
        OnlyTargetHouseEnemy = ini.Get_Bool(ID, "OnlyTargetHouseEnemy", OnlyTargetHouseEnemy);
        TransportsReturnOnUnload = ini.Get_Bool(ID, "TransportsReturnOnUnload", TransportsReturnOnUnload);
        AreTeamMembersRecruitable = ini.Get_Bool(ID, "AreTeamMembersRecruitable", AreTeamMembersRecruitable);
        char buffer[64];
        if (ini.Get_String(ID, "Waypoint", Waypoint_Name_7249f0(Waypoint), buffer, sizeof(buffer)) > 0) {
            Waypoint = Waypoint_From_Name_724a70(buffer);
        }
        if (ini.Get_String(ID, "TransportWaypoint", Waypoint_Name_7249f0(TransportWaypoint), buffer, sizeof(buffer)) > 0) {
            TransportWaypoint = Waypoint_From_Name_724a70(buffer);
        }
        Script = Get_Script(ini, ID, "Script", Script);
        TaskForce = Get_Task_Force(ini, ID, "TaskForce", TaskForce);
        return true;
    }
    return false;
}
