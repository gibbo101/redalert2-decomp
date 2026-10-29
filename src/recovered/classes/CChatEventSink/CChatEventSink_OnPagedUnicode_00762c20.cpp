// HRESULT __stdcall CChatEventSink::OnPagedUnicode(HRESULT result, WOL::User *user, unsigned short const *message) (0x00762C20, slot 44)
// Shows a received page "(<nick>) <message>": in game as a message and in the list; otherwise in
// the chat (or list) of the open dialogs, or, with none showing chat, in a new page reply dialog.
// Then plays the incoming-message sound.
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/gadget.hpp"
#include "shared/map_view.hpp"
#include "shared/dialog_create.hpp"
#include "shared/lobby.hpp"
#include "shared/sound_play.hpp"
// @ref ?unknown_color_7a7378@@3HA=007a7378
// @ref ?Unknown_00757cc0@@YI?AVWstring@@PAUHWND__@@@Z=00757cc0
// @ref ?Page_Dialog_Proc_00757d80@@YGHPAUHWND__@@IIJ@Z=00757d80
// @ref ?unknown_previous_key=007359b0

HRESULT __stdcall CChatEventSink::OnPagedUnicode(HRESULT result, WOL::User *user, unsigned short const *message)
{
    wchar_t text[256];
    if (result < 0) return S_OK;
    if (unknown_b2abd9) {
        swprintf(text, L"(%hs) %s", user->name, message);
        int color = Gadget_Color_Scheme();
        unknown_session_a3d298.Messages.Add_Message(0, 0, text, color, 0x16, Rules->MessageDelay * 900, false);
        Map.Flag_To_Redraw(false);
        Unknown_005c2d10(unknown_color_7a7378, L"(%hs) %s", user->name, message);
    } else {
        HWND dialog = Unknown_00735B10();
        while (dialog) {
            if (GetDlgItem(dialog, 0x53f)) {
                Unknown_005C2C80(unknown_color_7a7378, L"(%hs) %s", user->name, message);
                break;
            }
            if (GetDlgItem(dialog, 0x5b5)) Unknown_005c2d10(unknown_color_7a7378, L"(%hs) %s", user->name, message);
            dialog = (HWND)unknown_previous_key((int)dialog);
        }
        if (!dialog) {
            ReleaseCapture();
            unknown_5159b0(0, true);
            dialog = unknown_create_dialog_5ff610(0x11e, Page_Dialog_Proc_00757d80, 0);
            SetFocus(dialog);
            Unknown_005C2C80(unknown_color_7a7378, L"(%hs) %s", user->name, message);
            ShowWindow(dialog, 1);
        }
        Set_Edit_Text(GetDlgItem(dialog, 0x718), Unknown_00757cc0(GetDlgItem(dialog, 0x53f)));
    }
    Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
    return S_OK;
}
// @ref ??_C@_1BC@FOFN@?$AA?$CI?$AA?$CF?$AAh?$AAs?$AA?$CJ?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe0c0
