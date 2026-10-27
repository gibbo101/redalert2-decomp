// bool UnknownTable_00765E60::unknown_get_entry(UnknownEntry_00765e60 **entry, int index) -- 0x00765E60
// Purpose: the address of entry `index` (0xF8-byte entries at +0x08,
// count at +0x00); false when the index is out of range.
// Assumptions: owner and entry classes are unidentified (network area).

struct UnknownEntry_00765e60 {
    char unknown_00[0xF8];
};
struct UnknownTable_00765e60 {
    int Count;                              // +0x00
    int unknown_04;
    UnknownEntry_00765e60 *Entries;         // +0x08
    bool unknown_get_entry(UnknownEntry_00765e60 **entry, int index);
};

bool UnknownTable_00765e60::unknown_get_entry(UnknownEntry_00765e60 **entry, int index)
{
    if (index >= 0 && index < Count) {
        *entry = &Entries[index];
        return true;
    }
    return false;
}
