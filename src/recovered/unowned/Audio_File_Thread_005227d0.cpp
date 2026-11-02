// DWORD WINAPI Audio_File_Thread(void *data) -- 0x005227D0
// The file thread (data: the AudioFileThread state 0x00A521E0): until asked to stop, records a timing tick,
// then under the file lock tops the read queue up from the stream file while less than half the ring is
// buffered (mode 2; a short read sets 0x00A522D4) or flushes half the ring from the write queue into the
// file while the ring is more than half full (mode 1), and sleeps for the period.
#include "shared/audio_file.hpp"
extern int FUN_0078439c(void *file);
// @ref ?FUN_0078439c@@YAHPAX@Z=0078439c
// @ref ?unknown_audio_file_lock_a52280@@3UCRITICAL_SECTION@@A=00a52280

DWORD WINAPI Audio_File_Thread(void *data)
{
    AudioFileThread *thread = (AudioFileThread *)data;
    thread->Running = 1;
    thread->Stopped = 0;
    while (!thread->Stop) {
        thread->Timing.Tick(Audio_Now());
        AudioStream *ring = (AudioStream *)DAT_00a522c4;
        if (DAT_00a522c4 != 0 && DAT_00a522ac != 0 && DAT_00a522d0 != 0) {
            EnterCriticalSection(&unknown_audio_file_lock_a52280);
            if (DAT_00a522ac == 2 && (unsigned)Audio_Ring_Drain_Available(ring) < (unsigned)Audio_Ring_Size(ring) >> 1) {
                if (DAT_00a522c8 != 0) {
                    int done;
                    if (Audio_Queue_Stdio(DAT_00a522c8, DAT_00a522d0, Audio_Ring_Fill_Available(ring), &done) != 1) {
                        DAT_00a522d4 = 1;
                    }
                }
            } else if (DAT_00a522ac == 1 && (unsigned)Audio_Ring_Fill_Available(ring) < (unsigned)Audio_Ring_Size(ring) >> 1
                       && DAT_00a522cc != 0) {
                Audio_Queue_Stdio(DAT_00a522cc, DAT_00a522d0, (unsigned)Audio_Ring_Size(ring) >> 1, 0);
                FUN_0078439c(DAT_00a522d0);
            }
            LeaveCriticalSection(&unknown_audio_file_lock_a52280);
        }
        Sleep((DWORD)thread->Period);
        thread->Passes++;
    }
    thread->Stopped = 1;
    return 0;
}
