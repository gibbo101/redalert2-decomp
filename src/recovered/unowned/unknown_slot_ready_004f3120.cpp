// bool __fastcall unknown_slot_ready(UnknownSlotOwner_004f3120 const *) -- 0x004F3120
// Purpose: for the current slot index (+0x154, valid 0..11) of the owner's
// twelve record pointers (+0x158), true when the record's +0x38 is below the
// rules value at +0x98 (rules object at 0x00839848) and its +0x24 is -1.
// No direct callers. Types not identified (rules view only).
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

struct UnknownSlotRecord_004f3120 {
    char unknown_00[0x24];
    int unknown_24;
    char unknown_28[0x38 - 0x28];
    int unknown_38;
};

struct UnknownSlotOwner_004f3120 {
    char unknown_000[0x154];
    int current;                                 // +0x154
    UnknownSlotRecord_004f3120 *records[12];     // +0x158
};

bool __fastcall unknown_slot_ready_004f3120(UnknownSlotOwner_004f3120 const *owner)
{
    if (owner->current < 0 || owner->current >= 12) {
        return false;
    }
    UnknownSlotRecord_004f3120 const *record = owner->records[owner->current];
    return record->unknown_38 < Rules->unknown_98 && record->unknown_24 == -1;
}
