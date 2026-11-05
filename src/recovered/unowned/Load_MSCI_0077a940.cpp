#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"

static long Load_MSCH(VQAHandleP *player, unsigned long size)
{
    if (player->Config.StreamHandler((VQAHandle *)player, VQACMD_READ,
            (int)&player->MSCInfo.Header, PADSIZE(size))) return -4;
    return -1;
}
static long Load_MSCT(VQAHandleP *player, unsigned long size)
{
    if (player->Config.StreamHandler((VQAHandle *)player, VQACMD_READ,
            (int)player->MSCInfo.Table, PADSIZE(size))) return -4;
    return -1;
}

static long VQA_MSCIPrepare(VQAHandleP *player, unsigned long index)
{
    VQAConfig *config = &player->Config;
    int slots = config->NumFrameBufs;
    VQAMSCInfo *info = &player->MSCInfo;
    VQAChunkCache *cache = info->Data2;
    VQAMSCInfo::TABLE *table = player->MSCInfo.Table;
    int entry_size = table[index].EntrySize;
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
        allocation_size = PADSIZE(entry_size) * slots;
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

long __fastcall Load_MSCI(VQAHandleP *player)
{
    VQAChunkHeader chunk;
    VQAConfig *config = &player->Config;
    long size;
    unsigned long count, iffsize;
    if (config->StreamHandler((VQAHandle *)player, VQACMD_READ, (int)&chunk, sizeof(chunk))) return -2;
    if (chunk.ID != ID_MSCH) return -4;
    iffsize = REVERSE_LONG(chunk.Size);
    if (Load_MSCH(player, iffsize) != -1) return -4;
    VQAMSCInfo::HEADER *header = &player->MSCInfo.Header;
    count = header->Count;
    if (count > 0) {
        size = count * sizeof(VQAMSCInfo::TABLE);
        player->MSCInfo.Table = (VQAMSCInfo::TABLE *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, size);
        if (!player->MSCInfo.Table) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)player->MSCInfo.Table, size);
        player->MemUsed += size;
        if (config->StreamHandler((VQAHandle *)player, VQACMD_READ, (int)&chunk, sizeof(chunk))) return -2;
        if (chunk.ID != ID_MSCT) return -4;
        size = REVERSE_LONG(chunk.Size);
        if (Load_MSCT(player, size) != -1) return -4;
    }
    count = header->Count;
    if (count > 0) {
        size = count * sizeof(VQAChunkCache);
        player->MSCInfo.Data2 = (VQAChunkCache *)config->MemoryHandler(
            (VQAHandle *)player, VQAMEM_ALLOC, 0, size);
        if (!player->MSCInfo.Data2) return -8;
        config->MemoryHandler((VQAHandle *)player, VQAMEM_LOCK, (int)player->MSCInfo.Data2, size);
        player->MemUsed += size;
        for (unsigned long entry = 0; entry < count; ++entry) {
            long result = VQA_MSCIPrepare(player, entry);
            if (result != -1) return result;
        }
    }
    return -1;
}
