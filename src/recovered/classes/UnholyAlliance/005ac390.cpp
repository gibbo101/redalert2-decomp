// 0x005ac390: function not yet identified
//
// Owner: UnholyAlliance, virtual slot 5 (vtable +0x14) (from RTTI/vtables).
// Body: 36 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_005ac390(undefined4 param_1)
// Callees with accepted source:
//   FUN_005b73a0 -> src/recovered/classes/MultiplayerGameMode/005b73a0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005ac390 {

extern undefined4 __stdcall FUN_005b73a0(int);
extern "C" char DAT_00a3d2b8;

undefined4 __stdcall FUN_005ac390(undefined4 param_1)
{
    char cVar1;

    if (DAT_00a3d2b8 != '\0') {
        cVar1 = (char)(FUN_005b73a0((int)(param_1)));
        if (cVar1 != '\0') {
            return 1;
        }
    }
    return 0;
}

}  // namespace seed_005ac390
