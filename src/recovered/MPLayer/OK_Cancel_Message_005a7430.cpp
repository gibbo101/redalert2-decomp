// int __fastcall OK_Cancel_Message_005A7430(unsigned short const *text) (0x005A7430)
// TibSun mplayer.cpp's Surrender_Dialog: an OK/Cancel message box; 1 when the player picks OK.
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BD@BMMN@D?3?2Ra2?2MPLayer?4CPP?$AA@=007e38fc

int __fastcall OK_Cancel_Message_005A7430(unsigned short const *text)
{
    return WWMessageBox(L" ").Process(text, StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\MPLayer.CPP", 0x6C),
        StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\MPLayer.CPP", 0x6C), 0, false) == 0;
}
