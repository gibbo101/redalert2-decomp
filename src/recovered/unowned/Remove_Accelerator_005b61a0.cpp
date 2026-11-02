// void __fastcall Remove_Accelerator(HACCEL accelerator) -- 0x005B61A0 (Westwood msgloop.cpp)
#include "shared/msgloop.hpp"
#include "shared/crt_string.hpp"
// @ref ?_Accelerators@@3V?$DynamicVectorClass@UAcceleratorTracker@@@@A=00a71928

void __fastcall Remove_Accelerator(HACCEL accelerator)
{
    for (int index = 0; index < _Accelerators.Count(); index++) {
        if (_Accelerators[index].unknown_00 == (int)accelerator) {
            _Accelerators.Delete(index);
            break;
        }
    }
}
