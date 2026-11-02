// int MessageListClass::Num_Messages() -- 0x005B5C30
// The number of messages; the edit line counts when it is the list's last row.
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"

int MessageListClass::Num_Messages()
{
    int count = 0;
    for (TextLabelClass *node = First; node != 0; node = (TextLabelClass *)node->Get_Next()) {
        count++;
    }
    if (IsEdit && AdjustEdit) {
        count++;
    }
    return count;
}
