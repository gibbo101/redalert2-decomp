#include "shared/fly_control_ptr.hpp"
bool UnknownComPtr<IFlyControl,&unknown_uuid_7d80a8>::operator==(int null_value) const
{
    if (null_value!=0) _com_issue_error((long)0x80004003);
    return Pointer==0;
}
