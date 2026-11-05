// Copies the owner-draw record list; full original162code+14NOP independently verified.
#define RA2_OWNERDRAW_COPY_LIST_SOURCE
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {
inline void UnknownControlRecord::Copy_List_600460(UnknownNode_006003d0 const *source)
{
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
    for (; source; source = source->Next) {
        UnknownNode_006003d0 *node = (UnknownNode_006003d0 *)operator new(wcslen(source->Data) * 2 + 0x12);
        if (node) {
            node->Data = node->Text;
            node->Next = list_34;
            node->unknown_04 = 0;
            list_34 = node;
        }
        node->unknown_0c = source->unknown_0c;
        node->unknown_04 = source->unknown_04;
        wcscpy(node->Data, source->Data);
    }
}
}
