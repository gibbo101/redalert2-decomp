// Build the debug text dialog and size its 80-by-25 character client area.
#include "shared/mono_window.hpp"

void __fastcall Mono_Window_Create()
{
    unknown_mono_window_a70f10 = CreateDialogParamA(unknown_mono_instance_a70f00, MAKEINTRESOURCEA(248), unknown_mono_parent_a70f04, Mono_Dialog_Proc_0059dce0, 0);
    Unknown_Add_Modeless_Dialog_00522b20(unknown_mono_window_a70f10);
    HDC dc = GetDC(unknown_mono_window_a70f10);
    LOGFONTA font;
    font.lfHeight = -MulDiv(8, GetDeviceCaps(dc, 90), 72);
    font.lfWidth = 0;
    font.lfEscapement = 0;
    font.lfOrientation = 0;
    font.lfWeight = 0;
    font.lfItalic = 0;
    font.lfUnderline = 0;
    font.lfStrikeOut = 0;
    font.lfCharSet = 0;
    font.lfOutPrecision = 0;
    font.lfClipPrecision = 0;
    font.lfQuality = 0;
    font.lfPitchAndFamily = 0;
    strcpy(font.lfFaceName, "Courier");
    unknown_mono_font_a70f14 = CreateFontIndirectA(&font);
    HGDIOBJ previous = SelectObject(dc, unknown_mono_font_a70f14);
    GetTextMetricsA(dc, &unknown_mono_metrics_a70ea0);
    SelectObject(dc, previous);
    unknown_mono_back_color_a70e00 = GetSysColor(15);
    unknown_mono_text_color_a70de8 = GetSysColor(8);
    RECT frame;
    frame.left = 0;
    frame.top = 0;
    frame.right = unknown_mono_metrics_a70ea0.tmMaxCharWidth * 79 + 20;
    frame.bottom = (unknown_mono_metrics_a70ea0.tmExternalLeading + unknown_mono_metrics_a70ea0.tmHeight) * 25 + 20;
    AdjustWindowRect(&frame, 0x00c00000, 0);
    RECT parent;
    GetWindowRect(unknown_mono_parent_a70f04, &parent);
    MoveWindow(unknown_mono_window_a70f10, parent.right + 5, 0, frame.right - frame.left, frame.bottom - frame.top, 1);
    ShowWindow(unknown_mono_window_a70f10, 0);
    SetFocus(unknown_mono_parent_a70f04);
    ReleaseDC(unknown_mono_window_a70f10, dc);
}

// @ref ??_C@_07LMLG@Courier?$AA@=007a64bc
// @ref ?Mono_Dialog_Proc_0059dce0@@YGHPAUHWND__@@IIJ@Z=0059dce0
// @ref ?Unknown_Add_Modeless_Dialog_00522b20@@YIXPAUHWND__@@@Z=00522b20
// @ref ?unknown_mono_metrics_a70ea0@@3UTEXTMETRICA@@A=00a70ea0

// @ref ?Mono_Window_Create@@YIXXZ=0059db30
