// BlowfishEngine::Submit_Key(void const *key, int length) (0x00435600)
// Passes the cipher key to the server.
// @ref ?_com_issue_error@@YGXJ@Z=00795940
#include "shared/blowfish_engine.hpp"

void BlowfishEngine::Submit_Key(void const *key, int length)
{
    Server()->Submit_Key(length, (unsigned char const *)key);
}
