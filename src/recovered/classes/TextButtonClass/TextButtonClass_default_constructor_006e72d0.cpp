// TextButtonClass::TextButtonClass() (0x006E72D0)
// An empty button with the default text style 2.
#include "shared/gadget.hpp"

TextButtonClass::TextButtonClass() :
    ToggleClass(0, 0, 0, 0, 0)
{
    IsBlackBorder = false;
    String = 0;
    PrintFlags = 2;
}
