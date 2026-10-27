// 0x0051c0a0: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0051c0a0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0051c0a0 {

struct Callee_0049e3b0 { void FUN_0049e3b0(); };
struct Callee_004e09a0 { void FUN_004e09a0(int param_2); };
extern "C" undefined4 DAT_008324e0;
extern "C" int DAT_00a40c70;

void __stdcall FUN_0051c0a0(int unused_0)
{
    if (0 < DAT_00a40c70) {
        ((Callee_0049e3b0*)(&DAT_008324e0))->FUN_0049e3b0();
        ((Callee_004e09a0*)(&DAT_008324e0))->FUN_004e09a0((int)(1));
    }
    return;
}

}  // namespace seed_0051c0a0
