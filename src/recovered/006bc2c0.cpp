// 0x006bc2c0: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006bc2c0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006bc2c0 {

struct Callee_006e7e20 { void FUN_006e7e20(int param_2); };
extern "C" undefined4 DAT_00a35d78;

struct Owner_006bc2c0 { void FUN_006bc2c0(int param_2, int unused_1); };

void Owner_006bc2c0::FUN_006bc2c0(int param_2, int unused_1)
{
    int param_1 = (int)this;
    ((Callee_006e7e20*)(&DAT_00a35d78))->FUN_006e7e20((int)(*(undefined4 *)(param_2 + 4)));
    *(undefined1 *)(param_1 + 0x80) = 1;
    return;
}

}  // namespace seed_006bc2c0
