// long __fastcall VQA_OpenAudio(VQAHandleP *vqap) -- 0x00776380
// Purpose: -13 without an audio buffer; opens the audio handler (action 2) with the
// format and the fill/done callbacks and marks the module locked. -1 on success,
// else the handler's error.
#include "shared/vqa_player.hpp"

// The audio handler's open parameters (0x10 bytes on the stack).
struct VQAAudioOpenParams {
    unsigned short SampleRate;
    unsigned char Channels;
    unsigned char BitsPerSample;
    int unknown_04;
    int (__cdecl *FillCallback)(VQAHandleP *vqap);
    int (__cdecl *DoneCallback)(VQAHandleP *vqap, int buffer);
};

long __fastcall VQA_OpenAudio(VQAHandleP *vqap)
{
    VQAAudio *audio = &vqap->Audio;
    long rc;

    if (audio->Buffer == 0) {
        return -13;
    }
    audio->Block1 = 0;
    audio->Block2 = -1;
    audio->BufferPosition = 0;
    vqap->RepeatedBuffers = 0;
    VQAAudioOpenParams params;
    params.SampleRate = vqap->SampleRate;
    params.Channels = vqap->Channels;
    params.BitsPerSample = vqap->BitsPerSample;
    params.FillCallback = VQA_AudioFillCallback;
    params.DoneCallback = VQA_AudioDoneCallback;
    rc = vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_OPEN, (int)&params, sizeof(params));
    if (rc >= 0 || rc == -1) {
        if ((audio->Flags & VQAAUDF_MODLOCKED) == 0) {
            audio->Flags |= VQAAUDF_MODLOCKED;
        }
        return -1;
    }
    return rc;
}
