// 0x00763ab0: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 2 sites (data).
// Ghidra prototype: undefined4 FUN_00763ab0(undefined4 param_1,int param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00763ab0 {

extern void  FUN_005c2c80(int, int, int);
extern "C" undefined4 DAT_007a7360;
extern "C" char DAT_00b2abd9;
extern "C" wchar16 u______hs_007fe1c8[];

undefined4 __stdcall FUN_00763ab0(undefined4 param_1, int param_2, undefined4 param_3)
{
    if ((DAT_00b2abd9 == '\0') && (param_2 >= 0)) {
        FUN_005c2c80((int)(DAT_007a7360), (int)(u______hs_007fe1c8), (int)(param_3));
    }
    return 0;
}

}  // namespace seed_00763ab0
