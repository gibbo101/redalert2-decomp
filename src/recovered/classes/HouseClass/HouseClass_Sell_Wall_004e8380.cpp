// void HouseClass::Sell_Wall(Cell const &cell, bool quiet) (0x004E8380)
// RA's Sell_Wall: a wall overlay whose owner (+0x50) a human controls is
// sold through the building type that makes it (ToOverlay, not Unsellable):
// the sell sound for the player unless quiet, the type's slot 33 for this
// house, then the overlay and its owner are cleared and the cell, radar and
// map are refreshed.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/overlay_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_475960@CellClass@@QAEX_N@Z=00475960

void HouseClass::Sell_Wall(Cell const &cell, bool quiet)
{
    if (cell != unknown_cell_a40f10) {
        CellClass &cellptr = Map[cell];
        int overlay = cellptr.OverlayIndex;
        if (overlay != -1) {
            int owner = cellptr.unknown_50;
            if (owner != -1 && Houses[owner]->Is_Human_Control()) {
                OverlayTypeClass *otype = OverlayTypes[overlay];
                if (otype->Wall) {
                    BuildingTypeClass *btype = 0;
                    for (int index = 0; index < BuildingTypes.Count(); index++) {
                        if (BuildingTypes[index]->ToOverlay == otype) {
                            btype = BuildingTypes[index];
                            break;
                        }
                    }
                    if (btype != 0 && !btype->Unsellable) {
                        if (unknown_player_a35db4 == this && !quiet) {
                            Voc_Play(Rules->unknown_5c4, 1.0f, 0x2000, 0);
                        }
                        btype->unknown_slot33((int)this);
                        Map[cell].OverlayIndex = -1;
                        Map[cell].OverlayData = 0;
                        Map[cell].unknown_50 = -1;
                        Map[cell].Unknown_00472540(-1);
                        Map[cell].unknown_475960(false);
                        Map.Unknown_00631570(cell);
                        Unknown_006D7C80(&Map[cell]);
                        Map.Unknown_0054FB20(cell);
                        Map.Unknown_00566340(cell);
                    }
                }
            }
        }
    }
}
