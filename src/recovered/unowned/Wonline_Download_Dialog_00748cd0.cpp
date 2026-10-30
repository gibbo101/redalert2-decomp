#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND window,UINT message,WPARAM wparam,LPARAM lparam);
void __fastcall Wait_Paint_005e5f20(HWND window);
extern bool connection_wait_callback_0073c120();
#include "shared/string_table.hpp"
extern char wol_source_file_007fd62c[];
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
extern char wol_download_failed_label_7fea0c[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Wait_Paint_005e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?wol_download_failed_label_7fea0c@@3PADA=007fea0c
long __stdcall Wonline_Download_Dialog_00748cd0(HWND window,unsigned message,unsigned wparam,long lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    switch(message) {
    case 0x111:
        switch(wparam & 0xffff) {
        case 2:
            unknown_download_a72d04->Abort();
            Unknown_007357E0(window,2);
            break;
        default: return 0;
        }
        break;
    case 0x110: break;
    case 0x5f4:
        Unknown_007357E0(window,1);
        break;
    case 0x5f5:
        Message_Box_005c3230(StringTable::Load_String(wol_download_failed_label_7fea0c,0,wol_source_file_007fd62c,0x32f3),0,connection_wait_callback_0073c120,false);
        unknown_download_a72d04->Abort();
        Unknown_007357E0(window,2);
        break;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x14: return 1;
    case 0xf:
        Unknown_005FEE70(window);
        Wait_Paint_005e5f20(window);
        ValidateRect(window,0);
        return 0;
    default: return 0;
    }
    return 1;
}
