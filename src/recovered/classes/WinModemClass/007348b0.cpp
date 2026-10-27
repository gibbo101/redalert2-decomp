// 0x007348b0: function not yet identified
//
// Owner: WinModemClass, virtual slot 3 (vtable +0xc) (from RTTI/vtables).
// Body: 65 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: uint __fastcall FUN_007348b0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007348b0 {

extern "C" __declspec(dllimport) undefined4 __stdcall GetCommModemStatus(int, int);  // @ref __imp__GetCommModemStatus@8=0079a174

uint __fastcall FUN_007348b0(int param_1)
{
    uint uVar1;
    DWORD local_4;

    uVar1 = (uint)(0);
    local_4 = (DWORD)(0);
    GetCommModemStatus((int)(*(HANDLE *)(param_1 + 0x5c)), (int)(&local_4));
    if ((local_4 & 0x10) != 0) {
        uVar1 = (uint)(0x10);
    }
    if ((local_4 & 0x20) != 0) {
        uVar1 = (uint)(uVar1 | 0x20);
    }
    if ((local_4 & 0x40) != 0) {
        uVar1 = (uint)(uVar1 | 0x40);
    }
    if ((local_4 & 0x80) != 0) {
        uVar1 = (uint)(uVar1 | 0x80);
    }
    return uVar1;
}

}  // namespace seed_007348b0
