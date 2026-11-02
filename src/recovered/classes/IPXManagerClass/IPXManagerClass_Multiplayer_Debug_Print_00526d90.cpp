// void IPXManagerClass::Multiplayer_Debug_Print_00526d90() (0x00526D90; TibSun's Multiplayer_Debug_Print)
// The network statistics overlay: retry delta/timeout, latency fudge, frame syncs per second, the multicast
// response time, then per connection its name, queue delays, resends, losses, process time, frames behind
// (the session's per-player array), queue counts, missed packets and the router response time.
// @ref ??_C@_1BO@JIKG@?$AAR?$AAt?$AAr?$AAy?$AA?5?$AAd?$AAe?$AAl?$AAt?$AAa?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de4a4
// @ref ??_C@_1CC@MIAJ@?$AAR?$AAt?$AAr?$AAy?$AA?5?$AAt?$AAi?$AAm?$AAe?$AAo?$AAu?$AAt?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de480
// @ref ??_C@_1BO@HEMD@?$AAL?$AAa?$AAt?$AA?5?$AAF?$AAu?$AAd?$AAg?$AAe?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de460
// @ref ??_C@_1BE@DICJ@?$AAF?$AAS?$AAP?$AAS?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de44c
// @ref ??_C@_1BI@LPOL@?$AAM?$AAC?$AA?5?$AAr?$AAe?$AAs?$AAp?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de434
// @ref ??_C@_1BM@BLOM@?$AAA?$AAv?$AAe?$AAr?$AAa?$AAg?$AAe?$AA?5?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de418
// @ref ??_C@_1BM@NAGD@?$AAM?$AAa?$AAx?$AA?5?$AA?5?$AA?5?$AA?5?$AA?5?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de3fc
// @ref ??_C@_1BM@OIF@?$AAR?$AAe?$AAs?$AAe?$AAn?$AAd?$AAs?$AA?5?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de3e0
// @ref ??_C@_1BM@DACE@?$AAN?$AAu?$AAm?$AA?5?$AAl?$AAo?$AAs?$AAt?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de3c4
// @ref ??_C@_1BM@ONCH@?$AAP?$AAc?$AAn?$AAt?$AA?5?$AAl?$AAo?$AAs?$AAt?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de3a8
// @ref ??_C@_1BK@GNEK@?$AAP?$AAr?$AAo?$AAc?$AAe?$AAs?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de38c
// @ref ??_C@_1BK@CPKN@?$AAF?$AAr?$AAa?$AAm?$AAe?$AA?5?$AA?5?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de370
// @ref ??_C@_1CC@BJLO@?$AAQ?$AAu?$AAe?$AAu?$AAe?$AA?5?$AAs?$AA?1?$AAr?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?1?$AA?$CF?$AAd?$AA?$AA@=007de34c
// @ref ??_C@_1CE@IEFB@?$AAM?$AAi?$AAs?$AAs?$AAe?$AAd?$AA?5?$AAo?$AA?1?$AAm?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?1?$AA?$CF?$AAd?$AA?$AA@=007de328
// @ref ??_C@_1BM@IADI@?$AAR?$AAo?$AAu?$AAt?$AA?5?$AAr?$AAe?$AAs?$AAp?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de30c
// @ref ??_C@_04HPIL@Grey?$AA@=007d83b8
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref ?unknown_frame_sync_timer_a780c0@@3V?$BasicTimerClass@VSystemTimerClass@@@@A=00a780c0
// @ref ?unknown_response_times_a76c88@@3PAKA=00a76c88
#include "shared/ipx_manager.hpp"
#include "shared/house.hpp"
#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/progress_screen.hpp"
#include "shared/queue.hpp"
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"
#include "shared/connection.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"

template <class T>
class BasicTimerClass {
public:
    BasicTimerClass(int set = 0) : Started(Timer - set) {}
    ~BasicTimerClass() {}
    int Value() const { return Timer - Started; }
    operator int() const { return Value(); }
    int Started;
    T Timer;
};
extern BasicTimerClass<SystemTimerClass> unknown_frame_sync_timer_a780c0;

