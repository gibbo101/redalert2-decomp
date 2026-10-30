// long __fastcall VQA_SeekGroup(VQAHandleP *vqap, long framenum, long groupsize, bool preloadaudio, bool reset_state, bool &skipcodebook) -- 0x00779950
// Purpose: positions the loader at the codebook group holding a frame, rewinds the
// audio buffer for the preload and loads the frames up to the target
// (VQA_SeekLoop, a static helper expanded here, handles loop starts).
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"
// @ref ?VQA_LoadFrame@@YIJPAUVQAHandleP@@J@Z=00778680
// @ref ?VQA_GetCodebookFrameRange@@YIJPAUVQAHandleP@@JPAJ1@Z=0077ac00

static long VQA_SeekLoop(VQAHandleP *vqap, long framenum, long flags)
{
    long rc = -1;
    VQALoopCache *cache;
    bool needs_seek = false;
    long *foff;

    cache = &vqap->LoopCache;
    foff = vqap->Foff;
    if ((vqap->AltBufferFlags & VQAABUFF_ALTLOOP) && framenum == cache->Min && cache->Bytes != 0) {
        if ((long)cache->Buffer + cache->Bytes <= ((foff[vqap->LoopEndFrameMode2] & 0x0FFFFFFF) << 1)) {
            needs_seek = true;
        }
        cache->Offset = 0;
    } else if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 0, (foff[framenum] & 0x0FFFFFFF) << 1) != 0) {
        return -6;
    }
    if (framenum > 0 && (!(flags & 0x10) || !(vqap->Header.Flags & 0x10))) {
        rc = VQA_LoadFrame(vqap, flags | 2 | 4);
    }
    if (rc == -1) {
        if (needs_seek && vqap->Config.StreamHandler((VQAHandle *)vqap, 8, 0, (long)cache->Buffer + cache->Bytes) != 0) {
            return -6;
        }
    }
    return rc;
}

