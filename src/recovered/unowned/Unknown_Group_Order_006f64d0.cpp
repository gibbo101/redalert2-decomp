// void __fastcall Unknown_006F64D0(bool arg) (0x006F64D0)
// Unless the flag 0x00A3D548 is set: 0x00614760, then 0x00616EC0 (arg, true).
// @ref ?Unknown_00614760@@YAXXZ=00614760
// @ref ?Unknown_00616EC0@@YIX_N0@Z=00616ec0
// @ref ?unknown_int_a3d548@@3HA=00a3d548

extern int unknown_int_a3d548;
void Unknown_00614760();
void __fastcall Unknown_00616EC0(bool arg1, bool arg2);

void __fastcall Unknown_006F64D0(bool arg)
{
    if (unknown_int_a3d548 == 0) {
        Unknown_00614760();
        Unknown_00616EC0(arg, true);
    }
}
