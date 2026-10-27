// PKey::Decode_Modulus(void *buffer) (0x0060EDE0)
// Reads the modulus from its DER encoding and updates the precision.
// @ref ?XMP_Count_Bits@@YIHPBKH@Z=005a7cc0
// @ref ?XMP_DER_Decode@@YIXPAKPBEH@Z=005a76d0
#include "shared/pkey.hpp"

void PKey::Decode_Modulus(void *buffer)
{
    Modulus.DERDecode((unsigned char const *)buffer);
    BitPrecision = Modulus.BitCount() - 1;
}
