#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
WideString __fastcall User_List_Description_0073f250(WOL::User const &user);
extern char user_list_empty_label_007ea8e4[];
extern char wol_source_file_007fd62c[];
// @ref ?User_List_Description_0073f250@@YI?AVWideString@@ABUUser@WOL@@@Z=0073f250
// @ref ?user_list_empty_label_007ea8e4@@3PADA=007ea8e4
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
WideString __fastcall User_List_Row_Text_0073f850(HWND list,int row)
{
    if(row==-1) return WideString(StringTable::Load_String(user_list_empty_label_007ea8e4,0,wol_source_file_007fd62c,0xae1));
    int index=SendMessageA(list,0x199,row,0);
    if(index>=0 && index<unknown_users_b2a728.Count) {
        WOL::User user;
        memset(&user,0,sizeof(user));
        user=unknown_users_b2a728.Items[index];
        return User_List_Description_0073f250(user);
    }
    return WideString(StringTable::Load_String(user_list_empty_label_007ea8e4,0,wol_source_file_007fd62c,0xae6));
}
