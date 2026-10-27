// void __fastcall Audio_Bag_Close(AudioBag *bag) -- 0x00401910
// Purpose: forgets the entry being read and deletes the loose file that
// held it.
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

void __fastcall Audio_Bag_Close(AudioBag *bag)
{
    bag->Reader = 0;
    if (bag->File != 0) {
        delete bag->File;
        bag->File = 0;
    }
}
