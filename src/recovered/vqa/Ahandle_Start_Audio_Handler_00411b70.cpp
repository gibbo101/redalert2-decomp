// long __cdecl Start_Audio_Handler(VQAHandleP *) (0x00411B70): makes the looping secondary buffer (two HMI blocks),
// primes it and plays it at the movie volume (0x00A40B48); resumes a paused handle instead.
#include "shared/ahandle.hpp"

long __cdecl Start_Audio_Handler(VQAHandleP *vqap)
{
    VQAConfig *config = &vqap->Config;
    Ahandle *audio = &_handles[vqap->AudioHandleIndex];

    if (audio->Flags & AHANDLEF_IS_PAUSED) {
        return Play_Audio_Handler(vqap);
    }

    EnterCriticalSection(&audio->CriticalSection);

    if (audio->SecondaryBufferPtr != 0) {
        audio->SecondaryBufferPtr->Stop();
        audio->SecondaryBufferPtr->Release();
        audio->SecondaryBufferPtr = 0;
    }

    audio->SecondaryBufferSize = config->HMIBufSize * 2;

    memset(&audio->BufferDesc, 0, sizeof(DSBUFFERDESC));
    audio->BufferDesc.dwSize = sizeof(DSBUFFERDESC);
    audio->BufferDesc.dwFlags = 0x000100E0;
    audio->BufferDesc.dwBufferBytes = audio->SecondaryBufferSize;
    audio->BufferDesc.lpwfxFormat = &audio->DsBuffFormat;
    memset(&audio->DsBuffFormat, 0, sizeof(WAVEFORMATEX));
    audio->DsBuffFormat.wFormatTag = WAVE_FORMAT_PCM;
    audio->DsBuffFormat.nSamplesPerSec = audio->SampleRate;
    audio->DsBuffFormat.nChannels = audio->Channels;
    audio->DsBuffFormat.wBitsPerSample = audio->BitsPerSample;
    audio->DsBuffFormat.nBlockAlign = (short)((audio->DsBuffFormat.wBitsPerSample / 8) * audio->DsBuffFormat.nChannels);
    audio->DsBuffFormat.nAvgBytesPerSec = audio->DsBuffFormat.nSamplesPerSec * audio->DsBuffFormat.nBlockAlign;

    ((IDirectSound *)unknown_directsound_40a6c0())->CreateSoundBuffer(&audio->BufferDesc, &audio->SecondaryBufferPtr, 0);

    if (audio->SecondaryBufferPtr == 0) {
        LeaveCriticalSection(&audio->CriticalSection);
        return AHANDLE_ERROR;
    }

    _AHandleCallbackFunc1((VQAHandle *)vqap);
    _AHandleCallbackFunc1((VQAHandle *)vqap);
    audio->AudioBufWriteIndex = 0;
    audio->EndLastAudioChunk = 0;
    audio->ChunksMovedToAudioBuffer = 0;
    audio->SecondaryBufferPtr->SetCurrentPosition(0);

    audio->Volume = (int)(unknown_volume_a40b48 * 255.0f);
    audio->SecondaryBufferPtr->SetVolume(Audio_DS_Volume_Attenuation(audio->Volume & 255));

    HRESULT return_code = audio->SecondaryBufferPtr->Play(0, 0, 1);
    LeaveCriticalSection(&audio->CriticalSection);
    return return_code == 0 ? AHANDLE_OK : AHANDLE_ERROR;
}
