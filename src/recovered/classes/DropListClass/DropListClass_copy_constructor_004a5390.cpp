#include "shared/gadget.hpp"
DropListClass::DropListClass(DropListClass const &list) :
    EditClass(list), IsDropped(list.IsDropped), ListHeight(list.ListHeight),
    DropButton(list.DropButton), List(list.List)
{
    List.Make_Peer(*this);
    DropButton.Make_Peer(*this);
}
