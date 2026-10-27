// 0x004ff1f0: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool FUN_004ff1f0(void)
// Callees with accepted source:
//   FUN_004ff1e0 -> src/recovered/004ff1e0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004ff1f0 {

extern undefined4  FUN_004ff1e0(void);

bool  FUN_004ff1f0(void)
{
    char cVar1;

    cVar1 = (char)(FUN_004ff1e0());
    return cVar1 == '\0';
}

}  // namespace seed_004ff1f0
