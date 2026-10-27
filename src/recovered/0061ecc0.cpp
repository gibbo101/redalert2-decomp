// 0x0061ecc0: function not yet identified
//
// Body: 51 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0061ecc0(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0061ecc0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00a76a3c;
extern "C" char DAT_00a76a40;
extern "C" void* PTR_FUN_007a843c;
extern "C" undefined4 _DAT_00a769e8;

void  FUN_0061ecc0(void)
{
    _DAT_00a769e8 = (unsigned int)(&PTR_FUN_007a843c);
    if (DAT_00a76a40 != '\0') {
        FUN_00781d3b((undefined4)(DAT_00a76a3c));
        DAT_00a76a40 = '\0';
    }
    DAT_00a76a3c = 0;
    return;
}

}  // namespace seed_0061ecc0
