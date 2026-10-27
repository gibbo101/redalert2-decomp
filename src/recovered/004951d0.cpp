#include "shared/cstream.hpp"
// @ref ??8UnknownStreamPtr@@=004951d0
// Original operation returns 0/1 in EAX; callers test AL. Exact original
// C++ return spelling is unproved; unsigned char records the byte predicate.
unsigned char UnknownStreamPtr::operator==(int null_value) const
{
    if(null_value!=0) _com_issue_error(E_POINTER);
    return Pointer==0;
}
