// void UnknownState_006231A0::UnknownState_006231a0() -- 0x006231A0
// Purpose: clears +0x2EC, +0x300, the two 5-word arrays at +0x304 and
// +0x318, +0x32C..+0x334, and sets +0x338 to 0x20000.
// Assumptions: owner and fields unidentified.

struct UnknownState_006231a0 {
    char unknown_000[0x2EC];
    int unknown_2ec;                        // +0x2EC
    char unknown_2f0[0x300 - 0x2F0];
    int unknown_300;                        // +0x300
    int unknown_304[5];                     // +0x304
    int unknown_318[5];                     // +0x318
    int unknown_32c;                        // +0x32C
    int unknown_330;                        // +0x330
    int unknown_334;                        // +0x334
    int unknown_338;                        // +0x338
    UnknownState_006231a0();
};

UnknownState_006231a0::UnknownState_006231a0()
{
    unknown_300 = 0;
    unknown_2ec = 0;
    for (int index = 0; index < 5; index++) {
        unknown_318[index] = 0;
        unknown_304[index] = 0;
    }
    unknown_330 = 0;
    unknown_32c = 0;
    unknown_334 = 0;
    unknown_338 = 0x20000;
}
