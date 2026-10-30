// long __fastcall Load_SND2(VQAHandleP *vqap, unsigned long iffsize) -- 0x0077B620
// Purpose: reads an IMA ADPCM audio frame and decodes it.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"
// @ref _VQA_sosCODECDecompressData=00780581

long __fastcall Load_SND2(VQAHandleP *vqap, unsigned long iffsize)
{
    VQAAudio *audio;
    VQAConfig *config;
    unsigned char *loadbuf;
    unsigned long padsize;
    unsigned long uncomp_size;
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
    uncomp_size = iffsize * (vqap->BitsPerSample / 4);
    if ((uncomp_size > audio->TempBufSize) && (audio->AudBufPos == 0)) {
        loadbuf = (audio->Buffer + config->AudioBufSize) - padsize;
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)loadbuf, padsize)) {
            return -4;
        }
        VQA_sosCODECDecompressData(loadbuf, (char *)audio->Buffer, vqap->BitsPerSample, vqap->Channels, uncomp_size, &audio->ADPCM_Info);
        if (audio->BufferOffset) {
            uncomp_size -= audio->BufferOffset;
            memcpy(audio->Buffer, audio->Buffer + audio->BufferOffset, uncomp_size);
            audio->BufferOffset = 0;
        }
        audio->AudBufPos += uncomp_size;
        for (i = 0; i < (uncomp_size / config->HMIBufSize); i++) {
            audio->IsLoaded[i] = true;
        }
        return -1;
    }
    loadbuf = (audio->TempBuf + audio->TempBufSize) - padsize;
    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)loadbuf, padsize)) {
        return -4;
    }
    VQA_sosCODECDecompressData(loadbuf, (char *)audio->TempBuf, vqap->BitsPerSample, vqap->Channels, uncomp_size, &audio->ADPCM_Info);
    audio->TempBufLen = uncomp_size;
    return -1;
}
