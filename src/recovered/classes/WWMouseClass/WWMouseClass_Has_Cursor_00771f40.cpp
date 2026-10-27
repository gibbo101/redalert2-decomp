// bool WWMouseClass::Has_Cursor() const (0x00771F40)
// A cursor shape is set. Never called (inlined into Validate_Backgrounds);
// name is a hypothesis. The conditional form gives setne without a cleared eax.
#include "shared/wwmouse.hpp"

bool WWMouseClass::Has_Cursor() const
{
    return MouseCursor != 0 ? true : false;
}
