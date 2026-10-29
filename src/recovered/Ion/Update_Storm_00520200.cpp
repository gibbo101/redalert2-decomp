// 0x00520200: the storm's frame logic. The dominator states time out (1 ends
// as 0x00520980 does, 2 returns to 0); bolts half played and present clouds
// played out leave their lists; manifesting clouds past half strike their
// cell (0x0051FE50); with no clouds left a requested end stops the storm. An
// active storm ends after its duration, adds a cloud over its cell every
// LightningHitDelay frames and, every LightningScatterDelay frames, one more
// within LightningCellSpread / 2 cells that the map accepts and that is at
// least LightningSeparation from every present cloud (three tries). A
// deferred storm counts down, starts at zero and warns every 225 frames.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/anim.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/vox_class.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?StormOwner@@3PAVHouseClass@@A=00a51940
// @ref ?StormDeferment@@3HA=00a51938
// @ref ?StormTimeToEnd@@3_NA=00a51944
// @ref ?StormStartTime@@3HA=007ddb10
// @ref ?StormDuration@@3HA=007ddb14
// @ref ?unknown_dominator_start_7ddb18@@3HA=007ddb18
// @ref ?unknown_dominator_delay_7ddb1c@@3HA=007ddb1c
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?StormCloudsPresent@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?StormBoltsPresent@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref ?StormCloudsManifesting@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref ?Storm_Strike_0051FE50@@YIXUCoordStruct@@@Z=0051fe50
// @ref ?Unknown_0051FC90@@YGXVCell@@@Z=0051fc90
// @ref ?Unknown_0051F930@@YIXHHVCell@@H@Z=0051f930
// @ref _unknown_geometry_k=00a518a8
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??_C@_0P@CMOA@D?3?2Ra2?2Ion?4cpp?$AA@=007ddb84
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ??_C@_0BK@OPHL@EVA_LightningStormCreated?$AA@=007ddbc8
// @ref ??_C@_0CA@DHJF@TXT_LIGHTNING_STORM_APPROACHING?$AA@=007ddba8

void __fastcall Update_Storm_00520200()
{
    if (unknown_dominator_state_a5193c == 1) {
        if (unknown_dominator_delay_7ddb1c != -1 && unknown_dominator_start_7ddb18 + unknown_dominator_delay_7ddb1c < Frame) {
            End_Dominator_Lighting_00520980();
        }
    } else if (unknown_dominator_state_a5193c == 2) {
        if (unknown_dominator_delay_7ddb1c != -1 && unknown_dominator_start_7ddb18 + unknown_dominator_delay_7ddb1c < Frame) {
            unknown_dominator_state_a5193c = 0;
        }
    }

    if (StormBoltsPresent.Count() > 0) {
        for (int index = StormBoltsPresent.Count() - 1; index >= 0; index--) {
            AnimClass *bolt = StormBoltsPresent[index];
            int stage = bolt->Stage;
            if (stage >= ((ShapeFileStruct *)bolt->Class_Of()->unknown_slot39())->FrameCount / 2) {
                StormBoltsPresent.Delete(index);
            }
        }
    }
    for (int index = StormCloudsManifesting.Count() - 1; index >= 0; index--) {
        AnimClass *cloud = StormCloudsManifesting[index];
        int stage = cloud->Stage;
        if (stage > ((ShapeFileStruct *)cloud->Class_Of()->unknown_slot39())->FrameCount / 2) {
            Storm_Strike_0051FE50(cloud->Center_Coord());
            StormCloudsManifesting.Delete(index);
        }
    }
    if (StormCloudsPresent.Count() > 0) {
        for (int index = StormCloudsPresent.Count() - 1; index >= 0; index--) {
            AnimClass *cloud = StormCloudsPresent[index];
            int stage = cloud->Stage;
            if (stage >= ((ShapeFileStruct *)cloud->Class_Of()->unknown_slot39())->FrameCount - 1) {
                StormCloudsPresent.Delete(index);
            }
        }
    } else if (StormTimeToEnd) {
        Stop_Storm_0051FBD0();
        StormTimeToEnd = false;
    }

    if (StormActive && !StormTimeToEnd) {
        if (StormDuration != -1 && StormStartTime + StormDuration < Frame) {
            StormTimeToEnd = true;
            return;
        }
        if (Frame % Rules->LightningHitDelay == 0) {
            Unknown_0051FC90(StormCoords);
        }
        if (Frame % Rules->LightningScatterDelay == 0) {
            int range = Rules->LightningCellSpread >> 1;
            int tries;
            Cell cell;
            for (tries = 3; tries > 0; tries--) {
                cell = StormCoords;
                cell.X += Random_Pick(-range, range);
                cell.Y += Random_Pick(-range, range);
                bool crowded = false;
                for (int index = 0; index < StormCloudsPresent.Count(); index++) {
                    Cell other = Coord_Cell(StormCloudsPresent[index]->Center_Coord());
                    int dx = cell.X - other.X;
                    if (dx < 0) {
                        dx = -dx;
                    }
                    int dy = cell.Y - other.Y;
                    if (dy < 0) {
                        dy = -dy;
                    }
                    if (dx + dy < Rules->LightningSeparation) {
                        crowded = true;
                        break;
                    }
                }
                if (Map.Unknown_0054AAB0(cell) && !crowded) {
                    break;
                }
            }
            if (tries > 0) {
                Unknown_0051FC90(cell);
            }
        }
    } else if (StormDeferment > 0) {
        StormDeferment--;
        if (StormDeferment == 0) {
            Unknown_0051F930(StormDuration, 0, StormCoords, (int)StormOwner);
        } else if (StormDeferment % 225 == 0 && Rules->LightningPrintText) {
            int color = 3;
            if (unknown_player_a35db4 != 0) {
                color = unknown_player_a35db4->ColorSchemeIndex;
            }
            Speech_Play_Name("EVA_LightningStormCreated", -1, -1);
            unknown_session_a3d298.Messages.Add_Message(0, 0,
                StringTable::Load_String("TXT_LIGHTNING_STORM_APPROACHING", 0, "D:\\Ra2\\Ion.cpp", 904), color, 0x46, 150,
                false);
        }
    }
}
