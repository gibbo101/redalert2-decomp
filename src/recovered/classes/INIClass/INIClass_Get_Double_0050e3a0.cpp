// INIClass::Get_Double (0x0050E3A0)
// Reads an entry as a number (scanned as a float with "%f"); a value that
// contains '%' is a percentage and is scaled by 0.01. Returns defvalue when
// the section, entry or value is missing. The '%' test passes the
// multi-character constant '%%' (0x2525) to strchr, which only looks at its
// low byte.
#include "shared/ini_class.hpp"

double INIClass::Get_Double(char const *section, char const *entry, double defvalue) const
{
    if (section == 0 || entry == 0) {
        return defvalue;
    }

    INIEntry *entptr = Find_Entry(section, entry);
    if (entptr != 0 && entptr->Value != 0) {
        float value;
        sscanf(entptr->Value, "%f", &value);
        defvalue = value;
        if (strchr(entptr->Value, '%%') != 0) {
            defvalue = defvalue * 0.01;
        }
    }
    return defvalue;
}
