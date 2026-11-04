// void Clear_Scenario_0065d370() (0x0065D370)
// @ref ??_C@_0BC@BGO@Init_Campaigns?$CI?$CJ?6?$AA@=007f2054
// @ref ??_C@_0BC@EODN@Map?4Init_Clear?$CI?$CJ?6?$AA@=007f20b0
// @ref ??_C@_0BI@FJL@CurrentObjects?4Clear?$CI?$CJ?6?$AA@=007f2088
// @ref ??_C@_0BN@MFKB@Scen?9?$DOClear_All_Waypoints?$CI?$CJ?6?$AA@=007f2068
// @ref ??_C@_0O@PDD@Logic?4Init?$CI?$CJ?6?$AA@=007f20a0
// @ref ?CurrentObjects@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Set_Defaults@UnknownIDSource@@QAEXXZ=0065b830
// @ref ?Unknown_00613E50@@YAXXZ=00613e50
// @ref ?Unknown_006F89E0@@YAXXZ=006f89e0
// @ref ?Unknown_00714410@@YAXXZ=00714410
// @ref ?unknown_bomb_list_8322e0@@3VBombListClass@@A=008322e0
// @ref ?unknown_map_list_83252c@@3V?$DynamicVectorClass@H@@A=0083252c
// @ref ?unknown_gas_cloud_system_a40d20@@3PAVParticleSystemClass@@A=00a40d20
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_0051FBB0@@YAXXZ=0051fbb0
// @ref ?unknown_tags_866160@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866160
// @ref ?unknown_tags_866238@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866238
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"
#include "shared/object.hpp"
#include "shared/tag_type.hpp"
#include "shared/isometric_tile.hpp"

#include "shared/light_source.hpp"
#include "shared/empulse_class.hpp"
#include "shared/veinhole.hpp"
#include "shared/tactical.hpp"
#include "shared/particle_system.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
#include "shared/logic.hpp"
#include "shared/kamikaze_tracker.hpp"
#include "shared/unit.hpp"
#include "shared/lightning_storm.hpp"

// Existing canonical callees; no new ABI aliases.
void __fastcall Read_Battle_Files();
void __fastcall Delete_All_Objects_00519960();
void RadarEventClass_unknown_reset_cells();
// Existing accepted operation 00663220, expanded here as allowed for a caller in another population.
namespace seed_00663220 {
extern "C" unsigned int _DAT_00ab6e88;
inline void __fastcall FUN_00663220(int scenario)
{
    unsigned int *waypoint = (unsigned int *)(scenario + 0x632);
    int remaining = 101;
    do {
        *waypoint = _DAT_00ab6e88;
        ++waypoint;
        --remaining;
    } while (remaining != 0);
}
}
// LayerClass virtual slot8 is the original 5-byte dispatch to virtual Clear atslot3.
// The name remains the existing shared/layer.hpp contract; no new wrapper or ABI alias.
inline void LayerClass::unknown_slot8() { Clear(); }
// @ref ?unknown_slot8@LayerClass@@UAEXXZ=0040caf0

namespace seed_006e9670 { void FUN_006e9670(); }
namespace seed_006ea130 { void FUN_006ea130(); }
void Unknown_00714410();
void Unknown_00613E50();
void Unknown_0051FBB0();
extern HouseClass *unknown_player_a35db4;
extern BombListClass unknown_bomb_list_8322e0;
extern DynamicVectorClass<ObjectClass *> CurrentObjects;
extern DynamicVectorClass<int> unknown_map_list_83252c;
extern ParticleSystemClass *unknown_gas_cloud_system_a40d20;
extern DynamicVectorClass<TagClass *> unknown_tags_866160;
extern DynamicVectorClass<TagClass *> unknown_tags_866238;
extern Tactical *unknown_tactical_83996c;

