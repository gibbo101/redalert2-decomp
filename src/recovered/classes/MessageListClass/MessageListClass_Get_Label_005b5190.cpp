// UnknownMessageNode *MessageListClass::Get_Label(int identifier) -- 0x005B5190
// The message with the identifier, or none (inlined everywhere in the unit).
#include "shared/message_list.hpp"

UnknownMessageNode *MessageListClass::Get_Label(int identifier)
{
    for (UnknownMessageNode *node = First; node != 0; node = node->Next()) {
        if (node->Identifier == identifier) {
            return node;
        }
    }
    return 0;
}
