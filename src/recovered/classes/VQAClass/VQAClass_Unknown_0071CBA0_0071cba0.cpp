// int VQAClass::Unknown_0071CBA0() (0x0071CBA0): the handle's first word, or -1.
#include "shared/movie.hpp"

int VQAClass::Unknown_0071CBA0()
{
    if (Handle != 0) {
        return Handle->unknown_00;
    }
    return -1;
}
