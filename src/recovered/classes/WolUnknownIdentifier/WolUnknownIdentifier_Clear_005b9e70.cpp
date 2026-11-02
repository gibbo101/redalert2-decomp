// Clears the shared online identifier after changing network settings.
#define WOL_IDENTIFIER_DECLARE_CLEAR
#include "shared/wol_chat.hpp"

void WolUnknownIdentifier::Clear_005b9e70()
{
    unknown_00 = 0;
}
