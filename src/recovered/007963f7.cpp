// 0x007963f7: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_007963f7(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007963f7 {

extern void  FUN_00785c86(int param_1);
extern void  FUN_00785ce7(int param_1);
extern undefined4  FUN_0079642f(void);

undefined4  FUN_007963f7(void)
{
    undefined4 uVar1;

    FUN_00785c86((int)(8));
    uVar1 = (undefined4)(FUN_0079642f());
    FUN_00785ce7((int)(8));
    return uVar1;
}

}  // namespace seed_007963f7
