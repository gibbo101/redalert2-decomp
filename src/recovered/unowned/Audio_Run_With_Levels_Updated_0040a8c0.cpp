// void __fastcall Audio_Run_With_Levels_Updated(AudioDevice *device) -- 0x0040A8C0
// Purpose: with a device, updates the eight global level sets, runs the
// device's update (0x00403810) and clears the sets' changed flags, in the
// original's order.
// @ref ?Audio_Global_Levels@@3PAPAUAudioStateSet@@A=0083144c
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Clear_Changed@AudioLevelSet@@QAEXXZ=00401170
// @ref ?Update@AudioLevelSet@@QAEXXZ=00401080
// @ref ?Run_Update@AudioDevice@@QAEXXZ=00403810
#include "shared/audio.hpp"

void __fastcall Audio_Run_With_Levels_Updated(AudioDevice *device)
{
    if (device != 0) {
        Audio_Global_Levels[2]->Update();
        Audio_Global_Levels[3]->Update();
        Audio_Global_Levels[1]->Update();
        Audio_Global_Levels[0]->Update();
        Audio_Global_Levels[6]->Update();
        Audio_Global_Levels[7]->Update();
        Audio_Global_Levels[5]->Update();
        Audio_Global_Levels[4]->Update();
        device->Run_Update();
        Audio_Global_Levels[3]->Clear_Changed();
        Audio_Global_Levels[2]->Clear_Changed();
        Audio_Global_Levels[1]->Clear_Changed();
        Audio_Global_Levels[0]->Clear_Changed();
        Audio_Global_Levels[6]->Clear_Changed();
        Audio_Global_Levels[7]->Clear_Changed();
        Audio_Global_Levels[5]->Clear_Changed();
        Audio_Global_Levels[4]->Clear_Changed();
    }
}
