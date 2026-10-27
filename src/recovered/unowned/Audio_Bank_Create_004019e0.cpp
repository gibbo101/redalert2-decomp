// AudioBank *__fastcall Audio_Bank_Create(AudioBag *bag, int bytes, int entries, int block) -- 0x004019E0 (ret 8)
// Purpose: makes a bank with a pool of bytes / (block + 0x1C) pieces of
// block + 0x1C bytes and one of entries entries of 0x64 bytes. Destroys it
// again (0x00401B00, expanded inline) and returns 0 when a pool cannot be
// made.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioBank *__fastcall Audio_Bank_Create(AudioBag *bag, int bytes, int entries, int block)
{
    AudioBank *bank = (AudioBank *)operator new(sizeof(AudioBank));
    memset(bank, 0, sizeof(AudioBank));
    bank->Bag = bag;
    bank->BlockSize = block;
    bank->Pieces = Audio_Pool_Create(bytes / (block + 0x1c), block + 0x1c);
    bank->Entries = Audio_Pool_Create(entries, 100);
    Audio_List_Init(&bank->List);
    if (bank->Pieces != 0 && bank->Entries != 0) {
        goto done;
    }
    Audio_Bank_Destroy(bank);
    bank = 0;
done:
    return bank;
}
