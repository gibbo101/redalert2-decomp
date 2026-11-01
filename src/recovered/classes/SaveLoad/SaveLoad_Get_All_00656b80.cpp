// bool __fastcall Get_All(IStream *stream, bool save_net) (0x00656B80; TibSun saveload.cpp Get_All)
// Clears the scenario, reads the scenario, prepares the side, reallocates the surfaces
// for the tactical view, then reads back everything Put_All 0x006558B0 wrote. Each
// object list is recreated through Skip_Objects 0x00654C40 (TibSun's Load_Vector: the
// objects re-add themselves); the inline budget expands the early calls.
// @ref ?Load@UnknownLobbyState@@QAE_NPAUIStream@@@Z=00672880
// @ref ?Load@ThemeClass@@QAEJPAUIStream@@@Z=006e8340
// @ref ?Load@BombListClass@@QAEJPAUIStream@@@Z=00436860
// @ref ?unknown_slot30@MouseClass@@QAEJPAUIStream@@@Z=0059f530
// @ref ?unknown_slot42@MouseClass@@QAEXABVRect@@@Z=00498c80
// @ref ?Clear@BombListClass@@QAEXXZ=00436710
// @ref ??_C@_0CC@EKPA@Reading?5Skirmish?5Session?4Options@=007f1bec
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
#include "shared/swizzle.hpp"
#include "shared/main_opt.hpp"
#include "shared/main_loop.hpp"
#include "shared/saveload_lists.hpp"

bool __fastcall Get_All(IStream *stream, bool save_net)
{
    Clear_Scenario_0065d370();
    unknown_id_source_a3d290->Load(stream);
    if (!Unknown_0051a330(unknown_id_source_a3d290->unknown_2239 ? 0 : 1)) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    Rect temp = Unknown_006F1F30();
    {
        Rect sidebar(0, 0, unknown_int_7add80, unknown_window_839640.Height);
        Rect tile(0, 0, temp.Width, unknown_window_839640.Height);
        Rect composite(0, 0, temp.Width, unknown_window_839640.Height);
        Allocate_Surfaces(&unknown_window_839640, &composite, &tile, &sidebar, false);
    }
    Map.unknown_slot42(temp);
    unknown_scenario_checkpoint_00855a90.Read_004B5C50(stream);
    Init_Theater_00519e70(unknown_id_source_a3d290->Theater);
    Rules->Load(stream);
    if (FAILED(Skip_Objects(stream))) {    // AnimTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    Map.unknown_slot30(stream);
    if (FAILED(Skip_Objects(stream))) {    // Tubes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Load_Misc_Values(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    Map.Unknown_00563D40();
    Logic.Load(stream);
    if (unknown_tactical_83996c != 0) {
        delete unknown_tactical_83996c;
        unknown_tactical_83996c = 0;
    }
    Tactical *old_tactical;
    if (FAILED(OleLoadFromStream(stream, IID_IUnknown_7afce0, (void **)&old_tactical))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // HouseTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Houses
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Units
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // UnitTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // InfantryTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Infantry
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // BuildingTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Buildings
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // AircraftTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Aircraft
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Anims
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // TaskForces
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // TeamTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Teams
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // ScriptTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Scripts
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // TagTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Tags
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // TriggerTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Triggers
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // AITriggerTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Actions
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Events
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Factories
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // VoxelAnimTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // VoxelAnims
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Warheads
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Weapons
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // ParticleTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Particles
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // ParticleSystemTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // ParticleSystems
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // BulletTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Bullets
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // WaypointPaths
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // SmudgeTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // OverlayTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // LightSources
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // BuildingLights
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Sides
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Tiberiums
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // EMPulses
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // SuperWeaponTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // SuperWeapons
        DebugString("\t***** FAILED!\n");
        return false;
    }
    unknown_supers_a35db8.Clear();
    {
        int count;
        SuperClass *super;
        HRESULT result = stream->Read(&count, sizeof(count), 0);
        if (SUCCEEDED(result) && count > 0) {
            int index;
            for (index = 0; index < count; index++) {
                result = stream->Read(&super, sizeof(super), 0);
                if (FAILED(result)) {
                    break;
                }
                unknown_supers_a35db8.Add(super);
            }
            for (index = 0; index < count; index++) {
                SwizzleManager.Swizzle((void **)&unknown_supers_a35db8[index]);
            }
        }
        if (FAILED(result)) {
            DebugString("\t***** FAILED!\n");
            return false;
        }
    }
    if (FAILED(Skip_Objects(stream))) {    // TerrainTypes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Terrains
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // FoggedObjects
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // AlphaShapes
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Waves
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (!VeinholeMonsterClass::Load_All(stream)) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (!RadarEventClass_unknown_load_all(stream)) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // CaptureManagers
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Parasites
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Temporals
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // SpawnManagers
        DebugString("\t***** FAILED!\n");
        return false;
    }
    unknown_tracker_839ea0.Clear_00413540();
    if (FAILED(unknown_tracker_839ea0.Load_00413400(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    KamikazeTracker.Clear();
    if (FAILED(KamikazeTracker.Load(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    BombList.Clear();
    if (FAILED(BombList.Load(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // Bombs
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Skip_Objects(stream))) {    // RadSites
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (unknown_game_mode_a3d298 == 5) {
        Debug_Printf("Reading Skirmish Session.Options\n");
        if (!unknown_lobby_state_a3d2b0.Load(stream)) {
            Debug_Printf("\t***** FAILED!\n");
            return false;
        }
    }
    if (FAILED(Voc_Static_Load(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Speech_Load(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    if (FAILED(Theme.Load(stream))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }
    Map.Flag_To_Redraw(2);
    if (unknown_game_mode_a3d298 == 0) {
        unknown_flag_a6ebd0 = true;
    }
    return true;
}
