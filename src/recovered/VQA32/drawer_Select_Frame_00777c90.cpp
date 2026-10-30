// long __fastcall Select_Frame(VQAHandleP *vqap) -- 0x00777C90
// Purpose: chooses the frame to draw now: waits for the loader, honors
// forced redraws and single stepping, compares the clock with the last
// drawn frame and skips late non-key frames (dispatching their palettes,
// loop events and chunks) up to a third of the frame rate.
// -1 draw, -9 frame not loaded, -10 not time yet, -2 stopped by the callback.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"

static long VQA_CalcFramesSinceDrawn(VQAHandleP *vqap)
{
    VQAConfig *config;
    VQADrawer *drawer;
    VQAFrameNode *curframe;
    long cur;
    long loop_end;
    int to_loop_end;
    int from_loop_start;
    int fallback;

    drawer = &vqap->Drawer;
    curframe = drawer->CurFrame;
    config = &vqap->Config;
    cur = curframe->FrameNum;
    loop_end = vqap->LoopEndFrame2;

    if (cur >= drawer->LastFrameNum && cur <= loop_end) {
        return cur - drawer->LastFrameNum;
    }

    fallback = config->FrameRate / 3;
    to_loop_end = loop_end - drawer->LastFrameNum;
    if (to_loop_end < 0) {
        return fallback;
    }
    from_loop_start = curframe->FrameNum - vqap->LoopStartFrame0;
    if (from_loop_start < 0) {
        return fallback;
    }
    return to_loop_end + from_loop_start + 1;
}

static long VQA_SetCurrentFrameAsLast(VQAHandleP *vqap)
{
    VQADrawer *drawer;

    drawer = &vqap->Drawer;
    drawer->LastFrameNum = drawer->CurFrame->FrameNum;
    return -1;
}

static void VQA_SetPreviousFrameNode(VQAHandleP *vqap)
{
    VQADrawer *drawer;

    drawer = &vqap->Drawer;
    drawer->CurFrame = drawer->CurFrame->Prev;
    drawer->CurFrame->Flags = drawer->CurFrame->PrevFlags;
}

long __fastcall Select_Frame(VQAHandleP *vqap)
{
    VQADrawer *drawer;
    VQAConfig *config;
    VQAFrameNode *curframe;
    long desiredframe;
    unsigned long curtime;

    config = &vqap->Config;
    drawer = &vqap->Drawer;
    curframe = drawer->CurFrame;

    if ((curframe->Flags & VQAFRMF_LOADED) == 0) {
        drawer->WaitsOnLoader++;
        if ((drawer->Flags & VQADRWF_REPAINT) && !(vqap->Flags & VQADATF_LDONE)) {
            VQA_SetPreviousFrameNode(vqap);
            if (drawer->Flags & VQADRWF_FORCEDRAW) {
                drawer->Flags |= VQADRWF_HOLD;
                curframe->Flags |= VQAFRMF_HOLD;
            }
            return -1;
        } else {
            return -9;
        }
    }

    if (drawer->Flags & VQADRWF_FORCEDRAW) {
        VQA_SetCurrentFrameAsLast(vqap);
        drawer->Flags |= VQADRWF_HOLD;
        curframe->Flags |= VQAFRMF_HOLD;
        return -1;
    }

    if (config->OptionFlags & VQAOPTF_STEP) {
        drawer->LastFrameNum = curframe->FrameNum;
        curtime = ((curframe->FrameNum * VQA_TIMETICKS) / config->DrawRate);
        VQA_SetTimer(vqap, curtime);
        return -1;
    }

    curtime = VQA_GetTime(vqap);

    long endtime = 0;
    if (!(drawer->Flags & VQADRWF_STEP)) {
        endtime = drawer->LastFrameNum + 1;
    } else {
        endtime = drawer->LastFrameNum + 2;
    }

    if ((int)curtime < ((endtime * VQA_TIMETICKS) / config->DrawRate)) {
        if (drawer->Flags & VQADRWF_REPAINT) {
            if (VQA_ComputeDesiredFrame(vqap, config, drawer, curframe, curtime) == drawer->LastFrameNum
                && (curframe->Flags & VQAFRMF_HOLD)) {
                drawer->LastFrameNum = curframe->FrameNum;
                return -1;
            } else {
                drawer->LastFrameNum = curframe->FrameNum;
                drawer->Flags |= VQADRWF_HOLD;
                curframe->Flags |= VQAFRMF_HOLD;
                return -1;
            }
        } else {
            return -10;
        }
    }

    desiredframe = VQA_ComputeDesiredFrame(vqap, config, drawer, curframe, curtime);

    if (config->DrawFlags & VQACFGF_NOSKIP) {
        return VQA_SetCurrentFrameAsLast(vqap);
    }

    long maxskip = (config->FrameRate / 3) - 1;
    if (maxskip < 0) {
        maxskip = 0;
    }

    while (curframe->FrameNum != desiredframe) {
        if (curframe->Flags & VQAFRMF_KEY) {
            break;
        }
        if (VQA_CalcFramesSinceDrawn(vqap) > maxskip) {
            break;
        }

        if (curframe->Flags & VQAFRMF_PALETTE) {
            if (curframe->Flags & VQAFRMF_PALCOMP) {
                curframe->PaletteSize = VQA_LCW_Uncompress((char *)curframe->Palette + curframe->PalOffset,
                                                           (char *)curframe->Palette, vqap->Max_Pal_Size);
                curframe->Flags &= ~VQAFRMF_PALCOMP;
            }
            memcpy(drawer->Palette_24, curframe->Palette, curframe->PaletteSize);
            drawer->CurPalSize = curframe->PaletteSize;
            drawer->Flags |= VQADRWF_SETPAL;
        }

        if (config->EventHandler != 0) {
            if (curframe->Flags & VQAFRMF_LOOPED) {
                config->EventHandler((VQAHandle *)vqap, VQAEVENT_LOOPED, curframe->FrameNum, vqap->LoopID);
                curframe->Flags &= ~VQAFRMF_LOOPED;
            }
            if (curframe->Flags & VQAFRMF_LOOPJMP) {
                config->EventHandler((VQAHandle *)vqap, VQAEVENT_LOOPJUMP, curframe->FrameNum, vqap->LoopID);
                curframe->Flags &= ~VQAFRMF_LOOPJMP;
            }
            if (curframe->Flags & VQAFRMF_CHUNKS) {
                VQA_DispatchFrameChunks(vqap, curframe->FrameNum);
                curframe->Flags &= ~VQAFRMF_CHUNKS;
            }
        }

        if (config->DrawerCallback != 0) {
            if (config->DrawerCallback(0, curframe->FrameNum) != 0) {
                return -2;
            }
        }

        curframe->PrevFlags = curframe->Flags;
        curframe->Flags = 0;
        curframe = curframe->Next;
        drawer->CurFrame = curframe;
        vqap->SkippedFrames++;

        if (!(curframe->Flags & VQAFRMF_LOADED)) {
            drawer->WaitsOnLoader++;
            if ((drawer->Flags & VQADRWF_REPAINT) && !(vqap->Flags & VQADATF_LDONE)) {
                VQA_SetPreviousFrameNode(vqap);
                return -1;
            }
            return -9;
        }
    }

    return VQA_SetCurrentFrameAsLast(vqap);
}
