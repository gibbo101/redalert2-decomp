// int __fastcall VQA_Unknown_0077C8A0(VQAHandle *vqa, int stop) -- 0x0077C8A0
// Purpose: VQA_SetStop (TS): sets the frame playback stops at (1..Frames)
// and returns the previous one, else -1.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C8A0(VQAHandle *vqa, int stop)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    int oldstop = -1;
    VQAHeader *header;

    header = &vqap->Header;
    if ((stop > 0) && (header->Frames >= stop)) {
        oldstop = vqap->StopFrame;
        vqap->StopFrame = (unsigned short)stop;
    }
    return oldstop;
}
