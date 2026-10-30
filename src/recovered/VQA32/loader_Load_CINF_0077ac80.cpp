// long __fastcall Load_CINF(VQAHandleP *vqap) -- 0x0077AC80
// Purpose: reads the CINH codebook header and, without a group size, the CIND table.
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"

static long Load_CINH(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&vqap->CodebookInfo.Header, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}
static long Load_CIND(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)vqap->CodebookInfo.Data, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}

long __fastcall Load_CINF(VQAHandleP *vqap)
{
    int groupsize;
    long size;
    unsigned long iffsize;
    VQAChunkHeader chunk;
    VQAConfig *config;

    config = &vqap->Config;
    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
        return -2;
    }
    if (chunk.ID != ID_CINH) {
        return -4;
    }
    iffsize = REVERSE_LONG(chunk.Size);
    if (Load_CINH(vqap, iffsize) != -1) {
        return -4;
    }
    groupsize = vqap->Header.Groupsize;
    if (groupsize == 0 && vqap->CodebookInfo.Header.Count > 0) {
        size = vqap->CodebookInfo.Header.Count * sizeof(VQACodebookInfo::DATA);
        vqap->CodebookInfo.Data = (VQACodebookInfo::DATA *)config->MemoryHandler((VQAHandle *)vqap, VQAMEM_ALLOC, 0, size);
        if (vqap->CodebookInfo.Data == 0) {
            return -8;
        }
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_LOCK, (int)vqap->CodebookInfo.Data, size);
        vqap->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
            return -2;
        }
        if (chunk.ID != ID_CIND) {
            return -4;
        }
        iffsize = REVERSE_LONG(chunk.Size);
        if (Load_CIND(vqap, iffsize) != -1) {
            return -4;
        }
    }
    return -1;
}
