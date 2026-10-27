// 0x00792ad4: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_00792ad4(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00792ad4 {

extern void __cdecl FUN_00792a8e(void);
extern "C" __declspec(dllimport) undefined4 __stdcall SetUnhandledExceptionFilter(int);  // @ref __imp__SetUnhandledExceptionFilter@4=0079a13c
extern "C" undefined4 DAT_00b2b33c;

void  FUN_00792ad4(void)
{
    DAT_00b2b33c = SetUnhandledExceptionFilter((int)(FUN_00792a8e));
    return;
}

}  // namespace seed_00792ad4
