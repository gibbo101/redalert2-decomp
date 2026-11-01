// PhoneEd.cpp (shared/phone_edit.hpp; TibSun phoneed.cpp).
#define VECTOR_IMPLEMENT_ALL
#include "shared/phone_edit.hpp"
#include "shared/dialog_create.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"
#include "shared/vector_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/win32_window.hpp"
#include "shared/serial_ed.hpp"
#include "shared/debug_printf.hpp"

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);   // 0x00783689
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *destination, wchar_t const *source, unsigned int count);   // 0x00783622
extern "C" unsigned int __cdecl wcslen(wchar_t const *string);   // 0x00783605
extern "C" int __cdecl wcscmp(wchar_t const *left, wchar_t const *right);   // 0x007837D3
extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);   // 0x00783764

extern "C" wchar_t *__cdecl _wcsupr(wchar_t *string);   // 0x00796EF6
char *__fastcall strtrim(char *string);   // 0x006EEF10
wchar_t *__fastcall wcstrim(wchar_t *buffer);   // 0x006EEF80

#define MAKELONG(a, b) ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define MAKEWPARAM(l, h) ((WPARAM)(DWORD)MAKELONG(l, h))

static int __cdecl Phone_Compare(void const *p1, void const *p2);

// 0x0060D970
bool PhoneEdit::Dialog()
{
    _Dialog = unknown_create_dialog_5ff610(0xEE, Phone_Dialog_Proc, 0);
    if (_Dialog) {
        Changed = false;
        RC = -1;
        SetWindowLongA(_Dialog, DWL_USER, (LONG)this);
        Build_Phone_Listbox();
        unknown_dialog_5ff7c0(_Dialog);
        while (RC < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(_Dialog);
        if (Changed == true) {
            unknown_session_a3d298.Write_MultiPlayer_Settings();
        }
    }
    if (RC != 1) {
        return false;
    }
    return true;
}
// @ref ?Build_Phone_Listbox@PhoneEdit@@QAEXXZ=0060de40
// @ref ?Phone_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z=0060d9f0
// @ref ?Write_MultiPlayer_Settings@UnknownSessionState@@QAEXXZ=00670380
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref __imp__SetWindowLongA@12=0079a488
