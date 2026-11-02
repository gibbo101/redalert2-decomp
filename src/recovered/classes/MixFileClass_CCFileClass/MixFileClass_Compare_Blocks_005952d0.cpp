// int MixFileClass::Compare_Blocks(void const *left, void const *right) (0x005952D0)
// qsort/bsearch order of SubBlock records: signed compare of the CRCs.
#include "shared/mix_file_class.hpp"

class CCFileClass;

int MixFileClass::Compare_Blocks(void const *left, void const *right)
{
    if (*(long const *)left < *(long const *)right) {
        return -1;
    }
    return *(long const *)left > *(long const *)right;
}
