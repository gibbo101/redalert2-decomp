#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"

static long Load_MFCH(VQAHandleP *player, unsigned long size)
{
    if (player->Config.StreamHandler((VQAHandle *)player, VQACMD_READ,
            (int)&player->MFCInfo.Header, PADSIZE(size))) return -4;
    return -1;
}
static long Load_MFCD(VQAHandleP *player, unsigned long size)
{
    if (player->Config.StreamHandler((VQAHandle *)player, VQACMD_READ,
            (int)player->MFCInfo.StaticData, PADSIZE(size))) return -4;
    return -1;
}
static long Load_MFCT(VQAHandleP *player, unsigned long size)
{
    if (player->Config.StreamHandler((VQAHandle *)player, VQACMD_READ,
            (int)player->MFCInfo.Table, PADSIZE(size))) return -4;
    return -1;
}

static int VQA_MFCISpansLoop(VQAHandleP *player, unsigned long chunk_id, unsigned long interval)
{
    int distance_to_end = 0;
    int distance_from_start = 0;
    unsigned loop_count = player->LoopInfo.Header.Count;
    VQALoopInfo::DATA *loops = player->LoopInfo.Data;
    unsigned key_count = player->MFCInfo.Header.StaticCount;
    VQAMFCInfo::DATA *keys = player->MFCInfo.StaticData;
    for (unsigned loop = 0; loop < loop_count; ++loop) {
        unsigned short *loop_end = &loops[loop].EndFrame;
        distance_from_start = -1;
        for (unsigned key = 0; key < key_count; ++key) {
            if (keys[key].ChunkID == chunk_id) {
                unsigned frame = keys[key].KeyFrame;
                unsigned start = loop_end[-1];
                if (frame >= start) {
                    unsigned end = *loop_end;
                    if (frame > end) break;
                    if (distance_from_start < 0) {
                        distance_from_start = frame - start;
                        distance_to_end = end - frame;
                    } else {
                        distance_to_end = end - frame;
                    }
                }
            }
        }
        if (distance_from_start > 0 &&
                distance_from_start + distance_to_end + 1 < interval) return 1;
    }
    return 0;
}

static long VQA_MFCICalcCount(VQAHandleP *player, unsigned long chunk_id,
    long buffered_frames, unsigned long interval)
{
    if (!interval) return 0;
    long slots = (buffered_frames - 1) / interval + 1;
    if (VQA_MFCISpansLoop(player, chunk_id, interval)) ++slots;
    return slots;
}

static long VQA_MFCIPrepare(VQAHandleP *player, unsigned long index)
{
    VQAConfig *config = &player->Config;
    VQAMFCInfo *info = &player->MFCInfo;
    VQAMFCInfo::TABLE *table = player->MFCInfo.Table;
    VQAChunkCache *cache = info->Data2;
    int entry_size = table[index].EntrySize;
    int slots = VQA_MFCICalcCount(player, table[index].ChunkID, config->NumFrameBufs, table[index].FrameInterval);
    if (slots > 0) {
        cache[index].Count = slots;
        cache[index].WriteIndex = 0;
        unsigned long allocation_size = sizeof(VQAChunkCache::DATA) * slots;
        VQAChunkCache::DATA *records = (VQAChunkCache::DATA *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, allocation_size);
        if (!records) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)records, allocation_size);
        player->MemUsed += allocation_size;
        cache[index].Data = records;
        allocation_size = slots * PADSIZE(entry_size);
        char *storage = (char *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, allocation_size);
        if (!storage) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)storage, allocation_size);
        player->MemUsed += allocation_size;
        for (int slot = 0; slot < slots; ++slot) {
            cache[index].Data[slot].Buffer = storage;
            cache[index].Data[slot].Frame = -1;
            storage += entry_size;
        }
    }
    return -1;
}

long __fastcall Load_MFCI(VQAHandleP *player)
{
    VQAChunkHeader chunk;
    VQAConfig *config = &player->Config;
    long size;
    unsigned long count, iffsize;
    if (config->StreamHandler((VQAHandle *)player, VQACMD_READ, (int)&chunk, sizeof(chunk))) return -2;
    if (chunk.ID != ID_MFCH) return -4;
    iffsize = REVERSE_LONG(chunk.Size);
    if (Load_MFCH(player, iffsize) != -1) return -4;
    count = player->MFCInfo.Header.StaticCount;
    if (count > 0) {
        size = count * sizeof(VQAMFCInfo::DATA);
        player->MFCInfo.StaticData = (VQAMFCInfo::DATA *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, size);
        if (!player->MFCInfo.StaticData) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)player->MFCInfo.StaticData, size);
        player->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)player, VQACMD_READ, (int)&chunk, sizeof(chunk))) return -2;
        if (chunk.ID != ID_MFCD) return -4;
        size = REVERSE_LONG(chunk.Size);
        if (Load_MFCD(player, size) != -1) return -4;
    }
    count = player->MFCInfo.Header.Count;
    if (count > 0) {
        size = count * sizeof(VQAMFCInfo::TABLE);
        player->MFCInfo.Table = (VQAMFCInfo::TABLE *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, size);
        if (!player->MFCInfo.Table) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)player->MFCInfo.Table, size);
        player->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)player, VQACMD_READ, (int)&chunk, sizeof(chunk))) return -2;
        if (chunk.ID != ID_MFCT) return -4;
        size = REVERSE_LONG(chunk.Size);
        if (Load_MFCT(player, size) != -1) return -4;
    }
    count = player->MFCInfo.Header.Count;
    if (count > 0) {
        size = count * sizeof(VQAChunkCache);
        player->MFCInfo.Data2 = (VQAChunkCache *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, size);
        if (!player->MFCInfo.Data2) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)player->MFCInfo.Data2, size);
        player->MemUsed += size;
        for (unsigned long entry = 0; entry < count; ++entry) {
            long result = VQA_MFCIPrepare(player, entry);
            if (result != -1) return result;
        }
    }
    return -1;
}
