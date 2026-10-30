// long __fastcall Load_SND1(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B460
// Purpose: reads a ZAP-compressed audio frame and unpacks it.
#include "shared/vqa_player.hpp"
// @ref _AudioUnzap=00781130

long __fastcall Load_SND1(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAAudio *audio;
    VQAConfig *config;
    unsigned char *loadbuf;
    unsigned long padsize;
    ZAPHeader zap;
    long i;

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
    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&zap, sizeof(ZAPHeader))) {
        return -4;
    }
    padsize -= sizeof(ZAPHeader);
    if ((zap.UnCompSize > audio->TempBufSize) && (audio->AudBufPos == 0)) {
        if (zap.UnCompSize == zap.CompSize) {
            if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)audio->Buffer, padsize)) {
                return -4;
            }
        } else {
            loadbuf = (audio->Buffer + config->AudioBufSize) - padsize;
            if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)loadbuf, padsize)) {
                return -4;
            }
            AudioUnzap(loadbuf, audio->Buffer, zap.UnCompSize);
        }
        audio->AudBufPos += zap.UnCompSize;
        for (i = 0; i < (zap.UnCompSize / config->HMIBufSize); i++) {
            audio->IsLoaded[i] = 1;
        }
        return -1;
    }
    if (zap.UnCompSize == zap.CompSize) {
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)audio->TempBuf, padsize)) {
            return -4;
        }
    } else {
        loadbuf = (audio->TempBuf + audio->TempBufSize) - padsize;
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)loadbuf, padsize)) {
            return -4;
        }
        AudioUnzap(loadbuf, audio->TempBuf, zap.UnCompSize);
    }
    audio->TempBufLen = zap.UnCompSize;
    return -1;
}
