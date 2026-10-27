// CDControlClass::CDControlClass() (0x0046EA70)
// Clears the whole object.
#include "shared/cd_control.hpp"

CDControlClass::CDControlClass()
{
    memset(this, 0, sizeof(*this));
}
