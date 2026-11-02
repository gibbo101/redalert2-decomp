// long __cdecl Load_Audio_Handler(VQAHandleP *, void *buffer, long nbytes) (0x00411D80): follows a movie volume
// change, queues the block and copies it into the DirectSound buffer (Move_HMI_Audio_Block_To_Direct_Sound_Buffer
// expands inline).
#include "shared/ahandle.hpp"

static BOOL Move_HMI_Audio_Block_To_Direct_Sound_Buffer(VQAHandleP *vqap)
{
    Ahandle *audio;

    void *play_buffer_ptr1;
    void *play_buffer_ptr2;
    DWORD lock_length1;
    DWORD lock_length2;
    unsigned next_fill_pos;
    HRESULT return_code;

    audio = &_handles[vqap->AudioHandleIndex];
    VQAConfig *config = &vqap->Config;

    if (audio->SecondaryBufferPtr == 0) {
        return 0;
    }

    next_fill_pos = audio->EndLastAudioChunk;

    return_code = audio->SecondaryBufferPtr->Lock((DWORD)next_fill_pos, (DWORD)config->HMIBufSize,
        &play_buffer_ptr1, &lock_length1, &play_buffer_ptr2, &lock_length2, 0);

    if (return_code != 0) return FALSE;

    int index = audio->AudioBufReadIndex;

    if (audio->AudioBufSize[index] > lock_length1) {

        memcpy((char *)play_buffer_ptr1, audio->AudioBuf[index], lock_length1);

        if (audio->AudioBufSize[index] - lock_length1 > lock_length2) {
            memcpy(play_buffer_ptr2, audio->AudioBuf[index], lock_length2);
        } else {
            memcpy(play_buffer_ptr2, audio->AudioBuf[index], audio->AudioBufSize[index] - lock_length1);
        }

    } else {
        memcpy(play_buffer_ptr1, audio->AudioBuf[index], audio->AudioBufSize[index]);
    }

    audio->SecondaryBufferPtr->Unlock(play_buffer_ptr1, lock_length1, play_buffer_ptr2, lock_length2);

    audio->LastChunkPosition = next_fill_pos;
    audio->EndLastAudioChunk = next_fill_pos + audio->AudioBufSize[index];
    if (audio->EndLastAudioChunk >= audio->SecondaryBufferSize) {
        audio->EndLastAudioChunk = 0;
    }

    return TRUE;
}

long __cdecl Load_Audio_Handler(VQAHandleP *vqap, void *buffer, long nbytes)
{
    Ahandle *handle = &_handles[vqap->AudioHandleIndex];

    if (buffer != 0 && nbytes != 0) {
        EnterCriticalSection(&handle->CriticalSection);
        if (handle != 0 && handle->SecondaryBufferPtr != 0) {
            if (handle->Volume != unknown_volume_a40b48 * 256.0f) {
                handle->Volume = (int)(unknown_volume_a40b48 * 255.0f);
                handle->SecondaryBufferPtr->SetVolume(Audio_DS_Volume_Attenuation(handle->Volume & 255));
            }
        }
        int readindex = handle->AudioBufReadIndex;
        if (handle->AudioBufInUse[readindex] == TRUE) {
            LeaveCriticalSection(&handle->CriticalSection);
            return AHANDLE_ERROR;
        }
        handle->AudioBuf[readindex] = buffer;
        handle->AudioBufSize[readindex] = nbytes;
        handle->AudioBufInUse[readindex] = TRUE;
        Move_HMI_Audio_Block_To_Direct_Sound_Buffer(vqap);
        int index = readindex + 1;
        if (index >= Ahandle::MAX_BUFFERS) {
            index = 0;
        }
        handle->AudioBufReadIndex = index;
        LeaveCriticalSection(&handle->CriticalSection);
        return AHANDLE_OK;
    }
    return AHANDLE_ERROR;
}
