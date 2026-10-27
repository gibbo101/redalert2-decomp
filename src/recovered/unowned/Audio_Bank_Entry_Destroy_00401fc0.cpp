// void __fastcall Audio_Bank_Entry_Destroy(AudioBankEntry *entry) -- 0x00401FC0
// Purpose: unlinks the entry from its bank, gives its pieces back to the
// bank's piece pool and the entry to the entry pool.
#include "shared/audio.hpp"

void __fastcall Audio_Bank_Entry_Destroy(AudioBankEntry *entry)
{
    if (entry->Prev != entry) {
        Audio_List_Remove(entry);
    }
    AudioSourceInfo *piece;
    while ((piece = (AudioSourceInfo *)Audio_List_Next_Unchecked(&entry->Source.Pieces)) != 0) {
        Audio_List_Remove(piece);
        piece->Detach();
        Audio_Pool_Free(entry->Owner->Pieces, piece);
    }
    entry->Source.Finish();
    Audio_Pool_Free(entry->Owner->Entries, entry);
}
