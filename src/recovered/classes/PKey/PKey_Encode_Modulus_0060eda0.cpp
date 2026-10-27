// PKey::Encode_Modulus(void *buffer) const (0x0060EDA0)
// Writes the DER encoding of the modulus; returns its size.
// @ref ?XMP_DER_Encode@@YIHPBKPAEH@Z=005a7610
#include "shared/pkey.hpp"

int PKey::Encode_Modulus(void *buffer) const
{
    if (buffer == 0) {
        return 0;
    }
    return Modulus.DEREncode((unsigned char *)buffer);
}
