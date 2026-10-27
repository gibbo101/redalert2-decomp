// ListClass::ListClass(ListClass const &list) (0x00539D40)
// A copy whose arrows and scroll bar report to the new list.
#include "shared/gadget.hpp"
// @ref ??0ControlClass@@QAE@ABV0@@Z=00483480
// @ref ??4?$VectorClass@PAG@@QAEAAV0@ABV0@@Z=004a57e0
// @ref ??0SliderClass@@QAE@ABV0@@Z=0053ab60

ListClass::ListClass(ListClass const &list) :
    ControlClass(list),
    TextFlags(list.TextFlags),
    Tabs(list.Tabs),
    List(list.List),
    LineHeight(list.LineHeight),
    LineCount(list.LineCount),
    IsScrollActive(list.IsScrollActive),
    UpGadget(list.UpGadget),
    DownGadget(list.DownGadget),
    ScrollGadget(list.ScrollGadget),
    SelectedIndex(list.SelectedIndex),
    CurrentTopIndex(list.CurrentTopIndex)
{
    UpGadget.Make_Peer(*this);
    DownGadget.Make_Peer(*this);
    ScrollGadget.Make_Peer(*this);
}
