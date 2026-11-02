// The persona statistics page's text setup (0x00739A50; WOLPersonaInformation.cpp, name
// hypothesis): with clear set it empties control 0x628 (message 0x4B4) and repaints it, then
// empties control 0x6EF and shows the "GUI:UnknownStats" text in controls 0x6F0, 0x6F1,
// 0x701, 0x6F4 and 0x6F5 (message 0x4B2). Called by 0x00753A60.
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"
#include "shared/wide_string.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__InvalidateRect@12=0079a494
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??0WideString@@QAE@PBG@Z=0076f9c0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??_C@_0BB@DMDC@GUI?3UnknownStats?$AA@=007fd2c4
// @ref ??_C@_0CB@LNHD@D?3?2Ra2?2WOLPersonaInformation?4cpp@=007fd2a0

void __fastcall Unknown_Persona_Stats_Text_00739a50(HWND window, bool clear)
{
    HWND control;
    if (clear) {
        control = GetDlgItem(window, 0x628);
        SendMessageA(control, 0x4B4, 0, (LPARAM)"");
        InvalidateRect(control, 0, FALSE);
    }
    control = GetDlgItem(window, 0x6EF);
    SendMessageA(control, 0x4B2, 0, (LPARAM)L"");
    WideString text(StringTable::Load_String("GUI:UnknownStats", 0, "D:\\Ra2\\WOLPersonaInformation.cpp", 639));
    control = GetDlgItem(window, 0x6F0);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text.unknown_text_770430());
    control = GetDlgItem(window, 0x6F1);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text.unknown_text_770430());
    control = GetDlgItem(window, 0x701);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text.unknown_text_770430());
    control = GetDlgItem(window, 0x6F4);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text.unknown_text_770430());
    control = GetDlgItem(window, 0x6F5);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text.unknown_text_770430());
}
