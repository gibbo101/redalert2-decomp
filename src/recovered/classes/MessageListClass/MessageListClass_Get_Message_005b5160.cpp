// unsigned short *MessageListClass::Get_Message(int identifier) -- 0x005B5160
// The text of the message with the identifier, or none (inlined everywhere in the unit).
#include "shared/message_list.hpp"

unsigned short *MessageListClass::Get_Message(int identifier)
{
    for (UnknownMessageNode *node = First; node != 0; node = node->Next()) {
        if (node->Identifier == identifier) {
            return node->Text;
        }
    }
    return 0;
}
