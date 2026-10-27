// 0x00734170: function not yet identified
//
// Owner: WinModemClass, stores the WinModemClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 65 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00734170(undefined4 *param_1)
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

namespace seed_00734170 {

extern void  FUN_004068f0(int);
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" __declspec(dllimport) undefined4 __stdcall CloseHandle(int);  // @ref __imp__CloseHandle@4=0079a1d4
extern "C" void* PTR_FUN_007af4e0;
extern "C" char s_Closing_serial_port_007fca0c[];

void __fastcall FUN_00734170(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007af4e0);
    if (param_1[0x17] != -1) {
        FUN_004068f0((int)(s_Closing_serial_port_007fca0c));
        CloseHandle((int)((HANDLE)param_1[0x17]));
        param_1[0x17] = 0xffffffff;
    }
    if (param_1[9] != 0) {
        FUN_00781d3b((undefined4)(param_1[9]));
    }
    return;
}

}  // namespace seed_00734170
