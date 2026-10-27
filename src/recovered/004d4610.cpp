// 0x004d4610: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d4610(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_004d4610 {

extern "C" void* PTR_FUN_007a2abc;
extern "C" undefined4 _DAT_00a40c88;

void  FUN_004d4610(void)
{
    _DAT_00a40c88 = (unsigned int)(&PTR_FUN_007a2abc);
    return;
}

}  // namespace seed_004d4610
