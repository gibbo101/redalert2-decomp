// void __fastcall Wide_Area_Damage(CoordStruct const &coord, int radius, int rawdamage, TechnoClass *source, WarheadTypeClass *warhead) -- 0x0047F6E0
// TibSun combat.cpp Wide_Area_Damage without the terrain deformation; the cells keep the centre's height.
// The distance from the centre is TibSun's Distance(Coord(x + r, y + r), Coord(r, r)) on 3D coordinates
// (Coord_Distance): its 12-byte difference temporary gives the original's frame layout.
#include "shared/map_view.hpp"
#include "shared/anim.hpp"
#include "shared/infantry.hpp"
#include "shared/combat.hpp"
#include "shared/coord_distance.hpp"

void __fastcall Wide_Area_Damage(CoordStruct const &coord, int radius, int rawdamage, TechnoClass *source, WarheadTypeClass *warhead)
{
    if (warhead == 0) {
        return;
    }

    int cell_radius = (radius + 255) / 256;
    Cell cell = Cell(coord);

    for (int x = -cell_radius; x <= cell_radius; x++) {
        for (int y = -cell_radius; y <= cell_radius; y++) {
            int xpos = cell.X + x;
            int ypos = cell.Y + y;

            if ((unsigned)xpos > 512) {
                continue;
            }
            if ((unsigned)ypos > 512) {
                continue;
            }
            Cell tcell = Cell(xpos, ypos);
            if (!Map.Unknown_0054AAB0(tcell)) {
                continue;
            }

            int dist_from_center = Coord_Distance(CoordStruct(x + cell_radius, y + cell_radius, 0), CoordStruct(cell_radius, cell_radius, 0));
            double damagemod = 1;
            if (dist_from_center > 0) {
                damagemod = 1.0 / ((double)cell_radius / dist_from_center);
            }
            CoordStruct tcoord(tcell.X * 256 + 128, tcell.Y * 256 + 128, coord.Z);
            Unknown_0047E2C0(tcoord, (int)(rawdamage * damagemod), source, warhead, true);
        }
    }
}
