// Wstring __fastcall operator+(char const *string, Wstring const &other) (0x0076F6B0)
// A C string followed by a Wstring.
#include "shared/wstring.hpp"

Wstring __fastcall operator+(char const *string, Wstring const &other)
{
    return Wstring(string) + other;
}
