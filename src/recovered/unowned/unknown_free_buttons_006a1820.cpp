// void unknown_free_buttons() -- 0x006A1820
// Purpose: frees the button shapes loaded by 0x006A17C0 (the 25 pointers
// at 0x00ABD8A0; only those flagged as allocated at 0x00ABE32C are
// deleted) and clears the pointers and flags.
// Assumptions: as for 0x006A17C0 (what the buttons belong to is unknown).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_button_shapes_abd8a0@@3PAPBXA=00abd8a0
// @ref ?unknown_button_allocated_abe32c@@3PA_NA=00abe32c

extern void const *unknown_button_shapes_abd8a0[25];
extern bool unknown_button_allocated_abe32c[25];

void unknown_free_buttons()
{
    for (int index = 0; index < 25; index++) {
        if (unknown_button_allocated_abe32c[index]) {
            operator delete((void *)unknown_button_shapes_abd8a0[index]);
            unknown_button_allocated_abe32c[index] = false;
        }
        unknown_button_shapes_abd8a0[index] = 0;
    }
}
