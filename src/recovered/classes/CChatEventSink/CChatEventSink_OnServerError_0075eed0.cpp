// HRESULT __stdcall CChatEventSink::OnServerError(HRESULT result, char const *message) (0x0075EED0, slot 5)
// Unless 0x00B2ABD9 is set, shows "TXT_SERVER_ERROR: <message>" in the chat.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnServerError(HRESULT result, char const *message)
{
    if (!unknown_b2abd9) {
        wchar_t buffer[512];
        swprintf(buffer, L"%s : %hs", StringTable::Load_String("TXT_SERVER_ERROR", 0, "D:\\Ra2\\wonline.cpp", 4456), message);
        Unknown_005C2C80(-1, buffer);
    }
    return S_OK;
}
// @ref ??_C@_0BB@FFH@TXT_SERVER_ERROR?$AA@=007fdd00
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_1BC@HHDF@?$AA?$CF?$AAs?$AA?5?$AA?3?$AA?5?$AA?$CF?$AAh?$AAs?$AA?$AA@=007fdcec
