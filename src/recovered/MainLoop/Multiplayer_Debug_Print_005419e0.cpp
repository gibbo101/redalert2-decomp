// void __fastcall Unknown_005419E0(bool noframecheck) (0x005419E0; Westwood's Multiplayer_Debug_Print):
// prints the timing value at 0x007EC498 (milliseconds, as seconds) when set, then, with the debug
// display on in a network game, the frame, frame-rate, latency and processing figures across
// the screen and the connection manager's own lines (the argument is not read).
#include "shared/main_loop.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/gscreen.hpp"
#include "shared/surface.hpp"
#include "shared/mouse.hpp"
#include "shared/text_print.hpp"
#include "shared/color_scheme.hpp"
#include "shared/gadget.hpp"
#include "shared/progress_screen.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/queue.hpp"
#include "shared/session_state.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref ??_C@_04HPIL@Grey?$AA@=007d83b8
// @ref ??_C@_19KOLE@?$AA?$CF?$AA?4?$AA2?$AAf?$AA?$AA@=007dfd74
// @ref ??_C@_1BC@GNFJ@?$AAN?$AAF?$AAT?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfcd8
// @ref ??_C@_1BC@NPJC@?$AAF?$AAP?$AAS?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfd48
// @ref ??_C@_1BE@OANM@?$AAL?$AAN?$AAF?$AAT?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfcc4
// @ref ??_C@_1BG@MDKM@?$AAF?$AAr?$AAa?$AAm?$AAe?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfd5c
// @ref ??_C@_1BK@GNEK@?$AAP?$AAr?$AAo?$AAc?$AAe?$AAs?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de38c
// @ref ??_C@_1BK@HNKK@?$AAR?$AAe?$AAq?$AA?5?$AAf?$AAp?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfcec
// @ref ??_C@_1BM@HFNN@?$AAM?$AAa?$AAx?$AAA?$AAh?$AAe?$AAa?$AAd?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007dfd2c
// @ref ??_C@_1BM@IADI@?$AAR?$AAo?$AAu?$AAt?$AA?5?$AAr?$AAe?$AAs?$AAp?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007de30c
// @ref ??_C@_1CE@CBBH@?$AAR?$AAe?$AAs?$AAp?$AA?5?$AAT?$AAi?$AAm?$AAe?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAd?$AA?5?$AAm?$AAs?$AA?$AA@=007dfd08
// @ref ?Multiplayer_Debug_Print_00526d90@IPXManagerClass@@QAEXXZ=00526d90
// @ref ?unknown_time_7ec498@@3IA=007ec498

extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);
extern bool unknown_debug_display_a3d8c5;               // 0x00A3D8C5 (MultiplayerDebugCommandClass toggles it)

void __fastcall Unknown_005419E0(bool noframecheck)
{
    if (unknown_time_7ec498 != -1) {
        double seconds = unknown_time_7ec498 * 0.001;
        Fancy_Text_Printf(L"%.2f", unknown_surface_839964, &Rect(0, 0, 500, 15), &Point2D(100, 0),
            ColorSchemes[Gadget_Color_Scheme()], 0x1F, 6, seconds, unknown_id_source_a3d290->FileName);
    }

    if (unknown_debug_display_a3d8c5 && unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 1 && unknown_session_a3d298.Type != 2) {

        Surface *surface = unknown_surface_839964;
        WWMouse->Hide_Mouse();

        surface->Fill_Rect(Rect(0, 300, 639, 230), 0);

        wchar_t buffer[256];

        swprintf(buffer, L"Frame : %d", Frame);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 302),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"FPS : %d", unknown_a6eb1c);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 312),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"MaxAhead : %d", unknown_max_ahead_a3d560);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 322),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"Resp Time : %d ms", (int)(unknown_ipx_manager_a40978.Response_Time() * 1000) / 60);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 332),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"Req fps : %d", unknown_a3d568);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 342),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"Process : %d", unknown_session_a3d298.Players[0]->unknown_63);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 352),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"Rout resp: %d", (unknown_a402dc * 1000) / 60);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 362),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"NFT : %d", unknown_net_frame_timer_839970);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 372),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        swprintf(buffer, L"LNFT : %d", unknown_net_frame_delay_a6ebcc);
        Fancy_Text_Printf(buffer, surface, &surface->Get_Rect(), &Point2D(0, 382),
            unknown_color_scheme_663d30("Grey", 1), 0, 0x19);

        unknown_ipx_manager_a40978.Multiplayer_Debug_Print_00526d90();

        WWMouse->Show_Mouse();
    }
}
