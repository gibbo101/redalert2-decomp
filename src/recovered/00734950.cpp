// 0x00734950: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00734950(int param_1)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00734950 {

extern void  FUN_004068f0(int);
extern "C" __declspec(dllimport) undefined4 __stdcall CloseHandle(int);  // @ref __imp__CloseHandle@4=0079a1d4
extern "C" char s_Closing_serial_port_007fca0c[];

void __fastcall FUN_00734950(int param_1)
{
    if (*(int *)(param_1 + 0x5c) != -1) {
        FUN_004068f0((int)(s_Closing_serial_port_007fca0c));
        CloseHandle((int)(*(HANDLE *)(param_1 + 0x5c)));
        *(undefined4 *)(param_1 + 0x5c) = 0xffffffff;
    }
    return;
}

}  // namespace seed_00734950
