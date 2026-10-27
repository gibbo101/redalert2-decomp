// 0x0046da30: function not yet identified
//
// Owner: DynamicVectorClass<RGBClass>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 58 bytes (frozen inventory bound).
// Referenced from 2 sites (data).
// Ghidra prototype: int __thiscall FUN_0046da30(int param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0046da30 {

struct Owner_0046da30 { int FUN_0046da30(char *param_2); };

int Owner_0046da30::FUN_0046da30(char *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    char *pcVar2;

    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 0x10)) {
        pcVar2 = (char *)(*(char **)(param_1 + 4));
        do {
            if (((*pcVar2 == *param_2) && (pcVar2[1] == param_2[1])) && (pcVar2[2] == param_2[2])) {
                return iVar1;
            }
            iVar1 = (int)(iVar1 + 1);
            pcVar2 = (char *)(pcVar2 + 3);
        } while (iVar1 < *(int *)(param_1 + 0x10));
    }
    return -1;
}

}  // namespace seed_0046da30
