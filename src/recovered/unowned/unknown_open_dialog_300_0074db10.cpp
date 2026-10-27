// void unknown_open_dialog_300() -- 0x0074DB10
// Purpose: creates dialog 300 (0x00735700, with the main window, the
// instance at 0x00B26180 and the procedure 0x0074DB40) and, when it opens,
// runs 0x005FF7E0 on it with 300.
// Assumptions: the helpers' meanings are hypotheses (WOL area).
#include "shared/win32_api.hpp"
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_instance_b26180@@3PAXA=00b26180
// @ref ?unknown_create_dialog_735700@@YIPAXPAXHPAUHWND__@@P6GJ1IIJ@ZJ@Z=00735700
// @ref ?unknown_dialog_proc_74db40@@YGJPAUHWND__@@IIJ@Z=0074db40
// @ref ?unknown_show_dialog_5ff7e0@@YIXPAXH@Z=005ff7e0

extern HWND MainWindow;                 // 0x00B263D8
extern void *unknown_instance_b26180;
typedef long (__stdcall *UnknownDialogProc)(HWND window, unsigned message, unsigned wparam, long lparam);
long __stdcall unknown_dialog_proc_74db40(HWND window, unsigned message, unsigned wparam, long lparam);
void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent, UnknownDialogProc procedure, long arg);
void __fastcall unknown_show_dialog_5ff7e0(void *dialog, int id);

void unknown_open_dialog_300()
{
    void *dialog = unknown_create_dialog_735700(unknown_instance_b26180, 300, MainWindow, unknown_dialog_proc_74db40, 0);
    if (dialog != 0) {
        unknown_show_dialog_5ff7e0(dialog, 300);
    }
}
