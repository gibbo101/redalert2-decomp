// unsigned short *MessageListClass::Get_Message(int identifier) -- 0x005B5160
// The text of the message with the identifier, or none (inlined everywhere in the unit).
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"

unsigned short *MessageListClass::Get_Message(int identifier)
{
    for (TextLabelClass *node = First; node != 0; node = (TextLabelClass *)node->Get_Next()) {
        if (node->UserData2 == identifier) {
            return (unsigned short *)node->Text;
        }
    }
    return 0;
}
