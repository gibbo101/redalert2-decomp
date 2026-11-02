// Experience is the double at offset0 in the existing eight-byte shared type.
// Original class identity (reference VeterancyClass) is a hypothesis; no field/API retype.
#include "shared/techno_pair.hpp"

int UnknownTechnoPair::unknown_713440() const
{
    if (*reinterpret_cast<double const *>(this)>=2.0) return 0;
    return *reinterpret_cast<double const *>(this)>=1.0 ? 1 : 2;
}
