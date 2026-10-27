// PKey::PKey(void const *exponent, void const *modulus) (0x0060ED40)
// Builds a key from the DER encodings of its exponent and modulus.
// @ref ?XMP_Count_Bits@@YIHPBKH@Z=005a7cc0
// @ref ?XMP_DER_Decode@@YIXPAKPBEH@Z=005a76d0
// @ref ?XMP_Init@@YIXPAKKH@Z=005a7ca0
#include "shared/pkey.hpp"

PKey::PKey(void const *exponent, void const *modulus)
{
    Modulus.DERDecode((unsigned char const *)modulus);
    Exponent.DERDecode((unsigned char const *)exponent);
    BitPrecision = Modulus.BitCount() - 1;
}
