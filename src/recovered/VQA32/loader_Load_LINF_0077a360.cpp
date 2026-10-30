// long __fastcall Load_LINF(VQAHandleP *vqap) -- 0x0077A360
// Purpose: reads the LINH loop header and the LIND loop table.
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"

static long Load_LINH(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&vqap->LoopInfo.Header, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}
static long Load_LIND(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)vqap->LoopInfo.Data, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}

long __fastcall Load_LINF(VQAHandleP *vqap)
{
    unsigned long iffsize;
    VQAChunkHeader chunk;
    VQAConfig *config;

    config = &vqap->Config;
    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
        return -2;
    }
    if (chunk.ID != ID_LINH) {
        return -4;
    }
    iffsize = REVERSE_LONG(chunk.Size);
    if (Load_LINH(vqap, iffsize) != -1) {
        return -4;
    }
    if (vqap->LoopInfo.Header.Count > 0) {
        long size = vqap->LoopInfo.Header.Count * sizeof(VQALoopInfo::DATA);
        vqap->LoopInfo.Data = (VQALoopInfo::DATA *)config->MemoryHandler((VQAHandle *)vqap, VQAMEM_ALLOC, 0, size);
        if (vqap->LoopInfo.Data == 0) {
            return -8;
        }
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_LOCK, (int)vqap->LoopInfo.Data, size);
        vqap->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
            return -2;
        }
        if (chunk.ID != ID_LIND) {
            return -4;
        }
        size = REVERSE_LONG(chunk.Size);
        if (Load_LIND(vqap, size) != -1) {
            return -4;
        }
    }
    return -1;
}
