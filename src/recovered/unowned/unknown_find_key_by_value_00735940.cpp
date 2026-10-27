// void *__fastcall Unknown_00735940(int value) -- 0x00735940
// Purpose: in the table of {key, value} pairs at 0x00B25BB8 (count at
// 0x00B25DE0; also 0x00735970/0x007359B0), the key of the last entry whose
// value equals value; null when there is none. 0x0074D780 looks up entry
// 0xC4 with it and uses the key as a window.
// Assumptions: the table's meaning (window per id) and the names are
// hypotheses.

struct UnknownPair_b25bb8 {
    int Key;
    int Value;
};
extern UnknownPair_b25bb8 unknown_pairs_b25bb8[];
extern int unknown_pair_count_b25de0;
// @ref ?unknown_pairs_b25bb8@@3PAUUnknownPair_b25bb8@@A=00b25bb8
// @ref ?unknown_pair_count_b25de0@@3HA=00b25de0

void *__fastcall Unknown_00735940(int value)
{
    for (int index = unknown_pair_count_b25de0 - 1; index >= 0; index--) {
        if (value == unknown_pairs_b25bb8[index].Value) {
            return (void *)unknown_pairs_b25bb8[index].Key;
        }
    }
    return 0;
}
