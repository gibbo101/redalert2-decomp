// int NullModemConnClass::Compute_CRC(char *buf, int buflen) (0x005CDC80)
// The rotating checksum of the data: each step doubles the sum, adds back
// its top bit and adds the next byte. Send expands it inline.
#include "shared/null_modem.hpp"

int __fastcall NullModemConnClass::Compute_CRC(char *buf, int buflen)
{
    unsigned int sum = 0;
    unsigned int hibit;
    for (int index = 0; index < buflen; index++) {
        if (sum & 0x80000000) {
            hibit = 1;
        } else {
            hibit = 0;
        }
        sum <<= 1;
        sum += hibit;
        sum += (unsigned char)buf[index];
    }
    return (int)sum;
}
