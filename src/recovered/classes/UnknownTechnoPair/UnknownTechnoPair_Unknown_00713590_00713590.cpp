// Experience is the double at offset0 in the existing eight-byte shared type.
// Original class identity (reference VeterancyClass) is a hypothesis; no field/API retype.
#include "shared/techno_pair.hpp"

void UnknownTechnoPair::Unknown_00713590(int value)
{
    *reinterpret_cast<double *>(this)=(double)value*0.01;
}
