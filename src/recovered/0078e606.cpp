// 0x0078e606: function not yet identified
//
// Body: 57 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_0078e606(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0078e606 {

extern void  FUN_0078e63f(DWORD param_1);
extern "C" undefined4 DAT_0082ef34;
extern "C" undefined4 DAT_00b2b028;
extern "C" code * DAT_00b2b214;

void  FUN_0078e606(void)
{
    if ((DAT_00b2b028 == 1) || ((DAT_00b2b028 == 0 && (DAT_0082ef34 == 1)))) {
        FUN_0078e63f((DWORD)(0xfc));
        if ((uint)(DAT_00b2b214) != (uint)((code *)0x0)) {
            (*DAT_00b2b214)();
        }
        FUN_0078e63f((DWORD)(0xff));
    }
    return;
}

}  // namespace seed_0078e606
