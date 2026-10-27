// 0x005b9000: function not yet identified
//
// Owner: DynamicVectorClass<MultiplayerGameMode *>, virtual slot 3 (vtable +0xc) (from RTTI/vtables).
// Body: 42 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void __fastcall FUN_005b9000(int param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b9000 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_005b9000(int param_1)
{
    *(undefined4 *)(param_1 + 0x10) = 0;
    if ((*(int *)(param_1 + 4) != 0) && (*(char *)(param_1 + 0xd) != '\0')) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 4)));
        *(undefined4 *)(param_1 + 4) = 0;
    }
    *(undefined1 *)(param_1 + 0xd) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    return;
}

}  // namespace seed_005b9000
