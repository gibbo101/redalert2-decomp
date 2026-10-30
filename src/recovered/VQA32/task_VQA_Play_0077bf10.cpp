// int __fastcall VQA_Unknown_0077BF10(VQAHandle *vqa, int mode, int flags) -- 0x0077BF10
// Purpose: VQA_Play (TS): primes playback on the first call (clock, image
// buffer, audio), tracks the client callback count, then pauses (drawing
// one forced frame with VQAPLAYF_REPAINT) or runs the load/draw loop until
// both loader and drawer are done (one frame in walk mode), honoring the
// wait-for-refill audio sync. Returns the last drawn frame, -2 at the end.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077BF10(VQAHandle *vqa, int mode, int flags)
{
    VQAHandleP *vqabuf;
    VQAConfig *config;
    VQADrawer *drawer;
    VQAAudio *audio;
    int rc;
    long curtime;

    rc = -1;
    vqabuf = ((VQAHandleP *)vqa);
    drawer = &vqabuf->Drawer;
    config = &vqabuf->Config;
    audio = &vqabuf->Audio;

    if (!(vqabuf->Flags & VQADATF_PRIMED)) {
        rc = VQA_ResetLastFrameNum(vqa);
        if (rc != -1) {
            return rc;
        }
        if (!(vqabuf->Flags & VQADATF_BUFCONFIG)) {
            VQA_Configure_Buffer((VQAHandleP *)vqa);
        }
        if ((config->OptionFlags & VQAOPTF_AUDIO) && vqabuf->Audio.IsLoaded[0]) {
            VQA_StartAudio((VQAHandleP *)vqabuf);
        }
        curtime = ((drawer->CurFrame->FrameNum * VQA_TIMETICKS) / config->DrawRate);
        VQA_SetTimer((VQAHandleP *)vqabuf, curtime);
        ((VQAHandleP *)vqa)->StartTime = VQA_GetTime((VQAHandleP *)vqabuf);
        vqabuf->Flags |= VQADATF_PRIMED;
    }

    int count;
    if (config->UnusedCallback != 0) {
        count = config->UnusedCallback(vqa);
    } else {
        count = -1;
    }
    int lastcount = vqabuf->LastCallbackCount;
    if (lastcount == -1) {
        vqabuf->LastCallbackCount = count;
        vqabuf->MaxCallbackDelta = 0;
    } else {
        int delta = count - lastcount;
        vqabuf->LastCallbackCount = count;
        if (delta > vqabuf->MaxCallbackDelta) {
            vqabuf->MaxCallbackDelta = delta;
        }
    }

    switch (mode) {
    case VQAMODE_PAUSE:
        if ((vqabuf->Flags & VQADATF_PAUSED) == 0) {
            vqabuf->Flags |= VQADATF_PAUSED;
            ((VQAHandleP *)vqa)->EndTime = VQA_GetTime((VQAHandleP *)vqabuf);
            if (vqabuf->Audio.Flags & VQAAUDF_ISPLAYING) {
                VQA_PauseAudio((VQAHandleP *)vqabuf);
            }
        }
        if (flags & VQAPLAYF_REPAINT) {
            drawer->Flags |= VQADRWF_REPAINT;
            drawer->Flags |= VQADRWF_FORCEDRAW;
            if ((rc = (*(vqabuf->Draw_Frame))(vqa)) == -1) {
                if ((rc = User_Update(vqa)) != -1) {
                    vqabuf->Flags |= (VQADATF_DDONE | VQADATF_LDONE);
                } else {
                    rc = drawer->LastFrameNum;
                }
            } else {
                if (rc == -9 && (vqabuf->Flags & VQADATF_LDONE)) {
                    vqabuf->Flags |= (VQADATF_DDONE);
                }
            }
            drawer->Flags &= ~VQADRWF_STEP;
            drawer->Flags &= ~VQADRWF_REPAINT;
            drawer->Flags &= ~VQADRWF_FORCEDRAW;
        } else {
            rc = -14;
        }
        break;

    case VQAMODE_RUN:
    case VQAMODE_WALK:
    default:
        if (vqabuf->Flags & VQADATF_PAUSED) {
            vqabuf->Flags &= ~VQADATF_PAUSED;
            if (config->OptionFlags & VQAOPTF_AUDIO) {
                VQA_StartAudio((VQAHandleP *)vqabuf);
            }
            VQA_SetTimer((VQAHandleP *)vqabuf, ((VQAHandleP *)vqa)->EndTime);
        }

        while ((vqabuf->Flags & (VQADATF_DDONE | VQADATF_LDONE)) != (VQADATF_DDONE | VQADATF_LDONE)) {
            if (!(vqabuf->Flags & VQADATF_LDONE)) {
                if ((rc = VQA_LoadFrame(vqabuf, 0)) == -1) {
                    ((VQAHandleP *)vqa)->LoadedFrames++;
                } else {
                    if ((rc != -9) && (rc != -11)) {
                        vqabuf->Flags |= VQADATF_LDONE;
                    }
                }

                if (config->OptionFlags & VQAOPTF_WAITFILL) {
                    if (rc == -9 || (vqabuf->Flags & VQADATF_LDONE)) {
                        if (vqabuf->Flags & VQADATF_AUDIOSYNC) {
                            if (!(vqabuf->Flags & VQADATF_FRAMESTALL)) {
                                vqabuf->Flags |= VQADATF_REFILLED;
                                if (config->OptionFlags & VQAOPTF_AUDIO) {
                                    VQA_StartAudio(vqabuf);
                                }
                            }
                        }
                    } else if (!(vqabuf->Flags & VQADATF_LDONE)) {
                        if (vqabuf->Audio.Flags & VQAAUDF_ISSTARVED) {
                            if (vqabuf->Audio.Flags & VQAAUDF_ISPLAYING) {
                                VQA_PauseAudio(vqabuf);
                            }
                            vqabuf->Flags |= VQADATF_AUDIOSYNC;
                            audio->Flags &= ~VQAAUDF_ISSTARVED;
                        }
                    }
                }
            }

            if ((config->DrawFlags & VQACFGF_NODRAW) == 0) {
                if (vqabuf->Config.OptionFlags & VQAOPTF_WAITFILL) {
                    if (vqabuf->Flags & VQADATF_AUDIOSYNC) {
                        if (vqabuf->Flags & VQADATF_REFILLED) {
                            vqabuf->Flags &= ~VQADATF_AUDIOSYNC;
                            vqabuf->Flags &= ~VQADATF_REFILLED;
                        } else if ((vqabuf->Flags & VQADATF_FRAMESTALL) == 0) {
                            rc = -10;
                            break;
                        }
                    }
                }

                if (flags & VQAPLAYF_STEP) {
                    drawer->Flags |= VQADRWF_STEP;
                } else if (flags & VQAPLAYF_REPAINT) {
                    drawer->Flags |= VQADRWF_REPAINT;
                }

                if ((rc = ((VQAHandleP *)vqabuf)->Draw_Frame((VQAHandle *)vqabuf)) == -1) {
                    if (!(drawer->Flags & VQADRWF_HOLD)) {
                        ((VQAHandleP *)vqa)->DrawnFrames++;
                    }
                    if ((rc = User_Update((VQAHandle *)vqabuf)) != -1) {
                        vqabuf->Flags |= (VQADATF_DDONE | VQADATF_LDONE);
                    } else {
                        rc = drawer->LastFrameNum;
                    }
                } else {
                    if ((rc == -9) && (vqabuf->Flags & VQADATF_LDONE)) {
                        vqabuf->Flags |= VQADATF_DDONE;
                    }
                }
                drawer->Flags &= ~VQADRWF_STEP;
                drawer->Flags &= ~VQADRWF_REPAINT;
            } else {
                vqabuf->Flags |= VQADATF_DDONE;
                drawer->CurFrame->Flags = 0;
                drawer->CurFrame = drawer->CurFrame->Next;
            }

            if (mode == VQAMODE_WALK) {
                break;
            }
        }
        break;
    }

    if (((vqabuf->Flags & (VQADATF_DDONE | VQADATF_LDONE)) == (VQADATF_DDONE | VQADATF_LDONE))
        || (mode == VQAMODE_STOP)) {
        ((VQAHandleP *)vqa)->EndTime = VQA_GetTime((VQAHandleP *)vqabuf);
        if (vqabuf->Audio.Flags & VQAAUDF_ISPLAYING) {
            VQA_StopAudio((VQAHandleP *)vqabuf);
        }
        rc = -2;
    }
    return rc;
}
