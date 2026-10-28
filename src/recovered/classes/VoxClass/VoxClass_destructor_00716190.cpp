// VoxClass::~VoxClass() (0x00716190): leaves the unit's VoxClass list.
#include "shared/vox_speech.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930

VoxClass::~VoxClass()
{
    unknown_VoxClass_list_00ad0930.Delete(this);
}
