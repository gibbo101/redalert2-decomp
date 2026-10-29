// void __fastcall Main_Options_Apply(HWND window) (0x00542280)
// Reads the Options dialog's controls into Options: detail (0x52B), difficulty (0x50F), the unit action
// lines, show hidden and tool tip boxes (0x601, 0x604, 0x602), scroll rate (0x52A) and the score, sound and
// voice sliders (0x52F, 0x532, 0x536). The shell twin of GameControlsDialog::Apply_Settings (0x004CFA00).
#include "shared/main_opt.hpp"
#include "shared/theme.hpp"
#include "shared/event.hpp"
#include "shared/house.hpp"
#include "shared/techno.hpp"
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049E570@DisplayClass@@QAEXXZ=0049e570
// @ref ?unknown_6d79c0@TechnoClass@@SIXA_N@Z=006d79c0
// @ref ?Set_Score_Volume@OptionsClass@@QAEXM_N@Z=005d8980
// @ref ?Set_Sound_Volume@OptionsClass@@QAEXM_N@Z=005d89f0
// @ref ?Set_Voice_Volume@OptionsClass@@QAEXM_N@Z=005d8a70
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
// @ref ?Stop@ThemeClass@@QAEX_N@Z=006e81a0
// @ref __real@8@3ffbccccccccccccd000=0079c570
// @ref __real@4@00000000000000000000=0079a738

void __fastcall Main_Options_Apply(HWND window)
{
    HWND control = GetDlgItem(window, 0x52B);
    if (control) {
        int detail = SendMessageA(control, 0x400, 0, 0) ? 2 : 0;
        if (Options.DetailLevel != detail) {
            Options.DetailLevel = detail;
            Map.Unknown_0049E570();
        }
    }
    control = GetDlgItem(window, 0x50F);
    if (control) {
        Options.Difficulty = SendMessageA(control, 0x400, 0, 0);
    }
    control = GetDlgItem(window, 0x601);
    if (control) {
        Options.UnitActionLines = SendMessageA(control, 0xF0, 0, 0) == 1;
        TechnoClass::unknown_6d79c0(Options.UnitActionLines);
    }
    control = GetDlgItem(window, 0x604);
    if (control) {
        Options.ShowHidden = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    control = GetDlgItem(window, 0x602);
    if (control) {
        Options.ToolTips = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    control = GetDlgItem(window, 0x52A);
    if (control) {
        Options.ScrollRate = 6 - SendMessageA(control, 0x400, 0, 0);
    }
    control = GetDlgItem(window, 0x52F);
    if (control) {
        Options.Set_Score_Volume((float)(SendMessageA(control, 0x400, 0, 0) * 0.1), false);
        if (Options.ScoreVolume == 0.0f) {
            Theme.Queue_Song(Theme.Score == -1 ? Theme.Pending : Theme.Score);
            Theme.Stop(false);
        }
    }
    control = GetDlgItem(window, 0x532);
    if (control) {
        Options.Set_Sound_Volume((float)(SendMessageA(control, 0x400, 0, 0) * 0.1), false);
    }
    control = GetDlgItem(window, 0x536);
    if (control) {
        Options.Set_Voice_Volume((float)(SendMessageA(control, 0x400, 0, 0) * 0.1), false);
    }
}
