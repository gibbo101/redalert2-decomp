// HRESULT __stdcall CChatEventSink::OnServerBannedYou(HRESULT result, long banned_till) (0x007646C0, slot 29)
// Tells the player until when the server bans them.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref _ctime=007858af
// @ref _swprintf=00783764
// @ref ?Popup_005c3230=005c3230
// @ref ?Unknown_0073c120=0073c120

HRESULT __stdcall CChatEventSink::OnServerBannedYou(HRESULT result, long banned_till)
{
    if (!unknown_b2abd9 && result == S_OK) {
        wchar_t text[200];
        swprintf(text, StringTable::Load_String("TXT_BANNEDTILL", 0, "D:\\Ra2\\wonline.cpp", 0x1d54), ctime(&banned_till));
        Popup_005c3230(text, 0, Unknown_0073c120, 0);
    }
    return S_OK;
}
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_0P@BDBG@TXT_BANNEDTILL?$AA@=007fe2d4
