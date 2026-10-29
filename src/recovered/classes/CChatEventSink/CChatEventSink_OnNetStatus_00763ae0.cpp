// HRESULT __stdcall CChatEventSink::OnNetStatus(HRESULT result) (0x00763AE0, slot 19)
// While disconnecting, records the status and signals; on a lost connection reports it (in game
// as a message, otherwise in a popup) and clears the current and pending channels.
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/gadget.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_b2651c=00b2651c
// @ref ?unknown_net_status_b2ac00=00b2ac00

HRESULT __stdcall CChatEventSink::OnNetStatus(HRESULT result)
{
    if (unknown_b2abd8) {
        SetEvent(unknown_b2651c);
        unknown_net_status_b2ac00 = result;
        return S_OK;
    }
    if (result == 0x4012f) {
        if (unknown_b2abd9) {
            if (!unknown_b2abda) {
                wchar_t text[256];
                text[0] = 0;
                swprintf(text, StringTable::Load_String("TXT_WOL_CONNLOST", 0, "D:\\Ra2\\wonline.cpp", 0x1c09));
                int color = Gadget_Color_Scheme();
                unknown_session_a3d298.Messages.Add_Message(0, 0, text, color, 0x16, Rules->MessageDelay * 900, false);
                Map.Flag_To_Redraw(false);
                unknown_b2abda = true;
                unknown_b2abe8 = 0;
                memset(&unknown_channel_b299c0, 0, sizeof(unknown_channel_b299c0));
                memset(&unknown_pending_channel_b26a60, 0, sizeof(unknown_pending_channel_b26a60));
                Debug_Printf("NetStatus disconnect ingame\n");
            }
        } else {
            if (Unknown_00735940(0x113)) {
                Popup_005c3230(StringTable::Load_String("TXT_YOURE_DISCON", 0, "D:\\Ra2\\wonline.cpp", 0x1c1b), 0, Unknown_0073c120, 0);
            }
            unknown_b2abd8 = true;
            unknown_b2abda = true;
            SetEvent(unknown_b264f8);
            unknown_b2abe8 = 0;
            memset(&unknown_channel_b299c0, 0, sizeof(unknown_channel_b299c0));
            memset(&unknown_pending_channel_b26a60, 0, sizeof(unknown_pending_channel_b26a60));
            Debug_Printf("NetStatus disconnect not in game \n");
        }
    }
    return S_OK;
}
// @ref ??_C@_0BB@KHPB@TXT_WOL_CONNLOST?$AA@=007fe230
// @ref ??_C@_0BB@LPFA@TXT_YOURE_DISCON?$AA@=007fe1fc
// @ref ??_C@_0BN@OGGF@NetStatus?5disconnect?5ingame?6?$AA@=007fe210
// @ref ??_C@_0CD@DKOM@NetStatus?5disconnect?5not?5in?5game@=007fe1d8
