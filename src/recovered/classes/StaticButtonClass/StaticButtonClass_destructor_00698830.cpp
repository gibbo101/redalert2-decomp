// StaticButtonClass::~StaticButtonClass() (0x00698830)
#include "shared/gadget.hpp"

StaticButtonClass::~StaticButtonClass()
{
    if (Text != 0) {
        delete Text;
    }
}
