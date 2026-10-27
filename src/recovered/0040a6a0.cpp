// 0x0040a6a0: function not yet identified
//
// Body: 14 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_0040a6a0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040a6a0 {

extern "C" __declspec(dllimport) undefined4 __stdcall EnterCriticalSection(int);  // @ref __imp__EnterCriticalSection@4=0079a1dc
extern "C" undefined4 DAT_00831590;

undefined4  FUN_0040a6a0(void)
{
    EnterCriticalSection((int)((LPCRITICAL_SECTION)&DAT_00831590));
    return 0;
}

}  // namespace seed_0040a6a0
