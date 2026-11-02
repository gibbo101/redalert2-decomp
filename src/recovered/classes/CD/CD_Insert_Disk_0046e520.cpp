// @ref ??_C@_0BA@BICN@TXT_CD_DIALOG_S?$AA@=007d2104
// @ref ??_C@_0BA@EFJK@TXT_CD_DIALOG_2?$AA@=007d20e4
// @ref ??_C@_0BA@LKCD@TXT_CD_DIALOG_1?$AA@=007d2124
// @ref ??_C@_0BA@OEHD@TXT_CD_DIALOG_A?$AA@=007d2114
// @ref ??_C@_0O@BMBI@D?3?2Ra2?2CD?4CPP?$AA@=007d2134
// @ref ??_C@_0O@IIEK@TXT_DISK_NAME?$AA@=007d20f4
// @ref ?Unknown_00600C80@@YI_NPBG@Z=00600c80
// CD prompt handling, complete original 0x0046E520 body.
#include "shared/cd.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"

bool CD::Insert_Disk(int disk)
{
    wchar_t prompt[256];
    wchar_t name[128];
    if (disk == -1) {
        swprintf(prompt, StringTable::Load_String("TXT_CD_DIALOG_1", 0, "D:\\Ra2\\CD.CPP", 0x92));
    } else if (disk == 0) {
        swprintf(prompt, StringTable::Load_String("TXT_CD_DIALOG_A", 0, "D:\\Ra2\\CD.CPP", 0x97));
    } else if (disk == 1) {
        swprintf(prompt, StringTable::Load_String("TXT_CD_DIALOG_S", 0, "D:\\Ra2\\CD.CPP", 0x9C));
    } else {
        swprintf(name, StringTable::Load_String("TXT_DISK_NAME", 0, "D:\\Ra2\\CD.CPP", 0xA0), disk + 1);
        swprintf(prompt, StringTable::Load_String("TXT_CD_DIALOG_2", 0, "D:\\Ra2\\CD.CPP", 0xA1), disk + 1, name);
    }
    if (LastTheme == THEME_NONE) LastTheme = Theme.What_Is_Playing();
    Theme.Stop();
    int hidden = WWMouse->Get_Mouse_State() < 0;
    while (WWMouse->Get_Mouse_State() < 0) WWMouse->Show_Mouse();
    WWKeyboard->Clear();
    bool result = true;
    if (disk == 0) {
        if (!Unknown_00600C80(StringTable::Load_String("TXT_CD_DIALOG_A", 0, "D:\\Ra2\\CD.CPP", 0xC2))) result = false;
    } else if (disk == 1) {
        if (!Unknown_00600C80(StringTable::Load_String("TXT_CD_DIALOG_S", 0, "D:\\Ra2\\CD.CPP", 0xCA))) result = false;
    } else {
        if (!Unknown_00600C80(StringTable::Load_String("TXT_CD_DIALOG_1", 0, "D:\\Ra2\\CD.CPP", 0xD1))) result = false;
    }
    WWKeyboard->Clear();
    while (hidden--) WWMouse->Hide_Mouse();
    if (!result && LastTheme != THEME_NONE) {
        Theme.Queue_Song(LastTheme);
        LastTheme = THEME_NONE;
    }
    return result;
}
