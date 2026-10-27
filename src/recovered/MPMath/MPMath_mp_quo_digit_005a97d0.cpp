// mp_quo_digit(unsigned short const *dividend) (0x005A97D0)
// Estimates the next 16-bit quotient digit from the top three dividend
// units and the prepared reciprocal (never too small; at most 0xFFFF).
#include "shared/mpmath.hpp"

unsigned short __fastcall mp_quo_digit(unsigned short const *dividend)
{
    unsigned long q, q0, q1, q2;

    q1 = (((unsigned short)~dividend[-2]) + 1) * (unsigned long)upton_reciph;
    q2 = ((unsigned short)~dividend[-1]) * (unsigned long)upton_recipl + 0x10000L;
    q0 = (q1 >> 1) + (q2 >> 1) + 1;

    q1 = ((unsigned short)~dividend[0]) * (unsigned long)upton_recipl;
    q2 = ((unsigned short)~dividend[-1]) * (unsigned long)upton_reciph;
    q = ((unsigned short)~dividend[0]) * (unsigned long)upton_reciph;
    q0 = (q0 >> 16) + (q1 >> 1) + (q2 >> 1) + 1;
    q = (q0 >> 14) + (q << 1);
    q >>= upton_mshift;
    if (q >= 0xFFFF) {
        q = 0xFFFF;
    }
    return (unsigned short)q;
}
