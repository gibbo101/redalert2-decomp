// void Audio_Update() -- 0x00406EA0
// Purpose: the audio part of the game's main loop: when more than 0x21 ticks
// have passed since the last time, updates the events and the other layers
// that need it. Does not reenter.
#include "shared/audio.hpp"

struct unknown_00a35d78_type;
extern unknown_00a35d78_type unknown_00a35d78;      // 0x00A35D78
void unknown_00714330();                            // 0x00714330
void unknown_00715ba0();                            // 0x00715BA0
void __fastcall unknown_006e7cd0(unknown_00a35d78_type *object);        // 0x006E7CD0
void unknown_007717c0();                            // 0x007717C0

void Audio_Update()
{
    if (Audio_Update_Busy == 0 && Audio_Main_Device != 0) {
        Audio_Update_Busy = 1;
        __int64 now = Audio_Now();
        if ((unsigned __int64)(now - Audio_Update_Last) > 0x21) {
            Audio_Events_Update();
            unknown_00714330();
            unknown_00715ba0();
            unknown_006e7cd0(&unknown_00a35d78);
            unknown_007717c0();
            Audio_Update_Last = now;
        }
        Audio_Update_Busy = 0;
    }
}
