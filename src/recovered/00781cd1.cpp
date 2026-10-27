// 0x00781cd1: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: bool __thiscall FUN_00781cd1(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00781cd1 {

extern "C" undefined4 __cdecl _strcmp(...);  // @ref __strcmp=00785d20

struct Owner_00781cd1 { bool FUN_00781cd1(int param_2); };

bool Owner_00781cd1::FUN_00781cd1(int param_2)
{
    int param_1 = (int)this;
    int iVar1;

    iVar1 = (int)(_strcmp((char *)(param_2 + 9),(char *)(param_1 + 9)));
    return iVar1 == 0;
}

}  // namespace seed_00781cd1
