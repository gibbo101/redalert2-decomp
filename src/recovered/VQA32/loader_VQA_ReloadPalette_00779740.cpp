// long __fastcall VQA_ReloadPalette(VQAHandleP *vqap, long framenum, int force) -- 0x00779740
// Purpose: loads the palette in effect at a frame (PINF table or FINF palette flags).
#include "shared/vqa_player.hpp"
// @ref ?VQA_LoadFrame@@YIJPAUVQAHandleP@@J@Z=00778680
// @ref ?VQA_GetPaletteFrameRange@@YIJPAUVQAHandleP@@JPAJ1@Z=007798c0

long __fastcall VQA_ReloadPalette(VQAHandleP *vqap, long framenum, int force)
{
    VQALoader *loader;
    VQAFrameNode *curframe;
    VQAConfig *config;
    long rc = -1;
    long pal_frame;
    long last_pal_frame;
    int i;

    loader = &vqap->Loader;
    curframe = loader->CurFrame;
    config = &vqap->Config;

    if (framenum > vqap->StopFrame || vqap->Foff == 0) {
        return -6;
    }
    if (vqap->PaletteInfo.Data != 0) {
        VQA_GetPaletteFrameRange(vqap, framenum, &pal_frame, 0);
        if (!force) {
            VQA_GetPaletteFrameRange(vqap, loader->LastFrameNum, &last_pal_frame, 0);
            if (pal_frame == last_pal_frame) {
                pal_frame = -1;
            }
        }
    } else {
        pal_frame = -1;
        for (i = framenum; i >= 0; i--) {
            if (vqap->Foff[i] & 0x40000000) {
                pal_frame = i;
                break;
            }
        }
        if (!force) {
            last_pal_frame = -1;
            for (i = loader->LastFrameNum; i >= 0; i--) {
                if (vqap->Foff[i] & 0x40000000) {
                    last_pal_frame = i;
                    break;
                }
            }
            if (pal_frame == last_pal_frame) {
                pal_frame = -1;
            }
        }
    }
    if (pal_frame >= 0) {
        if (!config->StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 0, (vqap->Foff[pal_frame] & 0x0FFFFFFF) << 1)) {
            if (force) {
                loader->NumPartialCB = 0;
                loader->PartialCBSize = 0;
                loader->FullCB = vqap->CBData;
                loader->CurCB = vqap->CBData;
                loader->CurFrameNum = 0;
                curframe->Flags = 0;
            }
            rc = VQA_LoadFrame(vqap, 0x1E);
        } else {
            rc = -6;
        }
    }
    return rc;
}
