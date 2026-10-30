// INIClass::Get_PKey (0x00510370)
// Reads an RSA key stored by Put_PKey. The fast key's exponent is the known
// constant 65537, DER encoded here instead of read from [PrivateKey].
#include "shared/ini_class.hpp"
#include "shared/pkey.hpp"
// @ref ??_C@_09BCJE@PublicKey?$AA@=007db4ec
// @ref ??_C@_0L@PBJO@PrivateKey?$AA@=007db4e0

PKey INIClass::Get_PKey(bool fast) const
{
    PKey key;
    char buffer[512];

    if (fast) {
        BigInt exponent(0x10001);
        exponent.DEREncode((unsigned char *)buffer);
        key.Decode_Exponent(buffer);
    } else {
        Get_UUBlock("PrivateKey", buffer, sizeof(buffer));
        key.Decode_Exponent(buffer);
    }

    Get_UUBlock("PublicKey", buffer, sizeof(buffer));
    key.Decode_Modulus(buffer);

    return key;
}
