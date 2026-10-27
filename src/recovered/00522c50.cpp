// 0x00522c50: function not yet identified
//
// Body: 95 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_00522c50(undefined4 param_1)
// Callees with accepted source:
//   FUN_00783a45 -> src/recovered/00783a45.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00522c50 {

extern undefined4  FUN_00783a45(undefined4 param_1, undefined4 param_2);
extern "C" __declspec(dllimport) undefined4 __stdcall EnterCriticalSection(int);  // @ref __imp__EnterCriticalSection@4=0079a1dc
extern "C" __declspec(dllimport) undefined4 __stdcall LeaveCriticalSection(int);  // @ref __imp__LeaveCriticalSection@4=0079a1e0
extern "C" undefined4 DAT_007ddc68;
extern "C" undefined4 DAT_00a52280;
extern "C" undefined4 DAT_00a522ac;
extern "C" undefined4 DAT_00a522b0;
extern "C" undefined4 DAT_00a522d0;

int __fastcall FUN_00522c50(undefined4 param_1)
{
    if ((DAT_00a522b0 != 0) && (DAT_00a522d0 == 0)) {
        EnterCriticalSection((int)((LPCRITICAL_SECTION)&DAT_00a52280));
        DAT_00a522d0 = FUN_00783a45((undefined4)(param_1), (undefined4)(&DAT_007ddc68));
        if (DAT_00a522d0 != 0) {
            DAT_00a522ac = 1;
        }
        LeaveCriticalSection((int)((LPCRITICAL_SECTION)&DAT_00a52280));
        return DAT_00a522d0 != 0;
    }
    return false;
}

}  // namespace seed_00522c50
