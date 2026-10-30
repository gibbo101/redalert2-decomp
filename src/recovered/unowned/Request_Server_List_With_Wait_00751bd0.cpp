#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
int __fastcall Unknown_00751c30(unsigned int);
extern char server_list_wait_label_007fe670[];
extern char wol_source_file_007fd62c[];
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
// @ref ?Unknown_00751c30@@YIHI@Z=00751c30
// @ref ?server_list_wait_label_007fe670@@3PADA=007fe670
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
void __fastcall Request_Server_List_With_Wait_00751bd0()
{
    {
        WideString title(StringTable::Load_String(server_list_wait_label_007fe670,0,wol_source_file_007fd62c,0x56cc));
        Open_Wait_Window_0074d4d0(0x10,title,false);
    }
    unsigned int flags=0x2300;
    if(unknown_a3d2a4!=2) flags=0x2100;
    Unknown_00751c30(flags);
}
