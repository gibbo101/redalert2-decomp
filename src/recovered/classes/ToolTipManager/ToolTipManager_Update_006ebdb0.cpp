// bool ToolTipManager::Update() (0x006EBDB0; Tiberian Sun's Process)
// Prepares the tip under the mouse: its text (the string table label, or Get_Text(ID) without one) is
// copied into Record at the cursor and offered to Show; a tip without text, or one Show refuses, is
// dropped. True while a tip remains.
#define TOOL_TIP_UNIT
#include "shared/tool_tip.hpp"
// @ref ??_C@_0BD@LFLL@D?3?2Ra2?2ToolTip?4cpp?$AA@=007f859c

bool ToolTipManager::Update()
{
    ToolTip const *tip = Current;
    if (tip != 0) {
        wchar_t const *text = tip->Label == 0 ? Get_Text(tip->ID)
                                              : StringTable::Load_String(tip->Label, 0, "D:\\Ra2\\ToolTip.cpp", 0x233);
        if (text != 0 && wcslen(text) > 0) {
            wcsncpy(Record.Text, text, 256);
            Record.unknown_00 = Cursor.x;
            Record.unknown_04 = Cursor.y;
            ToolTipRecord &record = Record;
            if (!Show(&Record)) {
                record.unknown_00 = 0;
                record.unknown_04 = 0;
                record.unknown_08 = 0;
                record.unknown_0c = 0;
                Current = 0;
            }
        } else {
            Record.unknown_00 = 0;
            Record.unknown_04 = 0;
            Record.unknown_08 = 0;
            Record.unknown_0c = 0;
            Current = 0;
        }
    }
    return Current != 0;
}
