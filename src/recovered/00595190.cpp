// 0x00595190: function not yet identified
//
// Body: 71 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_00595190(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00595190 {

extern void __cdecl FUN_005951e0(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00a70cc4;
extern "C" undefined4 DAT_00a70cc8;
extern "C" undefined4 DAT_00a70ccc;
extern "C" undefined4 DAT_00a70cd0;
extern "C" undefined4 DAT_00a70cd4;
extern "C" undefined4 DAT_00a70cd8;
extern "C" void* PTR_FUN_0079aafc;
extern "C" void* PTR_FUN_007a6458;
extern "C" undefined4 _DAT_00a70cc0;
extern "C" undefined4 _DAT_00a70cc4;
extern "C" undefined4 _DAT_00a70cd0;

void  FUN_00595190(void)
{
    DAT_00a70ccc = 0;
    _DAT_00a70cc4 = (unsigned int)(&PTR_FUN_0079aafc);
    _DAT_00a70cd0 = (unsigned int)(&PTR_FUN_0079aafc);
    DAT_00a70cd4 = 0;
    DAT_00a70cd8 = (unsigned int)(&DAT_00a70cc4);
    DAT_00a70cc8 = (unsigned int)(&DAT_00a70cd0);
    _DAT_00a70cc0 = (unsigned int)(&PTR_FUN_007a6458);
    FUN_0078298a((undefined4)(FUN_005951e0));
    return;
}

}  // namespace seed_00595190
