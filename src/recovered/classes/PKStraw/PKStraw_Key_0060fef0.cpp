// PKStraw::Key(PKey const *key) (0x0060FEF0)
// Sets the key and restarts the key exchange.
#include "shared/pk_straw.hpp"

void PKStraw::Key(PKey const *key)
{
    CipherKey = key;
    if (key != 0) {
        IsGettingKey = true;
    }
    Counter = 0;
    BytesLeft = 0;
}
