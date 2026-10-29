// HRESULT __stdcall CChatEventSink::OnChannelBan(HRESULT result, char const *name, int banned) (0x00764730, slot 31)
// Reports that a user was banned from or unbanned in the channel.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2abd9@@3_NA=00b2abd9
// @ref ?Unknown_006FA180=006fa180
// @ref ?unknown_color_7a7360=007a7360
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80

HRESULT __stdcall CChatEventSink::OnChannelBan(HRESULT result, char const *name, int banned)
{
    if (!unknown_b2abd9) {
        if (banned) {
            Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_CHAN_BAN", 0, "D:\\Ra2\\wonline.cpp", 0x1d61), Unknown_006FA180(name));
        } else {
            Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_CHAN_UNBAN", 0, "D:\\Ra2\\wonline.cpp", 0x1d64), Unknown_006FA180(name));
        }
    }
    return S_OK;
}
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_0N@OBEP@TXT_CHAN_BAN?$AA@=007fe2f4
// @ref ??_C@_0P@HELC@TXT_CHAN_UNBAN?$AA@=007fe2e4
