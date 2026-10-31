// void Windows_Message_Handler() -- 0x005B5EE0 (Westwood msgloop.cpp; TS reconstruction name)
// Dispatches every pending window message: each goes to 0x004919B0 and the tooltips first, then to the
// modeless dialogs, the accelerators and the intercept handler; one none of them takes is translated and
// dispatched. Ends when the queue is empty or at WM_QUIT.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/movie.hpp"
#include "shared/tool_tip.hpp"
#include "shared/win32_window.hpp"
#include "shared/msgloop.hpp"
// @ref ?unknown_message_count_a52298@@3HA=00a52298
// @ref ?unknown_peek_message_522ed0@@YIHPAUtagMSG@@PAUHWND__@@III@Z=00522ed0
// @ref ?unknown_get_message_522e90@@YIHPAUtagMSG@@PAUHWND__@@II@Z=00522e90
// @ref __imp__TranslateMessage@4=0079a4b0
// @ref __imp__DispatchMessageA@4=0079a4b4
// @ref __imp__IsDialogMessageA@8=0079a4ec
// @ref __imp__TranslateAcceleratorA@12=0079a4e4
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Process_Message@ToolTipManager@@QAEXPAUtagMSG@@@Z=006eb4e0
// @ref ?unknown_message_4919b0@@YIXPAUtagMSG@@@Z=004919b0
// @ref ?_ModelessDialogs@@3V?$DynamicVectorClass@PAUHWND__@@@@A=00a71900
// @ref ?_Accelerators@@3V?$DynamicVectorClass@UAcceleratorTracker@@@@A=00a71928
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ?Message_Intercept_Handler@@3P6I_NAAUtagMSG@@@ZA=00a719a4

WIN32_IMPORT BOOL WINAPI IsDialogMessageA(HWND dialog, MSG *message);
WIN32_IMPORT int WINAPI TranslateAcceleratorA(HWND window, HACCEL accelerators, MSG *message);
extern CCToolTip *ToolTips;

void Windows_Message_Handler()
{
    if (MainWindow == 0) return;
    MSG msg;
    ++unknown_message_count_a52298;
    while (unknown_peek_message_522ed0(&msg, 0, 0, 0, 0)) {
        if (!unknown_get_message_522e90(&msg, 0, 0, 0)) {
            return;
        }
        unknown_message_4919b0(&msg);
        if (ToolTips != 0) {
            ToolTips->Process_Message(&msg);
        }
        bool processed = false;
        for (int index = 0; index < _ModelessDialogs.Count(); index++) {
            if (IsDialogMessageA(_ModelessDialogs[index], &msg)) {
                processed = true;
                break;
            }
        }
        if (processed) continue;
        for (int aindex = 0; aindex < _Accelerators.Count(); aindex++) {
            if (TranslateAcceleratorA((HWND)_Accelerators[aindex].unknown_04, (HACCEL)_Accelerators[aindex].unknown_00, &msg)) {
                processed = true;
                break;
            }
        }
        if (processed) continue;
        if (Message_Intercept_Handler != 0) {
            processed = Message_Intercept_Handler(msg);
        }
        if (processed) continue;
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
