// int __fastcall Audio_File_Open_Stream(char const *name) -- 0x00522CB0
// Opens the stream's file (mode string 0x007DDC6C), and marks the stream as read when the first queue accepts data.
// Placeholders: the globals are named by address until the audio file layer is recovered.
#include "shared/audio_file.hpp"

// @ref __imp__EnterCriticalSection@4=0079a1dc
// @ref __imp__LeaveCriticalSection@4=0079a1e0
// @ref ?unknown_audio_file_lock_a52280@@3UCRITICAL_SECTION@@A=00a52280
// @ref ?Audio_Queue_Stdio@@YIHPAUAudioQueue@@PAXHPAH@Z=00408f50
// @ref ?Audio_Queue_Available@@YIHPAUAudioQueue@@@Z=00409240
// @ref ?FUN_00783a45@@YAPAXPBD0@Z=00783a45
extern void *FUN_00783a45(char const *name, char const *mode);
extern "C" char const DAT_007ddc6c[];

int __fastcall Audio_File_Open_Stream(char const *name)
{
    if (DAT_00a522b0 != 0 && DAT_00a522d0 == 0) {
        EnterCriticalSection(&unknown_audio_file_lock_a52280);
        DAT_00a522d0 = FUN_00783a45(name, DAT_007ddc6c);
        DAT_00a522d4 = 0;
        if (DAT_00a522d0 != 0) {
            DAT_00a522ac = 2;
            if (Audio_Queue_Stdio(DAT_00a522c8, DAT_00a522d0, Audio_Queue_Available(DAT_00a522c8), 0) != 1) {
                DAT_00a522d4 = 1;
            }
        }
        LeaveCriticalSection(&unknown_audio_file_lock_a52280);
        return DAT_00a522d0 != 0;
    }
    return false;
}
