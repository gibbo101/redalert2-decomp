// void *UnknownOwner_00716770::unknown_select() -- 0x00716770
// Purpose: the member at +0x35 normally, the one at +0x2C while the flag
// at 0x00AD0958 is set.
// Assumptions: owner and members unidentified (sound area).
// @ref ?unknown_flag_ad0958@@3HA=00ad0958

extern int unknown_flag_ad0958;

struct UnknownOwner_00716770 {
    char unknown_00[0x2C];
    char unknown_2c[0x35 - 0x2C];           // +0x2C
    char unknown_35[1];                     // +0x35
    void *unknown_select();
};

void *UnknownOwner_00716770::unknown_select()
{
    return unknown_flag_ad0958 == 0 ? unknown_35 : unknown_2c;
}
