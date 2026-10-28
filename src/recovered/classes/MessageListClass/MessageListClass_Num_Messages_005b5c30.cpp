// int MessageListClass::Num_Messages() -- 0x005B5C30
// The number of messages; the edit line counts when it is the list's last row.
#include "shared/message_list.hpp"

int MessageListClass::Num_Messages()
{
    int count = 0;
    for (UnknownMessageNode *node = First; node != 0; node = node->Next()) {
        count++;
    }
    if (IsEdit && AdjustEdit) {
        count++;
    }
    return count;
}
