// void MessageListClass::Set_Width(int width) -- 0x005B5C60
// The list's text width (8 less than the width) for the list, every message and the edit line.
// @ref ??_C@_0CB@JPBD@MessageListClass?3?3Set_Width?$CI?$CFd?$CJ?6@=007e5e10
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"

void MessageListClass::Set_Width(int width)
{
    width -= 8;
    TextWidth = width;
    Debug_Printf("MessageListClass::Set_Width(%d)\n", width);
    TextLabelClass *node = First;
    while (node != 0) {
        node->PixWidth = width;
        node = (TextLabelClass *)node->Get_Next();
    }
    if (IsEdit) {
        EditLabel->PixWidth = width;
    }
}
