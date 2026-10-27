// void UnknownComHolder_00765B00::unknown_release() -- 0x00765B00
// Purpose: releases the COM interface held at +0x00 when there is one (the
// pointer is not cleared).
// Assumptions: owner unidentified; the interface is any IUnknown.
#include "shared/com_api.hpp"

struct UnknownComHolder_00765b00 {
    IUnknown *Interface;                    // +0x00
    void unknown_release();
};

void UnknownComHolder_00765b00::unknown_release()
{
    if (Interface != 0) {
        Interface->Release();
    }
}
