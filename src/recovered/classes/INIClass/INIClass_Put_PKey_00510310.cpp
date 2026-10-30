// INIClass::Put_PKey (0x00510310)
// Stores an RSA key: the DER modulus as [PublicKey] and the DER exponent as
// [PrivateKey], each uuencoded.
#include "shared/ini_class.hpp"
#include "shared/pkey.hpp"
// @ref ??_C@_09BCJE@PublicKey?$AA@=007db4ec
// @ref ??_C@_0L@PBJO@PrivateKey?$AA@=007db4e0

bool INIClass::Put_PKey(PKey const &key)
{
    char buffer[512];

    int length = key.Encode_Modulus(buffer);
    Put_UUBlock("PublicKey", buffer, length);

    length = key.Encode_Exponent(buffer);
    Put_UUBlock("PrivateKey", buffer, length);
    return true;
}
