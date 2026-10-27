// 0x004e12a0: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: bool FUN_004e12a0(void)
// Callees with accepted source:
//   FUN_004e1290 -> src/recovered/004e1290.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004e12a0 {

extern undefined4  FUN_004e1290(void);

bool  FUN_004e12a0(void)
{
    char cVar1;

    cVar1 = (char)(FUN_004e1290());
    return cVar1 == '\0';
}

}  // namespace seed_004e12a0
