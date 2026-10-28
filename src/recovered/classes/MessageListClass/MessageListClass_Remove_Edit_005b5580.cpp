// void MessageListClass::Remove_Edit() -- 0x005B5580
// Closes the open edit line; with AdjustEdit the messages move back up and the list holds one more.
// @ref ?Unknown_00738100@@YAXXZ=00738100
#include "shared/message_list.hpp"

void MessageListClass::Remove_Edit()
{
    if (IsEdit) {
        IsEdit = false;
        delete EditLabel;
        Unknown_00738100();
        if (AdjustEdit) {
            Restack_Messages();
            MaxMessages++;
        }
    }
}
