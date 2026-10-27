// int __fastcall unknown_lookup_pair(int key) -- 0x0065B250
// Purpose: the value paired with key in the 13 {key, value} pairs at
// 0x007F1C10, 0 when the key is not listed.
// Assumptions: what the pairs map is unknown.
// @ref ?unknown_pairs_7f1c10@@3PAUUnknownPair_0065b250@@A=007f1c10

struct UnknownPair_0065b250 {
    int Key;
    int Value;
};
extern UnknownPair_0065b250 unknown_pairs_7f1c10[13];

int __fastcall unknown_lookup_pair(int key)
{
    for (int index = 0; index < 13; index++) {
        if (unknown_pairs_7f1c10[index].Key == key) {
            return unknown_pairs_7f1c10[index].Value;
        }
    }
    return 0;
}
