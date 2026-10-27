// 0x00789927: function not yet identified
//
// Body: 9 bytes (frozen inventory bound).
// Referenced from 21 sites (unconditional call).
// Ghidra prototype: int FUN_00789927(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00789927 {

extern undefined4  FUN_0078969b(void);

int  FUN_00789927(void)
{
    int iVar1;

    iVar1 = (int)(FUN_0078969b());
    return iVar1 + 0xc;
}

}  // namespace seed_00789927
