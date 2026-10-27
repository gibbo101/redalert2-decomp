// 0x005c67a0: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_005c67a0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c67a0 {

extern "C" __declspec(dllimport) undefined4 __stdcall SendDlgItemMessageA(int, int, int, int, int);  // @ref __imp__SendDlgItemMessageA@20=0079a484
extern "C" undefined4 DAT_00a728e0;

void  FUN_005c67a0(void)
{
    SendDlgItemMessageA((int)(DAT_00a728e0), (int)(0x553), (int)(0x188), (int)(0), (int)(0));
    return;
}

}  // namespace seed_005c67a0
