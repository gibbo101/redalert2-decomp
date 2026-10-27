// PKey::Generate(Straw &random, int bits, PKey &fastkey, PKey &slowkey) (0x0060EE30)
// Makes an RSA key pair: two safe primes p and q, public exponent 65537
// (fastkey) and its inverse modulo (p-1)(q-1) (slowkey), both over n = pq.
// Repeats until a random test block survives an encrypt/decrypt round trip.
// Takes its first two arguments in ECX/EDX (__fastcall).
// @ref _rand=007846aa
// @ref __chkstk=00783850
// @ref ?Borrow@?$Int@$0EA@@@2_NA=00a417c5
// @ref ?Error@?$Int@$0EA@@@2HA=00a417c0
// @ref ?XMP_Compare@@YIHPBK0H@Z=005a7d40
// @ref ?XMP_Count_Bits@@YIHPBKH@Z=005a7cc0
// @ref ?XMP_Init@@YIXPAKKH@Z=005a7ca0
// @ref ?XMP_Is_Prime@@YI_NPBKH@Z=005aa380
// @ref ?XMP_Sub_Int@@YI_NPAKPBKG_NH@Z=005a7ec0
// @ref ?XMP_Unsigned_Mult@@YIHPAKPBK1H@Z=005a8340
#include "shared/pkey.hpp"
#include "shared/crt_memory.hpp"

extern "C" int __cdecl rand();

void __fastcall PKey::Generate(Straw &random, int bits, PKey &fastkey, PKey &slowkey)
{
    char plain[256];
    char crypt[256];

    do {
        BigInt p = Generate_Prime(random, bits, &p);
        BigInt q = Generate_Prime(random, bits, &q);
        BigInt e = 65537L;
        BigInt n = BigInt::Unsigned_Mult(p, q);
        BigInt pqmin = BigInt::Unsigned_Mult(p - (unsigned short)1, q - (unsigned short)1);
        BigInt d = e.Inverse(pqmin);

        fastkey.Exponent = e;
        fastkey.Modulus = n;
        fastkey.BitPrecision = n.BitCount() - 1;

        slowkey.Exponent = d;
        slowkey.Modulus = n;
        slowkey.BitPrecision = fastkey.BitPrecision;

        for (int index = 0; index < fastkey.Plain_Block_Size(); index++) {
            plain[index] = (char)rand();
        }
        fastkey.Encrypt(plain, fastkey.Plain_Block_Size(), crypt);
        slowkey.Decrypt(crypt, slowkey.Crypt_Block_Size(), crypt);
    } while (memcmp(plain, crypt, fastkey.Plain_Block_Size()) != 0);
}
