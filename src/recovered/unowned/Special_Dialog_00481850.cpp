// void __fastcall Special_Dialog_00481850() (0x00481850): runs the dialog the player asked for
// (unknown_int_a40d48, Red Alert's SpecialDialog) until none is pending, with the game focus,
// mouse and session timing released around it. Called from the Conquer.CPP game loop.
#include "shared/wol_sink.hpp"    // unknown_a72c68; ahead of house.hpp (after it, rc_ptr<WDTTerritory> COMDATs are emitted)
#include "shared/house.hpp"
#include "shared/mouse.hpp"
#include "shared/event.hpp"
#include "shared/string_table.hpp"
#include "shared/win32_window.hpp"
#include "shared/game_controls_dialog.hpp"
#include "shared/game_options_dialog.hpp"
#include "shared/queue.hpp"
#include "shared/options.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0
// @ref ?Unknown_004DD7D0@@YAXXZ=004dd7d0
// @ref ?Unknown_00634A00@@YIXPAVMouseClass@@@Z=00634a00
// @ref ?Unknown_0063B090@@YIXPAVUnknownIDSource@@@Z=0063b090
// @ref ?Unknown_005DA360@@YIXPAVOptionsClass@@@Z=005da360
// @ref ?Unknown_00672DE0@@YIXPAUUnknownSessionState@@@Z=00672de0
// @ref ?Unknown_0073C230@@YAXXZ=0073c230
// @ref ?OK_Cancel_Message_005A7430@@YIHPBG@Z=005a7430
// @ref ?Run_00688CD0@SoundControlsDialog@@QAEXXZ=00688cd0
// @ref ?unknown_flag_007d88e0@@3_NA=007d88e0
// @ref ?unknown_flag_00866250@@3_NA=00866250
// @ref ?unknown_a72c68@@3HA=00a72c68
// @ref ??_C@_0BD@GDCE@D?3?2Ra2?2Conquer?4CPP?$AA@=007d3350
// @ref ??_C@_0O@FMJJ@TXT_SURRENDER?$AA@=007d3340

// The Sound Controls dialog: Run (0x00688CD0) logs "SoundControls: GameSpeed = %d, ..." and shows
// dialog 0xD6 (0xB8 in one mode); it does not use its receiver.
class SoundControlsDialog {
public:
    void Run_00688CD0();
};
extern bool unknown_flag_007d88e0;      // 0x007D88E0 set when the dialog may open while the player is out
extern bool unknown_flag_00866250;      // 0x00866250 set by the game options dialog's result 5
void Unknown_004DD7D0();                                        // 0x004DD7D0 (a dialog)
void __fastcall Unknown_00634A00(MouseClass *map);              // 0x00634A00 (a dialog)
void __fastcall Unknown_0063B090(UnknownIDSource *scenario);    // 0x0063B090
void __fastcall Unknown_005DA360(OptionsClass *options);        // 0x005DA360 (a dialog)
void __fastcall Unknown_00672DE0(UnknownSessionState *session); // 0x00672DE0
void Unknown_0073C230();                                        // 0x0073C230 (a dialog)
// An OK/Cancel message box (MPLayer.CPP); nonzero on OK (0x005A7430).
int __fastcall OK_Cancel_Message_005A7430(wchar_t const *message);

void __fastcall Special_Dialog_00481850()
{
    if (unknown_int_a40d48 == 0) {
        return;
    }
    if (unknown_game_mode_a3d298 != 0) {
        if (unknown_player_a35db4->unknown_140 || unknown_player_a35db4->unknown_13f || unknown_player_a35db4->unknown_13e
            || (!unknown_flag_007d88e0 && !unknown_player_a35db4->unknown_13d)) {
            unknown_int_a40d48 = 0;
            return;
        }
        if (!unknown_flag_007d88e0) {
            unknown_flag_007d88e0 = true;
        }
    }
    Focus_Loss_0065c040();
    WWMouse->Release_Mouse();
    while (WWMouse->Get_Mouse_State() != 0) {
        WWMouse->Show_Mouse();
    }
    while (unknown_int_a40d48 != 0) {
        switch (unknown_int_a40d48) {
        case 9:
            Unknown_0063B090(unknown_id_source_a3d290);
            if (unknown_int_a40d48 == 9) {
                unknown_int_a40d48 = 0;
            }
            break;
        case 8:
            Unknown_00634A00(&Map);
            if (unknown_int_a40d48 == 8) {
                unknown_int_a40d48 = 0;
            }
            break;
        case 1:
            Unknown_004DD7D0();
            if (unknown_int_a40d48 == 1) {
                unknown_int_a40d48 = 0;
            }
            break;
        case 5:
            GameControlsDialog().Run();
            if (unknown_int_a40d48 == 5) {
                unknown_int_a40d48 = 1;
            }
            break;
        case 6:
            SoundControlsDialog().Run_00688CD0();
            unknown_int_a40d48 = 5;
            break;
        case 4:
            Unknown_005DA360(&Options);
            unknown_int_a40d48 = 5;
            break;
        case 3:
            switch (Run_Game_Options_Dialog()) {
            case 3:
                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 8));
                unknown_flag_007d88e0 = false;
            case 2:
                Queue_Exit();
                break;
            case 4:
                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 8));
                unknown_flag_007d88e0 = false;
                break;
            case 5:
                unknown_flag_00866250 = true;
                break;
            }
            unknown_int_a40d48 = 0;
            break;
        case 2:
            if (unknown_a72c68 != 0) {
                Queue_Exit();
            } else if (!unknown_player_a35db4->unknown_13d && !unknown_player_a35db4->unknown_13f
                       && !unknown_player_a35db4->unknown_140 && !unknown_player_a35db4->unknown_13e) {
                if (OK_Cancel_Message_005A7430(StringTable::Load_String("TXT_SURRENDER", 0, "D:\\Ra2\\Conquer.CPP", 487))) {
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 8));
                    unknown_flag_007d88e0 = false;
                }
            }
            unknown_int_a40d48 = 0;
            break;
        case 7:
            Unknown_0073C230();
            unknown_int_a40d48 = 0;
            break;
        }
    }
    UpdateWindow(MainWindow);
    if (unknown_id_source_a3d290->unknown_2306) {
        WWMouse->Hide_Mouse();
    }
    WWMouse->Capture_Mouse();
    Unknown_00672DE0(&unknown_session_a3d298);
    Focus_Restore_0065c140();
}
