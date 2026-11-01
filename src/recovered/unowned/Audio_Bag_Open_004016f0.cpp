// int Audio_Bag_Open(AudioBag *bag, int index) (0x004016F0)
// Makes entry index the one Audio_Bag_Read reads: closes the loose file of
// the previous entry, seeks the bag file to the entry (the result is 0 when
// the seek fails or the entry is empty). With loose files (bag->Loose) the
// entry is read from <directory><name>.wav instead when that file opens and
// has a wave header: the entry takes the file's format and data size and
// the result is 1; otherwise the loose file is deleted again.
// @ref ??_C@_04MPDF@?4wav?$AA@=007cc960
#include "shared/crt_string.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);

int __fastcall Audio_Bag_Open(AudioBag *bag, int index)
{
    int result = 1;
    AudioFormat format;
    int size;
    char name[0x104];
    AudioBagEntry *entry = &bag->Entries[index];
    Audio_Bag_Close(bag);
    bag->Reader = bag->BagFile;
    bag->Remaining = entry->Size;
    if (bag->BagFile->Seek(entry->Offset, 0) != entry->Offset) {
        result = 0;
    }
    if (entry->Size == 0) {
        result = 0;
    }
    if (bag->Loose) {
        strcpy(name, bag->Path);
        strcat(name, entry->Name);
        strcat(name, ".wav");
        FileClass *file = new RawFileClass(name);
        bag->File = file;
        if (file->Is_Available(0) && file->Open(1)) {
            Audio_Format_Init(&format);
            if (Audio_Format_Read_Wave(file, &format, &size)) {
                entry->Flags = 2;
                if (format.BytesPerSample == 2) {
                    entry->Flags = 6;
                }
                if (format.Channels == 2) {
                    entry->Flags |= AUDIO_BAG_STEREO;
                }
                entry->Rate = format.Rate;
                bag->Remaining = size;
                bag->Reader = bag->File;
                return 1;
            }
        }
        if (bag->File != 0) {
            delete bag->File;
            bag->File = 0;
        }
    }
    return result;
}
