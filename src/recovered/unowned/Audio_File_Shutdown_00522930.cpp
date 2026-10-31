// void Audio_File_Shutdown() -- 0x00522930
// Flushes the stream file into its queue while it is being read, closes it (Audio_File_Close_Stream's body),
// frees the block 0x00A522B4, stops the file thread (waits up to five seconds), releases the two queues and the
// ring, and deletes the locks. Placeholders: the globals are named by address until the layer is recovered.
#include "shared/audio_file.hpp"

// @ref __imp__EnterCriticalSection@4=0079a1dc
// @ref __imp__LeaveCriticalSection@4=0079a1e0
// @ref __imp__DeleteCriticalSection@4=0079a1d8
// @ref __imp__Sleep@4=0079a1e4
// @ref __imp__WaitForSingleObject@8=0079a1d0
// @ref __imp__CloseHandle@4=0079a1d4
// @ref ?unknown_audio_file_lock_a52280@@3UCRITICAL_SECTION@@A=00a52280
// @ref ?unknown_audio_file_lock_a52268@@3UCRITICAL_SECTION@@A=00a52268
// @ref ?Audio_Queue_Stdio@@YIHPAUAudioQueue@@PAXHPAH@Z=00408f50
// @ref ?Audio_Queue_Available@@YIHPAUAudioQueue@@@Z=00409240
// @ref ?FUN_0078439c@@YAHPAX@Z=0078439c
// @ref ?FUN_0078395b@@YAHPAX@Z=0078395b
// @ref ??3@YAXPAX@Z=00781d3b
extern int FUN_0078439c(void *file);
extern int FUN_0078395b(void *file);

void Audio_File_Shutdown()
{
    if (DAT_00a522b0 != 0) {
        EnterCriticalSection(&unknown_audio_file_lock_a52280);
        if (DAT_00a522d0 != 0 && DAT_00a522c4 != 0 && DAT_00a522ac == 1 && DAT_00a522cc != 0) {
            Audio_Queue_Stdio(DAT_00a522cc, DAT_00a522d0, Audio_Queue_Available(DAT_00a522cc), 0);
            FUN_0078439c(DAT_00a522d0);
        }
        LeaveCriticalSection(&unknown_audio_file_lock_a52280);
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
    if (DAT_00a522b4 != 0) {
        operator delete(DAT_00a522b4);
        DAT_00a522b4 = 0;
    }
    DAT_00a522b8 = 0;
    if (DAT_00a522c0 != 0) {
        DAT_00a521e0 = 1;
        while (DAT_00a521e8 == 0) {
            Sleep(0);
        }
        WaitForSingleObject(DAT_00a52260, 5000);
        CloseHandle(DAT_00a52260);
        DAT_00a522c0 = 0;
    }
    if (DAT_00a522c8 != 0) {
        Audio_Queue_Release(DAT_00a522c8);
        DAT_00a522c8 = 0;
    }
    if (DAT_00a522cc != 0) {
        Audio_Queue_Release(DAT_00a522cc);
        DAT_00a522cc = 0;
    }
    if (DAT_00a522c4 != 0) {
        Audio_Ring_Destroy((AudioStream *)DAT_00a522c4);
        DAT_00a522c4 = 0;
    }
    if (DAT_00a522bc != 0) {
        DeleteCriticalSection(&unknown_audio_file_lock_a52280);
        DeleteCriticalSection(&unknown_audio_file_lock_a52268);
        DAT_00a522bc = 0;
    }
    DAT_00a522b0 = 0;
}
