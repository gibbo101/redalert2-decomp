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
            int y;
            if (IsEdit) {
                y = Height + Y;
            } else {
                y = Y;
            }
            UnknownMessageNode *node = First;
            while (node != 0) {
                node->Y = y;
                node = node->Next();
                y += Height;
            }
            MaxMessages++;
        }
    }
}
