// bool __fastcall MixFileClass::Offset(char const *filename, void **realptr, MixFileClass **mixfile, (0x00595AA0)
// Locates a member by the CRC of its upper-cased name in every registered archive.
// @ref __strupr=007961e4
// @ref ?MixList@MixFileClass@@2V?$List@PAVMixFileClass@@@@A=00a70cc0
#include "shared/mix_file_class.hpp"

class CCFileClass;

bool __fastcall MixFileClass::Offset(char const *filename, void **realptr, MixFileClass **mixfile,
                                        long *offset, long *size)
{
    if (filename == 0) {
        return false;
    }

    // Note: upper-cases the caller's string in place.
    SubBlock key;
    key.ID = CRCEngine()(_strupr((char *)filename), strlen(filename));

    MixFileClass *ptr = MixList.First();
    while (ptr->Is_Valid()) {
        SubBlock *block = Binary_Search(ptr->HeaderBuffer, ptr->Count, key);
        if (block != 0) {
            if (mixfile != 0) {
                *mixfile = ptr;
            }
            if (size != 0) {
                *size = block->Size;
            }
            if (realptr != 0) {
                *realptr = 0;
            }
            if (offset != 0) {
                *offset = block->Offset;
            }
            if (realptr != 0 && ptr->Data != 0) {
                *realptr = (char *)ptr->Data + block->Offset;
            }
            if (ptr->Data == 0 && offset != 0) {
                *offset += ptr->DataStart;
            }
            return true;
        }
        ptr = ptr->Next();
    }
    return false;
}

