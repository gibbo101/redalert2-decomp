// VocClass::~VocClass() (0x00713880): leaves the unit's VocClass list.
#include "shared/voc_class.hpp"

VocClass::~VocClass()
{
    unknown_VocClass_list_00ad0818.Delete(this);
}
