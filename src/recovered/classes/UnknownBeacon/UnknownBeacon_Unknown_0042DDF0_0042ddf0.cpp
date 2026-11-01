// UnknownBeacon::Unknown_0042DDF0 (0x0042DDF0): clears the text and copies at most 127 characters of the
// new one (none: stays empty). Out of line here; 0x0042EC20 expands it.
#include "shared/beacon.hpp"
#include "shared/gadget.hpp"

void UnknownBeacon::Unknown_0042DDF0(unsigned short const *text)
{
    for (int index = 0; index < 128; index++) {
        unknown_text.chars[index] = 0;
    }
    if (text) {
        wcsncpy(unknown_text.chars, text, 127);
    }
}
