// void __fastcall Unknown_005c28e0() (0x005C28E0)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_0BI@MKML@GUI?3HostGameStartJoiner?$AA@=007e6d78

void __fastcall Unknown_005c28e0()
{
    HWND dialog = Unknown_00735B10();
    HWND item = GetDlgItem(dialog, 0x59F);
    if (Unknown_Find_Player_By_Name_005bcc60(0) != 1) {
        SendMessageA(item, 0x4DC, 0, 1);
        Unknown_005C2C80(-1, StringTable::Load_String("GUI:HostGameStartJoiner", 0, "D:\\Ra2\\netdlg2.cpp", 4958));
    }
}
