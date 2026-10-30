// Wstring __fastcall Unknown_00745450(WOL::Server const *server) (0x00745450)
// The server name after its first ':' (the whole name when it has none).
#include "shared/wol_sink.hpp"
// @ref ??_C@_01PKAG@?3?$AA@=007e6f8c

Wstring __fastcall Unknown_00745450(WOL::Server const *server)
{
    Wstring name(server->name);
    Wstring token;
    int position = name.Get_Token(0, ":", token);
    if (position >= 0) name.Remove(0, position + 1);
    return name;
}
