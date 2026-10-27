// void DropListClass::Set_Selected_Index(int index) (0x004A4FE0, slot 43)
// Selects a list item and copies it into the field (empty when invalid).
#include "shared/gadget.hpp"
// @ref _wcscpy=00783689

void DropListClass::Set_Selected_Index(int index)
{
    if ((unsigned)index < (unsigned)List.Count()) {
        List.Set_Selected_Index(index);
        wcscpy(String, List.Get_Item(Current_Index()));
    } else {
        String[0] = 0;
    }
}
