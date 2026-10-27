// void BuildingLightClass::Set_Behavior(int behavior) (0x00434370, name hypothesis)
// Clears the sweep angle; behavior 3 follows the nearest non-allied object of
// kind 15 or 1 in the 3x3 cells around the light.
// Uses the member CoordStruct::operator- of shared/coord.hpp (out-of-line copy 0x004348F0).
#include "shared/building_light.hpp"
#include "shared/house.hpp"
#include "shared/map_cell_view.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580

void BuildingLightClass::Set_Behavior(int behavior)
{
    Behavior = behavior;
    unknown_98 = 0;
    if (behavior == 3) {
        Cell cell = unknown_slot104();
        int best_distance = 9999999;
        ObjectClass *best = 0;
        HouseClass *house = Owner->House;
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                Cell neighbor = Cell(cell.X + x, cell.Y + y);
                for (ObjectClass *object = Map[neighbor].OccupierPtr; object != 0; object = object->unknown_30) {
                    if ((object->Kind_Of() == 0xf || object->Kind_Of() == 1) && !house->Is_Ally((TechnoClass *)object)) {
                        CoordStruct here = Coord;
                        CoordStruct diff = object->Center_Coord() - here;
                        int distance = (int)unknown_sqrt_4ba410((double)diff.X * diff.X + (double)diff.Z * diff.Z + (double)diff.Y * diff.Y);
                        if (distance < best_distance) {
                            best = object;
                            best_distance = distance;
                        }
                    }
                }
            }
        }
        if (best != 0) {
            Following = best;
        }
    }
}
