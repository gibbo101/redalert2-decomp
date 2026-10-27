// int __fastcall Audio_Bank_Evict(AudioBank *bank) -- 0x00401EF0
// Purpose: destroys the last entry of the bank that is not in use
// (0x00401FC0, expanded inline). Returns 1, or 0 when every entry is in use.
#include "shared/audio.hpp"

int __fastcall Audio_Bank_Evict(AudioBank *bank)
{
    AudioBankEntry *entry = (AudioBankEntry *)Audio_List_Last(&bank->List);
    while (entry != 0) {
        if (entry->unknown_0c == 0) {
            Audio_Bank_Entry_Destroy(entry);
            return 1;
        }
        entry = (AudioBankEntry *)Audio_List_Last(entry);
    }
    return 0;
}
