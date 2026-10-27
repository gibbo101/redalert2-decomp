// void UnknownComHolder_0065B2B0::unknown_release() -- 0x0065B2B0
// Purpose: releases the COM interface held at +0x00 when there is one (the
// pointer is not cleared).
// Assumptions: owner unidentified; the interface is any IUnknown (the
// same code as 0x00765B00 in another unit).
#include "shared/com_api.hpp"

struct UnknownComHolder_0065b2b0 {
    IUnknown *Interface;                    // +0x00
    void unknown_release();
};

void UnknownComHolder_0065b2b0::unknown_release()
{
    if (Interface != 0) {
        Interface->Release();
    }
}
