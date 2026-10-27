// 0x007871b9: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void FUN_007871b9(char *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007871b9 {

extern undefined4  FUN_00783290(undefined4 *param_1, undefined4 *param_2, uint param_3);
extern "C" undefined4 __cdecl _strlen(...);  // @ref __strlen=00789830

void  FUN_007871b9(char *param_1, int param_2)
{
    size_t sVar1;

    if (param_2 != 0) {
        sVar1 = (size_t)(_strlen(param_1));
        FUN_00783290((undefined4 *)(param_1 + param_2), (undefined4 *)(param_1), (uint)(sVar1 + 1));
    }
    return;
}

}  // namespace seed_007871b9
