// bool __fastcall Skirmish_Dialog() (0x00683BF0)
// Rereads the countries, sides and house types from the rules INI, runs the skirmish dialog (resource 0x102) until
// it ends with 0x617 (start) or 0x5C0, then frees the map preview and saves the session settings to RA2.INI.
// __fastcall: as __cdecl VC6 places `pop esi` before the 0x5C0 test instead of after it (98.72).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/rules.hpp"
#include "shared/ccini_class.hpp"
#include "shared/house_type.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/map_preview.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/wol_sink.hpp"
#include "shared/skirmish.hpp"
#include "shared/session_state.hpp"
#include "shared/dialog_create.hpp"
#include "shared/load_dlg.hpp"

// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?SkirmishDialog@@3PAUHWND__@@A=00abcdfc
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
int __stdcall Skirmish_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);  // @ref ?Skirmish_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z=00683d10

bool __fastcall Skirmish_Dialog()
{
    int result = -1;
    Rules->Countries(*unknown_ini_8396d0);
    Rules->Sides(*unknown_ini_8396d0);
    for (int index = 0; index < HouseTypes.Count(); index++) {
        HouseTypes[index]->Read_INI(*unknown_ini_8396d0);
    }
    HWND dialog = unknown_create_dialog_5ff610(0x102, Skirmish_Dialog_Proc, 0);
    if (dialog != 0) {
        SkirmishDialog = dialog;
        SetWindowLongA(dialog, 8, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        while (result != 0x617 && result != 0x5C0 && unknown_6000d0() != true) {
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(dialog);
        SkirmishDialog = 0;
    }
    if (unknown_dialog_preview_a72ce8 != 0) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = 0;
    }
    unknown_session_a3d298.Write_MultiPlayer_Settings();
    if (result == 0x5C0) {
        unknown_5159b0(0, true);
    }
    if (result == 0x617) {
        return true;
    }
    return false;
}
