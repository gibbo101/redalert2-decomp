// PKey::Encode_Exponent(void *buffer) const (0x0060EDC0)
// Writes the DER encoding of the exponent; returns its size.
// @ref ?XMP_DER_Encode@@YIHPBKPAEH@Z=005a7610
#include "shared/pkey.hpp"

int PKey::Encode_Exponent(void *buffer) const
{
    if (buffer == 0) {
        return 0;
    }
    return Exponent.DEREncode((unsigned char *)buffer);
}
