// HRESULT __stdcall CChatEventSink::OnPageSend(HRESULT result) (0x00762E00, slot 27)
// Reports the outcome of a page into the current dialog's chat or list, or as an in-game message.
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/gadget.hpp"

HRESULT __stdcall CChatEventSink::OnPageSend(HRESULT result)
{
    wchar_t text[128];
    if (result == S_OK) {
        Unknown_005c2d10(unknown_color_7a7360, StringTable::Load_String("TXT_PAGESENT", 0, "D:\\Ra2\\wonline.cpp", 0x1b20));
        return S_OK;
    }
    if (result == 0x40134) {
        swprintf(text, StringTable::Load_String("TXT_PAGEDISABLED", 0, "D:\\Ra2\\wonline.cpp", 0x1b24));
    } else if (result == 0x40133) {
        swprintf(text, StringTable::Load_String("TXT_PAGEUSERGONE", 0, "D:\\Ra2\\wonline.cpp", 0x1b26));
    } else {
        swprintf(text, StringTable::Load_String("TXT_PAGEFAILED", 0, "D:\\Ra2\\wonline.cpp", 0x1b28));
    }
    HWND dialog = Unknown_00735B10();
    if (dialog) {
        if (GetDlgItem(dialog, 0x53f)) {
            Unknown_005C2C80(unknown_color_7a7360, text);
            return S_OK;
        }
        if (GetDlgItem(dialog, 0x5b5)) {
            Unknown_005c2d10(unknown_color_7a7360, text);
            return S_OK;
        }
    }
    if (unknown_session_a3d298.Unknown_00672F10()) {
        int color = Gadget_Color_Scheme();
        unknown_session_a3d298.Messages.Add_Message(0, 0, text, color, 0x16, Rules->MessageDelay * 900, false);
    }
    return S_OK;
}
// @ref ??_C@_0BB@CMBL@TXT_PAGEDISABLED?$AA@=007fe0f8
// @ref ??_C@_0BB@IBOF@TXT_PAGEUSERGONE?$AA@=007fe0e4
// @ref ??_C@_0N@DG@TXT_PAGESENT?$AA@=007fe10c
// @ref ??_C@_0P@ECAO@TXT_PAGEFAILED?$AA@=007fe0d4
