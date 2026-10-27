// void unknown_init_identity_ad0970() -- 0x00716FA0
// Purpose: fills the 256 bytes at 0x00AD0970 with their own index (an
// identity translation table).
// Assumptions: what the table holds is unknown.
// @ref ?unknown_table_ad0970@@3PADA=00ad0970

extern char unknown_table_ad0970[256];

void unknown_init_identity_ad0970()
{
    for (int index = 0; index < 256; index++) {
        unknown_table_ad0970[index] = (char)index;
    }
}
