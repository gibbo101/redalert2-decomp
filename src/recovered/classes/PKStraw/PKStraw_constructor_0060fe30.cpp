// PKStraw::PKStraw(CryptControl control, RandomStraw &rnd) (0x0060FE30)
// The embedded Blowfish straw works in the same direction and is the
// straw this one draws from; the key exchange starts with the first data.
#include "shared/pk_straw.hpp"

PKStraw::PKStraw(CryptControl control, RandomStraw &rnd) :
    IsGettingKey(true),
    Rand(rnd),
    BF((control == ENCRYPT) ? BlowStraw::ENCRYPT : BlowStraw::DECRYPT),
    Control(control),
    CipherKey(0),
    Counter(0),
    BytesLeft(0)
{
    Get_From(BF);
}
