// Reserve the owning house's footprint and update the base perimeter cells (004510D0).
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/house.hpp"
#include "shared/base.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_47bfa0@CellClass@@=0047bfa0
void BuildingClass::Reserve_Base_Area_004510d0(bool skip_inner_cells)
{
    int spacing = Rules->AIBaseSpacing;
    int width = Type->Width() + spacing * 2;
    int height = Type->Foundation_Height(false) + spacing * 2;
    unsigned owner = 1U << House->ArrayIndex;
    CoordStruct position(Coord);
    Cell top_left = Cell(position) - Cell(spacing, spacing);
    for (int x = top_left.X; x < top_left.X + width; ++x) {
        for (int y = top_left.Y; y < top_left.Y + height; ++y) {
            Map[Cell(x, y)].unknown_dc |= owner;
        }
    }
    Rect &area = House->unknown_55f0.unknown_54;
    if (area.X == 0) area.X = top_left.X;
    if (area.Y == 0) area.Y = top_left.Y;
    if (top_left.X < area.X) {
        int old_x = area.X;
        area.X = top_left.X;
        area.Width += old_x - top_left.X;
    }
    if (top_left.X + width > area.Width + area.X) area.Width = top_left.X - area.X + width;
    if (top_left.Y < area.Y) {
        int old_y = area.Y;
        area.Y = top_left.Y;
        area.Height += old_y - top_left.Y;
    }
    if (top_left.Y + height > area.Height + area.Y) area.Height = top_left.Y - area.Y + height;
    if (!skip_inner_cells) {
        for (int cell_x = top_left.X - 1; cell_x < top_left.X + width + 2; ++cell_x) {
            for (int cell_y = top_left.Y - 1; cell_y < top_left.Y + height + 2; ++cell_y) {
                Cell cell = Cell(cell_x, cell_y);
                int mask = Map[cell].unknown_47bfa0(House->ArrayIndex);
                if (mask == 255) House->unknown_55f0.unknown_20.Delete(cell);
                else if (mask > 0) {
                    if (House->unknown_55f0.unknown_20.ID(cell) == -1) House->unknown_55f0.unknown_20.Add(cell);
                }
            }
        }
    }
}
