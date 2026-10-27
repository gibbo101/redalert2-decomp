// BlowStraw::Key(void const *key, int length) (0x00435930)
// Creates the Blowfish engine on first use and submits the key to it.
// @ref ??0BlowfishEngine@@QAE@XZ=00435580
// @ref ?Submit_Key@BlowfishEngine@@QAEXPBXH@Z=00435600
#include "shared/blow_straw.hpp"

void BlowStraw::Key(void const *key, int length)
{
    if (BF == 0) {
        BF = new BlowfishEngine;
    }
    if (BF != 0) {
        BF->Submit_Key(key, length);
    }
}
