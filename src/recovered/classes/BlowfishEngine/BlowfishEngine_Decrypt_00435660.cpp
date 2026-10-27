// BlowfishEngine::Decrypt(void const *cyphertext, int length, void *plaintext) (0x00435660)
// Decrypts length bytes of whole blocks; returns length.
// @ref ?_com_issue_error@@YGXJ@Z=00795940
#include "shared/blowfish_engine.hpp"

int BlowfishEngine::Decrypt(void const *cyphertext, int length, void *plaintext)
{
    Server()->Decrypt(length, (unsigned char const *)cyphertext, (unsigned char *)plaintext);
    return length;
}
