// Cell const *BuildingTypeClass::unknown_45e270() const (0x0045E270)
// The outer-cell list for the foundation (foundation 9 shares the list of
// foundation 6); each list holds 30 cells.
#include "shared/building_type.hpp"
// @ref ?unknown_foundation_outside_84f848@@3QAY0BO@$$CBVCell@@A=0084f848

Cell const *BuildingTypeClass::unknown_45e270() const
{
    int foundation = Foundation;
    if (foundation == 9) {
        foundation = 6;
    }
    return unknown_foundation_outside_84f848[foundation];
}
