// TextLabelClass *MessageListClass::Add_Edit(color, style, text, cursor, width) -- 0x005B5410
// Opens the edit line (an open one only takes the focus again). With AdjustEdit the edit line is the
// last row: the oldest message goes when the list is full, the messages move down a row and the list
// holds one message less.
// @ref ??0TextLabelClass@@QAE@PBGHHHI@Z=006f15c0
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/crt_memory.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern unsigned short const unknown_empty_wide_839d4c[];

TextLabelClass *MessageListClass::Add_Edit(int color, unsigned style, unsigned short const *text, char cursor, int width)
{
    if (IsEdit) {
        EditLabel->Set_Focus();
        return 0;
    }
    if (AdjustEdit) {
        int count = 0;
        for (TextLabelClass *node = First; node != 0; node = (TextLabelClass *)node->Get_Next()) {
            count++;
        }
        if (IsEdit && AdjustEdit) {
            count++;
        }
        if (count + 1 > MaxMessages) {
            TextLabelClass *oldest = First;
            First = (TextLabelClass *)oldest->Remove();
            for (int i = 0; i < 14; i++) {
                if (oldest->Text == Texts[i]) {
                    Slot_Free[i] = 1;
                }
            }
            delete oldest;
        }
    }
    if (text == 0) {
        text = unknown_empty_wide_839d4c;
    }
    EditCursor = cursor;
    memset(EditBuf, 0, sizeof(EditBuf));
    wcscpy(EditBuf, text);
    OverflowBuf[0] = 0;
    EditCurPos = EditInitPos = wcslen(text);
    EditLabel = new TextLabelClass(EditBuf, EditX, EditY, color, style | 0x8000);
    if (width > 0) {
        EditLabel->PixWidth = width;
    } else {
        EditLabel->PixWidth = TextWidth;
    }
    if (EditLabel) {
        IsEdit = true;
        EditLabel->Set_Focus();
    } else {
        IsEdit = false;
    }
    if (AdjustEdit) {
        Restack_Messages();
        MaxMessages--;
    }
    return EditLabel;
}
