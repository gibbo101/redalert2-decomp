// 0x0058de40: function not yet identified
//
// Owner: DynamicVectorClass<CellClass *>, virtual slot 5 (vtable +0x14) (from RTTI/vtables).
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: uint __thiscall FUN_0058de40(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0058de40 {

struct Owner_0058de40 { uint FUN_0058de40(int param_2); };

uint Owner_0058de40::FUN_0058de40(int param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0xc) == '\0') {
        return 0;
    }
    return (uint)(param_2 - *(int *)(param_1 + 4)) >> 2;
}

}  // namespace seed_0058de40
