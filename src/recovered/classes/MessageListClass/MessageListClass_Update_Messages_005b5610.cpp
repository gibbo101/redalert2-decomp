// int MessageListClass::Update_Messages() (0x005B5610)
// Drops every message whose time has come (freeing its text slot), and when any went restacks the rest from the top.
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/message_gadget_layout.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980

int MessageListClass::Update_Messages()
{
    int removed = 0;
    TextLabelClass *node = First;
    if (node != 0) {
        do {
            if (node->UserData1 != 0 && TickCount.Time() > node->UserData1) {
                TextLabelClass *next = (TextLabelClass *)node->Get_Next();
                First = (TextLabelClass *)node->Remove();
                for (int i = 0; i < 14; i++) {
                    if (node->Text == Texts[i]) {
                        Slot_Free[i] = 1;
                    }
                }
                if (node != 0) {
                    delete node;
                }
                removed = 1;
                node = next;
            } else {
                node = (TextLabelClass *)node->Get_Next();
            }
        } while (node != 0);
        if (removed != 0) {
            int y;
            if (IsEdit && AdjustEdit) {
                y = Height + Y;
            } else {
                y = Y;
            }
            node = First;
            while (node != 0) {
                node->Y = y;
                node = (TextLabelClass *)node->Get_Next();
                y += Height;
            }
        }
    }
    return removed;
}
