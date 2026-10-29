// ModemGuest::Show_Options_00597220 (0x00597220)
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
// @ref ??_C@_0BB@BKAI@Settings?5change?6?$AA@=007e20b0
// @ref ?Unknown_005c7570@@YIXPAUHWND__@@@Z=005c7570
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
void ModemGuest::Show_Options_00597220()
{
    Debug_Printf("Settings change\n");
    HWND control = GetDlgItem(Window, 0x669);
    if (control) {
        SendMessageA(control, 0x405, 1, unknown_session_a3d298.UnitCount);
    }
    control = GetDlgItem(Window, 0x550);
    if (control) {
        SendMessageA(control, 0x405, 1, unknown_house_setting_7d88d8);
    }
    control = GetDlgItem(Window, 0x402);
    if (control) {
        SendMessageA(control, 0x405, 1, unknown_session_a3d298.unknown_24);
    }
    control = GetDlgItem(Window, 0x552);
    if (control) {
        SendMessageA(control, 0x405, 1, unknown_session_a3d298.AICount);
    }
    control = GetDlgItem(Window, 0x529);
    if (control) {
        SendMessageA(control, 0x405, 1, 6 - unknown_session_a3d298.GameSpeed_30);
    }
    control = GetDlgItem(Window, 0x553);
    if (control) {
        SendMessageA(control, 0x405, 1, unknown_session_a3d298.unknown_difficulty_40);
    }
    control = GetDlgItem(Window, 0x66B);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_a8 == true, 0);
    }
    control = GetDlgItem(Window, 0x66A);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_bases_20 == true, 0);
    }
    control = GetDlgItem(Window, 0x551);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_34 == true, 0);
    }
    control = GetDlgItem(Window, 0x54E);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2a == true, 0);
    }
    control = GetDlgItem(Window, 0x69A);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2b == true, 0);
    }
    control = GetDlgItem(Window, 0x69D);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_2c == true, 0);
    }
    control = GetDlgItem(Window, 0x54C);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_crates_29 == true, 0);
    }
    control = GetDlgItem(Window, 0x54D);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_fog_a7 == true, 0);
    }
    control = GetDlgItem(Window, 0x624);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_28 == true, 0);
    }
    control = GetDlgItem(Window, 0x596);
    if (control) {
        SendMessageA(control, 0xF1, unknown_session_a3d298.unknown_a5 == true, 0);
    }
    control = GetDlgItem(Window, 0x5A8);
    if (control) {
        SendMessageA(control, 0x4B2, 0, (LPARAM)unknown_map_name_a3d342);
    }
    if (!unknown_dialog_preview_a72ce8 || !unknown_dialog_preview_a72ce8->Is_Present()) {
        Unknown_005c7570(Window);
    }
    control = GetDlgItem(Window, 1);
    if (control) {
        EnableWindow(control, 1);
    }
    Voc_Play(Rules->OptionsChanged, 1.0f, 0x2000, 0);
}
