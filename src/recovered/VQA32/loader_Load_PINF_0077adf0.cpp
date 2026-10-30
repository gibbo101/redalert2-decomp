// long __fastcall Load_PINF(VQAHandleP *vqap) -- 0x0077ADF0
// Purpose: reads the PINH palette header and the PIND table.
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"

static long Load_PINH(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&vqap->PaletteInfo.Header, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}
static long Load_PIND(VQAHandleP *vqap, unsigned long iffsize)
{
    if (vqap->Config.StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)vqap->PaletteInfo.Data, PADSIZE(iffsize))) {
        return -4;
    }
    return -1;
}

long __fastcall Load_PINF(VQAHandleP *vqap)
{
    unsigned long iffsize;
    VQAChunkHeader chunk;
    VQAConfig *config;

    config = &vqap->Config;
    if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
        return -2;
    }
    if (chunk.ID != ID_PINH) {
        return -4;
    }
    iffsize = REVERSE_LONG(chunk.Size);
    if (Load_PINH(vqap, iffsize) != -1) {
        return -4;
    }
    if (vqap->PaletteInfo.Header.Count > 0) {
        long size = vqap->PaletteInfo.Header.Count * sizeof(VQAPaletteInfo::DATA);
        vqap->PaletteInfo.Data = (VQAPaletteInfo::DATA *)config->MemoryHandler((VQAHandle *)vqap, VQAMEM_ALLOC, 0, size);
        if (vqap->PaletteInfo.Data == 0) {
            return -8;
        }
        config->MemoryHandler((VQAHandle *)vqap, VQAMEM_LOCK, (int)vqap->PaletteInfo.Data, size);
        vqap->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)vqap, VQACMD_READ, (int)&chunk, sizeof(chunk))) {
            return -2;
        }
        if (chunk.ID != ID_PIND) {
            return -4;
        }
        iffsize = REVERSE_LONG(chunk.Size);
        if (Load_PIND(vqap, iffsize) != -1) {
            return -4;
        }
    }
    return -1;
}
