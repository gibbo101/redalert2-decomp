// HRESULT __stdcall CNetUtilEventSink::OnAgeCheck(HRESULT result, int years, int consent) (0x0075DEB0, slot 7)
// Records the age-check answer, clears its pending bit (closing dialog 0xC4
// when nothing else is pending) and focuses control 0x540.
#include "shared/wol_sink.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_b2ac0c@@3HA=00b2ac0c
// @ref ?unknown_b2ac6c@@3HA=00b2ac6c
// @ref ?unknown_b2ac70@@3HA=00b2ac70
// @ref ?unknown_b2abe0@@3IA=00b2abe0
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_007357E0@@YIXPAXH@Z=007357e0
// @ref ?Unknown_00735B10@@YAPAUHWND__@@XZ=00735b10

HRESULT __stdcall CNetUtilEventSink::OnAgeCheck(HRESULT result, int years, int consent)
{
    Debug_Printf("OnAgeCheck\n");
    unknown_b2ac0c = result;
    if (result == S_OK) {
        unknown_b2ac6c = years;
        unknown_b2ac70 = consent;
    }
    void *dialog = Unknown_00735940(0xC4);
    if (dialog) {
        unknown_b2abe0 &= ~0x100;
        if (!unknown_b2abe0) {
            Unknown_007357E0(dialog, 0);
        }
    }
    HWND dialog_window = Unknown_00735B10();
    HWND window = GetDlgItem(dialog_window, 0x540);
    if (window) {
        SetFocus(window);
    }
    return S_OK;
}
// @ref ??_C@_0M@CEOJ@OnAgeCheck?6?$AA@=007fdbb8
