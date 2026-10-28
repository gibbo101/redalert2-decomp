// void Speech_Reset() (0x007169A0): stops the speech, drops the waiting ones
// and clears both speech blocks (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_countdown_ad08c8@@3HC=00ad08c8
// @ref ?unknown_vox_ad0878@@3HC=00ad0878

void Speech_Reset()
{
    Speech_Stop(true);
    unknown_countdown_ad08c8 = 0;
    unknown_vox_ad0878 = 0;
}
