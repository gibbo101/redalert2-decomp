// 0x00752930: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00752930(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00752930 {

extern "C" __declspec(dllimport) undefined4 __stdcall ResetEvent(int);  // @ref __imp__ResetEvent@4=0079a170
extern "C" undefined4 DAT_00b264f8;

void  FUN_00752930(void)
{
    undefined4 *puVar1;

    puVar1 = (undefined4 *)(&DAT_00b264f8);
    do {
        ResetEvent((int)((HANDLE)*puVar1));
        puVar1 = (undefined4 *)(puVar1 + 1);
    } while ((int)puVar1 < 0xb26540);
    return;
}

}  // namespace seed_00752930
