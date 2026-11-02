// unsigned long __cdecl Timer_Callback_Audio_Handler(VQAHandle *vqa) (0x00411420): the movie clock from the audio play
// position (the static Get_Playback_Position expands inline); the paused clock while paused.
// @ref __imp__EnterCriticalSection@4=0079a1dc
// @ref __imp__LeaveCriticalSection@4=0079a1e0
// @ref __imp__InitializeCriticalSection@4=0079a1e8
// @ref __imp__DeleteCriticalSection@4=0079a1d8
// @ref __imp__InterlockedIncrement@4=0079a1bc
// @ref __imp__InterlockedDecrement@4=0079a1c0
// @ref __imp__GetCurrentThreadId@0=0079a1c4
// @ref __imp__timeKillEvent@4=0079a51c
// @ref __imp__timeEndPeriod@4=0079a520
// @ref __imp__timeSetEvent@20=0079a528
// @ref __imp__timeBeginPeriod@4=0079a52c
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_ticks_004d0090@@YAKXZ=004d0090
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?unknown_directsound_40a6c0@@YAPAXXZ=0040a6c0
// @ref ?Audio_DS_Volume_Attenuation@@YIJH@Z=0040a820
// @ref ?unknown_volume_a40b48@@3MA=00a40b48
// @ref ?_handles@@3PAUAhandle@@A=00839d90
// @ref ?_AHandleCallbackFunc1@@3P6AJPAUVQAHandle@@@ZA=00839d84
// @ref ?_AHandleCallbackFunc2@@3P6AJPAUVQAHandle@@PAX@ZA=00839d88
// @ref ??_C@_0BF@NEEF@Ahandle?3?5Paused?5?$CFld?6?$AA@=007ce2f8
// @ref ??_C@_0BK@FKKL@Ahandle?3?5PauseAdjust?5?$CFld?6?$AA@=007ce310
// @ref ??_C@_0BM@HEDI@VQ?5audio?5handler?5closed?5OK?6?$AA@=007ce32c
// @ref ??_C@_0CG@DAHL@Deleting?5the?5critical?5section?5ob@=007ce348
// @ref ??_C@_0BH@PFLJ@Calling?5timeEndPeriod?6?$AA@=007ce370
// @ref ??_C@_0BH@ODEJ@Calling?5timeKillEvent?6?$AA@=007ce388
// @ref ??_C@_0BE@DLFF@Stop_Audio_Handler?6?$AA@=007ce3a0
// @ref ??_C@_0BK@FGKB@Closing?5VQ?5audio?5handler?6?$AA@=007ce3b4
// @ref ??_C@_0BM@NCNN@VQ?5audio?5handler?5opened?5OK?6?$AA@=007ce3d0
// @ref ??_C@_0CA@COBC@Creating?5VQ?5audio?5timer?5thread?6?$AA@=007ce3ec
// @ref ??_C@_0BJ@HECC@Calling?5timeBeginPeriod?6?$AA@=007ce40c
// @ref ??_C@_0EH@IGGP@Ahandle?5detected?5emulated?5sound?5@=007ce428
// @ref ??_C@_0BL@MFKE@Current?5thread?5ID?5is?5?$CF08x?6?$AA@=007ce470
// @ref ??_C@_0BK@DOOH@Opening?5VQ?5audio?5handler?6?$AA@=007ce48c
// @ref ?Open_Audio_Handler@@YAJPAUVQAHandleP@@PAUAhandleInitParams@@J@Z=004118a0
// @ref ?Close_Audio_Handler@@YAJPAUVQAHandleP@@@Z=00411a60
// @ref ?Start_Audio_Handler@@YAJPAUVQAHandleP@@@Z=00411b70
// @ref ?Load_Audio_Handler@@YAJPAUVQAHandleP@@PAXJ@Z=00411d80
// @ref ?AudioCallback@@YGXIIKKK@Z=00412120
// @ref ?Simple_Timer_Callback_Audio_Handler@@YAKPAUVQAHandle@@@Z=004122c0
#include "shared/ahandle.hpp"

static unsigned long Get_Playback_Position(VQAHandle *vqa, Ahandle *audio, VQAConfig *config)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;

    unsigned long s = audio->SecondaryBufferSize;

    unsigned long dma_diff;
    unsigned long totalbytes;
    DWORD play_cursor;
    DWORD write_cursor;

    EnterCriticalSection(&audio->CriticalSection);

    long r = vqap->RepeatedBuffers;
    long l = audio->LastChunkPosition;
    long m = audio->ChunksMovedToAudioBuffer;

    totalbytes = config->HMIBufSize * m;

    if (audio->SecondaryBufferPtr &&
        audio->SecondaryBufferPtr->GetCurrentPosition(&play_cursor, &write_cursor) == 0) {
        if (l) {
            totalbytes += play_cursor;
        } else {
            if (play_cursor >= (s / 2)) {
                totalbytes += play_cursor - (s / 2);
            } else {
                if (totalbytes > 0) {
                    totalbytes += play_cursor + (s / 2);
                }
            }
        }
    }

    LeaveCriticalSection(&audio->CriticalSection);

    dma_diff = totalbytes - config->HMIBufSize * r;
    if (dma_diff > totalbytes) {
        dma_diff = 0;
    }
    return dma_diff;
}

unsigned long __cdecl Timer_Callback_Audio_Handler(VQAHandle *vqa)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQAConfig *config = &vqap->Config;
    Ahandle *handle = &_handles[vqap->AudioHandleIndex];
    unsigned long d;
    unsigned long t;

    if (handle->Flags & AHANDLEF_IS_PAUSED) {
        Debug_Printf("Ahandle: Paused %ld\n", handle->TickCount);
        return handle->TickCount;
    }

    t = Simple_Timer_Callback_Audio_Handler(0) - handle->PauseAdjust;

    d = Get_Playback_Position(vqa, handle, config);

    if (d > 0 && d <= handle->LastPlaybackPosition) {
        if (t > handle->LastTimerTick) {
            d = (t - handle->LastTimerTick);
            handle->LastTimerTick = t;
            handle->TickCount += d;
        }
    } else {
        handle->LastPlaybackPosition = d;
        handle->LastTimerTick = t;
        handle->TickCount = (60 * (d / (vqap->Channels * (vqap->BitsPerSample >> 3))) / vqap->SampleRate);

        if (handle->TickCount >= (unsigned long)config->LatencyAdjustment) {
            handle->TickCount -= config->LatencyAdjustment;
        } else {
            handle->TickCount = 0;
        }
    }
    return handle->TickCount;
}
