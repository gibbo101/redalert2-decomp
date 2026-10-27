// unsigned char *unknown_fill_buffer_498160(int value) (0x00498160)
// Clears the unit's 16-byte buffer, fills its last five bytes with value
// and returns it.
#include "shared/text_print.hpp"
// @ref ?unknown_buffer_852480@@3PAEA=00852480

unsigned char *__fastcall unknown_fill_buffer_498160(int value)
{
    memset(unknown_buffer_852480, 0, 16);
    memset(unknown_buffer_852480 + 11, value, 5);
    return unknown_buffer_852480;
}
