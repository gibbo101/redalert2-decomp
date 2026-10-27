// INIClass::~INIClass (0x0050B8D0)
// Releases every section, entry and comment line, then the section index and
// section list (member destructors).
#include "shared/ini_class.hpp"

INIClass::~INIClass()
{
    Clear();
}
