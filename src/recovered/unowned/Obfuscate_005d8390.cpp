// long __fastcall Obfuscate(char const *string) (0x005D8390)
// Westwood's string obfuscation (TibSun obscure.cpp): a scrambled CRC of the
// upper-cased, padded string. Parse_Command_Line 0x00515110 hashes its
// command-line switches with it.
#include "shared/ini_class.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_string.hpp"
// @ref __strrev=00797070
// @ref _?_addbits@?BG@??Obfuscate@@YIJPBD@Z@4PAEA=007e823c
// @ref _?_lossbits@?BG@??Obfuscate@@YIJPBD@Z@4PAEA=007e8234

extern "C" char *__cdecl _strupr(char *string);
extern "C" char *__cdecl _strrev(char *string);
extern "C" int __cdecl isgraph(int c);

long __fastcall Obfuscate(char const *string)
{
    char buffer[128];

    if (!string) {
        return 0;
    }

    memset(buffer, '\xA5', sizeof(buffer));
    strncpy(buffer, string, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';
    int length = strlen(buffer);

    _strupr(buffer);

    for (int index = 0; index < length; index++) {
        if (!isgraph(buffer[index])) {
            buffer[index] = (char)('A' + (index % 26));
        }
    }

    if (length < 16 || (length & 0x03)) {
        int maxlen = 16;
        if (((length + 3) & 0x00FC) > maxlen) {
            maxlen = ((length + 3) & 0x00FC);
        }
        int pad;
        for (pad = length; pad < maxlen; pad++) {
            buffer[pad] = (char)('A' + ((('?' ^ buffer[pad - length]) + pad) % 26));
        }
        length = pad;
        buffer[length] = '\0';
    }

    long code = CRCEngine()(buffer, length);
    long copy = code;
    _strrev(buffer);
    code ^= CRCEngine()(buffer, length);
    code = code ^ copy;
    _strrev(buffer);

    for (int index2 = 0; index2 < length; index2++) {
        code ^= (unsigned char)buffer[index2];
        unsigned char low = (unsigned char)code;
        buffer[index2] ^= low;
        code >>= 8;
        code |= (((long)low) << 24);
    }

    for (int index3 = 0; index3 < length; index3++) {
        static unsigned char _lossbits[] = {0x00, 0x08, 0x00, 0x20, 0x00, 0x04, 0x10, 0x00};
        static unsigned char _addbits[] = {0x10, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x04};
        buffer[index3] |= _addbits[index3 % (sizeof(_addbits) / sizeof(_addbits[0]))];
        buffer[index3] &= (char)(~_lossbits[index3 % (sizeof(_lossbits) / sizeof(_lossbits[0]))]);
    }

    for (int index4 = 0; index4 < length; index4 += 4) {
        short key1 = buffer[index4];
        short key2 = buffer[index4 + 1];
        short key3 = buffer[index4 + 2];
        short key4 = buffer[index4 + 3];
        short val1 = key1;
        short val2 = key2;
        short val3 = key3;
        short val4 = key4;
        val1 *= key1;
        val2 += key2;
        val3 += key3;
        val4 *= key4;
        short s3 = val3;
        val3 ^= val1;
        val3 *= key1;
        short s2 = val2;
        val2 ^= val4;
        val2 += val3;
        val2 *= key3;
        val3 += val2;
        val1 ^= val2;
        val4 ^= val3;
        val2 ^= s3;
        val3 ^= s2;
        buffer[index4] = (char)val1;
        buffer[index4 + 1] = (char)val2;
        buffer[index4 + 2] = (char)val3;
        buffer[index4 + 3] = (char)val4;
    }

    code = CRCEngine()(buffer, length);
    return code;
}
