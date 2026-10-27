// 0x004cf160: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 39 sites (unconditional call).
// Ghidra prototype: bool __fastcall FUN_004cf160(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004cf160 {

bool __fastcall FUN_004cf160(int param_1)
{
    return *(char *)(param_1 + 0x1e) == '\0';
}

}  // namespace seed_004cf160
