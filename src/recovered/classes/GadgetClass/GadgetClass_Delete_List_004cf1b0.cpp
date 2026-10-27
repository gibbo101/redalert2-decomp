// void GadgetClass::Delete_List() (0x004CF1B0, slot 12)
// Deletes every gadget of the list, head first.
#include "shared/gadget.hpp"

void GadgetClass::Delete_List()
{
    GadgetClass *gadget = this;
    while (gadget->Get_Prev() != 0) {
        gadget = (GadgetClass *)gadget->Get_Prev();
    }
    while (gadget != 0) {
        gadget->Clear_Focus();
        GadgetClass *temp = gadget;
        gadget = (GadgetClass *)gadget->Get_Next();
        delete temp;
    }
}
