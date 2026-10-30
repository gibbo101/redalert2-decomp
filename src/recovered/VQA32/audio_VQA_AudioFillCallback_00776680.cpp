// int __cdecl VQA_AudioFillCallback(VQAHandleP *vqap) -- 0x00776680
// Purpose: the audio handler's request for the next HMIBufSize block: hands the
// next loaded block to the handler (action 5), or repeats the previous block
// (HMIBuffer) while the loader is behind, or the tail at end of file; returns its size.
#include "shared/vqa_player.hpp"

int __cdecl VQA_AudioFillCallback(VQAHandleP *vqap)
{
    VQAAudio *audio = &vqap->Audio;
    VQAConfig *config = &vqap->Config;
    long size = config->HMIBufSize;

    if (audio->Flags & 0x200) {
        return 0;
    }
    long pos = audio->BufferPosition;
    unsigned long block = audio->Block1;
    if (config->OptionFlags & 0x200) {
        long nblock = block + 1;
        if ((unsigned)nblock >= audio->NumAudBlocks) {
            nblock = 0;
        }
        if (!(audio->Flags & 0x100)) {
            if (audio->IsLoaded[nblock] == 0) {
                audio->Flags |= 0x400;
            }
        }
    }
    bool repeating = false;
    if (audio->IsLoaded[block] == 1) {
        if (audio->Block2 == -1) {
            audio->Block2 = block;
            audio->PlayPosition = pos;
        }
        audio->BlockRepeats[block] = 0;
        block++;
        long npos = pos + size;
        if (npos >= config->AudioBufSize) {
            npos = 0;
            block = 0;
        }
        audio->BufferPosition = npos;
        audio->Block1 = block;
    } else {
        if (audio->Flags & 0x100) {
            audio->Flags |= 0x200;
            if ((unsigned)pos < audio->AudBufPos) {
                size = audio->AudBufPos - pos;
            } else {
                size = 0;
            }
        } else {
            audio->Flags |= 0x80;
            repeating = true;
            vqap->RepeatedBuffers++;
            pos -= size;
            block--;
            if (pos < 0) {
                pos = config->AudioBufSize - size;
                block = audio->NumAudBlocks - 1;
            }
            audio->BlockRepeats[block]++;
        }
    }
    if (size > 0) {
        if (repeating == true) {
            config->AudioHandler((VQAHandle *)vqap, 5, (int)audio->HMIBuffer, size);
        } else {
            config->AudioHandler((VQAHandle *)vqap, 5, (int)(audio->Buffer + pos), size);
        }
    }
    return size;
}
