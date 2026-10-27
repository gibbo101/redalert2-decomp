// int __fastcall unknown_is_listed_b25bb8(int key) -- 0x00735910
// Purpose: whether key is the first word of one of the 0x00B25DE0 used
// 8-byte records at 0x00B25BB8.
// Assumptions: what the records are is unknown (WOL area).
// @ref ?unknown_records_b25bb8@@3PAUUnknownRecord_00735910@@A=00b25bb8
// @ref ?unknown_record_count_b25de0@@3HA=00b25de0

struct UnknownRecord_00735910 {
    int Key;
    int unknown_04;
};
extern UnknownRecord_00735910 unknown_records_b25bb8[];
extern int unknown_record_count_b25de0;

int __fastcall unknown_is_listed_b25bb8(int key)
{
    for (int index = 0; index < unknown_record_count_b25de0; index++) {
        if (unknown_records_b25bb8[index].Key == key) {
            return 1;
        }
    }
    return 0;
}
