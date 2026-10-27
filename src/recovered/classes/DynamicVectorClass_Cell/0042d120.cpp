// 0x0042d120: function not yet identified
//
// Owner: DynamicVectorClass<Cell>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 54 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_0042d120(int param_1,short *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042d120 {

struct Owner_0042d120 { int FUN_0042d120(short *param_2); };

int Owner_0042d120::FUN_0042d120(short *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    short *psVar2;

    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 0x10)) {
        psVar2 = (short *)(*(short **)(param_1 + 4));
        do {
            if ((*psVar2 == *param_2) && (psVar2[1] == param_2[1])) {
                return iVar1;
            }
            iVar1 = (int)(iVar1 + 1);
            psVar2 = (short *)(psVar2 + 2);
        } while (iVar1 < *(int *)(param_1 + 0x10));
    }
    return -1;
}

}  // namespace seed_0042d120
