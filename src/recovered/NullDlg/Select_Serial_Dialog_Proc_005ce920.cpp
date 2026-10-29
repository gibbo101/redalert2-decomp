// int __stdcall Select_Serial_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x005CE920)
// The shared handler first; 0x497 initialises the buttons, WM_COMMAND stores
// IDCANCEL or a button 0x652-0x655 through the DWL_USER pointer.
// The unit's first include of shared/vector_class.hpp is here: Destroy_Null_Connection
// needs the accessors and the DynamicVectorClass Delete members inline.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/null_dlg.hpp"
#include "shared/ms_message_box.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Select_Serial_Dialog_Init@@YIXPAUHWND__@@@Z=005ce990

int __stdcall Select_Serial_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497:
            Select_Serial_Dialog_Init(window);
            return 0;
        case 0x111: {
            int *result = (int *)GetWindowLongA(window, 8);
            if (wparam == 2 || (wparam > 0x651 && wparam <= 0x655)) {
                *result = wparam;
            }
            break;
        }
    }
    return 0;
}
