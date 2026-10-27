// PKey::Encrypt(void const *source, int length, void *dest) const (0x0060F520)
// Raises each whole plaintext block to the exponent modulo the modulus;
// returns the cyphertext bytes written.
// @ref ?Error@?$Int@$0EA@@@2HA=00a417c0
// @ref ?XMP_Exponent_Mod@@YIHPAKPBK11H@Z=005a9860
// @ref ?XMP_Init@@YIXPAKKH@Z=005a7ca0
#include "shared/pkey.hpp"
#include "shared/crt_string.hpp"

int PKey::Encrypt(void const *source, int length, void *dest) const
{
    int total = 0;

    while (length >= Plain_Block_Size()) {
        BigInt temp = 0;
        memmove(&temp, source, Plain_Block_Size());
        temp = temp.exp_b_mod_c(Exponent, Modulus);

        memmove(dest, &temp, Crypt_Block_Size());
        length -= Plain_Block_Size();
        source = (char const *)source + Plain_Block_Size();
        dest = (char *)dest + Crypt_Block_Size();
        total += Crypt_Block_Size();
    }

    return total;
}
