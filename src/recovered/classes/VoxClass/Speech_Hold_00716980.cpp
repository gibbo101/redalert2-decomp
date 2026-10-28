// void Speech_Hold() (0x00716980): pauses the speech stream and blocks new
// speeches from starting (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?unknown_countdown_ad08c8@@3HC=00ad08c8

void Speech_Hold()
{
    if (unknown_vox_stream_ad095c != 0) {
        Audio_Stream_Pause(unknown_vox_stream_ad095c);
    }
    unknown_countdown_ad08c8++;
}
