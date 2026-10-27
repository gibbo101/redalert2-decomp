// 0x00785bf1: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00785bf1(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00785bf1 {

extern "C" __declspec(dllimport) undefined4 __stdcall InitializeCriticalSection(int);  // @ref __imp__InitializeCriticalSection@4=0079a1e8
extern "C" void* PTR_DAT_0082ef3c;
extern "C" void* PTR_DAT_0082ef5c;
extern "C" void* PTR_DAT_0082ef6c;
extern "C" void* PTR_DAT_0082ef7c;

void  FUN_00785bf1(void)
{
    InitializeCriticalSection((int)((LPCRITICAL_SECTION)PTR_DAT_0082ef7c));
    InitializeCriticalSection((int)((LPCRITICAL_SECTION)PTR_DAT_0082ef6c));
    InitializeCriticalSection((int)((LPCRITICAL_SECTION)PTR_DAT_0082ef5c));
    InitializeCriticalSection((int)((LPCRITICAL_SECTION)PTR_DAT_0082ef3c));
    return;
}

}  // namespace seed_00785bf1
