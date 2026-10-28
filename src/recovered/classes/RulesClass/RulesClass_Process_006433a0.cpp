// void RulesClass::Process(CCINIClass &ini) (0x006433A0)
// Rebuilds the rules: deletes every colour scheme (then 0x00603950), team,
// task force, script, overlay, smudge, terrain, infantry, unit, aircraft,
// bullet, building, super weapon, animation, weapon, warhead, voxel
// animation, particle, particle system, house and house type; reads
// [Maximums] Players, then Addition(ini), then LANGRULE.INI when present
// (a load result above 1 stops here), then the multiplayer session's INI.
// @ref ??1ColorScheme@@QAE@XZ=00663bb0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_C@_07CGJA@Players?$AA@=007eef08
// @ref ??_C@_0N@MIIG@LANGRULE?4INI?$AA@=007dbb2c
// @ref ?Addition@RulesClass@@QAE_NAAVCCINIClass@@@Z=006437f0
// @ref ?Clear@?$VectorClass@PAVColorScheme@@@@UAEXXZ=00604eb0
// @ref ?Unknown_00603950@@YAXXZ=00603950
// @ref ?unknown_ini_005b7840@UnknownSessionA3D29C@@QAEPAVCCINIClass@@XZ=005b7840
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/color_scheme.hpp"
#include "shared/script.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/overlay_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/terrain_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/building_type.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/radar.hpp"

void Unknown_00603950();

void RulesClass::Process(CCINIClass &ini)
{
    while (ColorSchemes.Count()) delete ColorSchemes[0];
    ColorSchemes.Clear();
    Unknown_00603950();

    while (TeamTypes.Count()) delete TeamTypes[0];
    while (TaskForces.Count()) delete TaskForces[0];
    while (ScriptTypes.Count()) delete ScriptTypes[0];
    while (OverlayTypes.Count()) delete OverlayTypes[0];
    while (SmudgeTypes.Count()) delete SmudgeTypes[0];
    while (TerrainTypes.Count()) delete TerrainTypes[0];
    while (InfantryTypes.Count()) delete InfantryTypes[0];
    while (UnitTypes.Count()) delete UnitTypes[0];
    while (AircraftTypes.Count()) delete AircraftTypes[0];
    while (BulletTypes.Count()) delete BulletTypes[0];
    while (BuildingTypes.Count()) delete BuildingTypes[0];
    while (SuperWeaponTypes.Count()) delete SuperWeaponTypes[0];
    while (AnimTypes.Count()) delete AnimTypes[0];
    while (unknown_WeaponTypeClass_list_00839b90.Count()) delete unknown_WeaponTypeClass_list_00839b90[0];
    while (unknown_WarheadTypeClass_list_00839b00.Count()) delete unknown_WarheadTypeClass_list_00839b00[0];
    while (VoxelAnimTypes.Count()) delete VoxelAnimTypes[0];
    while (ParticleTypes.Count()) delete ParticleTypes[0];
    while (ParticleSystemTypes.Count()) delete ParticleSystemTypes[0];
    while (Houses.Count()) delete Houses[0];
    while (HouseTypes.Count()) delete HouseTypes[0];

    if (ini.Is_Present(RulesSection_Maximums)) {
        MaxPlayers = ini.Get_Int(RulesSection_Maximums, "Players", MaxPlayers);
    }
    Addition(ini);

    CCFileClass file("LANGRULE.INI");
    if (file.Is_Available() == true) {
        CCINIClass langini;
        if (langini.Load(file, true) > 1) {
            return;
        }
        Addition(langini);
    }
    if (unknown_game_mode_a3d298 && unknown_session_a3d29c) {
        Addition(*unknown_session_a3d29c->unknown_ini_005b7840());
    }
}
