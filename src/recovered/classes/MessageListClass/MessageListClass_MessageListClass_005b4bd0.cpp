// MessageListClass::MessageListClass() -- 0x005B4BD0
// Clears the list, the geometry and the selection range; the seven trailing words become 0x10001.
#include "shared/message_list.hpp"

MessageListClass::MessageListClass()
{
    First = 0;
    X = 0;
    Y = 0;
    MaxMessages = 0;
    MaxChars = 0;
    Height = 0;
    unknown_18 = false;
    unknown_19 = false;
    unknown_1a = false;
    unknown_1c = 0;
    unknown_20 = 0;
    unknown_24 = 0;
    unknown_2b0 = 0;
    unknown_2b4 = 0;
    unknown_2b8 = 0;
    Selection_First = 0;
    Selection_Last = 0;
    TextWidth = 0;
    unknown_28 = 0;
    unknown_16c = 0;
    for (int i = 0; i < 7; i++) {
        unknown_1480[i] = 0x10001;
    }
}
