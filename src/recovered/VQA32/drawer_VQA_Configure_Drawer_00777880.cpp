// long __fastcall VQA_Configure_Drawer(VQAHandleP *vqap) -- 0x00777880
// Purpose: computes the block grid of the movie and selects the frame
// drawer, page flipper and the two UnVQ decoders for the block size, color
// mode, transparency and draw flags.
#include "shared/vqa_player.hpp"
// @ref ?UnVQ_Nop@@YAXPAE00KKK@Z=00778430
// @ref ?PageFlip_Nop@@YIJPAUVQAHandle@@@Z=00778440
// @ref ?DrawFrame_MCGA@@YIJPAUVQAHandle@@@Z=00777c50
// @ref ?PageFlip_MCGA@@YIJPAUVQAHandle@@@Z=007782c0
// @ref ?DrawFrame_MCGABuf@@YIJPAUVQAHandle@@@Z=00778350
// @ref ?PageFlip_MCGABuf@@YIJPAUVQAHandle@@@Z=007783a0
// @ref ?UnVQ2_C1_4x4@@YAXPAE00KKK@Z=0077cbd0
// @ref ?UnVQ1_C4_4x4@@YAXPAE00KKK@Z=0077cf70
// @ref ?UnVQ2_C4_4x4@@YAXPAE00KKK@Z=0077d0c0
// @ref ?UnVQ1_C4_4x2@@YAXPAE00KKK@Z=0077d470
// @ref ?UnVQ2_C4_4x2@@YAXPAE00KKK@Z=0077d5b0
// @ref ?UnVQ2_C0_4x4_TRANS@@YAXPAE00KKK@Z=0077d940
// @ref ?UnVQ2_C0_4x4_KEY@@YAXPAE00KKK@Z=0077dd90
// @ref ?UnVQ2_C0_4x4_TRANS_HALF@@YAXPAE00KKK@Z=0077e1a0
// @ref ?UnVQ2_C0_4x2_TRANS@@YAXPAE00KKK@Z=0077e5b0
// @ref ?UnVQ2_C0_4x2_KEY@@YAXPAE00KKK@Z=0077e9e0
// @ref _ASM_UnVQ_4x2=0077ff50
// @ref _ASM_UnVQ_4x4=0077ffe6
// @ref _ASM_UnVQ_4x4_HALF=007800a4
// @ref _ASM_UnVQ1_C1_4x4=007801d8

long __fastcall VQA_Configure_Drawer(VQAHandleP *vqap)
{
    VQAHeader *header;
    VQADrawer *drawer;
    long blkdim;

    drawer = &vqap->Drawer;
    header = &vqap->Header;

    drawer->BlocksPerRow = header->ImageWidth / header->BlockWidth;
    drawer->NumRows = header->ImageHeight / header->BlockHeight;
    drawer->NumBlocks = drawer->BlocksPerRow * drawer->NumRows;

    blkdim = BLOCK_DIM(header->BlockWidth, header->BlockHeight);

    vqap->UnVQ1 = UnVQ_Nop;
    vqap->UnVQ2 = UnVQ_Nop;
    vqap->Page_Flip = PageFlip_Nop;

    if (!(vqap->Config.DrawFlags & VQACFGF_BUFFER)) {
        vqap->Draw_Frame = DrawFrame_MCGA;
        vqap->Page_Flip = PageFlip_MCGA;
    } else {
        vqap->Draw_Frame = DrawFrame_MCGABuf;
        vqap->Page_Flip = PageFlip_MCGABuf;
    }

    switch (blkdim) {
    case BLOCK_4X2:
        switch (header->ColorMode) {
        case 0:
            vqap->UnVQ1 = ASM_UnVQ_4x2;
            if (header->Flags & VQAHDF_TRANS) {
                if (vqap->Config.DrawFlags & VQACFGF_NOTRANS) {
                    vqap->UnVQ2 = UnVQ2_C0_4x2_KEY;
                } else {
                    vqap->UnVQ2 = UnVQ2_C0_4x2_TRANS;
                }
            }
            break;

        case 4:
            vqap->UnVQ1 = UnVQ1_C4_4x2;
            vqap->UnVQ2 = UnVQ2_C4_4x2;
            break;
        }
        break;

    case BLOCK_4X4:
        switch (header->ColorMode) {
        case 4:
            vqap->UnVQ1 = UnVQ1_C4_4x4;
            vqap->UnVQ2 = UnVQ2_C4_4x4;
            break;

        case 1:
            vqap->UnVQ1 = ASM_UnVQ1_C1_4x4;
            vqap->UnVQ2 = UnVQ2_C1_4x4;
            break;

        case 0:
            vqap->UnVQ1 = ASM_UnVQ_4x4;
            if (header->Flags & VQAHDF_TRANS) {
                if (vqap->Config.DrawFlags & VQACFGF_NOTRANS) {
                    vqap->UnVQ2 = UnVQ2_C0_4x4_KEY;
                } else if (vqap->Config.DrawFlags & VQACFGF_HALFSIZE) {
                    vqap->UnVQ2 = UnVQ2_C0_4x4_TRANS_HALF;
                } else {
                    vqap->UnVQ2 = UnVQ2_C0_4x4_TRANS;
                }
            } else {
                if (vqap->Config.DrawFlags & VQACFGF_HALFSIZE) {
                    vqap->UnVQ1 = ASM_UnVQ_4x4_HALF;
                }
            }
            break;
        }
        break;
    }

    return -1;
}
