// VoxClass::VoxClass(char const *name) (0x007160E0): a speech of a name at
// full volume, priority 1, type 0 and idle, added to the unit's VoxClass list.
#include "shared/vox_speech.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930

VoxClass::VoxClass(char const *name)
{
    Volume = 1.0f;
    strcpy(Name, name);
    Russian[0] = '\0';
    Allied[0] = '\0';
    Priority = 1;
    Type = 0;
    State = 2;
    unknown_VoxClass_list_00ad0930.Add(this);
}
