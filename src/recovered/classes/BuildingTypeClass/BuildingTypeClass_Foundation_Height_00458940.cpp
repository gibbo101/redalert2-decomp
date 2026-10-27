// int BuildingTypeClass::Foundation_Height(bool bib) const (0x00458940)
// Foundation height in cells, one more with a bib when asked.
#include "shared/building_type.hpp"
// @ref ?unknown_foundation_height_7cfcc8@@3QBHB=007cfcc8

int BuildingTypeClass::Foundation_Height(bool bib) const
{
    return unknown_foundation_height_7cfcc8[Foundation] + ((bib && Bib) ? 1 : 0);
}
