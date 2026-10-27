// void unknown_load_buttons() -- 0x006A17C0
// Purpose: loads Button00.SHP .. Button24.SHP (0x00495270) into the 25
// pointers at 0x00ABD8A0, recording whether each was allocated in the 25
// flags at 0x00ABE32C.
// Assumptions: what the buttons belong to is unknown.
// @ref _sprintf=007820f4
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ?unknown_button_shapes_abd8a0@@3PAPBXA=00abd8a0
// @ref ?unknown_button_allocated_abe32c@@3PA_NA=00abe32c
// @ref ??_C@_0P@ODHJ@Button?$CF02d?4SHP?$AA@=007f6850

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);
extern void const *unknown_button_shapes_abd8a0[25];
extern bool unknown_button_allocated_abe32c[25];

void unknown_load_buttons()
{
    char filename[256];
    bool allocated = false;
    for (int index = 0; index < 25; index++) {
        sprintf(filename, "Button%02d.SHP", index);
        unknown_button_shapes_abd8a0[index] = Unknown_Load_Shape_00495270(filename, allocated);
        unknown_button_allocated_abe32c[index] = allocated;
    }
}
