#ifndef RA2_OWNERDRAW_CHECK_FIELDS
#define RA2_OWNERDRAW_CHECK_FIELDS
#endif
// Original257code+15NOP; record copy without a self-assignment test.
#include "shared/crt_memory.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

UnknownControlRecord &UnknownControlRecord::unknown_copy_6006e0(UnknownControlRecord const &other)
{
    UnknownNode_006003d0 *list = list_34;
    wchar_t *text = text_28;
    WideString *kept_3c = unknown_3c;
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
    {
        UnknownNode_006003d0 const *source_list=other.list_34;
    while (list_34) {
        UnknownNode_006003d0 *node = list_34;
        UnknownNode_006003d0 *previous = 0;
        UnknownNode_006003d0 *current;
        for (current = list_34; current; current = current->Next) {
            if (node == current) {
                break;
            }
            previous = current;
        }
        if (current) {
            if (previous) {
                previous->Next = current->Next;
            } else {
                list_34 = current->Next;
            }
            operator delete(current);
        }
    }
    for (; source_list; source_list = source_list->Next) {
        UnknownNode_006003d0 *node = (UnknownNode_006003d0 *)operator new(wcslen(source_list->Data) * 2 + 0x12);
        if (node) {
            node->Data = node->Text;
            node->Next = list_34;
            node->unknown_04 = 0;
            list_34 = node;
        }
        node->unknown_0c = source_list->unknown_0c;
        node->unknown_04 = source_list->unknown_04;
        wcscpy(node->Data, source_list->Data);
    }
    }
    return *this;
}

}
