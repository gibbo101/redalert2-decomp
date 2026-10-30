// int __fastcall VQA_Unknown_0077C2E0(VQAHandle *vqa, int framenum, int fromwhere) -- 0x0077C2E0
// Purpose: VQA_SeekFrame (TS): repositions playback at a frame up to the
// stop frame: stops the audio, empties the loop cache, reloads the
// palette in effect there (color mode 0, not a loop start), seeks the
// loader to the frame's group, clears the frame ring, primes the buffers
// and sets the clock. Returns the frame, or -6 past the stop frame.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C2E0(VQAHandle *vqa, int framenum, int fromwhere)
{
    VQAHandleP *vqap;
    VQALoader *loader;
    VQAHeader *header;
    VQAFrameNode *frame;
    VQAConfig *config;
    int rc = -1;
    VQAAudio *audio;
    long audio_on;

    vqap = (VQAHandleP *)vqa;
    loader = &vqap->Loader;
    header = &vqap->Header;
    config = &vqap->Config;
    frame = loader->CurFrame;

    audio = &vqap->Audio;
    audio_on = (audio->Flags & VQAAUDF_ISPLAYING);
    if (audio_on) {
        VQA_StopAudio(vqap);
    }

    if ((framenum <= vqap->StopFrame) && (vqap->Foff != 0)) {
        VQA_ResetCache(vqap);
        VQA_ResetLastFrameNum(vqa);

        bool has_palette = false;
        if (header->ColorMode == 0 && !VQA_IsFrameStartOfLoop(vqap, framenum)) {
            rc = VQA_ReloadPalette(vqap, framenum, true);
            if (rc == -1) {
                if (frame->Flags & VQAFRMF_PALETTE) {
                    has_palette = true;
                }
            }
        }

        if (rc == -1) {
            loader->CurFrameNum = framenum;
            bool skipcodebook;
            bool preloadaudio = (((unsigned char)header->Flags) & VQAHDF_SNDJUMP) == 0;
            rc = VQA_SeekGroup(vqap, framenum, header->Groupsize, preloadaudio, 1, skipcodebook);
            if (rc == -1) {
                loader->CurFrameNum = framenum;
                loader->CurFrame->Flags = 0;
                if (has_palette) {
                    loader->CurFrame->Flags |= VQAFRMF_PALETTE;
                }
                frame = loader->CurFrame->Next;
                while (frame != loader->CurFrame) {
                    frame->Flags = 0;
                    frame = frame->Next;
                }
                vqap->Drawer.CurFrame = loader->CurFrame;
                rc = PrimeBuffers(vqap);
                if ((rc == -1) || (rc == -2)) {
                    rc = framenum;
                    VQA_SetTimer(vqap, VQA_TIMETICKS * framenum / config->DrawRate);
                }
            }
        }
        return rc;
    } else {
        rc = -6;
    }
    return rc;
}
