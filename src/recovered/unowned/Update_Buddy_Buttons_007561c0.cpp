#include "shared/wol_sink.hpp"
bool Can_Join_Selected_Buddy_00755ef0();
bool Selected_Buddy_Unavailable_00756140();
// @ref ?Can_Join_Selected_Buddy_00755ef0@@YA_NXZ=00755ef0
void __fastcall Update_Buddy_Buttons_007561c0(HWND dialog)
{
    EnableWindow(GetDlgItem(dialog,0x703),unknown_wstring_b29cd4.Length()>0);
    EnableWindow(GetDlgItem(dialog,0x62d),(unsigned char)Can_Join_Selected_Buddy_00755ef0());
    EnableWindow(GetDlgItem(dialog,0x5c2),(unsigned char)Selected_Buddy_Unavailable_00756140());
}
