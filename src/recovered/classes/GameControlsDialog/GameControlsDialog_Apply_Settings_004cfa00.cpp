// void GameControlsDialog::Apply_Settings() (0x004CFA00)
// Reads the dialog's sliders and check boxes into Options. A changed game speed
// is queued as event 0xD (kept for later when the queue is full) while playing
// a session game (otherwise it is applied directly); a changed detail level
// resets the map's cells; the tool tip box enables the tool tips. Outside a game
// (unknown_flag_a40958 clear) the difficulty slider 0x50F is read as well.
#include "shared/game_controls_dialog.hpp"
#include "shared/options.hpp"
#include "shared/event.hpp"
#include "shared/house.hpp"
#include "shared/techno.hpp"
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tool_tip.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ??0EventClass@@QAE@HHK@Z=004b6030
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049E570@DisplayClass@@QAEXXZ=0049e570
// @ref ?unknown_6d79c0@TechnoClass@@SIXA_N@Z=006d79c0
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Enable@ToolTipManager@@QAEX_N@Z=006eb480

void GameControlsDialog::Apply_Settings()
{
    HWND control = GetDlgItem(Window, 0x529);
    if (control) {
        int speed = 6 - SendMessageA(control, 0x400, 0, 0);
        if (Options.GameSpeed != speed) {
            if (unknown_flag_a40958 == 1 && unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xD, speed));
            } else {
                Options.GameSpeed = speed;
            }
        }
    }
    control = GetDlgItem(Window, 0x52A);
    if (control) {
        Options.ScrollRate = 6 - SendMessageA(control, 0x400, 0, 0);
    }
    control = GetDlgItem(Window, 0x52B);
    if (control) {
        int detail = SendMessageA(control, 0x400, 0, 0);
        if (Options.DetailLevel != detail) {
            Options.DetailLevel = detail;
            Map.Unknown_0049E570();
        }
    }
    control = GetDlgItem(Window, 0x601);
    if (control) {
        Options.UnitActionLines = SendMessageA(control, 0xF0, 0, 0) == 1;
        TechnoClass::unknown_6d79c0(Options.UnitActionLines);
    }
    control = GetDlgItem(Window, 0x604);
    if (control) {
        Options.ShowHidden = SendMessageA(control, 0xF0, 0, 0) == 1;
    }
    control = GetDlgItem(Window, 0x602);
    if (control) {
        Options.ToolTips = SendMessageA(control, 0xF0, 0, 0) == 1;
        if (ToolTips && unknown_flag_a40958 == 1) {
            ToolTips->Enable(Options.ToolTips);
        }
    }
    if (!unknown_flag_a40958) {
        control = GetDlgItem(Window, 0x50F);
        if (control) {
            Options.Difficulty = SendMessageA(control, 0x400, 0, 0);
        }
    }
}
