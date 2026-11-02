// void MessageListClass::Init(int x, int y, int max_messages, int max_chars, int unknown_arg5, int x2, int y2,
//     bool unknown_flag, int first, int last, int width) -- 0x005B4C60
// Deletes the messages, resets the list and stores the geometry (message and character limits clamped to 14
// and 112), the second position (or the first when either is -1) and the selection range.
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
// @ref ??_C@_0CD@CKH@MessageListClass?3?3Init?$CIWidth?3?5?$CFd@=007e5de8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0

void MessageListClass::Init(int x, int y, int max_messages, int max_chars, int unknown_arg5, int x2, int y2,
    bool unknown_flag, int first, int last, int width)
{
    TextWidth = width - 8;
    Debug_Printf("MessageListClass::Init(Width: %d)\n", width - 8);
    TextLabelClass *node = First;
    while (node) {
        First = (TextLabelClass *)node->Remove();
        if (node) {
            delete node;
        }
        node = First;
    }
    for (int i = 0; i < 7; i++) {
        unknown_1480[i] = 0x10001;
    }
    if (IsEdit) {
        if (EditLabel) {
            delete EditLabel;
        }
        EditLabel = 0;
    }
    First = 0;
    X = x;
    Y = y;
    MaxMessages = max_messages;
    if (max_messages > 14) {
        MaxMessages = 14;
    }
    MaxChars = max_chars;
    if (max_chars > 112) {
        MaxChars = 112;
    }
    Height = 19;
    unknown_18 = unknown_flag;
    IsEdit = false;
    if (x2 == -1 || y2 == -1) {
        AdjustEdit = true;
        EditX = x;
        EditY = y;
    } else {
        AdjustEdit = false;
        EditX = x2;
        EditY = y2;
    }
    EditLabel = 0;
    EditBuf[0] = 0;
    OverflowBuf[0] = 0;
    EditCurPos = 0;
    EditInitPos = 0;
    EditCursor = 0;
    Selection_First = first;
    Selection_Last = last;
    if (Selection_Last >= MaxChars) {
        Selection_Last = MaxChars - 1;
    }
    if (Selection_First >= Selection_Last) {
        Selection_First = Selection_Last - 1;
    }
}