void Clear_Scenario_0065d370()
{
    unknown_id_source_a3d290->UniqueID = 1000000;
    unknown_id_source_a3d290->RandomNumber.unknown_0x00 = true;
    unknown_saved_volume_7f1dec = 0x4000;
    Audio_Global_Levels[7]->Volume.Set(0x4000);
    Unknown_00714410();
    unknown_player_a35db4 = 0;
    unknown_id_source_a3d290->Set_Defaults();
    Unknown_0051FBB0();
    for (int index = AbstractTypes.Count() - 1; index >= 0; index--) {
        if (AbstractTypes[index]->What_Am_I() == 0x12) {
            AbstractTypes.Delete(index);
        }
    }
    Delete_All_Objects_00519960();
    for (int tile = 0; tile < IsoTileTypes.Count(); tile++) {
        AbstractTypes.Add((AbstractTypeClass *)IsoTileTypes[tile]);
    }
    Map.MapClass::unknown_slot23();
    unknown_map_list_83252c.Clear();
    TagClass::Clear_All();
    // Expand the existing global-variable setter for the scenario reset loop.
    for (unsigned variable = 0; variable < 50; ++variable) {
        UnknownIDSource *scenario = unknown_id_source_a3d290;
        if (variable * sizeof(scenario->Variables[0]) < sizeof(scenario->Variables)) {
                UnknownScenarioVariable_004B5AB0 &state = scenario->Variables[variable];
                bool old_value = state.Value;
                if (old_value != false) {
                    state.Value = false;
                    scenario->unknown_222e = true;
                    TagClass::unknown_func_6b4220(variable);
                }
        }
    }
    delete unknown_tactical_83996c;
    unknown_tactical_83996c = new Tactical;
    unknown_tactical_83996c->Reset_Dirty_Rectangles();
    unknown_flag_7df630 = false;
    while (unknown_objects_a40368.Count()) {
        if (unknown_objects_a40368[0]->Kind_Of() == 8) {
            unknown_objects_a40368[0]->Release();
        } else {
            delete unknown_objects_a40368[0];
        }
    }
    unknown_flag_7df630 = true;
    while (unknown_TagTypeClass_list_00abfea0.Count()) {
        delete unknown_TagTypeClass_list_00abfea0[0];
    }
    unknown_tags_866238.Clear();
    unknown_tags_866160.Clear();
    unknown_id_source_a3d290->ParTimeEasy = 3600;
    unknown_id_source_a3d290->ParTimeMedium = unknown_id_source_a3d290->ParTimeEasy;
    unknown_id_source_a3d290->ParTimeHard = unknown_id_source_a3d290->ParTimeEasy;
    unknown_id_source_a3d290->UnderParTitle[0] = '\0';
    unknown_id_source_a3d290->UnderParMessage[0] = '\0';
    unknown_id_source_a3d290->OverParTitle[0] = '\0';
    unknown_id_source_a3d290->OverParMessage[0] = '\0';
    LightSourceClass::Clear_All();
    Init_Storm_0051F2F0();
    EMPulseClass::Delete_All_004B4DC0();
    VeinholeMonsterClass::Clear_All();
    seed_006e9670::FUN_006e9670();
    seed_006ea130::FUN_006ea130();
    unknown_bomb_list_8322e0.Clear();
    KamikazeTracker.Clear();
    unknown_tracker_839ea0.Clear_00413540();
    Unknown_00613E50();
    Map.MapSize = Rect(0, 0, 0, 0);
    Debug_Printf("Map.Init_Clear()\n");
    Map.MouseClass::Init_Clear();
    Debug_Printf("Logic.Init()\n");
    Logic.LayerClass::unknown_slot8();
    Debug_Printf("CurrentObjects.Clear()\n");
    CurrentObjects.Clear();
    Debug_Printf("Scen->Clear_All_Waypoints()\n");
    // The existing accepted seed takes the scenario pointer in ECX as a 32-bit integer.
    seed_00663220::FUN_00663220((int)unknown_id_source_a3d290);
    Debug_Printf("Init_Campaigns()\n");
    Read_Battle_Files();
    if (unknown_gas_cloud_system_a40d20 != 0) {
        unknown_gas_cloud_system_a40d20->Remove_All_Particles();
        delete unknown_gas_cloud_system_a40d20;
        unknown_gas_cloud_system_a40d20 = 0;
    }
    unknown_id_source_a3d290->RandomNumber.unknown_0x00 = false;
    Unknown_006F89E0();
    Unknown_006F8A20(0);
    RadarEventClass_unknown_reset_cells();
    unknown_id_source_a3d290->UniqueID = 1000000;
}

