// AnimTypeClass::~AnimTypeClass() (0x00425170)
// Removes the type from the 0x00AC0CB0 list and AnimTypes.
#include "shared/anim_type.hpp"
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60

AnimTypeClass::~AnimTypeClass()
{
    unknown_objects_ac0cb0.Delete(this);
    AnimTypes.Delete(this);
}
