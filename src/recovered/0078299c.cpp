// 0x0078299c: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0078299c(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0078299c {

extern "C" undefined4 __cdecl __amsg_exit(...);  // @ref ___amsg_exit=00785ba8
extern "C" undefined4 __cdecl _malloc(...);  // @ref __malloc=00782630
extern "C" undefined4 DAT_00b2b9b4;
extern "C" undefined4 * DAT_00b2b9b8;

void  FUN_0078299c(void)
{
    DAT_00b2b9b8 = (unsigned int *)(_malloc(0x80));
    if ((uint)(DAT_00b2b9b8) == (uint)((undefined4 *)0x0)) {
        __amsg_exit(0x18);
    }
    *DAT_00b2b9b8 = 0;
    DAT_00b2b9b4 = (unsigned int)(DAT_00b2b9b8);
    return;
}

}  // namespace seed_0078299c
