// TextLabelClass *MessageListClass::Get_Label(int identifier) -- 0x005B5190
// The message with the identifier, or none (inlined everywhere in the unit).
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"

TextLabelClass *MessageListClass::Get_Label(int identifier)
{
    for (TextLabelClass *node = First; node != 0; node = (TextLabelClass *)node->Get_Next()) {
        if (node->UserData2 == identifier) {
            return node;
        }
    }
    return 0;
}
