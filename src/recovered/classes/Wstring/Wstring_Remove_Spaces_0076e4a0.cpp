// void Wstring::Remove_Spaces() (0x0076E4A0)
// Deletes all spaces and tabs.
#include "shared/wstring.hpp"

void Wstring::Remove_Spaces()
{
    Remove_Character(' ');
    Remove_Character('\t');
}
