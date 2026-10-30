// void __fastcall Load_Random_Map_Preview_005cc800(HWND dialog) (0x005CC800)
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/map_preview.hpp"
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
// @ref ?Load_0061E170@UnknownPreview_0061D430@@QAE_NPBD@Z=0061e170

void __fastcall Load_Random_Map_Preview_005cc800(HWND dialog)
{
    if (unknown_multi_missions_a3d8d8[unknown_session_a3d2b4]->Unknown_006720C0()) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
        unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
        if (unknown_dialog_preview_a72ce8->unknown_00 == 0) {
            Unknown_005c7570(dialog);
        }
        InvalidateRect(dialog, 0, 0);
    } else {
        Unknown_005c7570(dialog);
    }
}
