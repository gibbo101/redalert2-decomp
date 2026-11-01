// bool __fastcall Put_All(IStream *stream, int save_net) (0x006558B0; TibSun saveload.cpp Put_All)
// Writes the scenario, the checkpoint, the rules, every object and type list, the
// misc values, the logic and tactical map, the trackers, the skirmish options and
// the theme. Lists go through Save_Vector (shared/save_vector.hpp): the inline
// budget expands the first 23 and keeps the rest as out-of-line COMDATs
// (0x006580C0-0x00659140); the pointer list 0x00A35DB8 is written as raw pointers;
// the AITriggerTypes and Actions results are not tested. DebugString is the
// release build's empty inline (TibSun dbgprint.h): its calls emit nothing, but
// their IL sets the caller's inline budget (the "Saving" lines of the non-list
// steps and the FAILED lines; which ones the original kept is a hypothesis
// bounded by the budget: 6 to ~20 "Saving" lines give the original's 23 inline
// copies). The skirmish lines call Debug_Printf 0x004068F0.
// @ref ?Logic@@3VLogicClass@@A=00832470
// @ref ?BombList@@3VBombListClass@@A=008322e0
// @ref ?unknown_slot31@MouseClass@@QAEJPAUIStream@@@Z=0059fc80
// @ref ?Save@UnknownLobbyState@@QAE_NPAUIStream@@@Z=00672830
// @ref ?Save@ThemeClass@@QAEJPAUIStream@@@Z=006e8310
// @ref ?Voc_Static_Save@@YIJPAUIStream@@@Z=00714a90
// @ref ?Speech_Save@@YIJPAUIStream@@@Z=00716790
// @ref ??_C@_0CC@ODF@Writing?5Skirmish?5Session?4Options@=007f1b94
// @ref ??_C@_0BA@JBMB@?7?$CK?$CK?$CK?$CK?$CK?5FAILED?$CB?6?$AA@=007f1b3c
#include "shared/abstract.hpp"
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/aircraft.hpp"
#include "shared/house_type.hpp"
#include "shared/house.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/ai_trigger_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/task_force.hpp"
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/script.hpp"
#include "shared/tag_type.hpp"
#include "shared/tag.hpp"
#include "shared/trigger_type.hpp"
#include "shared/trigger.hpp"
#include "shared/taction.hpp"
#include "shared/tevent.hpp"
#include "shared/factory_class.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/voxel_anim.hpp"
#include "shared/warhead_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/particle.hpp"
#include "shared/bullet_type.hpp"
#include "shared/bullet.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/smudge_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/light_source.hpp"
#include "shared/building_light.hpp"
#include "shared/tube.hpp"
#include "shared/side.hpp"
#include "shared/tiberium.hpp"
#include "shared/empulse_class.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/super.hpp"
#include "shared/terrain_type.hpp"
#include "shared/terrain.hpp"
#include "shared/object.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/fogged_object.hpp"
#include "shared/alpha_shape.hpp"
#include "shared/alpha_shape_list.hpp"
#include "shared/wave.hpp"
#include "shared/veinhole.hpp"
#include "shared/capture_manager.hpp"
#include "shared/parasite.hpp"
#include "shared/temporal.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/spawn_manager_list.hpp"
#include "shared/radsite.hpp"
#include "shared/foot.hpp"
#include "shared/kamikaze_tracker.hpp"
#include "shared/id_source.hpp"
#include "shared/scenario_checkpoint.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/debug_printf.hpp"
#define LOBBY_STATE_SAVELOAD
#include "shared/lobby.hpp"
#define THEME_SAVELOAD
#include "shared/theme.hpp"
#include "shared/save_vector.hpp"
#include "shared/saveload_lists.hpp"

bool __fastcall Put_All(IStream *stream, int save_net)
{
    unknown_id_source_a3d290->Save(stream);
    unknown_scenario_checkpoint_00855a90.Write_004B5C70(stream);
    Rules->Save(stream);
    if (FAILED(Save_Vector(stream, AnimTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Map\n");
    Map.unknown_slot31(stream);
    if (FAILED(Save_Vector(stream, unknown_TubeClass_list_008661c8))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Misc. Values\n");
    if (FAILED(Save_Misc_Values(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Logic\n");
    Logic.Save(stream);
    DebugString("Saving TacticalMap\n");
    if (FAILED(OleSaveToStream(unknown_tactical_83996c, stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, HouseTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Houses))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Units))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, UnitTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, InfantryTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Infantry))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, BuildingTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_BuildingClass_list_00a40af8))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, AircraftTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Aircraft))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Anims))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, TaskForces))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, TeamTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Teams))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, ScriptTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Scripts))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_TagTypeClass_list_00abfea0))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_TagClass_list_00abfe48))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, TriggerTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_TriggerClass_list_00a40aa0))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    Save_Vector(stream, AITriggerTypes);
    DebugString("\t***** FAILED!\n");
    Save_Vector(stream, unknown_TActionClass_list_00abfd88);
    DebugString("\t***** FAILED!\n");
    if (FAILED(Save_Vector(stream, unknown_TEventClass_list_00ac0808))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Factories))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, VoxelAnimTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_VoxelAnimClass_list_008399d0))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_WarheadTypeClass_list_00839b00))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_WeaponTypeClass_list_00839b90))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, ParticleTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_ParticleClass_list_00a35e28))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, ParticleSystemTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, ParticleSystems))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, BulletTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_BulletClass_list_00a40ce8))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_WaypointPathClass_list_00b25590))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, SmudgeTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, OverlayTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_LightSourceClass_list_00a6e818))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, BuildingLights))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Sides))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_TiberiumClass_list_00ac0b30))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, EMPulseClass::Array))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, SuperWeaponTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Supers))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    {
        int count = unknown_supers_a35db8.Count();
        HRESULT result = stream->Write(&count, sizeof(count), 0);
        if (SUCCEEDED(result)) {
            for (int index = 0; index < count; index++) {
                SuperClass *super = unknown_supers_a35db8[index];
                result = stream->Write(&super, sizeof(super), 0);
                if (FAILED(result)) {
                    break;
                }
            }
        }
        if (FAILED(result)) {
            return false;
        }
    }
    if (FAILED(Save_Vector(stream, TerrainTypes))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Terrains))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, FoggedObjectClass::Array))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_AlphaShapeClass_list_0083c648))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, Waves))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving VeinholeMonster\n");
    if (!VeinholeMonsterClass::Save_All(stream)) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving RadarEvents\n");
    if (!RadarEventClass_unknown_save_all(stream)) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_CaptureManagerClass_list_008505a0))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_ParasiteClass_list_00a76430))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_TemporalClass_list_00ac02e0))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_SpawnManagerClass_list_00abd028))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Unit Tracker\n");
    if (FAILED(unknown_tracker_839ea0.Save_00413590(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving KamikazeTracker\n");
    if (FAILED(KamikazeTracker.Save(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving BombList\n");
    if (FAILED(BombList.Save(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_BombClass_list_0084eb78))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Save_Vector(stream, unknown_RadSiteClass_list_00ab6620))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (unknown_game_mode_a3d298 == 5) {
        Debug_Printf("Writing Skirmish Session.Options\n");
        if (!unknown_lobby_state_a3d2b0.Save(stream)) {
            Debug_Printf("\t***** FAILED!\n");
            return false;
        }
    }
    DebugString("Saving Static Sounds\n");
    if (FAILED(Voc_Static_Save(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Speech\n");
    if (FAILED(Speech_Save(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    DebugString("Saving Theme\n");
    if (FAILED(Theme.Save(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    return true;
}
