// Packed compression header read by 004953B0 and decoded by 0053AEB0.
#ifndef RA2_SHARED_COMPRESSED_FILE_HPP
#define RA2_SHARED_COMPRESSED_FILE_HPP
#include "shared/raw_file_class.hpp"
#include "shared/buffer.hpp"
#pragma pack(push, 1)
struct CompressedFileHeader {
    unsigned char Type;
    unsigned char unknown_01;
    unsigned long DecodedBytes;
    short ExtraBytes;
};
#pragma pack(pop)
typedef char CompressedFileHeader_size_check[sizeof(CompressedFileHeader) == 8 ? 1 : -1];
unsigned long __fastcall Unknown_Uncompress_Data_0053aeb0(void const *source, void *destination);
int __fastcall Load_Compressed_Data_004953b0(FileClass &file, Buffer const &scratch,
    Buffer const &output, void *extra);
#endif
