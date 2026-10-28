// int MessageListClass::Update_Messages() (0x005B5610)
// Drops every message whose time has come (freeing its text slot), and when any went restacks the rest from the top.
#include "shared/message_list.hpp"
#include "shared/message_gadget_layout.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980

int MessageListClass::Update_Messages()
{
    int removed = 0;
    UnknownMessageNode *node = First;
    if (node != 0) {
        do {
            if (node->Expires != 0 && TickCount.Time() > node->Expires) {
                UnknownMessageNode *next = node->Next();
                First = node->Remove();
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
                node = node->Next();
            }
        } while (node != 0);
        if (removed != 0) {
            int y;
            if (unknown_19 && unknown_1a) {
                y = Height + Y;
            } else {
                y = Y;
            }
            node = First;
            while (node != 0) {
                node->Y = y;
                node = node->Next();
                y += Height;
            }
        }
    }
    return removed;
}
