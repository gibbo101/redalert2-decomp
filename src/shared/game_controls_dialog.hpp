// The Game Controls dialog (GameCtrl unit 0x004CF900-0x004CFFFF; the file name is not evidenced).
//
// Run (0x004CF920) logs "GameControls: GameSpeed=%d, ScrollRate=%d, DetailLevel=%d" before and after,
// shows dialog 0xBBB (0xF5 in the shell), pumps messages until a button sets the result held in
// DWL_USER (index 8; -1 while waiting, 1 OK, 2 cancel), and on OK applies the sliders and saves the
// options. Apply_Settings (0x004CFA00) reads the sliders (0x529 speed, 0x52A scroll rate, 0x52B detail)
// and check boxes (0x601 unit action lines, 0x604 show hidden, 0x602 tool tips) back into Options.
#ifndef RA2_SHARED_GAME_CONTROLS_DIALOG_HPP
#define RA2_SHARED_GAME_CONTROLS_DIALOG_HPP

#include "shared/win32_api.hpp"

class GameControlsDialog {
public:
    void Run();                 // 0x004CF920
    void Apply_Settings();      // 0x004CFA00

    HWND Window;                // +0x00
};

// The dialog procedure (0x004CFC00).
int __stdcall Game_Controls_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

// Label keys by slider position (the slider text at 0x671 / 0x672 / 0x673 / 0x670 shows the label).
extern char const *Game_Speed_Labels[7];        // 0x007D83C0 TXT_SLOWEST .. TXT_FASTEST
extern char const *Scroll_Rate_Labels[7];       // 0x007D83DC the same seven labels
extern char const *Detail_Level_Labels[3];      // 0x007D83F8 TXT_LOW, TXT_MEDIUM, TXT_HIGH
extern char const *Difficulty_Labels[3];        // 0x007D8404 TXT_EASY, TXT_NORMAL, TXT_HARD

#endif
