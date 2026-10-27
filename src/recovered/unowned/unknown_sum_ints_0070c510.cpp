// int __fastcall unknown_sum_ints(UnknownIntList_0070c510 const *) -- 0x0070C510
// Purpose: adds the first `count` ints of a fixed 512-entry list whose count
// follows the array (+0x800). No direct callers (alignment-bounded entry).
struct UnknownIntList_0070c510 {
    int values[0x200];
    int count;
};

int __fastcall unknown_sum_ints_0070c510(UnknownIntList_0070c510 const *list)
{
    int total = 0;
    for (int index = 0; index < list->count; index++) {
        total += list->values[index];
    }
    return total;
}
