// 0x00787a0f: function not yet identified
//
// Body: 62 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00787a0f(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00787a0f {

extern "C" __declspec(dllimport) undefined4 __stdcall HeapAlloc(int, int, int);  // @ref __imp__HeapAlloc@12=0079a270
extern "C" undefined4 DAT_00b2b984;
extern "C" undefined4 DAT_00b2b98c;
extern "C" undefined4 DAT_00b2b990;
extern "C" undefined4 DAT_00b2b994;
extern "C" undefined4 DAT_00b2b998;
extern "C" undefined4 DAT_00b2b99c;

undefined4  FUN_00787a0f(void)
{
    DAT_00b2b998 = HeapAlloc((int)(DAT_00b2b99c), (int)(0), (int)(0x140));
    if ((uint)(DAT_00b2b998) == (uint)((LPVOID)0x0)) {
        return 0;
    }
    DAT_00b2b990 = 0;
    DAT_00b2b994 = 0;
    DAT_00b2b98c = DAT_00b2b998;
    DAT_00b2b984 = 0x10;
    return 1;
}

}  // namespace seed_00787a0f
