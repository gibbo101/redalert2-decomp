// void __fastcall Clear_Listbox(ListClass *list) (0x005BBAD0)
// TibSun netdlg.cpp shape: deletes every text item, then flags the list for redraw.
#include "shared/netdlg.hpp"
#include "shared/gadget.hpp"

void __fastcall Clear_Listbox(ListClass *list)
{
    wchar_t *item;

    while (list->Count()) {
        item = list->Get_Item(0);
        list->Remove_Item(item);
        delete[] item;
    }
    list->Flag_To_Redraw();
}
