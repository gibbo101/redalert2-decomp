// 0x0046d020: function not yet identified
//
// Owner: VectorClass<int>, stores the VectorClass<int> vtable (constructor or destructor) (from RTTI/vtables).
// Body: 74 bytes (frozen inventory bound).
// Referenced from 67 sites (unconditional call).
// Ghidra prototype: undefined4 * __thiscall FUN_0046d020(undefined4 *param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0046d020 {

extern "C" undefined4 __cdecl operator_new(...);  // @ref _operator_new=00782017
extern "C" void* PTR_FUN_0079d9d4;

struct Owner_0046d020 { undefined4 * FUN_0046d020(int param_2, int param_3); };

undefined4 * Owner_0046d020::FUN_0046d020(int param_2, int param_3)
{
    undefined4 * param_1 = (undefined4 *)this;
    void *pvVar1;

    param_1[1] = 0;
    param_1[2] = param_2;
    *(undefined1 *)(param_1 + 3) = 1;
    *(undefined1 *)((int)param_1 + 0xd) = 0;
    *param_1 = (undefined4)(&PTR_FUN_0079d9d4);
    if (param_2 != 0) {
        if (param_3 != 0) {
            param_1[1] = param_3;
            return param_1;
        }
        pvVar1 = (void *)(operator_new(param_2 << 2));
        param_1[1] = (unsigned int)(pvVar1);
        *(undefined1 *)((int)param_1 + 0xd) = 1;
    }
    return param_1;
}

}  // namespace seed_0046d020
