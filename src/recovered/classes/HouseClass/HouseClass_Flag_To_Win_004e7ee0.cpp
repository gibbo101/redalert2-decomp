// bool HouseClass::Flag_To_Win(bool quiet) (0x004E7EE0)
// RA's Flag_To_Win: unless the house is already winning, dying or losing
// (+0x13F, +0x13E, +0x140), marks it as winning and, unless quiet, starts the
// borrowed time (+0x1E0, Rules SavourDelay minutes; in a network game at
// least the frames ahead and ending on a multiple of ten frames). The
// player's house is told (campaign: the game pauses).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/string_table.hpp"
#include "shared/tactical.hpp"
#include "shared/vox_class.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ?Unknown_006A53F0@Tactical@@QAEXPBGH@Z=006a53f0
// @ref ?unknown_max_ahead_a3d560@@3HA=00a3d560
// @ref ??_C@_0BO@GOFO@Frame?5?$CFd?0?5BorrowedTime?5?$DN?$DN?5?$CFd?6?$AA@=007da76c
// @ref ??_C@_0BB@IOJF@TXT_SCENARIO_WON?$AA@=007da758
// @ref ??_C@_0BI@HFKI@EVA_MissionAccomplished?$AA@=007da740
// @ref ??_C@_0P@CNCL@TXT_VICTORIOUS?$AA@=007da730
// @ref ??_C@_0BF@NIKG@EVA_YouAreVictorious?$AA@=007da718
extern int unknown_max_ahead_a3d560;

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

bool HouseClass::Flag_To_Win(bool quiet)
{
    if (!unknown_13f && !unknown_13e && !unknown_140) {
        unknown_13f = true;
        if (!quiet) {
            unknown_1e0 = (int)(Rules->SavourDelay * 900.0);
            if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
                unknown_1e0 = ((Frame + (unknown_1e0.Value() > unknown_max_ahead_a3d560 ? unknown_1e0 : CDTimerClass<FrameTimerClass>(unknown_max_ahead_a3d560)).Value() + 9) / 10) * 10 - Frame;
            }
            Debug_Printf("Frame %d, BorrowedTime == %d\n", Frame, unknown_1e0.Value());
        }
        if (unknown_game_mode_a3d298 == 0) {
            if (Is_Player_Control()) {
                Pause_Game_0065c3d0();
                unknown_tactical_83996c->Unknown_006A53F0(StringTable::Load_String("TXT_SCENARIO_WON", 0, "D:\\Ra2\\House.CPP", 5304), 0);
                Speech_Play_Name("EVA_MissionAccomplished", -1, -1);
                Map.Flag_To_Redraw(false);
            }
        } else if (Is_Player_Control()) {
            unknown_tactical_83996c->Unknown_006A53F0(StringTable::Load_String("TXT_VICTORIOUS", 0, "D:\\Ra2\\House.CPP", 5307), 2);
            Speech_Play_Name("EVA_YouAreVictorious", -1, -1);
            Map.Flag_To_Redraw(false);
        }
    }
    return unknown_13f;
}
