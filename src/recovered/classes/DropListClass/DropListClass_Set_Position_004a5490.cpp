// void DropListClass::Set_Position(int x, int y) (0x004A5490, slot 25)
// The list goes under the button's height, the button to the field's right.
#include "shared/gadget.hpp"
// @ref ?Set_Position@GadgetClass@@UAEXHH@Z=004cf660

void DropListClass::Set_Position(int x, int y)
{
    GadgetClass::Set_Position(x, y);
    List.Set_Position(x, ((short const *)DropButton.Shape)[2] + y);
    DropButton.Set_Position(Width + x, y);
}
