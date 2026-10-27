// int __fastcall unknown_next_key(int key) -- 0x00735970
// Purpose: in the table of {key, value} pairs at 0x00B25BB8 (count at
// 0x00B25DE0), the key that follows the first entry equal to key; 0 when
// key is absent or last.
// Assumptions: the table's meaning is unidentified; names are placeholders.

struct UnknownPair_b25bb8 {
    int Key;
    int Value;
};
extern UnknownPair_b25bb8 unknown_pairs_b25bb8[];
extern int unknown_pair_count_b25de0;
// @ref ?unknown_pairs_b25bb8@@3PAUUnknownPair_b25bb8@@A=00b25bb8
// @ref ?unknown_pair_count_b25de0@@3HA=00b25de0

int __fastcall unknown_next_key(int key)
{
    for (int index = 0; index < unknown_pair_count_b25de0; index++) {
        if (key == unknown_pairs_b25bb8[index].Key && index < unknown_pair_count_b25de0 - 1) {
            return unknown_pairs_b25bb8[index + 1].Key;
        }
    }
    return 0;
}
