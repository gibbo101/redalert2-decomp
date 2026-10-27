#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
// @ref ?OverlayTypes@@=00a35de8
// @ref ?Houses@@=00a32298
// @ref ?Rules@@=00839848
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

bool __fastcall Cell_Wall_Transition_004bbe60(CellClass const *origin,
    CellClass const *nearby, CellClass const *destination, HouseClass const *house)
{
    bool wall = nearby->OverlayIndex != -1 &&
        OverlayTypes[nearby->OverlayIndex]->Wall;
    if (nearby != destination && wall && origin->unknown_11b <= destination->unknown_11b) {
        if (Rules->unknown_1498) {
            HouseClass *owner=Houses[nearby->unknown_50];
            if (owner && owner->Is_Ally(house)) return false;
        }
        return true;
    }
    return false;
}
