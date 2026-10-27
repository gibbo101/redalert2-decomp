// PKey::Decode_Exponent(void *buffer) (0x0060EE10)
// Reads the exponent from its DER encoding.
// @ref ?XMP_DER_Decode@@YIXPAKPBEH@Z=005a76d0
#include "shared/pkey.hpp"

void PKey::Decode_Exponent(void *buffer)
{
    Exponent.DERDecode((unsigned char const *)buffer);
}
