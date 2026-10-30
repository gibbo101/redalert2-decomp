// long __fastcall VQA_LoadFrame(VQAHandleP *vqap, long flags) -- 0x00778680
// Purpose: loads the next frame; while a loop is cached (OptionFlags 0x20, AltBufferFlags
// ALTLOOP) it fills the loop cache and reads the frame through the memory stream
// handler, and at a loop start it marks the current codebook full.
#include "shared/vqa_player.hpp"
// @ref ?VQA_LoadFrame_Internal@@YIJPAUVQAHandleP@@J@Z=00778950
// @ref ?Memory_VQA_Stream_Handler@@YAHPAUVQAHandle@@HHH@Z=007785b0

long __fastcall VQA_LoadFrame(VQAHandleP *vqap, long flags)
{
    VQAConfig *config;
    VQALoader *loader;
    VQALoopCache *cache;
    int frame;
    int loop_bytes;
    int scan_frame;
    int tocache;
    long rc;
    int fsize;
    VQACallback oldhandler;
    bool restore_handler;

    oldhandler = 0;
    long foffset = 0;
    config = &vqap->Config;
    loader = &vqap->Loader;
    long *foff = vqap->Foff;
    frame = loader->CurFrameNum;
    restore_handler = false;

    if ((config->OptionFlags & 0x20) && (vqap->AltBufferFlags & VQAABUFF_ALTLOOP) && vqap->LoopID >= 0) {
        if (frame < vqap->NumFrames) {
            foffset = (foff[frame] & 0x0FFFFFFF) << 1;
        }
        cache = &vqap->LoopCache;
        if (frame == vqap->LoopStartFrame0 && vqap->LoopID != cache->ID) {
            if (frame != cache->Min) {
                cache->Buffer = (char *)foffset;
                cache->Bytes = 0;
                cache->Offset = 0;
            }
            cache->ID = vqap->LoopID;
            cache->Min = vqap->LoopStartFrame0;
            cache->Max = -1;
            loop_bytes = 0;
            for (scan_frame = vqap->LoopStartFrame0; scan_frame <= vqap->LoopEndFrameMode2; scan_frame++) {
                if (scan_frame < vqap->NumFrames - 1) {
                    loop_bytes += ((foff[scan_frame + 1] & 0x0FFFFFFF) << 1) - ((foff[scan_frame] & 0x0FFFFFFF) << 1);
                } else {
                    if (config->StreamHandler((VQAHandle *)vqap, 9, (int)&fsize, 0)) {
                        cache->Max = scan_frame - 1;
                        break;
                    }
                    loop_bytes += fsize - ((foff[vqap->LoopEndFrameMode2] & 0x0FFFFFFF) << 1);
                }
                if (loop_bytes >= cache->Size) {
                    cache->Max = scan_frame - 1;
                    break;
                }
            }
            if (loop_bytes < cache->Size && cache->Max == -1) {
                cache->Max = vqap->LoopEndFrameMode2;
            }
        }
        if (frame >= cache->Min && frame <= cache->Max) {
            if (foffset == (long)cache->Buffer + cache->Bytes) {
                if (frame < vqap->NumFrames - 1) {
                    tocache = ((foff[frame + 1] & 0x0FFFFFFF) << 1) - foffset;
                } else {
                    if (!config->StreamHandler((VQAHandle *)vqap, 9, (int)&fsize, 0)) {
                        tocache = fsize - foffset;
                    } else {
                        tocache = 0;
                    }
                }
                if (tocache > 0) {
                    if (config->StreamHandler != Memory_VQA_Stream_Handler) {
                        config->StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 0, foffset);
                    }
                    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&cache->Ptr[cache->Offset], tocache)) {
                        return -4;
                    }
                    cache->Bytes += tocache;
                }
            }
            if (foffset < (long)cache->Buffer + cache->Bytes) {
                restore_handler = true;
                cache->Offset = foffset - (long)cache->Buffer;
                oldhandler = config->StreamHandler;
                config->StreamHandler = Memory_VQA_Stream_Handler;
            }
        }
    }

    if (VQA_IsFrameStartOfLoop(vqap, frame)) {
        if ((flags & 0x20) == 0) {
            vqap->Loader.FullCB = vqap->Loader.CurCB;
        }
    }

    rc = VQA_LoadFrame_Internal(vqap, flags);

    if (restore_handler) {
        config->StreamHandler = oldhandler;
    }
    return rc;
}
