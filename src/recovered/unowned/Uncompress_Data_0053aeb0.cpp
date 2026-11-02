// unsigned long Unknown_Uncompress_Data_0053aeb0(void const *, void *) (0x0053AEB0)
// Westwood's Uncompress_Data (TibSun load.cpp): decodes a block that starts
// with a CompressedFileHeader; returns the decoded size.
// @ref ?LCW_Uncomp@@YIHPBXPAXK@Z=00534b50
// @ref _memmove=00783290
#include "shared/compressed_file.hpp"
#include "shared/lcw.hpp"
#include "shared/crt_memory.hpp"

unsigned long __fastcall Unknown_Uncompress_Data_0053aeb0(void const *source, void *destination)
{
    unsigned int skip;
    int method;
    unsigned long size = 0;

    if (!source || !destination) return 0;

    size = ((CompressedFileHeader const *)source)->DecodedBytes;
    skip = ((CompressedFileHeader const *)source)->ExtraBytes;
    method = ((CompressedFileHeader const *)source)->Type;
    source = ((char const *)source) + (int)sizeof(CompressedFileHeader) + (int)skip;

    switch (method) {
    default:
    case 0:
        memmove(destination, (void *)source, size);
        break;
    case 3:
        break;
    case 4:
        LCW_Uncomp((void *)source, (void *)destination, (unsigned int)size);
        break;
    }
    return size;
}
