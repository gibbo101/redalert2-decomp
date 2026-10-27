// PKPipe::PKPipe(CryptControl control, RandomStraw &rnd) (0x0060FA90)
// The embedded Blowfish pipe works in the same direction; the key exchange
// starts with the first data.
#include "shared/pk_pipe.hpp"

PKPipe::PKPipe(CryptControl control, RandomStraw &rnd) :
    IsGettingKey(true),
    Rand(rnd),
    BF((control == ENCRYPT) ? BlowPipe::ENCRYPT : BlowPipe::DECRYPT),
    Control(control),
    CipherKey(0),
    Counter(0),
    BytesLeft(0)
{
}
