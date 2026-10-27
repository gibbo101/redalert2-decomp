// int ListClass::Step_Selected_Index(int forward) (0x0053A970, slot 41)
// Moves the selection by forward; returns the old index.
#include "shared/gadget.hpp"

int ListClass::Step_Selected_Index(int forward)
{
    int old = SelectedIndex;
    Set_Selected_Index(old + forward);
    return old;
}
