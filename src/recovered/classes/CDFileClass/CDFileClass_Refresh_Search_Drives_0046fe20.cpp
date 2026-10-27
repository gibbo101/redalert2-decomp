// void __fastcall CDFileClass::Refresh_Search_Drives() (0x0046FE20)
// Rebuilds the search list from every path list given so far.
#include "shared/cd_file_class.hpp"

void __fastcall CDFileClass::Refresh_Search_Drives()
{
    Clear_Search_Drives();
    Set_Search_Drives(RawPath);
}
