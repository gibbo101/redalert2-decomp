// The null-modem and modem dialogs and their helpers (NullDlg.CPP, Westwood's
// NULLDLG.CPP; the unit follows the header statics at 0x005CDD10).
#ifndef RA2_SHARED_NULL_DLG_HPP
#define RA2_SHARED_NULL_DLG_HPP

#include "shared/null_modem.hpp"
#include "shared/win32_api.hpp"

// The number to dial, with its call-waiting prefix (0x00A72D78; Red Alert's DialString).
extern char DialString[];
// The modem settings of the dial and answer dialogs (0x00A72DC4; Red Alert's DialSettings).
extern SerialSettingsType *DialSettings;

// The serial game dialog (hypothesis: Red Alert's Select_Serial_Dialog): its
// procedure (0x005CE920) stores IDCANCEL or a button 0x652-0x655 through the
// DWL_USER pointer; the 0x497 initialisation (0x005CE990) enables the buttons
// 0x653-0x655 only when the session's default port settings open.
int __stdcall Select_Serial_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void __fastcall Select_Serial_Dialog_Init(HWND window);

// Appends a character the modem echoed to NullModem's echo buffer (0x005CFD70; Red Alert's Modem_Echo).
void __fastcall unknown_text_buffer_append_005cfd70(char character);

void Shutdown_Modem();                                                  // 0x005CEA60
// Reconnect_Modem (0x005CEB40) and Destroy_Null_Connection (0x005CEBA0) are in shared/queue.hpp.
bool __fastcall Reconnect_Null_Modem();                                 // 0x005CEDD0
bool __fastcall Dial_Modem(SerialSettingsType *settings, bool reconnect);   // 0x005CF0B0
bool __fastcall Answer_Modem(SerialSettingsType *settings, bool reconnect); // 0x005CF780

#endif
