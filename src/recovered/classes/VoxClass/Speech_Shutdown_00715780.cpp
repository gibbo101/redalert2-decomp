// void Speech_Shutdown() (0x00715780): clears the speech queue, then stops and
// destroys the stream (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?Speech_Clear@@YIXXZ=007157b0

void Speech_Shutdown()
{
    Speech_Clear();
    if (unknown_vox_stream_ad095c != 0) {
        Audio_Stream_Stop(unknown_vox_stream_ad095c);
        Audio_Stream_Destroy(unknown_vox_stream_ad095c);
        unknown_vox_stream_ad095c = 0;
    }
}
