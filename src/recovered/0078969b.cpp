// 0x0078969b: function not yet identified
//
// Body: 103 bytes (frozen inventory bound).
// Referenced from 14 sites (unconditional call).
// Ghidra prototype: DWORD * FUN_0078969b(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078969b {

extern void  FUN_00789688(int param_1);
extern undefined4  FUN_0078b604(int param_1, int param_2);
extern "C" __declspec(dllimport) undefined4 __stdcall GetCurrentThreadId(void);  // @ref __imp__GetCurrentThreadId@0=0079a1c4
extern "C" __declspec(dllimport) undefined4 __stdcall GetLastError(void);  // @ref __imp__GetLastError@0=0079a1f4
extern "C" __declspec(dllimport) undefined4 __stdcall SetLastError(int);  // @ref __imp__SetLastError@4=0079a2b8
extern "C" __declspec(dllimport) undefined4 __stdcall TlsGetValue(int);  // @ref __imp__TlsGetValue@4=0079a2b0
extern "C" __declspec(dllimport) undefined4 __stdcall TlsSetValue(int, int);  // @ref __imp__TlsSetValue@8=0079a2a8
extern "C" undefined4 __cdecl __amsg_exit(...);  // @ref ___amsg_exit=00785ba8
extern "C" undefined4 DAT_0082f438;
extern "C" char LAB_007896f6[];

DWORD *  FUN_0078969b(void)
{
    DWORD dwErrCode;
    DWORD *lpTlsValue;
    BOOL BVar1;
    DWORD DVar2;

    dwErrCode = (DWORD)(GetLastError());
    lpTlsValue = (DWORD *)(TlsGetValue((int)(DAT_0082f438)));
    if (lpTlsValue == (DWORD *)0x0) {
        lpTlsValue = (DWORD *)FUN_0078b604((int)(1), (int)(0x74));
        if (lpTlsValue != (DWORD *)0x0) {
            BVar1 = (BOOL)(TlsSetValue((int)(DAT_0082f438), (int)(lpTlsValue)));
            if (BVar1 != 0) {
                FUN_00789688((int)(lpTlsValue));
                DVar2 = (DWORD)(GetCurrentThreadId());
                lpTlsValue[1] = 0xffffffff;
                *lpTlsValue = DVar2;
                goto LAB_007896f6;
            }
        }
        __amsg_exit(0x10);
    }
LAB_007896f6:
    SetLastError((int)(dwErrCode));
    return lpTlsValue;
}

}  // namespace seed_0078969b
