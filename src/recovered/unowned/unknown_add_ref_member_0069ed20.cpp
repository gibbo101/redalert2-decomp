// void UnknownComHolder_0069ED20::unknown_add_ref() -- 0x0069ED20
// Purpose: adds a reference to the COM interface held at +0x00 when there is one.
// Assumptions: owner unidentified; the interface is any IUnknown.
#include "shared/com_api.hpp"

struct UnknownComHolder_0069ed20 {
    IUnknown *Interface;                    // +0x00
    void unknown_add_ref();
};

void UnknownComHolder_0069ed20::unknown_add_ref()
{
    if (Interface != 0) {
        Interface->AddRef();
    }
}
