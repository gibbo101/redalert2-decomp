// bool UnknownOwner_0072C390::unknown_has_44() const -- 0x0072C390
// Purpose: whether the word at +0x44 is set.
// Assumptions: owner unidentified.

struct UnknownOwner_0072c390 {
    char unknown_00[0x44];
    int unknown_44;                         // +0x44
    bool unknown_has_44() const;
};

bool UnknownOwner_0072c390::unknown_has_44() const
{
    return unknown_44 != 0 ? true : false;
}
