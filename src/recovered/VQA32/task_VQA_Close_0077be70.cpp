// void __fastcall VQA_Unknown_0077BE70(VQAHandle *vqa) -- 0x0077BE70
// Purpose: VQA_Close (TS): closes the audio (and releases the game's audio
// lock), frees the private image buffer and all player buffers, closes the
// stream and frees the handle.
#include "shared/vqa_player.hpp"
// @ref ?Unlock_Audio_Handler@@YAHXZ=00412380

void __fastcall VQA_Unknown_0077BE70(VQAHandle *vqa)
{
    VQAHandleP *vqap;
    VQAConfig *config;
    VQAAudio *audio;

    vqap = (VQAHandleP *)vqa;
    config = &vqap->Config;
    audio = &vqap->Audio;

    if (config->OptionFlags & VQAOPTF_AUDIO && vqap->Header.Flags & (VQAHDF_AUDIO | VQAHDF_ALTAUDIO)) {
        VQA_CloseAudio(vqap);
        if (audio->Flags & VQAAUDF_MEMLOCKED) {
            Unlock_Audio_Handler();
            audio->Flags &= ~VQAAUDF_MEMLOCKED;
        }
    }

    if (vqap->Flags & VQADATF_ALTIMG && vqap->AltImageBuf != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->AltImageBuf,
                              vqap->AltImageWidth * vqap->AltImageHeight);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->AltImageBuf, 0);
    }

    FreeBuffers(vqap);
    config->StreamHandler((VQAHandle *)vqap, VQACMD_CLOSE, 0, 0);
    config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap, sizeof(VQAHandleP));
    config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap, 0);
}
