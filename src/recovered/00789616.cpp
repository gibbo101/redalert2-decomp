// 0x00789616: function not yet identified
//
// Body: 84 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00789616(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00789616 {

extern void  FUN_00785bf1(void);
extern void  FUN_00789688(int param_1);
extern undefined4  FUN_0078b604(int param_1, int param_2);
extern "C" __declspec(dllimport) undefined4 __stdcall GetCurrentThreadId(void);  // @ref __imp__GetCurrentThreadId@0=0079a1c4
extern "C" __declspec(dllimport) undefined4 __stdcall TlsAlloc(void);  // @ref __imp__TlsAlloc@0=0079a2ac
extern "C" __declspec(dllimport) undefined4 __stdcall TlsSetValue(int, int);  // @ref __imp__TlsSetValue@8=0079a2a8
extern "C" undefined4 DAT_0082f438;

undefined4  FUN_00789616(void)
{
    DWORD *lpTlsValue;
    BOOL BVar1;
    DWORD DVar2;

    FUN_00785bf1();
    DAT_0082f438 = TlsAlloc();
    if (DAT_0082f438 != 0xffffffff) {
        lpTlsValue = (DWORD *)FUN_0078b604((int)(1), (int)(0x74));
        if (lpTlsValue != (DWORD *)0x0) {
            BVar1 = (BOOL)(TlsSetValue((int)(DAT_0082f438), (int)(lpTlsValue)));
            if (BVar1 != 0) {
                FUN_00789688((int)(lpTlsValue));
                DVar2 = (DWORD)(GetCurrentThreadId());
                lpTlsValue[1] = 0xffffffff;
                *lpTlsValue = DVar2;
                return 1;
            }
        }
    }
    return 0;
}

}  // namespace seed_00789616
