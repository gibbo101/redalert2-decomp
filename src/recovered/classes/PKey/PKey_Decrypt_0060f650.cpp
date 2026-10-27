// PKey::Decrypt(void const *source, int length, void *dest) const (0x0060F650)
// Raises each whole cyphertext block to the exponent modulo the modulus;
// returns the plaintext bytes written.
// @ref ?Error@?$Int@$0EA@@@2HA=00a417c0
// @ref ?XMP_Exponent_Mod@@YIHPAKPBK11H@Z=005a9860
// @ref ?XMP_Init@@YIXPAKKH@Z=005a7ca0
#include "shared/pkey.hpp"
#include "shared/crt_string.hpp"

int PKey::Decrypt(void const *source, int length, void *dest) const
{
    int total = 0;
    BigInt temp;

    while (length >= Crypt_Block_Size()) {
        temp = 0;
        memmove(&temp, source, Crypt_Block_Size());
        temp = temp.exp_b_mod_c(Exponent, Modulus);

        memmove(dest, &temp, Plain_Block_Size());
        length -= Crypt_Block_Size();
        source = (char const *)source + Crypt_Block_Size();
        dest = (char *)dest + Plain_Block_Size();
        total += Plain_Block_Size();
    }

    return total;
}
