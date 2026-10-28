// void Unknown_007160D0() (0x007160D0): stops the taunt stream.
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968

void __fastcall Unknown_007160D0()
{
    if (unknown_taunt_stream_ad0968 != 0) {
        Audio_Stream_Stop(unknown_taunt_stream_ad0968);
    }
}
