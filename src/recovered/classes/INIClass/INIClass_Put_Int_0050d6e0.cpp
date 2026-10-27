// INIClass::Put_Int (0x0050D6E0)
// Stores an integer as text: format 1 writes hex with an 'h' suffix
// ("1Fh"), format 2 hex with a '$' prefix ("$1F"), anything else decimal.
#include "shared/ini_class.hpp"

bool INIClass::Put_Int(char const *section, char const *entry, int number, int format)
{
    char buffer[512];

    switch (format) {
        default:
        case 0:
            sprintf(buffer, "%d", number);
            break;

        case 1:
            sprintf(buffer, "%Xh", number);
            break;

        case 2:
            sprintf(buffer, "$%X", number);
            break;
    }
    return Put_String(section, entry, buffer);
}
