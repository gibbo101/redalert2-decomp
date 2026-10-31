// The Sound Controls dialog (SoundDlg.cpp, 0x00688CD0-; TS SoundControlsClass in sounddlg.cpp).
// The class name is the one the accepted caller Special_Dialog 0x00481850 binds; TS calls it
// SoundControlsClass with Dialog() and Sound_Option_Dialog_Func.
#ifndef RA2_SHARED_SOUND_CONTROLS_HPP
#define RA2_SHARED_SOUND_CONTROLS_HPP
#include "shared/win32_api.hpp"

class SoundControlsDialog {
public:
    // Runs the dialog (0xB8 in a game, 0xD6 otherwise) until it is dismissed (0x00688CD0; TS Dialog).
    void Run_00688CD0();
    // Its dialog procedure (0x00688DA0; TS Sound_Option_Dialog_Func).
    static int __stdcall Sound_Option_Dialog_Func(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

    static bool DialogInitialized;      // 0x00ABCFB0
};
#endif
