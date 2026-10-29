// 0x0051F930: starts the lightning storm at cell for owner (a random cell the
// map accepts when cell is unknown_geometry_k). With a deferment the storm is
// only armed (the shorter deferment wins). Otherwise a radar event marks the
// cell, the houses that are not the owner's allies get the storm warning, the
// ion lighting comes on (unless the dominator lighting holds) and the player
// is told (Rules LightningPrintText).
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/radar_event.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?StormOwner@@3PAVHouseClass@@A=00a51940
// @ref ?StormDeferment@@3HA=00a51938
// @ref ?StormStartTime@@3HA=007ddb10
// @ref ?StormDuration@@3HA=007ddb14
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref _unknown_geometry_k=00a518a8
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??_C@_0BE@JBMD@TXT_LIGHTNING_STORM?$AA@=007ddb94
// @ref ??_C@_0P@CMOA@D?3?2Ra2?2Ion?4cpp?$AA@=007ddb84
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?unknown_int_a3d548@@3HA=00a3d548

void __fastcall Unknown_0051F930(int duration, int deferment, Cell cell, int owner)
{
    if (cell == unknown_geometry_k) {
        while (!Map.Unknown_0054AAB0(cell)) {
            cell = Cell(Random_Pick(0, Map.unknown_128), Random_Pick(0, Map.unknown_12c));
        }
    }
    StormCoords = cell;
    StormOwner = (HouseClass *)owner;
    if (StormActive) {
        return;
    }
    if (deferment) {
        if (StormDeferment == 0 || StormDeferment >= deferment) {
            StormDeferment = deferment;
        }
        StormDuration = duration;
        return;
    }
    Unknown_0063B5B0(13, cell);
    StormDuration = duration;
    StormStartTime = Frame;
    StormActive = true;
    for (int index = 0; index < Houses.Count(); index++) {
        if (StormOwner == 0 || !StormOwner->Is_Ally(Houses[index])) {
            if (!Houses[index]->unknown_13d && !unknown_int_a3d548) {
                Houses[index]->unknown_func_4f5840(duration);
            }
        }
    }
    if (unknown_player_a35db4 != 0) {
        unknown_player_a35db4->unknown_5669 = true;
    }
    if (unknown_dominator_state_a5193c != 1) {
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->IonAmbient;
        Set_Lighting_00520B00(unknown_id_source_a3d290->IonRed * 1000 / 100,
            unknown_id_source_a3d290->IonGreen * 1000 / 100,
            unknown_id_source_a3d290->IonBlue * 1000 / 100, true);
    }
    if (Rules->LightningPrintText) {
        int color = 3;
        if (unknown_player_a35db4 != 0) {
            color = unknown_player_a35db4->ColorSchemeIndex;
        }
        Voc_Play(Rules->StormSound, 1.0f, 0x2000, 0);
        unknown_session_a3d298.Messages.Add_Message(0, 0,
            StringTable::Load_String("TXT_LIGHTNING_STORM", 0, "D:\\Ra2\\Ion.cpp", 465), color, 0x4046, 150, false);
    }
    Map.Flag_To_Redraw(true);
}
