// Release the footprint, reapply neighbouring reservations, then rebuild perimeter cells (004513B0).
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/house.hpp"
#include "shared/base.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_47bfa0@CellClass@@=0047bfa0
// @ref ?Reserve_Base_Area_004510d0@BuildingClass@@=004510d0
void BuildingClass::unknown_4513b0()
{
    int spacing = Rules->AIBaseSpacing;
    int width = Type->Width() + spacing * 2;
    int height = Type->Foundation_Height(false) + spacing * 2;
    unsigned owner = 1U << House->ArrayIndex;
    CoordStruct position(Coord);
    Cell top_left = Cell(position) - Cell(spacing, spacing);
    int x, y;
    for (x = top_left.X; x < top_left.X + width; ++x) {
        for (y = top_left.Y; y < top_left.Y + height; ++y) Map[Cell(x, y)].unknown_dc &= ~owner;
    }
    for (x = top_left.X - spacing; x < top_left.X + width + spacing * 2; ++x) {
        for (y = top_left.Y - spacing; y < top_left.Y + height + spacing * 2; ++y) {
            BuildingClass *building = (BuildingClass *)Map[Cell(x, y)].unknown_4717b0();
            if (building && building != this) building->Reserve_Base_Area_004510d0(true);
        }
    }
    for (x = top_left.X - 1; x < top_left.X + width + 2; ++x) {
        for (y = top_left.Y - 1; y < top_left.Y + height + 2; ++y) {
            Cell cell = Cell(x, y);
            int mask = Map[cell].unknown_47bfa0(House->ArrayIndex);
            if (mask == 255) House->unknown_55f0.unknown_20.Delete(cell);
            else if (mask > 0) {
                if (House->unknown_55f0.unknown_20.ID(cell) == -1) House->unknown_55f0.unknown_20.Add(cell);
            } else {
                House->unknown_55f0.unknown_20.Delete(cell);
                Map[cell].unknown_dc &= ~owner;
            }
        }
    }
}
