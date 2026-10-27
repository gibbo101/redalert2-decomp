// void UnknownNamed_007320B0::unknown_set_name(Wstring const &name) -- 0x007320B0
// Purpose: copies name into the Wstring at +0x00 (Wstring::operator=,
// 0x0076DC30).
// Assumptions: owner unidentified; the string is its first member.
#include "shared/wstring.hpp"

struct UnknownNamed_007320b0 {
    Wstring Name;                           // +0x00
    void unknown_set_name(Wstring const &name);
};

void UnknownNamed_007320b0::unknown_set_name(Wstring const &name)
{
    Name = name;
}
