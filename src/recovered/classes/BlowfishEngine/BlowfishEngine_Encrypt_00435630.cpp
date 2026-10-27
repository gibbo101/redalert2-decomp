// BlowfishEngine::Encrypt(void const *plaintext, int length, void *cyphertext) (0x00435630)
// Encrypts length bytes of whole blocks; returns length.
// @ref ?_com_issue_error@@YGXJ@Z=00795940
#include "shared/blowfish_engine.hpp"

int BlowfishEngine::Encrypt(void const *plaintext, int length, void *cyphertext)
{
    Server()->Encrypt(length, (unsigned char const *)plaintext, (unsigned char *)cyphertext);
    return length;
}
