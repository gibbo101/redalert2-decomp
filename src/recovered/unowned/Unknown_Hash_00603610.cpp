// int __fastcall Unknown_Hash_00603610(HashString const &key) (0x00603610): the scheme table's hash,
// (c + hash * 26) % 31 over the key's text.
#define RA2_HASH_STRING_UNIT
#include "shared/scheme_table.hpp"

int __fastcall Unknown_Hash_00603610(HashString const &key)
{
    char const *text = key.Text;
    int hash = 0;
    for (char c = *text; c != '\0'; c = *++text) {
        hash = (c + hash * 26) % 31;
    }
    return hash;
}
