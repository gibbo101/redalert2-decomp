// 0x005d5f40: function not yet identified
//
// Body: 120 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_005d5f40(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005d5f40 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00a72fe0;
extern "C" undefined4 DAT_00a72fe4;
extern "C" undefined4 DAT_00a72fe8;
extern "C" undefined4 DAT_00a72fec;
extern "C" char DAT_00a72ff0;
extern "C" char DAT_00a72ff1;
extern "C" char DAT_00a72ff2;
extern "C" char DAT_00a72ff3;

void  FUN_005d5f40(void)
{
    if (DAT_00a72ff0 != '\0') {
        FUN_00781d3b((undefined4)(DAT_00a72fe0));
        DAT_00a72ff0 = '\0';
    }
    if (DAT_00a72ff1 != '\0') {
        FUN_00781d3b((undefined4)(DAT_00a72fe4));
        DAT_00a72ff1 = '\0';
    }
    if (DAT_00a72ff2 != '\0') {
        FUN_00781d3b((undefined4)(DAT_00a72fe8));
        DAT_00a72ff2 = '\0';
    }
    if (DAT_00a72ff3 != '\0') {
        FUN_00781d3b((undefined4)(DAT_00a72fec));
        DAT_00a72ff3 = '\0';
    }
    return;
}

}  // namespace seed_005d5f40
