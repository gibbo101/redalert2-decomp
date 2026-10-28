// void Taunt_Resume() (0x007168E0): resumes the taunt stream.
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968

void Taunt_Resume()
{
    if (unknown_taunt_stream_ad0968 != 0) {
        Audio_Stream_Resume(unknown_taunt_stream_ad0968);
    }
}
