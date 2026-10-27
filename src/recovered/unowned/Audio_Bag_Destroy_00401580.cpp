// void __fastcall Audio_Bag_Destroy(AudioBag *bag) -- 0x00401580
// Purpose: deletes the bag's files and entry table, then the bag.
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Bag_Destroy(AudioBag *bag)
{
    if (bag->BagFile != 0) {
        delete bag->BagFile;
    }
    if (bag->File != 0) {
        delete bag->File;
    }
    if (bag->Entries != 0) {
        operator delete(bag->Entries);
    }
    operator delete(bag);
}
