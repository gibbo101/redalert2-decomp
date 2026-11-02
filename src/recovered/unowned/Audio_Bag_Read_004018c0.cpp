// int __fastcall Audio_Bag_Read(AudioBag *bag, void *buffer, int length) -- 0x004018C0
// Purpose: read up to length bytes of the open entry (clamped to what is left) into buffer; returns the bytes read.
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_Bag_Read(AudioBag *bag, void *buffer, int length)
{
    if (bag->Reader == 0) {
        return 0;
    }
    if (length > bag->Remaining) {
        length = bag->Remaining;
    }
    int read = length > 0 ? bag->Reader->Read(buffer, length) : 0;
    if (read < 0) {
        read = 0;
    }
    bag->Remaining -= read;
    return read;
}
