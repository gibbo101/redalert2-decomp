// 0x00766ab0: function not yet identified
//
// Owner: ATL::CComObject<CDownloadEventSink>, virtual slot 1 (vtable +0x4) (from RTTI/vtables).
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_00766ab0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00766ab0 {

extern "C" __declspec(dllimport) undefined4 __stdcall InterlockedIncrement(int);  // @ref __imp__InterlockedIncrement@4=0079a1bc

void __stdcall FUN_00766ab0(int param_1)
{
    InterlockedIncrement((int)((LONG *)(param_1 + 4)));
    return;
}

}  // namespace seed_00766ab0
