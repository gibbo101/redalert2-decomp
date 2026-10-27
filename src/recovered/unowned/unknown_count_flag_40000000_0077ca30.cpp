// int __fastcall unknown_count_flagged(UnknownFlagTable_0077ca30 const *) -- 0x0077CA30
// Purpose: counts the entries of a word table (+0x764, count at +0x10)
// that have bit 0x40000000 set. No direct callers.
struct UnknownFlagTable_0077ca30 {
    char unknown_000[0x10];
    int count;                       // +0x10
    char unknown_014[0x764 - 0x14];
    unsigned int *entries;           // +0x764
};

int __fastcall unknown_count_flag_40000000_0077ca30(UnknownFlagTable_0077ca30 const *table)
{
    int found = 0;
    for (int index = 0; index < table->count; index++) {
        if ((table->entries[index] & 0x40000000) != 0) {
            found++;
        }
    }
    return found;
}
