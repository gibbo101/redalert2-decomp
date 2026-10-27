// 0x005aa770: function not yet identified
//
// Owner: Megawealth, virtual slot 29 (vtable +0x74) (from RTTI/vtables).
// Body: 13 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined1 FUN_005aa770(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005aa770 {

struct Callee_0055a1f0 { void FUN_0055a1f0(); };
extern "C" undefined4 DAT_008324e0;

undefined1  FUN_005aa770(void)
{
    ((Callee_0055a1f0*)(&DAT_008324e0))->FUN_0055a1f0();
    return 1;
}

}  // namespace seed_005aa770
