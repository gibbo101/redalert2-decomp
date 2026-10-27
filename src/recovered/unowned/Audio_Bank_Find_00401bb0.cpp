// AudioBankEntry *__fastcall Audio_Bank_Find(AudioBank *bank, int id) -- 0x00401BB0
// Purpose: returns the bank's entry for the sound id that holds data, or 0.
#include "shared/audio.hpp"

AudioBankEntry *__fastcall Audio_Bank_Find(AudioBank *bank, int id)
{
    for (AudioBankEntry *entry = (AudioBankEntry *)bank->List.Next; entry != (AudioBankEntry *)&bank->List;
         entry = (AudioBankEntry *)entry->Next) {
        if (entry->Id == id && entry->Data != 0) {
            return entry;
        }
    }
    return 0;
}
