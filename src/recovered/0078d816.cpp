// 0x0078d816: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 16 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078d816(char *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078d816 {

extern undefined4  FUN_0078d6e0(uint *param_1, uint *param_2);
extern "C" undefined4 __cdecl _malloc(...);  // @ref __malloc=00782630
extern "C" undefined4 __cdecl _strlen(...);  // @ref __strlen=00789830

undefined4  FUN_0078d816(char *param_1)
{
    size_t sVar1;
    void *pvVar2;
    undefined4 uVar3;

    if (param_1 != (char *)0x0) {
        sVar1 = (size_t)(_strlen(param_1));
        pvVar2 = (void *)(_malloc(sVar1 + 1));
        if (pvVar2 != (void *)0x0) {
            uVar3 = (undefined4)(FUN_0078d6e0((uint *)(pvVar2), (uint *)(param_1)));
            return uVar3;
        }
    }
    return 0;
}

}  // namespace seed_0078d816
