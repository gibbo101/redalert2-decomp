// 0x00786d3f: function not yet identified
//
// Body: 18 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00786d3f(void)
// Callees with accepted source:
//   FUN_00785049 -> src/recovered/00785049.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00786d3f {

extern void  FUN_00785049(undefined4 param_1, uint param_2);

void  FUN_00786d3f(void)
{
    FUN_00785049((undefined4)(0x10000), (uint)(0x30000));
    return;
}

}  // namespace seed_00786d3f
