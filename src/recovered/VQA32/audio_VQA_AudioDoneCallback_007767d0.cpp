// int __cdecl VQA_AudioDoneCallback(VQAHandleP *vqap, int buffer) -- 0x007767D0
// Purpose: the audio handler finished a buffer: frees its block (unless it was
// repeated) and advances PlayPosition/Block2. -20 without a playing block, -19
// for a buffer out of sync.
#include "shared/vqa_player.hpp"

int __cdecl VQA_AudioDoneCallback(VQAHandleP *vqap, int buffer)
{
    VQAAudio *audio = &vqap->Audio;
    VQAConfig *config = &vqap->Config;
    unsigned long block;

    if ((void *)buffer == audio->Buffer + audio->PlayPosition || (void *)buffer == audio->HMIBuffer) {
        block = audio->Block2;
        if (block != -1) {
            if (!audio->BlockRepeats[block]) {
                audio->IsLoaded[block] = 0;
                block++;
                if (block >= audio->NumAudBlocks) {
                    block = 0;
                }
                if (audio->IsLoaded[block] == 1) {
                    audio->PlayPosition += config->HMIBufSize;
                    if (audio->PlayPosition >= (unsigned)config->AudioBufSize) {
                        audio->PlayPosition = 0;
                    }
                    audio->Block2 = block;
                } else {
                    audio->Block2 = -1;
                }
            } else {
                audio->BlockRepeats[block]--;
            }
            return -1;
        }
        return -20;
    }
    return -19;
}
