// Quoted-printable conversion for campaign section names, using the shared output buffer.
#include "shared/crt_memory.hpp"
#include "shared/quoted_printable.hpp"
extern "C" int __cdecl isalnum(int);
extern char unknown_encoded_buffer_00851170[];
// @ref _isalnum=00782c31
// @ref ?unknown_encoded_buffer_00851170@@=00851170
char *__fastcall Quoted_Printable_Encode_0048dec0(char const *input)
{
    char const *cursor=input;
    int length;
    for(length=0; *cursor && length < 1021; ++length,++cursor) {
        if(!isalnum(*cursor)) {
            unknown_encoded_buffer_00851170[length] = '=';
            ++length;
            unknown_encoded_buffer_00851170[length] = Hex_Digit_0048de60(*cursor >> 4);
            ++length;
            unknown_encoded_buffer_00851170[length] = Hex_Digit_0048de60(*cursor & 15);
        } else unknown_encoded_buffer_00851170[length] = *cursor;
    }
    unknown_encoded_buffer_00851170[length]=0;
    return unknown_encoded_buffer_00851170;
}
