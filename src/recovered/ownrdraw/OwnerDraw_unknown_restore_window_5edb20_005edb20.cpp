// BOOL __fastcall unknown_restore_window_5edb20(HWND window) (0x005EDB20)
// Undoes the owner-draw subclassing of a window and its children (EnumChildWindows with 0x005EDD30): drops its
// window procedure, registry record and 0x00A73400 entry, frees its GWL_USERDATA block and removes it from the
// modeless dialogs (0x00522B80). No callers in the image. Name hypothesis.
// @ref ?unknown_restore_child_5edd30@OwnerDraw@@YGHPAUHWND__@@J@Z=005edd30
// @ref ?Remove@UnknownControlIndex@OwnerDraw@@QAE_NABIAAUUnknownControlRecord@2@@Z=00601c50
// @ref ?Unknown_Remove_Modeless_Dialog_00522b80@@YIXPAUHWND__@@@Z=00522b80
// @ref ?unknown_window_table_a73400@@3V?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@A=00a73400
// @ref ?Shrink_Table@?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@QAEXXZ=00602730
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

void __fastcall Unknown_Remove_Modeless_Dialog_00522b80(HWND__ *dialog);
// unknown_window_table_a73400: defined at 0x005DEB90 in this unit (VC6 refuses a second extern declaration).

namespace OwnerDraw {

// ~UnknownControlRecord: inline, defined beside the control registry's definition (0x005DED60's source).

// The GWL_USERDATA block of a subclassed window (layout unknown). Hypothesis: a class with an inline empty
// destructor; that `delete` is a later /Ob2 inline site, so the 0xA73400 remove calls Shrink_Table 0x602730.
struct UnknownWindowData_5edb20 {
    ~UnknownWindowData_5edb20() {}
};

BOOL __stdcall unknown_restore_child_5edd30(HWND window, LPARAM lparam);

BOOL __fastcall unknown_restore_window_5edb20(HWND window)
{
    EnumChildWindows(window, unknown_restore_child_5edd30, 0);
    HWND key = window;
    {
        WNDPROC proc;
        unknown_window_procs_a73688.Remove(key, proc);
    }
    {
        UnknownControlRecord record;
        unknown_registry_a73640.Remove((unsigned int const &)key, record);
    }
    WNDPROC old_proc;
    unknown_window_table_a73400.Remove_Entry(key, &old_proc);
    UnknownWindowData_5edb20 *data = (UnknownWindowData_5edb20 *)GetWindowLongA(key, -21);
    if (data != 0) {
        delete data;
    }
    SetWindowLongA(key, -21, 0);
    Unknown_Remove_Modeless_Dialog_00522b80(key);
    return 1;
}

}
