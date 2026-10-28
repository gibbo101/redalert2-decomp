// void MessageListClass::Reset() -- 0x005B4C40
// Init with everything cleared and the default width of 640.
#include "shared/message_list.hpp"

void MessageListClass::Reset()
{
    Init(0, 0, 0, 0, 0, 0, 0, false, 0, 0, 0x280);
}
