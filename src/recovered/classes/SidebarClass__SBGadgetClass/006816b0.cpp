// 0x006816b0: function not yet identified
//
// Owner: SidebarClass::SBGadgetClass, virtual slot 31 (vtable +0x7c) (from RTTI/vtables).
// Body: 22 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_006816b0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006816b0 {

struct Callee_0059f250 { undefined4 FUN_0059f250(int param_2, char param_3); };
extern "C" undefined4 DAT_008324e0;

undefined4 __stdcall FUN_006816b0(int unused_0, int unused_1)
{
    ((Callee_0059f250*)(&DAT_008324e0))->FUN_0059f250((int)(0), (char)(0));
    return 1;
}

}  // namespace seed_006816b0
