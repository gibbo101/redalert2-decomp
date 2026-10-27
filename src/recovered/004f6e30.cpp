// 0x004f6e30: function not yet identified
//
// Owner: DynamicVectorClass<bool>, virtual slot 5 (vtable +0x14) (from RTTI/vtables).
// Body: 24 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_004f6e30(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004f6e30 {

struct Owner_004f6e30 { int FUN_004f6e30(int param_2); };

int Owner_004f6e30::FUN_004f6e30(int param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0xc) == '\0') {
        return 0;
    }
    return param_2 - *(int *)(param_1 + 4);
}

}  // namespace seed_004f6e30
