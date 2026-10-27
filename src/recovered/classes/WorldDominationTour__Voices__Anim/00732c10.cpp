// 0x00732c10: function not yet identified
//
// Owner: WorldDominationTour::Voices::Anim, virtual slot 7 (vtable +0x1c) (from RTTI/vtables).
// Body: 11 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: bool FUN_00732c10(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00732c10 {

extern undefined4  FUN_00715e20(void);

bool  FUN_00732c10(void)
{
    char cVar1;

    cVar1 = (char)(FUN_00715e20());
    return cVar1 == '\0';
}

}  // namespace seed_00732c10