long __fastcall VQA_SeekGroup(VQAHandleP *vqap, long framenum, long groupsize, bool preloadaudio, bool reset_state, bool &skipcodebook)
{
    VQALoader *loader;
    VQADrawer *drawer;
    VQAHeader *header;
    VQAFrameNode *frame;
    VQACBNode *curcb;
    VQAConfig *config;
    long group;
    long i;
    VQAAudio *audio;
    int audpreload;
    int bytes_per_frame;
    int preload_frames;
    int covered_bytes;
    long rc;
    int loadflags;
    long group_end;
    long group_start;
    int group_index;
    int last_group_index;
    bool cb_valid;
    long audio_start;

    loader = &vqap->Loader;
    drawer = &vqap->Drawer;
    header = &vqap->Header;
    config = &vqap->Config;
    audio = &vqap->Audio;
    group_index = 0;
    frame = drawer->CurFrame;

    if (vqap->Foff) {
        group = framenum;
        if (config->NumCBBufs > 1) {
            cb_valid = false;
            if (groupsize > 0) {
                group_index = framenum / groupsize;
                group_start = group_index * groupsize;
                if (group_start >= groupsize) {
                    group_start -= groupsize;
                }
                if (group_index == 0) {
                    group_end = -1;
                } else {
                    group_end = group_start + groupsize - 1;
                }
                last_group_index = loader->LastFrameNum / groupsize;
            } else {
                group_index = VQA_GetCodebookFrameRange(vqap, framenum, &group_start, &group_end);
                last_group_index = VQA_GetCodebookFrameRange(vqap, loader->LastFrameNum, 0, 0);
            }
            group = group_start;
            if (!reset_state) {
                if (last_group_index == group_index) {
                    group = group_end + 1;
                    loader->FullCB = loader->PrevCB;
                    loader->CurCB = loader->FullCB->Next;
                    cb_valid = true;
                } else if (loader->NumPartialCB == 0) {
                    bool dont_set_cur = false;
                    curcb = loader->FullCB;
                    while (true) {
                        if (curcb == frame->Codebook && (frame->Flags & 1) != 0) {
                            dont_set_cur = true;
                            break;
                        }
                        frame = frame->Next;
                        if (drawer->CurFrame == frame) {
                            break;
                        }
                    }
                    if (!dont_set_cur) {
                        loader->CurCB = curcb;
                    }
                }
            } else {
                loader->FullCB = vqap->CBData;
                loader->CurCB = vqap->CBData;
            }
            loader->NumPartialCB = 0;
            loader->PartialCBSize = 0;
        } else {
            cb_valid = true;
            group_start = framenum;
            group_end = framenum;
        }
        skipcodebook = cb_valid;

        if ((config->OptionFlags & 1) && (audio->Buffer != 0)) {
            int bytes_per_sec = ((vqap->SampleRate * vqap->Channels) * (vqap->BitsPerSample >> 3));
            bytes_per_frame = bytes_per_sec / config->FrameRate;
            audpreload = header->AudioPreload;
            if ((header->Flags & 8) == 0 && audpreload == 0) {
                audpreload = (long)(bytes_per_sec / 2);
            }
            if (preloadaudio && audpreload > 0) {
                preload_frames = audpreload / bytes_per_frame;
                covered_bytes = bytes_per_frame * preload_frames;
                if (audpreload > covered_bytes) {
                    ++preload_frames;
                }
                audio_start = framenum - preload_frames;
                if (audio_start < 0) {
                    audio_start = 0;
                    audio->BufferOffset = framenum * bytes_per_frame;
                } else {
                    audio->BufferOffset = bytes_per_frame + covered_bytes - audpreload;
                }
                if (audio_start < group) {
                    group = audio_start;
                }
            } else {
                audio_start = framenum;
                audio->BufferOffset = 0;
            }
            if (reset_state) {
                memset(audio->IsLoaded, 0, audio->NumAudBlocks * sizeof(*audio->IsLoaded));
                memset(audio->Buffer, 0, config->AudioBufSize);
                audio->TempBufLen = 0;
                if (audio_start == 0) {
                    audio->AudBufPos = 0;
                } else {
                    audio->AudBufPos = audpreload;
                    int blocks = int(audio->AudBufPos / config->HMIBufSize);
                    for (i = 0; i < blocks; i++) {
                        audio->IsLoaded[i] = 1;
                    }
                }
            }
        } else {
            preloadaudio = false;
            audio_start = framenum;
            audio->BufferOffset = 0;
        }

        if (VQA_IsFrameStartOfLoop(vqap, framenum)) {
            if (reset_state) {
                loader->CurFrame->Flags = 0;
            }
            if (cb_valid) {
                loadflags = 0x10;
            } else {
                loadflags = 0;
                loader->FullCB = loader->CurCB;
            }
            rc = VQA_SeekLoop(vqap, framenum, loadflags);
            if (reset_state) {
                if (rc == -9 || rc == -11) {
                    rc = -1;
                }
            }
            return rc;
        }

        if (!config->StreamHandler((VQAHandle *)vqap, VQACMD_SEEK, 0, (vqap->Foff[group] & 0x0FFFFFFF) << 1)) {
            loader->CurFrameNum = group;
            rc = -1;
            loadflags = 1 | 4;
            if (group_index) {
                loadflags |= 0x10;
            }
            if (!preloadaudio) {
                loadflags |= 2;
            }
            long loadframe = loader->CurFrameNum;
            for (i = 0; i < (framenum - group); i++) {
                if (reset_state) {
                    loader->CurFrame->Flags &= ~1;
                }
                if (preloadaudio) {
                    if (reset_state) {
                        if (loadframe == audio_start) {
                            audio->TempBufLen = 0;
                        }
                    }
                    if (loadframe < audio_start) {
                        loadflags |= 2;
                    } else {
                        loadflags &= ~2;
                    }
                }
                if (cb_valid && loadframe <= group_end) {
                    loadflags |= 8;
                } else {
                    loadflags &= ~8;
                }
                rc = VQA_LoadFrame(vqap, loadflags);
                if (rc != -1) {
                    if (!reset_state || ((rc != -9) && (rc != -11))) {
                        break;
                    } else {
                        rc = -1;
                    }
                }
                loadframe++;
            }
        } else {
            return -6;
        }
        return rc;
    }
    return -6;
}
