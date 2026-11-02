// bool MessageListClass::Has_Edit_Focus() (0x005B53F0)
// Whether the open edit line has the focus (Westwood's Has_Edit_Focus).
#include "shared/message_list.hpp"
#include "shared/text_label.hpp"

bool MessageListClass::Has_Edit_Focus()
{
    if (IsEdit) {
        return EditLabel->Has_Focus();
    } else {
        return false;
    }
}
