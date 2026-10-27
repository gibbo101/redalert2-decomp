// void UnknownRecord_006E7740::UnknownRecord_006e7740() -- 0x006E7740
// Purpose: resets the record: two words at +0x280, flags +0x288 (set),
// +0x289, +0x28A, +0x28C = -1, and empties the strings at +0x000,
// +0x100 and the wide string at +0x200.
// Assumptions: a theme record (Theme.cpp area); field meanings unknown.

struct UnknownRecord_006e7740 {
    char Name[0x100];                       // +0x000
    char unknown_100[0x100];                // +0x100
    unsigned short unknown_200[0x40];       // +0x200
    int unknown_280;                        // +0x280
    int unknown_284;                        // +0x284
    bool unknown_288;                       // +0x288
    bool unknown_289;                       // +0x289
    bool unknown_28a;                       // +0x28A
    int unknown_28c;                        // +0x28C
    UnknownRecord_006e7740();
};

UnknownRecord_006e7740::UnknownRecord_006e7740()
{
    unknown_280 = 0;
    unknown_284 = 0;
    unknown_288 = true;
    unknown_289 = false;
    unknown_28a = false;
    unknown_28c = -1;
    Name[0] = 0;
    unknown_100[0] = 0;
    unknown_200[0] = 0;
}
