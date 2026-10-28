// void Taunt_Shutdown() (0x00715F80): stops and destroys the taunt stream
// (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968

void Taunt_Shutdown()
{
    if (unknown_taunt_stream_ad0968 != 0) {
        Audio_Stream_Stop(unknown_taunt_stream_ad0968);
        Audio_Stream_Destroy(unknown_taunt_stream_ad0968);
        unknown_taunt_stream_ad0968 = 0;
    }
}
