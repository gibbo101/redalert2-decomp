// int __fastcall Unknown_0073c2e0(Wstring const &name) (0x0073C2E0)
// The index of the user list entry with this name (case-insensitive), -1 when none.
#include "shared/wol_sink.hpp"

int __fastcall Unknown_0073c2e0(Wstring const &name)
{
    return unknown_users_b2a728.Find_Name(name);
}
