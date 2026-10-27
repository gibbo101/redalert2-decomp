// bool AbstractTypeClass::operator==(char const *ini_name) const (0x004107C0)
// Whether the ID matches ini_name, ignoring case.
#include "shared/abstract_type.hpp"

bool AbstractTypeClass::operator==(char const *ini_name) const
{
    return _stricmp(ini_name, ID) == 0;
}
