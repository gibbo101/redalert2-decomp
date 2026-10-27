// 0x0046d8b0: function not yet identified
//
// Owner: VectorClass<RGBClass>, virtual slot 4 (vtable +0x10) (from RTTI/vtables).
// Body: 73 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int __thiscall FUN_0046d8b0(int param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0046d8b0 {

struct Owner_0046d8b0 { int FUN_0046d8b0(char *param_2); };

int Owner_0046d8b0::FUN_0046d8b0(char *param_2)
{
    int param_1 = (int)this;
    int iVar1;
    char *pcVar2;

    if (*(char *)(param_1 + 0xc) == '\0') {
        return 0;
    }
    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 8)) {
        pcVar2 = (char *)(*(char **)(param_1 + 4));
        do {
            if (((*pcVar2 == *param_2) && (pcVar2[1] == param_2[1])) && (pcVar2[2] == param_2[2])) {
                return iVar1;
            }
            iVar1 = (int)(iVar1 + 1);
            pcVar2 = (char *)(pcVar2 + 3);
        } while (iVar1 < *(int *)(param_1 + 8));
    }
    return -1;
}

}  // namespace seed_0046d8b0
