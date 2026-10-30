// int __fastcall VQA_Unknown_0077B7A0(char const *filename, VQAConfig *_config, VQAHandle **handle) -- 0x0077B7A0
// Purpose: VQA_Open (TS): allocates and clears a private handle, copies the
// configuration (default memory and disk stream handlers), opens the
// stream, keeps the last 31 characters of the name, reads the FORM/WVQA
// header chunks up to FINF (VQHD, CINF, PINF, LINF, MFCI, MSCI, CLIP; others
// skipped), then resets playback, opens the audio, sizes the loop cache,
// sets the initial loop, configures the drawer and primes the buffers.
// Stores the handle and returns -1, else an error after closing.
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_string.hpp"
// @ref ?Lock_Audio_Handler@@YAHXZ=00412370
// @ref _VQA_sosCODECInitStream=00780560
// @ref ?Load_MFCI@@YIJPAUVQAHandleP@@@Z=0077a4c0
// @ref ?Load_MSCI@@YIJPAUVQAHandleP@@@Z=0077a940

int __fastcall VQA_Unknown_0077B7A0(char const *filename, VQAConfig *_config, VQAHandle **handle)
{
    VQAHandle *vqa;
    VQAHandleP *vqap;
    VQAHeader *header;
    VQAConfig *config;
    VQAChunkHeader chunk;
    bool done;

    *handle = 0;

    if (!_config) {
        return -17;
    }
    if (!_config->TimerCallback) {
        return -15;
    }
    if (_config->RefreshRate == 0) {
        return -16;
    }

    if (_config->MemoryHandler == 0) {
        vqa = (VQAHandle *)VQA_Memory_Handler(0, VQAMEM_ALLOC, 0, sizeof(VQAHandleP));
        if (vqa != 0) {
            VQA_Memory_Handler(vqa, VQAMEM_LOCK, (int)vqa, sizeof(VQAHandleP));
        } else {
            return -8;
        }
    } else {
        vqa = (VQAHandle *)_config->MemoryHandler(0, VQAMEM_ALLOC, 0, sizeof(VQAHandleP));
        if (vqa != 0) {
            _config->MemoryHandler(vqa, VQAMEM_LOCK, (int)vqa, sizeof(VQAHandleP));
        } else {
            return -8;
        }
    }

    vqap = (VQAHandleP *)vqa;
    memset(vqap, 0, sizeof(VQAHandleP));
    vqap->MemUsed = sizeof(VQAHandleP);
    memcpy(&vqap->Config, _config, sizeof(VQAConfig));
    config = &vqap->Config;

    if (config->MemoryHandler == 0) {
        config->MemoryHandler = VQA_Memory_Handler;
    }
    if (config->StreamHandler == 0) {
        config->StreamHandler = Disk_VQA_Stream_Handler;
    }

    header = &vqap->Header;

    if (config->StreamHandler(vqa, VQACMD_OPEN, (int)filename, 0)) {
        config->MemoryHandler(vqa, VQAMEM_UNLOCK, (int)vqa, sizeof(VQAHandleP));
        config->MemoryHandler(vqa, VQAMEM_FREE, (int)vqa, 0);
        return -3;
    }

    int pos = strlen(filename) - 31;
    if (pos < 0) pos = 0;
    strcpy(vqap->Filename, filename + pos);

    if (config->StreamHandler(vqa, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
        VQA_Unknown_0077BE70(vqa);
        return -4;
    }
    if ((chunk.ID != ID_FORM) || (chunk.Size == 0)) {
        VQA_Unknown_0077BE70(vqa);
        return -7;
    }
    if (config->StreamHandler(vqa, VQACMD_READ, (int)&chunk, sizeof(chunk.ID))) {
        VQA_Unknown_0077BE70(vqa);
        return -4;
    }
    if (chunk.ID != ID_WVQA) {
        VQA_Unknown_0077BE70(vqa);
        return -7;
    }

    done = 0;
    while (!done) {
        if (config->StreamHandler(vqa, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
            VQA_Unknown_0077BE70(vqa);
            return -4;
        }
        chunk.Size = REVERSE_LONG(chunk.Size);

        switch (chunk.ID) {
        case ID_VQHD:
            if (chunk.Size != sizeof(VQAHeader)) {
                VQA_Unknown_0077BE70(vqa);
                return -7;
            }
            if (config->StreamHandler(vqa, VQACMD_READ, (int)header, PADSIZE(chunk.Size))) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            vqap->Version = header->Version;
            vqap->NumFrames = header->Frames;
            vqap->ImageWidth = header->ImageWidth;
            vqap->ImageHeight = header->ImageHeight;
            vqap->ColorMode = header->ColorMode;
            vqap->FrameRate = header->FPS;
            if (config->FrameRate == -1) {
                config->FrameRate = header->FPS;
            }
            if (config->DrawRate == -1) {
                config->DrawRate = header->FPS;
            }
            if ((config->DrawRate == -1) || (config->DrawRate == 0)) {
                config->DrawRate = header->FPS;
            }
            if ((header->Version > VQAHD_VER1) && !(header->Flags & VQAHDF_ALTAUDIO)) {
                config->OptionFlags &= ~VQAOPTF_ALTAUDIO;
            }
            break;

        case ID_CLIP:
            if (Load_CLIP(vqap, chunk.Size) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        case ID_LINF:
            if (Load_LINF(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        case ID_MFCI:
            if (Load_MFCI(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        case ID_CINF:
            if (Load_CINF(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        case ID_PINF:
            if (Load_PINF(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        case ID_FINF:
            if (AllocBuffers(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -8;
            }
            if (Load_FINF(vqap, chunk.Size) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            done = true;
            break;

        case ID_MSCI:
            if (Load_MSCI(vqap) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -4;
            }
            break;

        default:
            if (config->StreamHandler(vqa, VQACMD_SEEK, 1, PADSIZE(chunk.Size))) {
                VQA_Unknown_0077BE70(vqa);
                return -6;
            }
            break;
        }
    }

    if (header->ColorMode == 0 && vqap->PaletteInfo.Header.Count == 0) {
        vqap->PaletteInfo.Header.Count = (unsigned short)VQA_NumFramesWithPalettes(vqap);
    }

    VQA_Unknown_0077C7D0((VQAHandle *)vqap);

    if ((header->Flags & VQAHDF_AUDIO) == 0) {
        config->OptionFlags &= ~VQAOPTF_AUDIO;
    }

    if (config->OptionFlags & VQAOPTF_AUDIO) {
        VQAAudio *audio;
        if (config->AudioHandler == 0) {
            VQA_Unknown_0077BE70(vqa);
            return -21;
        }
        audio = &vqap->Audio;
        if (config->OptionFlags & VQAOPTF_ALTAUDIO) {
            vqap->SampleRate = header->AltSampleRate;
            vqap->Channels = header->AltChannels;
            vqap->BitsPerSample = header->AltBitsPerSample;
        } else {
            vqap->SampleRate = header->SampleRate;
            vqap->Channels = header->Channels;
            vqap->BitsPerSample = header->BitsPerSample;
        }
        if (VQA_OpenAudio(vqap) != -1) {
            VQA_Unknown_0077BE70(vqa);
            return -13;
        }
        Lock_Audio_Handler();
        audio->Flags |= VQAAUDF_MEMLOCKED;
        VQA_sosCODECInitStream(&audio->ADPCM_Info);
    } else {
        if (config->AudioHandler != 0) {
            vqap->Config.AudioHandler(vqa, VQAAUDIO_INIT, 0, 0);
        }
    }

    if (config->OptionFlags & VQAOPTF_LOOPS) {
        if (config->OptionFlags & VQAOPTF_LOOPCACHE) {
            VQALoopInfo *info = &vqap->LoopInfo;
            if (info->Header.Count > 0) {
                long cached;
                long size;
                if (config->StreamHandler(vqa, VQACMD_SIZE, (int)&size, 0) != 0) {
                    size = 0;
                }
                VQALoopCache *cache = &vqap->LoopCache;
                cache->Size = VQA_LargestLoop(vqap, size);
                config->MemoryHandler(vqa, VQAMEM_QUERYSIZE, (int)&cached, 0);
                if (cached < 0) {
                    if (size > 0) {
                        cached = size;
                    } else {
                        cached = 0;
                    }
                }
                if (cache->Size > cached) {
                    cache->Size = cached;
                }
                if (cache->Size > 0) {
                    void *ptr = (void *)config->MemoryHandler(vqa, VQAMEM_ALLOC, 0, vqap->LoopCache.Size);
                    cache->Ptr = (char *)ptr;
                    if (ptr == 0) {
                        VQA_Unknown_0077BE70(vqa);
                        return -8;
                    }
                    config->MemoryHandler(vqa, VQAMEM_LOCK, (int)vqap->LoopCache.Ptr, vqap->LoopCache.Size);
                    vqap->AltBufferFlags |= VQAABUFF_ALTLOOP;
                    vqap->MemUsed += vqap->LoopCache.Size;
                    VQA_ResetCache(vqap);
                }
            }
        }

        if (config->InitialLoopID >= 0) {
            if (VQA_Unknown_0077C640(vqa, config->InitialLoopID, config->InitialLoopIterations, 2) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -23;
            }
        } else {
            if (VQA_Unknown_0077C6C0(vqa, 0, vqap->StopFrame, 0, 0) != -1) {
                VQA_Unknown_0077BE70(vqa);
                return -23;
            }
        }
    } else {
        vqap->LoopEndFrameMode2 = vqap->StopFrame;
    }

    if (VQA_Configure_Drawer(vqap) != -1) {
        return -3;
    }

    if (!(config->OptionFlags & VQAOPTF_LOOPS) || config->InitialLoopID < 0) {
        if (PrimeBuffers(vqap) != -1) {
            VQA_Unknown_0077BE70(vqa);
            return -4;
        }
    }

    *handle = vqa;
    return -1;
}
