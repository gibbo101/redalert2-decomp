// void __fastcall FreeBuffers(VQAHandleP *vqap) -- 0x00777190
// Purpose: unlocks and frees every buffer the player allocated: the loop
// cache, the frame offset table, the audio buffers, the frame and codebook
// node lists (and their alternative buffers), the palette and codebook
// info tables and the MSCI/MFCI chunk caches and tables.
#include "shared/vqa_player.hpp"

void __fastcall FreeBuffers(VQAHandleP *vqap)
{
    VQAConfig *config = &vqap->Config;
    VQAHeader *header = &vqap->Header;
    VQAAudio *audio = &vqap->Audio;

    if (vqap->LoopCache.Ptr != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->LoopCache.Ptr, vqap->LoopCache.Size);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->LoopCache.Ptr, 0);
    }
    if (vqap->Foff != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->Foff, header->Frames * sizeof(*vqap->Foff));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->Foff, 0);
    }
    if (config->AudioBuf == 0 && audio->Buffer != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)audio->Buffer, config->AudioBufSize);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)audio->Buffer, 0);
    }
    if (audio->IsLoaded != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)audio->IsLoaded, audio->NumAudBlocks * sizeof(*audio->IsLoaded));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)audio->IsLoaded, 0);
    }
    if (audio->BlockRepeats != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)audio->BlockRepeats, audio->NumAudBlocks * sizeof(*audio->BlockRepeats));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)audio->BlockRepeats, 0);
    }
    if (audio->TempBuf != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)audio->TempBuf, audio->TempBufSize);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)audio->TempBuf, 0);
    }
    if (audio->HMIBuffer != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)audio->HMIBuffer, config->HMIBufSize);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)audio->HMIBuffer, 0);
    }

    VQAFrameNode *frame_this = vqap->FrameData;
    for (int i = 0; i < config->NumFrameBufs; i++) {
        if (frame_this == 0) {
            break;
        }
        VQAFrameNode *frame_next = frame_this->Next;
        vqap->Max_Pal_Size += 4;
        vqap->Max_Ptr_Size += 4;
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)frame_this,
                              sizeof(VQAFrameNode) + vqap->Max_Ptr_Size + vqap->Max_Pal_Size);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)frame_this, 0);
        frame_this = frame_next;
    }
    if (vqap->AltBufferFlags & VQAABUFF_ALTPTR) {
        if (vqap->AltPtrBuffer != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->AltPtrBuffer, vqap->PtrBufferSize);
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->AltPtrBuffer, 0);
            vqap->AltPtrBuffer = 0;
        }
    }

    VQACBNode *cb_this = vqap->CBData;
    for (int j = 0; j < config->NumCBBufs; j++) {
        if (cb_this == 0) {
            break;
        }
        VQACBNode *cb_next = cb_this->Next;
        vqap->Max_CB_Size += 4;
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)cb_this, sizeof(VQACBNode) + vqap->Max_CB_Size);
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)cb_this, 0);
        cb_this = cb_next;
    }
    if (vqap->AltBufferFlags & VQAABUFF_ALTCB) {
        if (vqap->AltCBBuffer != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->AltCBBuffer, vqap->CBBufferSize);
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->AltCBBuffer, 0);
            vqap->AltCBBuffer = 0;
        }
    }

    if (vqap->PaletteInfo.Data != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->PaletteInfo.Data,
                              vqap->PaletteInfo.Header.Count * sizeof(*vqap->PaletteInfo.Data));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->PaletteInfo.Data, 0);
    }
    if (vqap->CodebookInfo.Data != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->CodebookInfo.Data,
                              vqap->CodebookInfo.Header.Count * sizeof(*vqap->CodebookInfo.Data));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->CodebookInfo.Data, 0);
    }

    {
    unsigned long tablecount = vqap->MSCInfo.Header.Count;
    unsigned long k;
    for (k = 0; k < tablecount; k++) {
        unsigned long count = vqap->MSCInfo.Data2[k].Count;
        VQAChunkCache::DATA *data = vqap->MSCInfo.Data2[k].Data;
        char *buffer = data->Buffer;
        if (buffer != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)buffer, count * PADSIZE(vqap->MSCInfo.Table[k].EntrySize));
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)buffer, 0);
        }
        if (data != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)data, count * sizeof(*data));
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)data, 0);
        }
    }
    if (vqap->MSCInfo.Data2 != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->MSCInfo.Data2, tablecount * sizeof(*vqap->MSCInfo.Data2));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->MSCInfo.Data2, 0);
    }
    if (vqap->MSCInfo.Table != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->MSCInfo.Table, tablecount * sizeof(*vqap->MSCInfo.Table));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->MSCInfo.Table, 0);
    }

    }
    {
    unsigned long tablecount = vqap->MFCInfo.Header.Count;
    unsigned long k;
    for (k = 0; k < tablecount; k++) {
        unsigned long count = vqap->MFCInfo.Data2[k].Count;
        VQAChunkCache::DATA *data = vqap->MFCInfo.Data2[k].Data;
        char *buffer = data->Buffer;
        if (buffer != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)buffer, count * PADSIZE(vqap->MFCInfo.Table[k].EntrySize));
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)buffer, 0);
        }
        if (data != 0) {
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)data, count * sizeof(*data));
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)data, 0);
        }
    }
    if (vqap->MFCInfo.Data2 != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->MFCInfo.Data2, tablecount * sizeof(*vqap->MFCInfo.Data2));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->MFCInfo.Data2, 0);
    }
    if (vqap->MFCInfo.Table != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->MFCInfo.Table, tablecount * sizeof(*vqap->MFCInfo.Table));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->MFCInfo.Table, 0);
    }
    }
    if (vqap->MFCInfo.StaticData != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->MFCInfo.StaticData,
                              vqap->MFCInfo.Header.StaticCount * sizeof(*vqap->MFCInfo.StaticData));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->MFCInfo.StaticData, 0);
    }
    if (vqap->LoopInfo.Data != 0) {
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_UNLOCK, (int)vqap->LoopInfo.Data,
                              vqap->LoopInfo.Header.Count * sizeof(*vqap->LoopInfo.Data));
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_FREE, (int)vqap->LoopInfo.Data, 0);
    }
}
