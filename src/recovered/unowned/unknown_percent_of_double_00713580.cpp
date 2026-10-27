// int UnknownScaled_00713580::unknown_percent() const -- 0x00713580
// Purpose: the double at +0x00 times 100, truncated.
// Assumptions: owner unidentified (a ratio stored as a double).
// @ref __real@8@4005c800000000000000=0079b7f0

struct UnknownScaled_00713580 {
    double Value;                           // +0x00
    int unknown_percent() const;
};

int UnknownScaled_00713580::unknown_percent() const
{
    return (int)(Value * 100.0);
}
