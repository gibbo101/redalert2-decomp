// CoordStruct MapClass::Unknown_00569FB0(CoordStruct const &from, CoordStruct const &to, HouseClass *house) (0x00569FB0)
// The first hostile firestorm wall on a path (TibSun Firestorm_On_Path): along a column, a
// row or (otherwise) the cell edges a straight line crosses, the first cell whose building is a
// firestorm wall (+0x135A of its type) of a house with its firestorm up (+0x142) other than
// house; the cell's centre (the crossing point on a slanted line), else the zero coordinate.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/house_screen.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0

CoordStruct MapClass::Unknown_00569FB0(CoordStruct const &from, CoordStruct const &to, HouseClass *house)
{
    if (from != to) {

        if ((short)(from.X / 256) == (short)(to.X / 256)) {
            Cell current_cell(from);
            Cell target_cell(to);
            int step = current_cell.Y < target_cell.Y ? 1 : -1;

            while (current_cell != target_cell) {
                BuildingClass *building = (BuildingClass *)Map[current_cell].unknown_4717b0();
                if (building != 0 && building->Type->FirestormWall) {
                    HouseClass *owner = building->House;
                    if (owner->FirestormActive && owner != house) {
                        return Cell_Coord(current_cell);
                    }
                }

                current_cell.Y += step;
            }

        } else if ((short)(from.Y / 256) == (short)(to.Y / 256)) {
            Cell current_cell(from);
            Cell target_cell(to);
            int step = current_cell.X < target_cell.X ? 1 : -1;

            while (current_cell != target_cell) {
                BuildingClass *building = (BuildingClass *)Map[current_cell].unknown_4717b0();
                if (building != 0 && building->Type->FirestormWall) {
                    HouseClass *owner = building->House;
                    if (owner->FirestormActive && owner != house) {
                        return Cell_Coord(current_cell);
                    }
                }

                current_cell.X += step;
            }

        } else {
            int x_step = from.X < to.X ? 256 : -256;
            int y_step = from.Y < to.Y ? 256 : -256;
            int current_x = x_step < 0 ? from.X - from.X % 256 : from.X - from.X % 256 + 256;
            int current_y = y_step < 0 ? from.Y - from.Y % 256 : from.Y - from.Y % 256 + 256;
            int delta_x = to.X - from.X;
            double x_progress = (double)(current_x - from.X) / (double)delta_x;
            int delta_y = to.Y - from.Y;
            double y_progress = (double)(current_y - from.Y) / (double)delta_y;
            double inv_delta_x = 1.0 / (double)delta_x;
            double inv_delta_y = 1.0 / (double)delta_y;

            while ((x_progress <= 1.0 || y_progress <= 1.0) && x_progress >= 0.0 && y_progress >= 0.0) {
                BuildingClass *building = (BuildingClass *)Map[CoordStruct(current_x, current_y, 0)].unknown_4717b0();
                if (building != 0 && building->Type->FirestormWall) {
                    HouseClass *owner = building->House;
                    if (owner->FirestormActive && owner != house) {
                        return CoordStruct(current_x, current_y, 0);
                    }
                }

                if (x_progress < y_progress) {
                    current_x += x_step;
                    x_progress = (double)(current_x - from.X) * inv_delta_x;
                } else {
                    current_y += y_step;
                    y_progress = (double)(current_y - from.Y) * inv_delta_y;
                }
            }
        }
    }

    return unknown_geometry_l;
}
