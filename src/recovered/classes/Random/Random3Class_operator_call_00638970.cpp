// Random3Class::operator()() (0x00638970)
// Mixes the seed with the next counter value through four rounds of the
// psdes function.
// @ref ?Mix1@Random3Class@@0PAKA=007ee4ac
// @ref ?Mix2@Random3Class@@0PAKA=007ee4fc
#include "shared/random.hpp"

int Random3Class::operator()()
{
    int loword = Seed;
    int hiword = Index++;
    for (int i = 0; i < 4; i++) {
        int hihold = hiword;
        int temp = hihold ^ Mix1[i];
        int itmpl = temp & 0xFFFF;
        int itmph = temp >> 16;
        temp = itmpl * itmpl + ~(itmph * itmph);
        temp = (temp >> 16) | (temp << 16);
        hiword = loword ^ ((temp ^ Mix2[i]) + itmpl * itmph);
        loword = hihold;
    }
    return hiword;
}
