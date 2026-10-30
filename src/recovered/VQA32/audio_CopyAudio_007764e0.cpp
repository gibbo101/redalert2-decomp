// long __fastcall CopyAudio(VQAHandleP *vqap) -- 0x007764E0
// Purpose: moves the decoded audio waiting in TempBuf into the audio ring buffer
// (wrapping at its end) and marks the blocks it fills loaded. -11 (and a loader
// wait) when the last block is still loaded; -1 otherwise.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"

long __fastcall CopyAudio(VQAHandleP *vqap)
{
    VQAAudio *audio = &vqap->Audio;
    VQAConfig *config = &vqap->Config;
    VQALoader *loader = &vqap->Loader;
    unsigned long startblock;
    unsigned long endblock;
    unsigned long len1;
    unsigned long len2;
    unsigned long i;
    unsigned char *tempbuf;
    unsigned long tempbuflen;

    if ((config->OptionFlags & 1) == 0 || audio->Buffer == 0 || audio->TempBufLen == 0) {
        return -1;
    }
    tempbuf = audio->TempBuf + audio->BufferOffset;
    tempbuflen = audio->TempBufLen - audio->BufferOffset;
    startblock = audio->AudBufPos / config->HMIBufSize;
    endblock = (audio->AudBufPos + tempbuflen) / config->HMIBufSize;
    if (endblock >= audio->NumAudBlocks) {
        endblock -= audio->NumAudBlocks;
    }
    if (audio->IsLoaded[endblock] == 1) {
        loader->WaitsOnAudio++;
        return -11;
    }
    if (startblock <= endblock) {
        memcpy(audio->Buffer + audio->AudBufPos, tempbuf, tempbuflen);
        audio->AudBufPos += tempbuflen;
        audio->TempBufLen = 0;
        audio->BufferOffset = 0;
        for (i = startblock; i < endblock; i++) {
            audio->IsLoaded[i] = 1;
        }
    } else {
        len1 = config->AudioBufSize - audio->AudBufPos;
        len2 = tempbuflen - len1;
        memcpy(audio->Buffer + audio->AudBufPos, tempbuf, len1);
        memcpy(audio->Buffer, tempbuf + len1, len2);
        audio->AudBufPos = len2;
        audio->TempBufLen = 0;
        audio->BufferOffset = 0;
        for (i = startblock; i < audio->NumAudBlocks; i++) {
            audio->IsLoaded[i] = 1;
        }
        for (i = 0; i < endblock; i++) {
            audio->IsLoaded[i] = 1;
        }
    }
    return -1;
}
