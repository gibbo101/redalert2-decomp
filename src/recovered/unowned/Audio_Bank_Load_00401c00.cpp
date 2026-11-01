// AudioBankEntry *Audio_Bank_Load(AudioBank *bank, int id) (0x00401C00)
// Returns the bank's entry for sound id, reading it from the bag when it is
// not cached: moves a cached entry to the head of the list; otherwise opens
// the sound in the bag, takes an entry (evicting the oldest unused one when
// the pool is empty) and reads the sound into pieces of the bank's block
// size, evicting entries while the piece pool is empty. Returns 0 when the
// sound cannot be opened or read.
// @ref ?Audio_Bag_Open@@YIHPAUAudioBag@@H@Z=004016f0
// @ref ?Audio_Bag_Read@@YIHPAUAudioBag@@PAXH@Z=004018c0
#include "shared/audio.hpp"

AudioBankEntry *__fastcall Audio_Bank_Load(AudioBank *bank, int id)
{
    AudioBankEntry *entry = Audio_Bank_Find(bank, id);
    if (entry != 0) {
        Audio_List_Remove(entry);
        Audio_List_Add_Head(&bank->List, entry);
        return entry;
    }
    if (Audio_Bag_Open(bank->Bag, id)) {
        entry = (AudioBankEntry *)Audio_Pool_Alloc(bank->Entries);
        if (entry == 0) {
            Audio_Bank_Evict(bank);
            entry = (AudioBankEntry *)Audio_Pool_Alloc(bank->Entries);
            if (entry == 0) {
                Audio_Bag_Close(bank->Bag);
                return 0;
            }
        }
        entry->Id = id;
        entry->Owner = bank;
        Audio_List_Init_Node(entry);
        entry->unknown_0c = 0;
        Audio_Source_Reset(&entry->Source);
        Audio_Format_Init(&entry->Format);
        entry->Source.Format = &entry->Format;
        int remaining = bank->Bag->Remaining;
        for (;;) {
            if (remaining == 0) {
                Audio_Bag_Get_Format(bank->Bag, entry->Id, &entry->Format);
                Audio_List_Add_Head(&bank->List, entry);
                entry->Data = (void *)1;
                Audio_Bag_Close(bank->Bag);
                return entry;
            }
            int size = bank->BlockSize;
            if (size > remaining) {
                size = remaining;
            }
            AudioSourceInfo *piece = (AudioSourceInfo *)Audio_Pool_Alloc(bank->Pieces);
            while (piece == 0) {
                if (!Audio_Bank_Evict(bank)) {
                    goto failed;
                }
                piece = (AudioSourceInfo *)Audio_Pool_Alloc(bank->Pieces);
            }
            piece->Init((char *)piece + 0x1c, size);
            Audio_Source_Add_Piece(&entry->Source, piece);
            int read = Audio_Bag_Read(bank->Bag, (char *)piece + 0x1c, size);
            if (read != size) {
                break;
            }
            remaining -= read;
        }
failed:
        Audio_Bank_Entry_Destroy(entry);
    }
    return 0;
}
