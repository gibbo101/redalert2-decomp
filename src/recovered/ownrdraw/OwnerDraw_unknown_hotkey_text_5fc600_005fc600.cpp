// @ref ??_C@_01PJOB@?$CL?$AA@=007eaf8c
// @ref ??_C@_17DPNG@?$AA?$CF?$AAh?$AAs?$AA?$AA@=007eadcc
// @ref __imp__MapVirtualKeyA@8=0079a3d8
// @ref __imp__GetKeyNameTextA@12=0079a44c
// @ref _swprintf=00783764
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// The text of a hot key control's value ("Alt+Ctrl+Shift+Key"; nothing for an extended key) (0x005FC600).
void __fastcall unknown_hotkey_text_5fc600(unsigned short hotkey, wchar_t *text)
{
    char name[32];
    char buffer[500];
    unsigned char modifiers = (unsigned char)(hotkey >> 8);
    buffer[0] = 0;
    *text = 0;
    if (modifiers & 8) {
        return;
    }
    if (modifiers & 4) {
        LONG key = MapVirtualKeyA(0x12, 0) << 16 | 0x2000001;
        GetKeyNameTextA(key, name, sizeof(name));
        strcat(buffer, name);
        strcat(buffer, "+");
    }
    if (modifiers & 2) {
        LONG key = MapVirtualKeyA(0x11, 0) << 16 | 0x2000001;
        GetKeyNameTextA(key, name, sizeof(name));
        strcat(buffer, name);
        strcat(buffer, "+");
    }
    if (modifiers & 1) {
        LONG key = MapVirtualKeyA(0x10, 0) << 16 | 0x2000001;
        GetKeyNameTextA(key, name, sizeof(name));
        strcat(buffer, name);
        strcat(buffer, "+");
    }
    LONG key = MapVirtualKeyA(hotkey & 0xff, 0) << 16 | 0x2000001;
    GetKeyNameTextA(key, name, sizeof(name));
    strcat(buffer, name);
    swprintf(text, L"%hs", buffer);
}

}
