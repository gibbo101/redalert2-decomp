// Experience is the double at offset0 in the existing eight-byte shared type.
// Original class identity (reference VeterancyClass) is a hypothesis; no field/API retype.
#include "shared/techno_pair.hpp"

bool UnknownTechnoPair::unknown_7133a0() const
{
    return *reinterpret_cast<double const *>(this)>=1.0 && *reinterpret_cast<double const *>(this)<2.0;
}
