#define DESCRIPTION_LIST_INLINE_GET_RECORD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/quoted_printable.hpp"
extern char unknown_decoded_buffer_00851570[];
// @ref ?unknown_decoded_buffer_00851570@@3PADA=00851570
char *__fastcall Quoted_Printable_Decode_0048df70(char const *input)
{
    char *output=unknown_decoded_buffer_00851570;
    while(*input) {
        if(*input=='=') {
            if(!input[1]) break;
            *output=Hex_Value_0048de80(input[1]);
            ++input;
            if(input[1]) {
                *output <<= 4;
                *output |= Hex_Value_0048de80(input[1]);
                ++input;
            }
        } else *output=*input;
        ++input;
        ++output;
    }
    *output=0;
    return unknown_decoded_buffer_00851570;
}