void IPXManagerClass::Multiplayer_Debug_Print_00526d90()
{
    wchar_t buffer[256];
    wchar_t name[200];
    Surface *surface = unknown_surface_839964;

    swprintf(buffer, L"Rtry delta: %d", 1000 * RetryDelta / 60);
    Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 402), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

    swprintf(buffer, L"Rtry timeout: %d", 1000 * Timeout / 60);
    Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 412), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

    swprintf(buffer, L"Lat Fudge : %d", unknown_a3fba4);
    Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 422), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

    if (unknown_frame_sync_timer_a780c0 / 60) {
        swprintf(buffer, L"FSPS : %d", unknown_frame_syncs_ab62e4 / (unknown_frame_sync_timer_a780c0 / 60));
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 432), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);
        if ((Frame & 0x7F) == 0x7F) {
            unknown_frame_sync_timer_a780c0 = 0;
            unknown_frame_syncs_ab62e4 = 0;
        }
    }

    if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
        swprintf(buffer, L"MC resp: %d", 1000 * unknown_ipx_manager_a40978.unknown_526c70() / 60);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 442), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);
    }

    for (int i = 0; i < NumConnections; i++) {
        HouseClass *house = Houses[Connection[i]->ID];
        if (house != 0 && house != unknown_player_a35db4) {
            int scheme = house->ColorSchemeIndex;
            int x = (i + 1) * 100;

            swprintf(name, L"%s", Connection[i]->Name);
            Fancy_Text_Printf(name, surface, &surface->Get_Rect(), &Point2D(x, 302), ColorSchemes[scheme], 0, 0x19);

            int avg = Connection[i]->Queue->Avg_Delay();
            swprintf(buffer, L"Average  : %d", 1000 * avg / 60);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 311), ColorSchemes[scheme], 0, 0x19);

            int max = Connection[i]->Queue->Max_Delay();
            swprintf(buffer, L"Max      : %d", 1000 * max / 60);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 319), ColorSchemes[scheme], 0, 0x19);

            int resends = Connection[i]->unknown_08;
            swprintf(buffer, L"Resends  : %d", resends);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 327), ColorSchemes[scheme], 0, 0x19);

            int numlost = (0 > (int)Connection[i]->unknown_0c) ? 0 : (int)Connection[i]->unknown_0c;
            swprintf(buffer, L"Num lost : %d", numlost);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 335), ColorSchemes[scheme], 0, 0x19);

            int pcnt_lost = Connection[i]->unknown_10;
            swprintf(buffer, L"Pcnt lost: %d", pcnt_lost);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 343), ColorSchemes[scheme], 0, 0x19);

            int process_time = 0;
            for (int j = 0; j < unknown_players_a3fa7c.Count(); ++j) {
                if (Connection[i]->ID == unknown_players_a3fa7c[j]->ID) {
                    process_time = unknown_players_a3fa7c[j]->unknown_63;
                    break;
                }
            }
            swprintf(buffer, L"Process : %d", process_time);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 351), ColorSchemes[scheme], 0, 0x19);

            swprintf(buffer, L"Frame   : %d", -unknown_session_a3d298.unknown_frames_behind_28ec[i]);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 359), ColorSchemes[scheme], 0, 0x19);

            swprintf(buffer, L"Queue s/r: %d/%d", Connection[i]->Queue->SendCount, Connection[i]->Queue->ReceiveCount);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 367), ColorSchemes[scheme], 0, 0x19);

            swprintf(buffer, L"Missed o/m: %d/%d", Connection[i]->unknown_14, Connection[i]->unknown_18);
            Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 375), ColorSchemes[scheme], 0, 0x19);

            if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
                swprintf(buffer, L"Rout resp: %d", 1000 * unknown_response_times_a76c88[i] / 60);
                Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(x, 383), ColorSchemes[scheme], 0, 0x19);
            }
        }
    }
}
