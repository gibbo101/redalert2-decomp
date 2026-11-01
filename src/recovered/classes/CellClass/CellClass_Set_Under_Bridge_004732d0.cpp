// void CellClass::Set_Under_Bridge(unsigned facing, bool state) (0x004732D0):
// marks the cells one high-bridge deck piece covers (TibSun Set_Under_Bridge).
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"

// @ref ?Destroy_Bridge@CellClass@@QAEXXZ=00473000
void CellClass::Set_Under_Bridge(unsigned facing, bool state)
{
    if (facing == 0) {
        OverlayData = 0;
    } else {
        OverlayData = 9;
    }

    IsBridgeDeck = state;
    IsUnderBridge = state;
    IsBridgeTraversable = state;
    IsBridgeSurface = state;
    IsOvershadowed = state;
    WasUnderBridge = !state;
    IsBridgeEastWest = (facing == 0) ? true : false;
    if (state) {
        OverlayData = (facing != 0) ? 9 : 0;
    } else {
        OverlayData = 0;
        Destroy_Bridge();
    }
    Map.Unknown_00631570(MapCoords);

    CellClass *across1 = &Adjacent_Cell(facing);
    across1->unknown_2c = state ? this : 0;
    across1->IsUnderBridge = state;
    across1->IsBridgeTraversable = state;
    across1->IsBridgeSurface = state;
    across1->IsOvershadowed = state;
    across1->WasUnderBridge = !state;
    across1->IsBridgeEastWest = (facing == 0) ? true : false;
    if (state) {
        across1->OverlayData = (facing != 0) ? 9 : 0;
    } else {
        across1->OverlayData = 0;
        across1->Destroy_Bridge();
    }
    Map.Unknown_00631570(across1->MapCoords);

    CellClass *across2 = &across1->Adjacent_Cell(facing);
    across2->unknown_2c = state ? this : 0;
    across2->IsUnderBridge = state;
    across2->IsBridgeTraversable = false;
    across2->IsBridgeSurface = state;
    across2->IsOvershadowed = state;
    across2->WasUnderBridge = !state;
    across2->IsBridgeEastWest = (facing == 0) ? true : false;
    if (state) {
        across2->OverlayData = (facing != 0) ? 9 : 0;
    } else {
        across2->OverlayData = 0;
        across2->Destroy_Bridge();
    }
    Map.Unknown_00631570(across2->MapCoords);

    CellClass *across3 = &across2->Adjacent_Cell(facing);
    across3->IsBridgeSurface = state;

    CellClass *back = (CellClass *)&((CellClass const *)this)->Adjacent_Cell((facing - 4) & 7);
    back->unknown_2c = state ? this : 0;
    back->IsUnderBridge = state;
    back->IsBridgeTraversable = state;
    back->WasUnderBridge = !state;
    back->IsBridgeSurface = false;
    back->IsOvershadowed = state;
    back->IsBridgeEastWest = (facing == 0) ? true : false;
    if (state) {
        back->OverlayData = (facing != 0) ? 9 : 0;
    } else {
        back->OverlayData = 0;
        back->Destroy_Bridge();
    }
    Map.Unknown_00631570(back->MapCoords);

    if (facing == 6) {
        CellClass *back2 = &back->Adjacent_Cell(2);
        back2->unknown_2c = state ? this : 0;
        back2->IsOvershadowed = state;
    }
}
