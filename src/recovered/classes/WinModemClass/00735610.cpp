// 0x00735610: function not yet identified
//
// Owner: WinModemClass, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 85 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_00735610(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00735610 {

extern void  FUN_004068f0(int);
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" __declspec(dllimport) undefined4 __stdcall CloseHandle(int);  // @ref __imp__CloseHandle@4=0079a1d4
extern "C" void* PTR_FUN_007af4e0;
extern "C" char s_Closing_serial_port_007fca0c[];

struct Owner_00735610 { undefined4 * FUN_00735610(byte param_2); };

undefined4 * Owner_00735610::FUN_00735610(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_007af4e0);
    if (param_1[0x17] != -1) {
        FUN_004068f0((int)(s_Closing_serial_port_007fca0c));
        CloseHandle((int)((HANDLE)param_1[0x17]));
        param_1[0x17] = 0xffffffff;
    }
    if (param_1[9] != 0) {
        FUN_00781d3b((undefined4)(param_1[9]));
    }
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_00735610
