// HashString (unit 0x004E1130): the upper-cased 256-byte key of the colour scheme hash table.
#define RA2_HASH_STRING_UNIT
#include "shared/hash_string.hpp"
#include "shared/crt_string.hpp"
// @ref __strupr=007961e4

extern "C" char *__cdecl _strupr(char *string);

HashString::HashString()
{
    Text[0] = '\0';
}
