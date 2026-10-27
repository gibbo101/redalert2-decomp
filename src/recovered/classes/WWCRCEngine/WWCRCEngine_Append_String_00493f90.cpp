#include "shared/wwcrc_engine.hpp"
extern "C" unsigned int __cdecl strlen(char const *string);
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
void WWCRCEngine::operator()(char const *string)
{
    if (string) (*this)(string, strlen(string));
}
