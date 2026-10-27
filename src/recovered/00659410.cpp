// 0x00659410: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_00659410(int param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00659410 {

extern "C" undefined4 __cdecl _strncpy(...);  // @ref __strncpy=007823d0

struct Owner_00659410 { void FUN_00659410(char *param_2); };

void Owner_00659410::FUN_00659410(char *param_2)
{
    int param_1 = (int)this;
    *(undefined1 *)(param_1 + 0x3d7) = 0;
    _strncpy((char *)(param_1 + 0x2d4),param_2,0x103);
    return;
}

}  // namespace seed_00659410
