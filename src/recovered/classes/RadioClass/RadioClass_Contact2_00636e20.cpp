// TechnoClass *RadioClass::Contact2(int index) const (0x00636E20): the radio link.
#include "shared/radio.hpp"

TechnoClass *RadioClass::Contact2(int index) const
{
    return RadioLinks[index];
}
