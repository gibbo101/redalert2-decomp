// 0x00769590: function not yet identified
//
// Body: 6 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined * FUN_00769590(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00769590 {

extern "C" undefined4 DAT_00b2ad80;

undefined *  FUN_00769590(void)
{
    return (unsigned char *)(&DAT_00b2ad80);
}

}  // namespace seed_00769590
