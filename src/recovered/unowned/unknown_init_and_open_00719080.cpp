// UnknownRecord_00719080::UnknownRecord_00719080(void *arg1, void *arg2) -- 0x00719080
// Purpose: clears the record (flag +0x00, six words) and runs 0x00719160
// with both arguments; the flag is set when that returns 0.
// Assumptions: an unidentified 0x1C-byte record; that the flag means
// success is a hypothesis.
// @ref ?unknown_load_719160@UnknownRecord_00719080@@QAEHPAX0@Z=00719160

struct UnknownRecord_00719080 {
    UnknownRecord_00719080(void *arg1, void *arg2);
    int unknown_load_719160(void *arg1, void *arg2);    // 0x00719160

    bool unknown_00;                        // +0x00
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
};

UnknownRecord_00719080::UnknownRecord_00719080(void *arg1, void *arg2)
{
    unknown_00 = false;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0c = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    if (unknown_load_719160(arg1, arg2) == 0) {
        unknown_00 = true;
    }
}
