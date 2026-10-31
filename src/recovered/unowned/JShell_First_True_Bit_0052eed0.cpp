// First_True_Bit (0x0052EED0): index of the first set bit (the array must hold one).
#include "shared/jshell.hpp"

int __fastcall First_True_Bit(void const *array)
{
    int index = 0;
    while (*((unsigned char *)array) == 0) {
        index++;
        array = ((char *)array) + 1;
    }

    int subindex;
    for (subindex = 0; subindex < 8; subindex++) {
        if (Get_Bit(array, subindex)) {
            break;
        }
    }
    return index * 8 + subindex;
}
