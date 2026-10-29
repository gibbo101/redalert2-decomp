#include "shared/crt_memory.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

UnknownControlRecord &UnknownControlRecord::operator=(UnknownControlRecord const &other)
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
    wchar_t *source = other.text_28;
    if (text_28) {
        operator delete(text_28);
        text_28 = 0;
    }
    if (source && *source) {
        text_28 = (wchar_t *)operator new(wcslen(source) * 2 + 2);
        wcscpy(text_28, source);
    }
    Copy_List_600460(other.list_34);
    return *this;
}

}
