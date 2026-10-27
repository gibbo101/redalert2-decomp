// TechnoClass *RadioClass::Contact(int index) const (0x00636E10): the radio link.
#include "shared/radio.hpp"

TechnoClass *RadioClass::Contact(int index) const
{
    return RadioLinks[index];
}
