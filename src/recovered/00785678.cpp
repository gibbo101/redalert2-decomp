// 0x00785678: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00785678(LPCSTR param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00785678 {

extern void  FUN_007898ab(uint param_1);
extern "C" __declspec(dllimport) undefined4 __stdcall DeleteFileA(int);  // @ref __imp__DeleteFileA@4=0079a128
extern "C" __declspec(dllimport) undefined4 __stdcall GetLastError(void);  // @ref __imp__GetLastError@0=0079a1f4

undefined4  FUN_00785678(LPCSTR param_1)
{
    BOOL BVar1;
    DWORD DVar2;

    BVar1 = (BOOL)(DeleteFileA((int)(param_1)));
    if (BVar1 == 0) {
        DVar2 = (DWORD)(GetLastError());
    }
    else {
        DVar2 = (DWORD)(0);
    }
    if (DVar2 != 0) {
        FUN_007898ab((uint)(DVar2));
        return 0xffffffff;
    }
    return 0;
}

}  // namespace seed_00785678
