// WDTState::~WDTState() (0x0072C2D0, slot 0 body)
// Clears the territory list, frees the three label strings and the owned string table (ConflictCount entries), then the list storage and the ReferenceCounted base.
// @ref ??_7?$VectorClass@V?$rc_ptr@VWDTTerritory@@@@@@6B@=007af2e8
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/wdt_state.hpp"
#include "shared/wdt_territory.hpp"

WDTState::~WDTState()
{
    Territories.Clear();
    if (LongLabel != 0) {
        delete LongLabel;
    }
    if (ShortLabel != 0) {
        delete ShortLabel;
    }
    if (unknown_10 != 0) {
        delete unknown_10;
    }
    if (unknown_44 != 0) {
        for (unsigned i = 0; (int)i < (int)ConflictCount; i++) {
            if (unknown_44[i] != 0) {
                delete (char *)unknown_44[i];
            }
        }
        delete unknown_44;
    }
}
