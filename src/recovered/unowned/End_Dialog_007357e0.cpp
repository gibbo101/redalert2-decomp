// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// bool __fastcall End_Dialog_007357e0(HWND dialog, int result) (0x007357E0)
// Adopted from ra2-decomp WS_Destroy_Dialog (YR 0x007757E0).
// Closes dialog (the top dialog when null) and every dialog above it on the
// stack, makes the one below current and records result; false when dialog
// is not on the stack.
#include "shared/win_util.hpp"
#include "shared/win32_window.hpp"

bool __fastcall End_Dialog_007357e0(HWND dialog, int result)
{
    int index;
    int i;
    if (dialog == 0 && DialogStackCount != 0) {
        dialog = DialogStack[DialogStackCount - 1].Window;
    }
    if (dialog == 0) {
        return false;
    }

    index = -1;
    for (i = 0; i < DialogStackCount; i++) {
        if (DialogStack[i].Window == dialog) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false;
    }

    OwnerDraw::unknown_5e5fc0(dialog);

    for (i = DialogStackCount - 1; i >= index; i--) {
        Unknown_005B6060(DialogStack[i].Window);
        DestroyWindow(DialogStack[i].Window);
        unknown_int_a40d34--;
    }

    DialogStackCount = index;

    if (DialogStackCount != 0) {
        HWND window = DialogStack[DialogStackCount - 1].Window;
        int resource = DialogStack[DialogStackCount - 1].Resource;
        SetForegroundWindow(window);
        InvalidateRect(window, 0, FALSE);
        UpdateWindow(window);
        CurrentDialog = window;
        CurrentDialogResource = resource;
        SetFocus(window);
        SendMessageA(CurrentDialog, 0x4B0, 0, 0);   // ra2-decomp OD_REFOCUS
    } else {
        CurrentDialog = 0;
        CurrentDialogResource = 0;
        SetFocus(MainWindow);
    }
    unknown_dialog_result_b25ddc = result;

    return true;
}
