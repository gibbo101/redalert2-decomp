// void __fastcall Select_Serial_Dialog_Init(HWND window) (0x005CE990)
// Enables the buttons 0x653-0x655 only when the default port settings are
// complete and the port opens (the session's SerialDefaults).
#include "shared/null_dlg.hpp"
#include "shared/serial_progress.hpp"
#include "shared/session_state.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__EnableWindow@8=0079a490
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?Detect_Port@NullModemClass@@QAEHPAUSerialSettingsType@@@Z=005d03e0

void __fastcall Select_Serial_Dialog_Init(HWND window)
{
    bool enable = true;
    if (unknown_session_a3d298.SerialDefaults.Port == 0 || unknown_session_a3d298.SerialDefaults.IRQ == -1 || unknown_session_a3d298.SerialDefaults.Baud == -1) {
        enable = false;
    } else if (serial_manager_00a40a28.Detect_Port(&unknown_session_a3d298.SerialDefaults) != 0) {
        enable = false;
    }

    HWND item = GetDlgItem(window, 0x653);
    if (item) {
        EnableWindow(item, enable);
    }
    item = GetDlgItem(window, 0x654);
    if (item) {
        EnableWindow(item, enable);
    }
    item = GetDlgItem(window, 0x655);
    if (item) {
        EnableWindow(item, enable);
    }
}
