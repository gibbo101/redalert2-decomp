// void __stdcall AudioCallback(UINT timer, UINT, DWORD vqap, DWORD, DWORD) (0x00412120): the timer callback that
// refills the buffer half the play cursor left (and restores a lost buffer).
#include "shared/ahandle.hpp"

void __stdcall AudioCallback(unsigned int uTimerID, unsigned int, DWORD dwUser, DWORD, DWORD)
{
    Ahandle *audio;
    DWORD play_cursor;
    DWORD write_cursor;
    HRESULT return_code;
    bool buffer_stopped = false;
    DWORD status;

    VQAHandle *vqa = (VQAHandle *)dwUser;
    VQAHandleP *vqap = (VQAHandleP *)dwUser;

    audio = &_handles[vqap->AudioHandleIndex];

    if (InterlockedIncrement(&audio->SuspendAudioCallback) != TRUE || (audio->Flags & AHANDLEF_IS_PAUSED)) {
        InterlockedDecrement(&audio->SuspendAudioCallback);
        return;
    }

    EnterCriticalSection(&audio->CriticalSection);

    if (!audio->SecondaryBufferPtr || audio->TimerHandle != uTimerID) {
        LeaveCriticalSection(&audio->CriticalSection);
        InterlockedDecrement(&audio->SuspendAudioCallback);
        return;
    }

    return_code = audio->SecondaryBufferPtr->GetStatus(&status);
    if (!(status & 1) && !(status & 4)) {
        LeaveCriticalSection(&audio->CriticalSection);
        InterlockedDecrement(&audio->SuspendAudioCallback);
        return;
    }

    return_code = audio->SecondaryBufferPtr->GetCurrentPosition(&play_cursor, &write_cursor);

    bool write_more = false;

    if (return_code == (HRESULT)0x88780096) {
        audio->SecondaryBufferPtr->Restore();
        audio->SecondaryBufferPtr->Stop();
        buffer_stopped = true;
        audio->SecondaryBufferPtr->SetCurrentPosition(0);
        audio->LastChunkPosition = 0;
        audio->EndLastAudioChunk = 0;
        write_more = true;
    }

    if (play_cursor < audio->EndLastAudioChunk) {
        write_more = true;
    } else {
        if ((play_cursor >= audio->SecondaryBufferSize / 2) && audio->EndLastAudioChunk == 0) {
            write_more = true;
        }
    }

    if (write_more == true) {
        _AHandleCallbackFunc2((VQAHandle *)vqa, audio->AudioBuf[audio->AudioBufWriteIndex]);
        audio->ChunksMovedToAudioBuffer++;
        int index = audio->AudioBufWriteIndex + 1;
        if (index >= Ahandle::MAX_BUFFERS) {
            index = 0;
        }
        audio->AudioBufInUse[audio->AudioBufWriteIndex] = FALSE;
        _AHandleCallbackFunc1((VQAHandle *)vqa);

        if (audio->AudioBufInUse[index]) {
            audio->AudioBufWriteIndex = index;
        }

        if (buffer_stopped == true) {
            audio->SecondaryBufferPtr->Play(0, 0, 1);
        }
    }
    LeaveCriticalSection(&audio->CriticalSection);
    InterlockedDecrement(&audio->SuspendAudioCallback);
}
