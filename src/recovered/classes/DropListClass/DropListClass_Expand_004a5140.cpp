// void DropListClass::Expand() (0x004A5140)
// Drops the list under the field and links it in.
#include "shared/gadget.hpp"

void DropListClass::Expand()
{
    if (!IsDropped) {
        List.X = X;
        List.Y = Y + 18;
        List.Width = Width;
        List.Height = ListHeight;
        List.Add(Head_Of_List());
        List.Flag_To_Redraw();
        IsDropped = true;
    }
}
