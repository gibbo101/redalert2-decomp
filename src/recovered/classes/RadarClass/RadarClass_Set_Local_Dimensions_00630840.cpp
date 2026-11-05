#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
void RadarClass::unknown_slot29(Rect const &size)
{
    MapClass::unknown_slot29(size);
    unknown_1498.Y = 10000;
    unknown_1498.X = 10000;
    unknown_1498.Height = 0;
    unknown_1498.Width = 0;
    Cell corner(MapLocalSize.Y + MapLocalSize.X + 1,
        MapLocalSize.Y + MapSize.Width - MapLocalSize.X);
    Cell original_corner(corner);
    int x = MapLocalSize.Width - 1;
    int y = 1 - MapLocalSize.Width;
    Cell opposite = corner + Cell(x, y);
    unknown_148c = original_corner.Y - corner.X;
    unknown_1490 = opposite.X - opposite.Y;
    unknown_1494 = -1;
    Map.Unknown_0055A550();
    CellClass *iter = Unknown_0055A490();
    while (iter != 0) {
        Cell cell = iter->MapCoords;
        if (Unknown_0055A660(cell, true)) {
            if (unknown_1494 == -1) unknown_1494 = iter->MapCoords.X + iter->MapCoords.Y;
            cell = iter->MapCoords;
            Rect area = Unknown_00631400(cell);
            if (area.X < unknown_1498.X) unknown_1498.X = area.X;
            else if (area.X + area.Width > unknown_1498.X + unknown_1498.Width) unknown_1498.Width = area.X + area.Width - unknown_1498.X;
            if (area.Y < unknown_1498.Y) unknown_1498.Y = area.Y;
            else if (area.Y + area.Height > unknown_1498.Y + unknown_1498.Height) unknown_1498.Height = area.Y + area.Height - unknown_1498.Y;
        }
        iter = Unknown_0055A490();
    }
}
