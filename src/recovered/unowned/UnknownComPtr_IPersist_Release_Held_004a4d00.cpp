// UnknownComPtr<IPersist>::Release_Held at0x004a4d00.
// Existing authored shared template member emitted by the Drive Piggyback_CLSID/Save bodies.
#include "shared/drive_locomotion.hpp"
#include "shared/com_ptr.hpp"

// Original Drive callers retain every Release_Held call out of line; these
// independently bounded copies are never expanded in this unit.
#pragma auto_inline(off)
template <>
void UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208>::Release_Held()
{
    if (Pointer != 0) {
        Pointer->Release();
    }
}

#pragma auto_inline(on)
