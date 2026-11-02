// bool __fastcall Unknown_0056d5f0(int value) (0x0056D5F0): true unless value is 3 or 4. The test is an inline
// int helper whose result is narrowed to a byte and negated (xor/sete), the shape of the generation unit's
// (unsigned char)Equal(...) tests; the neighbour 0x0056D5D0 tests 1, 3 and 4 directly.
static inline int Unknown_Is_3_Or_4(int value)
{
    if (value == 3 || value == 4) {
        return 1;
    }
    return 0;
}

bool __fastcall Unknown_0056d5f0(int value)
{
    return !(unsigned char)Unknown_Is_3_Or_4(value);
}
