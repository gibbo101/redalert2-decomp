// long __cdecl Open_Audio_Handler(VQAHandleP *, AhandleInitParams *, long) (0x004118A0): claims the handle, reads the
// format and starts the 16 ms audio timer (RA2 drops TibSun's primary-buffer format change).
#include "shared/ahandle.hpp"

long __cdecl Open_Audio_Handler(VQAHandleP *vqap, AhandleInitParams *params, long b)
{
    IDirectSound *sound = (IDirectSound *)unknown_directsound_40a6c0();
    DSCAPS dscaps;

    Debug_Printf("Opening VQ audio handler\n");
    Debug_Printf("Current thread ID is %08x\n", GetCurrentThreadId());

    if (!unknown_check_406f30()) {
        return AHANDLE_ERROR;
    }

    int index = 0;
    while (index < Ahandle::MAX_HANDLES) {
        if (!_handles[index].Used) {
            break;
        }
        index++;
    }

    if (index != 1 && b == 16) {

        VQAConfig *config = &vqap->Config;

        vqap->AudioHandleIndex = index;

        Ahandle *handle = &_handles[index];
        memset(handle, 0, sizeof(*handle));
        handle->Used = true;
        handle->Volume = config->Volume;

        InitializeCriticalSection(&handle->CriticalSection);

        if (config->AudioRate != -1) {
            handle->SampleRate = config->AudioRate;
        } else {
            if (config->FrameRate != vqap->FrameRate) {
                handle->SampleRate = params->SampleRate * (unsigned)config->FrameRate / vqap->FrameRate;
            } else {
                handle->SampleRate = params->SampleRate;
            }
        }

        memset(&dscaps, 0, sizeof(dscaps));
        dscaps.dwSize = sizeof(DSCAPS);

        sound->GetCaps(&dscaps);

        if (dscaps.dwFlags & 0x20) {
            Debug_Printf("Ahandle detected emulated sound driver. LatencyAdjustment = %ld ticks\n", config->LatencyAdjustment);
        } else {
            config->LatencyAdjustment = 0;
        }

        handle->Channels = params->Channels;
        handle->BitsPerSample = params->BitsPerSample;
        handle->InitFlags = params->Flags;
        _AHandleCallbackFunc1 = (AHANDLE_CALLBACK_1)params->Callback1;
        _AHandleCallbackFunc2 = (AHANDLE_CALLBACK_2)params->Callback2;

        Debug_Printf("Calling timeBeginPeriod\n");
        if (timeBeginPeriod(1000 / 60) != 97) {
            Debug_Printf("Creating VQ audio timer thread\n");
            handle->TimerHandle = timeSetEvent(1000 / 60, 1, AudioCallback, (DWORD)vqap, 1);
            Debug_Printf("VQ audio handler opened OK\n");
            if (handle->TimerHandle != 0) {
                return AHANDLE_OK;
            }
            return AHANDLE_ERROR;
        }
    }
    return AHANDLE_ERROR;
}
