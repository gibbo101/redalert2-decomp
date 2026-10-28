// void Taunt_Pause() (0x007168D0): pauses the taunt stream.
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968

void Taunt_Pause()
{
    if (unknown_taunt_stream_ad0968 != 0) {
        Audio_Stream_Pause(unknown_taunt_stream_ad0968);
    }
}
