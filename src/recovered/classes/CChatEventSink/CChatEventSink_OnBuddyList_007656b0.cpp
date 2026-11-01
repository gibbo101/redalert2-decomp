// HRESULT __stdcall CChatEventSink::OnBuddyList(HRESULT result, WOL::User *buddies) (0x007656B0, slot 37)
// Records each acceptable buddy name in the three buddy lists and sends the next pending request
// (at most one every five seconds), then refreshes the buddy dialogs.
#include "shared/wol_sink.hpp"
// @ref ?Unknown_00756790@@YI_NABVWstring@@@Z=00756790
// @ref ?Unknown_00757380@@YAXXZ=00757380
// @ref ?unknown_wstring_b26944@@3VWstring@@A=00b26944
// @ref ?unknown_b2a7f8@@3KA=00b2a7f8
// @ref ?Get_007662c0@?$WolArrayList@VWstring@@@@QAE_NAAVWstring@@H@Z=007662c0
// @ref ?Remove_007661f0@?$WolArrayList@VWstring@@@@QAE_NH@Z=007661f0

HRESULT __stdcall CChatEventSink::OnBuddyList(HRESULT result, WOL::User *buddies)
{
    if (result >= 0) {
        for (WOL::User *buddy = buddies; buddy; buddy = buddy->next) {
            Wstring name(buddy->name);
            if (Unknown_00756790(name)) {
                Wstring copy(name);
                unknown_strings_b26920.Insert(copy, unknown_strings_b26920.Count);
                unknown_strings_b29838.Insert(copy, unknown_strings_b29838.Count);
                unknown_strings_b2a7d8.Add(copy);
                if (unknown_wstring_b26944.Length() > 0) {
                    if (time(0) - unknown_b2a7f8 < 5) continue;
                    unknown_wstring_b26944.Release();
                }
                if (unknown_strings_b29838.Count) {
                    if (unknown_strings_b29838.Get_007662c0(unknown_wstring_b26944, 0)) unknown_strings_b29838.Remove_007661f0(0);
                    unknown_b2a7f8 = time(0);
                    WOL::User user;
                    memset(&user, 0, sizeof(user));
                    strcpy(user.name, unknown_wstring_b26944.Get());
                    unknown_chat_a72cfc->unknown_slot24(&user);
                }
            }
        }
        Unknown_00757380();
        void *list = Unknown_00735940(0xc4);
        if (list) {
            if (!(unknown_b2abe0 &= ~0x200)) Unknown_007357E0(list, 0);
        }
        HWND current = Unknown_00735B10();
        HWND edit = GetDlgItem(current, 0x540);
        if (edit) SetFocus(edit);
        HWND dialog = (HWND)Unknown_00735940(0x116);
        if (dialog) {
            Unknown_00755180(dialog);
            KillTimer(dialog, 0x704);
            EnableWindow(GetDlgItem(dialog, 0x704), 1);
        }
    }
    return S_OK;
}
