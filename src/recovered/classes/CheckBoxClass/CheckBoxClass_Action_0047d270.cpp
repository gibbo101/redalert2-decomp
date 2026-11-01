// int CheckBoxClass::Action(unsigned flags, unsigned &key) (0x0047D270; TibSun
// checkbox.cpp): a left release (flag 4) flips the state, then ToggleClass::Action.
#include "shared/gadget.hpp"

int CheckBoxClass::Action(unsigned flags, unsigned &key)
{
    if (flags & 4) {
        if (IsOn) {
            Turn_Off();
        } else {
            Turn_On();
        }
    }
    return ToggleClass::Action(flags, key);
}
