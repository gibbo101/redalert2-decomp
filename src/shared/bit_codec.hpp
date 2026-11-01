// Bit-group codec after Bink.cpp (0x00430D20-0x00431015): a byte stream read and written one bit at a time
// (bit 0 first), and three converters that insert or drop a bit after every seventh (callers 0x00771621 and
// 0x00771720). Names are placeholders; the owning module is not identified.
#ifndef RA2_SHARED_BIT_CODEC_HPP
#define RA2_SHARED_BIT_CODEC_HPP

struct BitStreamType {
    unsigned char *Ptr;     // +0x00 current byte
    unsigned char Bit;      // +0x04 bit number in it (0-7)
};

bool __fastcall Bit_Read_Start(BitStreamType *stream, unsigned char *data);           // 0x00430D20 (returns bit 0)
bool __fastcall Bit_Read_Next(BitStreamType *stream);                                 // 0x00430D30
void __fastcall Bit_Write_Start(BitStreamType *stream, unsigned char *data, bool bit); // 0x00430D60
void __fastcall Bit_Write_Next(BitStreamType *stream, unsigned char bit);             // 0x00430D70

int __fastcall Bit_Expand_7(unsigned char const *source, unsigned char *dest, unsigned count);   // 0x00430DA0 (a set bit after every seventh)
unsigned __fastcall Bit_Compress_7(unsigned char const *source, unsigned char *dest, unsigned count);   // 0x00430E80 (drops every eighth bit)
unsigned __fastcall Bit_Compress_7_String(unsigned char const *source, unsigned short *dest, unsigned count);   // 0x00430F30 (to a wide string of at most count characters)

#endif
