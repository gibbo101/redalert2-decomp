// void __fastcall Audio_Bank_Destroy(AudioBank *bank) -- 0x00401B00
// Purpose: destroys every entry of the bank (0x00401FC0, expanded inline),
// then its pools and the bank.
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Bank_Destroy(AudioBank *bank)
{
    AudioBankEntry *entry;
    while ((entry = (AudioBankEntry *)Audio_List_Next_Unchecked(&bank->List)) != 0) {
        Audio_Bank_Entry_Destroy(entry);
    }
    if (bank->Pieces != 0) {
        Audio_Pool_Destroy(bank->Pieces);
    }
    if (bank->Entries != 0) {
        Audio_Pool_Destroy(bank->Entries);
    }
    operator delete(bank);
}
