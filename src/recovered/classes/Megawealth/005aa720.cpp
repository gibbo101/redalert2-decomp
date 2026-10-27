// 0x005aa720: function not yet identified
//
// Owner: Megawealth, stores the Megawealth vtable (constructor or destructor) (from RTTI/vtables).
// Body: 52 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 * __thiscall FUN_005aa720(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005aa720 {

struct Callee_005b6cd0 { void FUN_005b6cd0(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined1 param_6, undefined4 param_7); };
extern "C" void* PTR_FUN_007a6aa4;

struct Owner_005aa720 { undefined4 * FUN_005aa720(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7); };

undefined4 * Owner_005aa720::FUN_005aa720(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7)
{
    undefined4 * param_1 = (undefined4 *)this;
    ((Callee_005b6cd0*)(param_1))->FUN_005b6cd0((undefined4)(param_2), (undefined4)(param_3), (undefined4)(param_4), (undefined4)(param_5), (undefined1)(param_6), (undefined4)(param_7));
    *param_1 = (undefined4)(&PTR_FUN_007a6aa4);
    return param_1;
}

}  // namespace seed_005aa720
