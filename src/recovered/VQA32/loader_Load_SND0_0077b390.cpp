// long __fastcall Load_SND0(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B390
// Purpose: reads raw audio into the audio buffer (startup chunk) or the temporary buffer.
#include "shared/vqa_player.hpp"

long __fastcall Load_SND0(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAAudio *audio;
    VQAConfig *config;
    unsigned long padsize;
    unsigned long i;

    audio = &vqap->Audio;
    config = &vqap->Config;
    padsize = PADSIZE(iffsize);
    if (((config->OptionFlags & 1) == 0) || (audio->Buffer == 0)) {
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 1, padsize)) {
            return -6;
        } else {
            return -1;
        }
    }
    if ((padsize > audio->TempBufSize) && (audio->AudBufPos == 0)) {
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)audio->Buffer, padsize)) {
            return -4;
        }
        audio->AudBufPos += iffsize;
        for (i = 0; i < (iffsize / config->HMIBufSize); i++) {
            audio->IsLoaded[i] = 1;
        }
        return -1;
    } else {
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)audio->TempBuf, padsize)) {
            return -4;
        }
    }
    audio->TempBufLen = iffsize;
    return -1;
}
