#include "shared/ini_class.hpp"
template<> IndexClass<int, INIClass::INISection *>::IndexClass() :
    IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(false), Archive(0)
{
}
