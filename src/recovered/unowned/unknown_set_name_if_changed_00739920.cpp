// void UnknownNamed_00739920::unknown_set_name(Wstring const &name) -- 0x00739920
// Purpose: replaces the name at +0x0C when it differs and marks the
// object changed (+0x08).
// Assumptions: owner unidentified; names are hypotheses.
#include "shared/wstring.hpp"

struct UnknownNamed_00739920 {
    int unknown_00;
    int unknown_04;
    bool Changed;                           // +0x08
    Wstring Name;                           // +0x0C
    void unknown_set_name(Wstring const &name);
};

void UnknownNamed_00739920::unknown_set_name(Wstring const &name)
{
    if (!(name == Name)) {
        Name = name;
        Changed = true;
    }
}
