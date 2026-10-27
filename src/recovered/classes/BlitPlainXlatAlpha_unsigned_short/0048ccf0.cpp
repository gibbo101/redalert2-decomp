// 0x0048ccf0: function not yet identified
//
// Owner: BlitPlainXlatAlpha<unsigned short>, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 59 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_0048ccf0(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0048ccf0 {

struct Callee_0041e510 { void FUN_0041e510(int param_1); };
extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_008315b8;
extern "C" void* PTR_FUN_0079e2bc;
extern "C" void* PTR_FUN_0079e52c;

struct Owner_0048ccf0 { undefined4 * FUN_0048ccf0(byte param_2); };

undefined4 * Owner_0048ccf0::FUN_0048ccf0(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = (undefined4)(&PTR_FUN_0079e2bc);
    ((Callee_0041e510*)(&DAT_008315b8))->FUN_0041e510((int)(param_1[2]));
    param_1[2] = 0;
    *param_1 = (undefined4)(&PTR_FUN_0079e52c);
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_0048ccf0
