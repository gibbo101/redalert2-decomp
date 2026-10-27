// HRESULT __stdcall CChatEventSink::OnMessageOfTheDay(HRESULT result, char const *motd) (0x0075F290, slot 7)
// Shows the message of the day line by line, then an empty line.
#include "shared/wol_sink.hpp"
// @ref __strdup=0078d816
// @ref _strtok=00782ec2
// @ref _free=007825e8
// @ref ?Unknown_006FA0C0@@YIXPAGPBDH@Z=006fa0c0
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80
// @ref ?unknown_color_7a7360@@3HA=007a7360

HRESULT __stdcall CChatEventSink::OnMessageOfTheDay(HRESULT result, char const *motd)
{
    wchar_t buffer[1024];
    if (result < 0) {
        return S_OK;
    }
    char *copy = _strdup(motd);
    char *line = strtok(copy, "\n");
    while (line) {
        Unknown_006FA0C0(buffer, line, -1);
        Unknown_005C2C80(unknown_color_7a7360, buffer);
        line = strtok(0, "\n");
    }
    free(copy);
    Unknown_005C2C80(unknown_color_7a7360, L"\n");
    return S_OK;
}
// @ref ??_C@_01BJG@?6?$AA@=007f3830
// @ref ??_C@_13DEJI@?$AA?6?$AA?$AA@=007e58ec
