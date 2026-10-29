// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

WideString __fastcall unknown_5e2160(HWND window, int a)
{
    UnknownTextRequest request;
    request.unknown_00 = a;
    request.unknown_04 = -1;
    SendMessageA(window, 0x4e9, 0, (LPARAM)&request);
    return request.text;
}

}
