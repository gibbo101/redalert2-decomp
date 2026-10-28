// void Audio_File_Close_Stream() -- 0x00522D50
// Flushes the open stream's file into its queue while it is being read (mode 1), then closes it.
// Placeholders: the globals are named by address until the audio file layer is recovered.
#include "shared/audio_file.hpp"

// @ref __imp__EnterCriticalSection@4=0079a1dc
// @ref __imp__LeaveCriticalSection@4=0079a1e0
// @ref ?unknown_audio_file_lock_a52280@@3UCRITICAL_SECTION@@A=00a52280
// @ref ?Audio_Queue_Stdio@@YIHPAUAudioQueue@@PAXHPAH@Z=00408f50
// @ref ?Audio_Queue_Available@@YIHPAUAudioQueue@@@Z=00409240
// @ref ?FUN_0078439c@@YAHPAX@Z=0078439c
extern int FUN_0078439c(void *file);
extern int FUN_0078395b(void *file);

void Audio_File_Close_Stream()
{
    if (DAT_00a522b0 != 0) {
        EnterCriticalSection(&unknown_audio_file_lock_a52280);
        if (DAT_00a522b0 != 0) {
            EnterCriticalSection(&unknown_audio_file_lock_a52280);
            if (DAT_00a522d0 != 0 && DAT_00a522c4 != 0 && DAT_00a522ac == 1 && DAT_00a522cc != 0) {
                Audio_Queue_Stdio(DAT_00a522cc, DAT_00a522d0, Audio_Queue_Available(DAT_00a522cc), 0);
                FUN_0078439c(DAT_00a522d0);
            }
            LeaveCriticalSection(&unknown_audio_file_lock_a52280);
        }
        DAT_00a522ac = 0;
        if (DAT_00a522d0 != 0) {
            FUN_0078395b(DAT_00a522d0);
            DAT_00a522d0 = 0;
        }
        LeaveCriticalSection(&unknown_audio_file_lock_a52280);
    }
}
