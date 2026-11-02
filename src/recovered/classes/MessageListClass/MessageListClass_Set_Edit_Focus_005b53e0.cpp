// void MessageListClass::Set_Edit_Focus() -- 0x005B53E0
// Gives the open edit line the focus (inlined everywhere in the unit).
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"

void MessageListClass::Set_Edit_Focus()
{
    if (IsEdit) {
        EditLabel->Set_Focus();
    }
}
