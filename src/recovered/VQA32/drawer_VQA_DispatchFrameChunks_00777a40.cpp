// void __fastcall VQA_DispatchFrameChunks(VQAHandleP *vqap, long frame) -- 0x00777A40
// Purpose: hands every cached MFCI and MSCI chunk recorded for the frame to
// the client's event handler (chunk ID, buffer, size).
#include "shared/vqa_player.hpp"

void __fastcall VQA_DispatchFrameChunks(VQAHandleP *vqap, long frame)
{
    unsigned long chunkid;
    unsigned long count1;
    unsigned long count2;
    unsigned long i;
    unsigned long j;

    VQAMFCInfo *mfci_info = &vqap->MFCInfo;
    count1 = mfci_info->Header.Count;
    for (i = 0; i < count1; i++) {
        chunkid = mfci_info->Table[i].ChunkID;
        VQAChunkCache::DATA *mfci_data = mfci_info->Data2[i].Data;
        count2 = mfci_info->Data2[i].Count;
        for (j = 0; j < count2; j++) {
            if (mfci_data[j].Frame == frame) {
                vqap->Config.EventHandler((VQAHandle *)vqap, chunkid, (int)mfci_data[j].Buffer, mfci_data[j].Size);
            }
        }
    }

    VQAMSCInfo *msci_info = &vqap->MSCInfo;
    count1 = msci_info->Header.Count;
    for (i = 0; i < count1; i++) {
        chunkid = msci_info->Table[i].ChunkID;
        VQAChunkCache::DATA *msci_data = msci_info->Data2[i].Data;
        count2 = msci_info->Data2[i].Count;
        for (j = 0; j < count2; j++) {
            if (msci_data[j].Frame == frame) {
                vqap->Config.EventHandler((VQAHandle *)vqap, chunkid, (int)msci_data[j].Buffer, msci_data[j].Size);
            }
        }
    }
}
