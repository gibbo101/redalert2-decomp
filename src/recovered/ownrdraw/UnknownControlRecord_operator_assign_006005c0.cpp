#include "shared/crt_memory.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

inline UnknownControlRecord &UnknownControlRecord::operator=(UnknownControlRecord const &other)
{
    UnknownNode_006003d0 *list = list_34;
    wchar_t *text = text_28;
    WideString *kept_3c = unknown_3c;
    if (this == &other) {
        return *this;
    }
    memcpy(this, &other, sizeof(UnknownControlRecord));
    text_28 = text;
    unknown_3c = kept_3c;
    list_34 = list;
    Set_Wide_Text_600510(other.text_28);
    Copy_List_600460(other.list_34);
    return *this;
}

}
