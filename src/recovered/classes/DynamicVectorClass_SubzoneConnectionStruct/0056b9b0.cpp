// 0x0056b9b0: function not yet identified
//
// Owner: DynamicVectorClass<SubzoneConnectionStruct>, stores the DynamicVectorClass<SubzoneConnectionStruct> vtable (constructor or destructor) (from RTTI/vtables).
// Body: 56 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 * __fastcall FUN_0056b9b0(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056b9b0 {

extern "C" void* PTR_FUN_007a5ad8;
extern "C" void* PTR_FUN_007a5ae4;

undefined4 * __fastcall FUN_0056b9b0(undefined4 *param_1)
{
    param_1[1] = 0;
    param_1[2] = 0;
    *(undefined1 *)(param_1 + 3) = 1;
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    *param_1 = (undefined4)(&PTR_FUN_007a5ad8);
    param_1[5] = 10;
    param_1[4] = 0;
    (*(code *)PTR_FUN_007a5ae4)();
    *(undefined2 *)(param_1 + 6) = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    return param_1;
}

}  // namespace seed_0056b9b0
