// void Speech_Stop(bool clear) (0x00715DE0): stops the speech playing (its
// VoxClass idle again) and, with clear set, drops the waiting speeches too
// (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_playing_ad0954@@3PAVVoxClass@@A=00ad0954
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?Audio_Stream_Stop@@YIXPAUAudioStreamPlayer@@@Z=00407e60
// @ref ?Speech_Clear@@YAXXZ=007157b0

void __fastcall Speech_Stop(bool clear)
{
    if (unknown_vox_playing_ad0954 != 0) {
        unknown_vox_playing_ad0954->State = 2;
        unknown_vox_playing_ad0954 = 0;
    }
    if (unknown_vox_stream_ad095c != 0) {
        Audio_Stream_Stop(unknown_vox_stream_ad095c);
    }
    if (clear) {
        Speech_Clear();
    }
}
