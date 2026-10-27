// @ref ??4GadgetClass@@QAEAAV0@ABV0@@Z=004a5730
// @ref ??4ShapeButtonClass@@QAEAAV0@ABV0@@Z=004a55e0
// @ref ??4SliderClass@@QAEAAV0@ABV0@@Z=004a5690
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/gadget.hpp"
// @ref ??4?$VectorClass@PAG@@QAEAAV0@ABV0@@Z=004a57e0
DropListClass &DropListClass::operator=(DropListClass &list)
{
 if(this==&list) return *this;
  EditClass::operator=(list);
  List=list.List;
  IsDropped=list.IsDropped;
  ListHeight=list.ListHeight;
  DropButton=list.DropButton;
  List.Make_Peer(*this);
  DropButton.Make_Peer(*this);
 return *this;
}

