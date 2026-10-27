// int __fastcall unknown_find_free_slot(UnknownSlotOwner_00661960 *) -- 0x00661960
// Purpose: returns the index of the first of 50 records (0x29 bytes each,
// starting at +0x1A12) whose first byte is zero, or -1 when all are in use.
// No direct callers (alignment-bounded entry). Owner type not identified.
struct UnknownSlot_00661960 {
    char unknown_00;
    char unknown_01[0x28];
};

struct UnknownSlotOwner_00661960 {
    char unknown_0000[0x1a12];
    UnknownSlot_00661960 unknown_slots_1a12[50];
};

int __fastcall unknown_find_free_slot_00661960(UnknownSlotOwner_00661960 *owner)
{
    for (int index = 0; index < 50; index++) {
        if (owner->unknown_slots_1a12[index].unknown_00 == '\0') {
            return index;
        }
    }
    return -1;
}
